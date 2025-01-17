#pragma once

#include <iostream>

// @�ۼ���: ������
// - ��� ������ �����߱� ������ ������ �ȴٸ� ���ľ� ��
#pragma warning(disable:4251)

template <typename T>
class List
{
public:
	List()
		: capacity(2)
	{
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}

	~List()
	{
		if (data != nullptr)
		{
			delete[] data;
		}
	}

	void PushBack(const T& value)
	{
		if (size == capacity)
		{
			ReAllocate(capacity * 2);
		}

		data[size] = value;
		size++;
	}

	void PushBack(T&& value)
	{
		if (size == capacity)
		{
			ReAllocate(capacity * 2);
		}

		data[size] = std::move(value);
		size++;
	}

	void Erase(int index)
	{
		// ���� ó��
		if (index < 0 || index >= size)
		{
			__debugbreak();
		}

		// ������ �������� �ε��� ���� ��ġ�� �� ĭ ������ ��� �̵�
		for (int i = index; i < size - 1; ++i)
		{
			data[i] = std::move(data[i + 1]);
		}

		// ���� �� ũ�� ���̱�
		--size;
	}

	int Size() const
	{
		return size;
	}

	int Capacity() const
	{
		return capacity;
	}

	const T& operator[](int index) const
	{
		if (index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	T& operator[](int index)
	{
		if (index >= size)
		{
			__debugbreak();
		}

		return data[index];
	}

	T* begin() const
	{
		return data;
	}

	T* end() const
	{
		return data + size;
	}

private:
	void ReAllocate(int newCapacity)
	{
		// 1. allocate a new block of memory.
		// 2. copy/move old elements into new block.
		// 3. delete.

		T* newBlock = new T[newCapacity];
		memset(newBlock, 0, sizeof(T) * newCapacity);

		if (newCapacity < size)
		{
			size = newCapacity;
		}

		if (data != nullptr)
		{
			memcpy(newBlock, data, sizeof(T) * capacity);
		}
		//for (int ix = 0; ix < size; ++ix)
		//{
		//	// newBlock[ix] = data[ix];
		//	newBlock[ix] = std::move(data[ix]);
		//}

		delete[] data;
		data = newBlock;
		capacity = newCapacity;
	}

private:
	T* data = nullptr;
	int size = 0;
	int capacity = 0;
};