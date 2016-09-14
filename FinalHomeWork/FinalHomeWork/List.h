#pragma once
#include <iostream>

template <typename T> class List;

/// <summary>
/// ���Խṹ�ڵ���
/// </summary>
template <typename T>
class Node
{
	friend class List<T>;
public:
	static int _total;
protected:
	Node<T>* _before;
	Node<T>* _next;
	T data;
	Node()
	{
		_total++;
	}
	~Node()
	{
		_total--;
	}
};


/// <summary>
/// ȫ����δ���ٵĽڵ����
/// </summary>
template <typename T>
int Node<T>::_total = 0;

/// <summary>
/// ����
/// </summary>
template <typename T>
class List
{
protected:
	Node<T>* head;
	Node<T>* tail;
	
	/// <summary>
	/// ��ȡ���ݽڵ�.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <returns></returns>
	Node<T>& GetNodeAt(size_t index)
	{
		Node<T>* that = this->head;
		for (int i = 0; i < Length; i++)
		{
			if (i == index)
			{
				return *that;
			}
			that = that->_next;
		}
		throw length_error("Segement fault");
	}
public:

	/// <summary>
	/// ��ȡԪ�ظ���
	/// </summary>
	int Length;

	/// <summary>
	/// Initializes a new instance of the <see cref="List"/> class.
	/// </summary>
	List()
	{
		cout << "Init a List!" << endl;
		head = tail = nullptr;
		Length = 0;
	}


	/// <summary>
	/// ��ĩβ���һ��Ԫ�ء�
	/// </summary>
	/// <param name="value">The value.</param>
	/// <returns></returns>
	List<T>& Add(T value)
	{
		Node<T>* next = new Node<T>();
		next->data = value;
		if (head == nullptr)
		{
			head = tail = next;
		}
		else
		{
			tail->_next = next;
			next->_before = tail;
			tail = next;
		}
		Length++;
		return *this;
	}

	/// <summary>
	/// �±����
	/// </summary>
	/// <param name="n">The n.</param>
	/// <returns></returns>
	T& operator[] (std::size_t n)
	{
		return this->GetNodeAt(n).data;
	}

	List<T>& RemoveAt(size_t index)
	{
	}




};