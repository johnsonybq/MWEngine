#pragma once



#define		SINGLE_INSTANCE( CLASSNAME )		\
private:										\
	CLASSNAME();								\
public:											\
	static CLASSNAME* GetInstance()				\
	{											\
		static CLASSNAME	_##CLASSNAME_;		\
		return &_##CLASSNAME_;					\
	}