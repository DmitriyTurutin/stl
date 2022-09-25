#pragma once
#include "Exception.h"
#include "Iterator.h"

template<typename DataType>
class ListIterator;

template<typename DataType>
class List
{
public:
	template<typename DataType> friend class ListIterator;
	using ValueType = DataType;
	using Iterator = ListIterator<DataType>;
private:
	//template<class DataType>
	class Node
	{
	public:
		Node() : value(DataType()), next(nullptr), prev(nullptr) {}
		Node(const DataType& value, Node* next, Node* prev)
			: value(value),
			  next(next),
			  prev(prev)
		{}

		Node(DataType&& value, Node* next, Node* prev)
			: value(std::move(value)),
			next(next),
			prev(prev)
		{}

		DataType value;
		Node* next;
		Node* prev;
	};

public:
	using node_t = Node;

	List() : size(0), head(nullptr), tail(nullptr) {}

	List(const std::initializer_list<DataType>& list)
	{
		for (DataType element : list)
		{
			pushBack(element);
		}
	}

	explicit List(int size, const DataType initial_value = DataType())
	{
		for (int i = 0; i < size; i++)
			pushBack(initial_value);
	}

	template <typename IteratorType>
	List(IteratorType beg, IteratorType end)
	{
		while (beg != end)
		{
			pushBack(*beg);
			++beg;
		}

	}

	

	void operator=(const List& other)
	{
		node_t* tmp = other.head;

		clear();
		while (tmp != nullptr)
		{
			pushBack(tmp->value);
			tmp = tmp->next;
		}
	}

	//	~List() { clear(); }

	void pushBack(DataType& value)
	{
		if (head == nullptr)
		{
			node_t* new_node = new node_t(value, nullptr, nullptr);
			head = tail = new_node;
		}
		else 
		{
			node_t* new_node = new node_t(value, nullptr, tail);
			tail->next = new_node;
			tail = new_node;
		}
		this->size++;
	}

	void pushBack(DataType&& value)
	{
		if (head == nullptr)
		{
			node_t* new_node= new node_t(std::move(value), nullptr, nullptr);
			head = tail = new_node;
		}
		else 
		{
			node_t* new_node = new node_t(std::move(value), nullptr, tail);
			tail->next = new_node;
			tail = new_node;
		}
		this->size++;
	}

	void popBack()
	{
		if (head == tail)
		{
			delete head;
			tail = head = nullptr;
		}
		else
		{
			node_t* tmp = tail->prev;
			delete tail;
			tail = tmp;
			tail->next = nullptr;
		}
		this->size--;
	}

	void clear()
	{
		while (!empty())
			popBack();
	}
	bool empty() const { return size == 0; }
	size_t getSize() const { return size; }

	Iterator begin() const
	{
		return Iterator(*this, head);
	}

	Iterator end() const
	{
		if (head == nullptr)
			throw Exception("List is empty!");

		return Iterator(*this, tail->next);
	}

	void pushFront(DataType&& value)
	{
		if (head == nullptr)
		{
			head = new node_t(std::move(value), nullptr, nullptr);
			tail = head;
		}
		else
		{
			node_t* tmp = new node_t(std::move(value), head, nullptr);
			head->prev = tmp;
			head = tmp;
		}
		size++;
	}

	void pushFront(DataType& value)
	{
		if (head == nullptr)
		{
			node_t* new_node = new node_t(value, nullptr, nullptr);
			head = tail = new_node;
		}
		else
		{
			node_t* new_node = new node_t(value, head, nullptr);
			head->prev = new_node;
			head = new_node;
		}
	}

	Iterator Insert(const Iterator& position, DataType&& value)
	{
		node_t* tmp = head;

		while (tmp != position.m_Ptr)
		{
			tmp = tmp->next;
		}

		if (tmp == head)
		{
			pushFront(std::move(value));
			return Iterator(*this, head);
		}

		node_t* new_node = new node_t(std::move(value), tmp, tmp->prev);
		node_t* dummy = tmp->prev;
		tmp->prev = new_node;
		dummy->next = new_node;
		size++;

		return Iterator(*this, position.m_Ptr->prev);
	}

	Iterator Insert(const Iterator& position, DataType& value)
	{
		node_t* tmp = head;

		while (tmp != position.m_Ptr)
		{
			tmp = tmp->next;
		}

		if (tmp == head)
		{
			pushFront(value);
			return Iterator(*this, head);
		}

		node_t* new_node = new node_t(value, tmp, tmp->prev);
		node_t* dummy = tmp->prev;
		tmp->prev = new_node;
		dummy->next = new_node;
		size++;

		return Iterator(*this, position.m_Ptr->prev);

	}

	template<typename IterType>
	Iterator Insert(const Iterator position, const IterType begin, const IterType end)
	{
		for (auto val = begin; val != end; val++)
		{
			Insert(position, *val);
		}
		Iterator new_position(position);
		for (auto i = begin; i != end; i++)
		{
			--new_position;
		}
		return new_position;
	}


	template <typename... Args>
	void Emplace(const Iterator& position, Args&&... args)
	{
		DataType value(std::forward<Args>(args)...);
		Insert(position, std::move(value));
	}

	void resize(const unsigned int& num)
	{
		if (this->size == num) return;

		if (num > this->size)
		{
			for (int i = this->size; i < num; i++)
				pushBack(ValueType());
		}
		else 
		{
			for (int i = num; i <= this->size; i++)
				popBack();
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const List& lst) 
	{
		node_t* tmp = lst.head;

		while (tmp != nullptr)
		{
			if (tmp->next == nullptr)
			{
				os << tmp->value;
			}
			else 
			{
				os << tmp->value << " -> ";
			}

			tmp = tmp->next;
		}
		os << '\n';
		return os;

	}

private:
	size_t size;
	node_t* head;
	node_t* tail;
};


