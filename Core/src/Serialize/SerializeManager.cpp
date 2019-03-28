#include "Log\ILog.h"
#include "SerializeManager.h"
#include "Reflect\IReflectManager.h"

namespace Core
{

	SerializeManger::SerializeManger()
	{

	}


	SerializeManger::~SerializeManger()
	{

	}

	bool SerializeManger::Initialize()
	{
		return true;
	}


	ByteArray * SerializeManger::ToByteArray(ISerializable * pSerializable, ByteArray * bytes)
	{
		if (pSerializable == nullptr)
			return bytes;

		const char* pClassName = pSerializable->GetSerializeClassName();

		if (pClassName == nullptr)
			return bytes;

		SerializeClassMap::iterator itor = m_allClass.find(pClassName);

		if (itor == m_allClass.end() || itor->second == nullptr)
			return bytes;

		SerializeClass* pClassInfo = itor->second;

		if (bytes == nullptr)
			bytes = MW_New ByteArray;

		if (pClassInfo->GetName() == nullptr)
			pClassInfo->SetName(pClassName);

		// 写入类名
		std::string name = pClassName;
		bytes->writeUTF(name);

		int classVersion = pClassInfo->GetVersion();
		bytes->writeInt(classVersion);

		// 写入成员变量数据
		int count = pClassInfo->GetMemberCount();

		for (int i = 0; i < count; ++i)
		{
			SerializeMember* pMember = pClassInfo->GetMember(i);
			if (pMember == nullptr)
				continue;

			if (pMember->version > classVersion)
				continue;

			MemberToByteArray(pMember, pSerializable, bytes);
		}

		return bytes;
	}


	ISerializable * SerializeManger::FromByteArray(ByteArray * bytes)
	{
		if (bytes == nullptr)
			return nullptr;

		std::string className = "";
		bytes->readUTF(className);

		if (className == "")
			return nullptr;

		SerializeClassMap::iterator itor = m_allClass.find(className);

		if (itor == m_allClass.end() || itor->second == nullptr)
		{
			LogEBus::Broadcast(&ILog::Error, "[SerializeManger] Cannot Find SerializeClass. ClassName is %s ", className.c_str());
			return nullptr;
		}
		SerializeClass* pClassInfo = itor->second;

		int configVersion = bytes->readInt();

		IReflectFactory* pFactory = nullptr;
		ReflectionEBus::BroadcastResult(pFactory, &Core::IReflectManager::GetReflectFactory, className.c_str());

		if (pFactory == nullptr)
		{
			LogEBus::Broadcast(&ILog::Error, "[SerializeManger] Cannot Find Reflect Factory ClassName is %s ", className.c_str());
			return nullptr;
		}

		void* pClass = pFactory->CreateClass(className.c_str());
		ISerializable * pObject = (ISerializable *)pClass;

		if (pObject == nullptr)
		{
			LogEBus::Broadcast(&ILog::Error, "[SerializeManger] Cannot Create Class, ClassName is %s ", className.c_str());
			pFactory->DestoryClass(pClass);
			return nullptr;
		}

		if (configVersion > pClassInfo->GetVersion())
		{
			LogEBus::Broadcast(&ILog::Error, "[SerializeManger] configVersion is higher then Class Code, ClassName is %s ", className.c_str());
			pFactory->DestoryClass(pClass);
			return nullptr;
		}

		int count = pClassInfo->GetMemberCount();

		for (int i = 0; i < count; ++i)
		{
			SerializeMember* pMember = pClassInfo->GetMember(i);

			if (pMember == nullptr)
				continue;

			MemberFromByteArray(pMember, pObject, bytes, configVersion);
		}

		return pObject;
	}


