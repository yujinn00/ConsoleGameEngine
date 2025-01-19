#pragma once

#include "Core.h"

// 클래스 간 동적 형 변환 및 런타임에 타입을 확인하기 위한 커스텀 RTTI
class ENGINE_API RTTI
{
public:
	// 객체의 타입 ID를 반환하는 순수 가상 함수
	virtual const size_t& TypeIdInstance() const = 0;

	// 주어진 타입 ID와 객체의 타입이 일치하는지 확인하는 가상 함수
	virtual bool Is(const size_t id) const
	{
		return false;
	}

	// 객체를 런타임에 특정 타입으로 변환하려고 시도하는 함수 (비 const)
	template<typename T>
	T* As()
	{
		if (Is(T::TypeIdClass()))
		{
			return (T*)this;
		}
		return nullptr;
	}

	// 객체를 런타임에 특정 타입으로 변환하려고 시도하는 함수 (const)
	template<typename T>
	const T* As() const
	{
		if (Is(T::TypeIdClass()))
		{
			return (T*)this;
		}
		return nullptr;
	}
};

// 특정 클래스에서 RTTI 기능을 쉽게 구현할 수 있도록 돕는 매크로
#define RTTI_DECLARATIONS(Type, ParentType)												\
public:																					\
	/* 부모 클래스를 Super라는 별칭으로 정의 */											\
	using Super = ParentType;															\
	/* 객체의 타입 ID를 반환하는 함수 */												\
	virtual const size_t& TypeIdInstance() const { return Type::TypeIdClass(); }		\
	/* 클래스의 정적 타입 ID를 생성하는 함수 */											\
	static const size_t TypeIdClass()													\
	{																					\
		static int runTimeTypeId = 0;													\
		return reinterpret_cast<size_t>(&runTimeTypeId);								\
	}																					\
	/* 현재 객체의 타입 ID와 전달받은 ID를 비교하여 일치 여부를 확인하는 함수 */		\
	virtual bool Is(const size_t id) const												\
	{																					\
		if (id == TypeIdClass())														\
		{																				\
			return true;																\
		}																				\
		else																			\
		{																				\
			return Super::Is(id);														\
		}																				\
	}
