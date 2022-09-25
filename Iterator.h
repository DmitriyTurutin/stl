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

	template<typename DataType> friend class List;
public:
	ListIterator() noexcept : m_Ptr(nullptr), lst() {};

	ListIterator(const List<DataType>& lst, Nodeptr ptr)
	{
		this->lst = lst;
		m_Ptr = ptr;
	}

	ListIterator(const ListIterator& iter)
	{
		this->lst = iter.lst;
		this->m_Ptr = iter.m_Ptr;
	}

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

private:
	Nodeptr m_Ptr;
	List<DataType> lst;
};