	// 写入二进制成员变量
	void SerializeManger::MemberToByteArray(SerializeMember * pMember, ISerializable * pSerializable, ByteArray * bytes)
	{
		BYTE* pPointer = (BYTE*)pSerializable;
		switch (pMember->eMemberType)
		{
		case ESMT_BYTE:
		{
			BYTE* pBValue = (BYTE*)(pPointer + pMember->offset);
			bytes->writeByte(*pBValue);
		}break;
		case ESMT_UNBYTE:
		{
			BYTE* pUBValue = (BYTE*)(pPointer + pMember->offset);
			bytes->writeUnsingnedByte(*pUBValue);
		}break;
		case EAMT_BOOL:
		{
			bool* pBLValue = (bool*)(pPointer + pMember->offset);
			bytes->writeBoolean(*pBLValue);
		}break;
		case EAMT_INT:
		{
			int* pIValue = (int*)(pPointer + pMember->offset);
			bytes->writeInt(*pIValue);
		}break;
		case EAMT_UNINT:
		{
			unsigned int* pUIValue = (unsigned int*)(pPointer + pMember->offset);
			bytes->writeUnsignedInt(*pUIValue);
		}break;
		case EAMT_DOUBLE:
		{
			double* pDValue = (double*)(pPointer + pMember->offset);
			bytes->writeDouble(*pDValue);
		}break;
		case EAMT_FLOAT:
		{
			float* pFValue = (float*)(pPointer + pMember->offset);
			bytes->writeFloat(*pFValue);
		}break;
		case EAMT_SHORT:
		{
			short* pSValue = (short*)(pPointer + pMember->offset);
			bytes->writeShort(*pSValue);
		}break;
		case EAMT_UNSHORT:
		{
			unsigned short* pUSValue = (unsigned short*)(pPointer + pMember->offset);
			bytes->writeUnsignedShort(*pUSValue);
		}break;
		case EAMT_STRING:
		{
			std::string* pCValue = (std::string*)(pPointer + pMember->offset);
			bytes->writeUTF(*pCValue);
		}break;
		case EAMT_U29INT:
		{
			int* pU29Value = (int*)(pPointer + pMember->offset);
			bytes->writeU29Int(*pU29Value);
		}break;
		case EAMT_BYTEARRAY:
		{
			ISerializable * pSerValue = (ISerializable *)(pPointer + pMember->offset);
			ToByteArray(pSerValue, bytes);
		}break;
		default:
			LogEBus::Broadcast(&ILog::Error, "[SerializeManger] eMemberType is undefine, eMemberType is %d ", pMember->eMemberType);
			break;
		}
	}

	void SerializeManger::MemberFromByteArray(SerializeMember * pMember, ISerializable * pSerializable, ByteArray * bytes, int configVersion)
	{
		// 新版本类读老版本数据，新增属性不做序列化，做默认值出来
		if (pMember->version > configVersion)
			return;

		BYTE* pPointer = (BYTE*)pSerializable;
		switch (pMember->eMemberType)
		{
		case ESMT_BYTE:
		case ESMT_UNBYTE:
		{
			BYTE bValue = bytes->readUnsignedByte();
			BYTE* pMemValue = (BYTE*)(pPointer + pMember->offset);
			*pMemValue = bValue;
		}break;
		case EAMT_BOOL:
		{
			bool blValue = bytes->readBoolean();
			bool* pbMemValue = (bool*)(pPointer + pMember->offset);
			*pbMemValue = blValue;
		}break;
		case EAMT_INT:
		{
			int iValue = bytes->readInt();
			int* piMemValue = (int*)(pPointer + pMember->offset);
			*piMemValue = iValue;
		}break;
		case EAMT_UNINT:
		{
			unsigned int niValue = bytes->readUnsignedInt();
			unsigned int* pniMemValue = (unsigned int*)(pPointer + pMember->offset);
			*pniMemValue = niValue;
		}break;
		case EAMT_DOUBLE:
		{
			double dValue = bytes->readDouble();
			double* pdMemValue = (double*)(pPointer + pMember->offset);
			*pdMemValue = dValue;
		}break;
		case EAMT_FLOAT:
		{
			float fValue = bytes->readFloat();
			float* pfMemValue = (float*)(pPointer + pMember->offset);
			*pfMemValue = fValue;
		}break;
		case EAMT_SHORT:
		{
			short sValue = bytes->readShort();
			short* psMemValue = (short*)(pPointer + pMember->offset);
			*psMemValue = sValue;
		}break;
		case EAMT_UNSHORT:
		{
			unsigned short usValue = bytes->readUnsignedShort();
			unsigned short* pusMemValue = (unsigned short*)(pPointer + pMember->offset);
			*pusMemValue = usValue;
		}break;
		case EAMT_STRING:
		{
			std::string strValue = "";
			bytes->readUTF(strValue);
			std::string* pstrMemValue = (std::string*)(pPointer + pMember->offset);
			*pstrMemValue = strValue;
		}break;
		case EAMT_U29INT:
		{
			int u29Value = bytes->readU29Int();
			int* pu29MemValue = (int*)(pPointer + pMember->offset);
			*pu29MemValue = u29Value;
		}break;
		case EAMT_BYTEARRAY:
		{
			ISerializable * pSerValue = (ISerializable *)(pPointer + pMember->offset);

			ISerializable * pSubSerializable = FromByteArray(bytes);

			if (pSubSerializable != nullptr)
			{
				int subObjectSize = pSubSerializable->GetSerializeClassSize();
				memcpy((void*)pSerValue, (void*)pSubSerializable, subObjectSize);
				*pSerValue = *pSubSerializable;
			}
			else
			{
				LogEBus::Broadcast(&ILog::Error, "[SerializeManger] SubSerializable is nullptr ");
			}
		}break;
		default:
			LogEBus::Broadcast(&ILog::Error, "[SerializeManger] eMemberType is undefine, eMemberType is %d ", pMember->eMemberType);
			break;
		}
	}

}