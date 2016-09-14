#pragma once
#include <iostream>
#include <functional>

template <typename T> class List;

/// <summary>
/// ���Խṹ�ڵ���
/// </summary>
template <typename T>
class ListNode
{
	friend class List<T>;
public:
	static int _total;
protected:
	ListNode<T>* _before;
	ListNode<T>* _next;
	T data;
	ListNode()
	{
		_before = _next = nullptr;
		_total++;
	}
	~ListNode()
	{
		_total--;
		cout << endl << "delete a node : " << ListNode<T>::_total;
	}
};


/// <summary>
/// ȫ����δ���ٵĽڵ����
/// </summary>
template <typename T>
int ListNode<T>::_total = 0;




/// <summary>
/// ����
/// </summary>
template <typename T>
class List
{
protected:
	ListNode<T>* head;
	ListNode<T>* tail;

	/// <summary>
	/// ��ȡ���ݽڵ�.
	/// </summary>
	/// <param name="index">The index.</param>
	/// <returns></returns>
	ListNode<T>& GetNodeAt(size_t index)
	{
		ListNode<T>* that = this->head;
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

	List<T>& RemoveNode(ListNode<T>& that)
	{
		ListNode<T>* before = that._before;
		ListNode<T>* after = that._next;
		if (before != nullptr)
		{
			before->_next = after;
		}
		if (after != nullptr)
		{
			after->_before = before;
		}
		delete &that;
		Length--;
		return *this;
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
		ListNode<T>* next = new ListNode<T>();
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
		ListNode<T>& that = this->GetNodeAt(index);
		RemoveNode(that);
		return *this;
	}

	List<T>& Remove(std::function<bool(T&)> predicate)
	{
		ListNode<T>* that = this->head;
		for (int i = 0; i < Length; i++)
		{
			if (predicate(that->data))
			{
				RemoveNode(*that);
			}
			that = that->_next;
		}
		return *this;
	}

	List<T>& ForEach(std::function<void(T)> action)
	{
		ListNode<T>* that = this->head;
		for (int i = 0; i < Length; i++)
		{
			action(that->data);
			that = that->_next;
		}
	}
};