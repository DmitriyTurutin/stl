#pragma once 
#include "Container.h"

template <class DataType>
class List;
template <typename DataType>
class ListIterator
{
public:
	using value_type = DataType;
	using Nodeptr = List<DataType>::Node*;
	using pointer_type = value_type*;
	using reference_type = value_type&;
	using listpointer_type = const List<DataType>*;

	template<typename DataType> friend class List;
public:
	ListIterator() noexcept : m_Ptr(nullptr), lst() {};

	//ListIterator(const List<DataType>& lst, Nodeptr ptr)
	//	: lst(lst),
	//	  m_Ptr(ptr)
	//{}
	ListIterator(const List<DataType> lst, Nodeptr ptr)
		: lst(&lst), m_Ptr(ptr)
	{
	}

	ListIterator(const List<DataType>& lst, int n)
	{
		m_Ptr = lst.head;
		lst = &lst;

		for (int i = 0; i < n; i++)
		{
			m_Ptr = m_Ptr->next;
		}
	}

	ListIterator(const ListIterator& iter)
		: lst(iter.lst),
		m_Ptr(iter.m_Ptr)
	{}

	ListIterator& operator++()
	{
		m_Ptr = m_Ptr->next;
		return *this;
	}

	ListIterator operator++(int)
	{
		ListIterator iterator = *this;
		m_Ptr = m_Ptr->next;
		return iterator;
	}

	ListIterator& operator--()
	{
		m_Ptr = m_Ptr->prev;
		return *this;
	}

	ListIterator operator--(int)
	{
		ListIterator iterator = *this;
		m_Ptr = m_Ptr->prev;
		return iterator;
	}

	reference_type operator*()
	{
		return m_Ptr->value;
	}

	bool operator==(const ListIterator& other) const
	{
		return m_Ptr == other.m_Ptr;
	}

	ListIterator& operator=(const ListIterator other) noexcept
	{
		lst = other.list;
		m_Ptr = other.m_Ptr;
		return *this;
	}

	reference_type operator*() const
	{
		return m_Ptr->value;
	}

	pointer_type operator->()
	{
		return &m_Ptr->value;
	}

	explicit operator value_type*() const
	{
		return &m_Ptr->value;
	}

private:
	Nodeptr m_Ptr;
	listpointer_type lst;
};
