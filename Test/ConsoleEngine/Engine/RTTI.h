#pragma once

#include "Core.h"

// Ŭ���� �� ���� �� ��ȯ �� ��Ÿ�ӿ� Ÿ���� Ȯ���ϱ� ���� Ŀ���� RTTI
class ENGINE_API RTTI
{
public:
	// ��ü�� Ÿ�� ID�� ��ȯ�ϴ� ���� ���� �Լ�
	virtual const size_t& TypeIdInstance() const = 0;

	// �־��� Ÿ�� ID�� ��ü�� Ÿ���� ��ġ�ϴ��� Ȯ���ϴ� ���� �Լ�
	virtual bool Is(const size_t id) const
	{
		return false;
	}

	// ��ü�� ��Ÿ�ӿ� Ư�� Ÿ������ ��ȯ�Ϸ��� �õ��ϴ� �Լ� (�� const)
	template<typename T>
	T* As()
	{
		if (Is(T::TypeIdClass()))
		{
			return (T*)this;
		}
		return nullptr;
	}

	// ��ü�� ��Ÿ�ӿ� Ư�� Ÿ������ ��ȯ�Ϸ��� �õ��ϴ� �Լ� (const)
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

// Ư�� Ŭ�������� RTTI ����� ���� ������ �� �ֵ��� ���� ��ũ��
#define RTTI_DECLARATIONS(Type, ParentType)												\
public:																					\
	/* �θ� Ŭ������ Super��� ��Ī���� ���� */											\
	using Super = ParentType;															\
	/* ��ü�� Ÿ�� ID�� ��ȯ�ϴ� �Լ� */												\
	virtual const size_t& TypeIdInstance() const { return Type::TypeIdClass(); }		\
	/* Ŭ������ ���� Ÿ�� ID�� �����ϴ� �Լ� */											\
	static const size_t TypeIdClass()													\
	{																					\
		static int runTimeTypeId = 0;													\
		return reinterpret_cast<size_t>(&runTimeTypeId);								\
	}																					\
	/* ���� ��ü�� Ÿ�� ID�� ���޹��� ID�� ���Ͽ� ��ġ ���θ� Ȯ���ϴ� �Լ� */		\
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
