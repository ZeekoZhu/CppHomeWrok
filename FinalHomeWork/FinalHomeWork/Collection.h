#pragma once
#include <iostream>
#include <functional>

#ifndef MYLIST_H
#define MYLIST_H
template <typename T> class List;
template <typename T> class Stack;

/// <summary>
/// ���Խṹ�ڵ���
/// </summary>
template <typename T>
class Node
{
	friend class List<T>;
	friend class Stack<T>;
public:
	static int _total;
protected:
	Node<T>* _before;
	Node<T>* _next;
	T data;
	Node()
	{
		_before = _next = nullptr;
		_total++;
	}
	~Node()
	{
		_total--;
		cout << endl << "delete a node : " << Node<T>::_total;
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

	List<T>& RemoveNode(Node<T>& that)
	{
		Node<T>* before = that._before;
		Node<T>* after = that._next;
		if (before != nullptr)
		{
			before->_next = after;
		}
		else
		{
			this->head = after;
		}

		if (after != nullptr)
		{
			after->_before = before;
		}
		else
		{
			this->tail = before;
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
		Total++;
		cout << "Init a List!" << endl;
		head = tail = nullptr;
		Length = 0;
	}

	~List()
	{
		Total--;
		cout << "list count : " << Total;
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

   /* const T& operator[] (std::size_t n)
    {
        return this->GetNodeAt(n).data;
    }*/

	List<T>& RemoveAt(size_t index)
	{
		Node<T>& that = this->GetNodeAt(index);
		RemoveNode(that);
		return *this;
	}

	List<T>& Remove(std::function<bool(T&)> predicate)
	{
		Node<T>* that = this->head;
		Node<T>* next = nullptr;
		while (that->_next != nullptr)
		{
			next = that->_next;
			if (predicate(that->data))
			{
				RemoveNode(*that);
			}
			that = next;
		}
		return *this;
	}

	List<T>& Clear()
	{
		Node<T>* that = this->head;
		Node<T>* next = nullptr;
		while (that != nullptr)
		{
			next = that->_next;
			RemoveNode(*that);
			that = next;
		}
		return *this;
	}

	List<T>& InsertAt(T value, int index)
	{
		if (index < 0 || index > Length)
		{
			throw length_error("Segement fault!");
		}
		else if (index == Length)
		{
			this->Add(value);
		}
		else
		{
			Node<T>* target = new Node<T>();
			target->data = value;
			Node<T>& that = this->GetNodeAt(index);
			target->_before = that._before;
			that._before = target;
			target->_next = &that;
			this->Length++;
		}
		return *this;
	}

	/// <summary>
	/// �Լ���������Ԫ��ִ�в���
	/// </summary>
	/// <param name="action">The action.</param>
	/// <returns></returns>
	List<T>& ForEach(std::function<void(T&)> action)
	{
		Node<T>* that = this->head;
		while (that != nullptr)
		{
			action(that->data);
			that = that->_next;
		}
		return *this;
	}


	/// <summary>
	/// �μ� https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/map
	/// </summary>
	/// <param name="action">The action.</param>
	/// <returns></returns>
	template <typename TRes>
	List<T>* Map(std::function<TRes(T&)> action)
	{
		List<TRes>* result = new List<TRes>();
		Node<T>* that = this->head;
		while (that != nullptr)
		{
			TRes temp = action(that->data);
			result->Add(temp);
			that = that->_next;
		}

		return result;
	}

	List<T>* Where(std::function<bool(T&)> predicate)
	{
		List<T>* result = new List<T>();
		Node<T>* that = this->head;
		while (that != nullptr)
		{
			if (predicate(that->data))
			{
				result->Add(that->data);
			}
			that = that->_next;
		}
		return result;
	}

	double Sum(std::function<double(T&)> propertySelector)
	{
		double result = 0.0;
		this->ForEach([&result,&propertySelector](T& item)->void
		{
			result += propertySelector(item);
		});
		return result;
	}

	static int Total;
};

template <typename T> int List<T>::Total = 0;



template<typename T> class Stack
{
private:
	Node<T>* _top;
public:
	int Length;
	Stack()
	{
		Length = 0;
		_top = nullptr;
	}
	Stack<T>& Push(T data)
	{
		Node<T>* value = new Node<T>();
		value->data = data;
		value->_before = this->_top;
		Length++;
		_top = value;
		return *this;
	}
	T Pop()
	{
		T result;
		if (_top != nullptr)
		{
			result = _top->data;
			_top = _top->_before;
			Length--;
		}
		else
		{
			throw length_error("Segament Error!");
		}
		return result;
	}
};

#endif