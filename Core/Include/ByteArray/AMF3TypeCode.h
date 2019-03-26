#pragma once
#ifndef AMF3TypeCode_h__
#define AMF3TypeCode_h__

namespace Core
{
	enum TimezoneCompensation
	{
		/// <summary>
		/// No timezone compensation.
		/// </summary>
		//[XmlEnum(Name = "none")]
		None = 0,
		/// <summary>
		/// Auto timezone compensation.
		/// </summary>
		//	[XmlEnum(Name = "auto")]
		Auto = 1,
		/// <summary>
		/// Convert to the server timezone.
		/// </summary>
		//	[XmlEnum(Name = "server")]
		Server = 2,
		/// <summary>
		/// Ignore UTCKind for DateTimes received from the client code.
		/// </summary>
		//	[XmlEnum(Name = "ignoreUTCKind")]
		IgnoreUTCKind = 3
	};

	enum AMF3TypeCode
	{
		/// <summary>
		/// AMF Undefined data type.
		/// </summary>
		ATC_Undefined = 0,
		/// <summary>
		/// AMF Null data type.
		/// </summary>
		ATC_Null = 1,
		/// <summary>
		/// AMF Boolean false data type.
		/// </summary>
		ATC_BooleanFalse = 2,
		/// <summary>
		/// AMF Boolean true data type.
		/// </summary>
		ATC_BooleanTrue = 3,
		/// <summary>
		/// AMF Integer data type.
		/// </summary>
		ATC_Integer = 4,
		/// <summary>
		/// AMF Number data type.
		/// </summary>
		ATC_Double = 5,
		/// <summary>
		/// AMF String data type.
		/// </summary>
		ATC_String = 6,
		/// <summary>
		/// AMF DateTime data type.
		/// </summary>
		ATC_DateTime = 8,
		/// <summary>
		/// AMF Array data type.
		/// </summary>
		ATC_Array = 9,
		/// <summary>
		/// AMF Object data type.
		/// </summary>
		ATC_Object = 10,
		/// <summary>
		/// AMF Xml data type.
		/// </summary>
		ATC_Xml = 11,
		/// <summary>
		/// AMF Xml data type.
		/// </summary>
		ATC_Xml2 = 7,
		/// <summary>
		/// AMF ByteArray data type.
		/// </summary>
		ATC_ByteArray = 12,
		/// <summary>
		/// AMF Integer Vector data type.
		/// </summary>
		ATC_IntVector = 13,
		/// <summary>
		/// AMF Uint Vector data type.
		/// </summary>
		ATC_UIntVector = 14,
		/// <summary>
		/// AMF Number Vector data type.
		/// </summary>
		ATC_NumberVector = 15,
		/// <summary>
		/// AMF Object Vector data type.
		/// </summary>
		ATC_ObjectVector = 16,
		/// <summary>
		/// AMF Dictionray data type.
		/// </summary>
		ATC_Dictionary = 17
	};
}

#endif // AMF3TypeCode_h__