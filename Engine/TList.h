#pragma once

namespace Engine
{
	template<class T>
	class Node
	{
	public:
		T * data;
		Node<T>* next;
		Node<T>(T&);
		Node<T>(T*);
		Node<T>(const Node<T>& copyNode) : data(copyNode.data), next(copyNode.next) {}
		~Node<T>() { delete data; }
		Node<T>& operator=(const Node<T>&);
		Node<T>& operator=(const Node<T> *);
	};

	template<class T>
	inline Node<T>::Node(T& d)
	{
		this->data = &d;
		this->next = nullptr;
	}

	template<class T>
	inline Node<T>::Node(T* d)
	{
		this->data = d;
		this->next = nullptr;
	}

	template<class T>
	inline Node<T>& Engine::Node<T>::operator=(const Node<T>& other)
	{
		this->data = other.data;
		this->next = other.next;
		return *this;
	}

	template<class T>
	inline Node<T>& Engine::Node<T>::operator=(const Node<T> *other)
	{
		this->data = other->data;
		this->next = other->next;
		return *this;
	}

	template<class T>
	class TList
	{
	public:
		TList(const TList&);
		TList() : head(NULL), tail(NULL) {}
		TList(Node<T> * newNode) : head(newNode), tail(newNode) {}
		~TList();

		Node<T>* Remove(Node<T>*);
		Node<T>* InsertToTail(T*);

		Node<T>* head;
		Node<T>* tail;
	};

	template<class T>
	inline TList<T>::TList(const TList<T>& List) : head(nullptr), tail(nullptr)
	{

	}

	template<class T>
	inline Node<T>* TList<T>::Remove(Node<T>* node)
	{
		Node<T>* ptr = this->head;
		Node<T>* ptr_previous = nullptr;
		while (ptr != nullptr)
		{
			if (ptr == node)
			{
				if (ptr_previous == nullptr)
				{
					this->head = this->head->next;
					delete ptr;
					ptr = this->head;
					break;
				}
				else
				{
					ptr_previous->next = ptr->next;
					delete ptr;
					ptr = ptr_previous->next;
					break;
				}

				//if the removed node is the tail
				if (ptr == this->tail)
				{
					this->tail = ptr_previous;
				}
			}
			else
			{
				ptr_previous = ptr;
				ptr = ptr->next;
			}
		}
		return ptr;
	}

	template<class T>
	inline TList<T>::~TList()
	{
		auto cur = head;
		while (head)
		{
			head = head->next;
			delete cur;
			cur = head;
		}
		head = nullptr;
		tail = nullptr;
	}

	template<class T>
	inline Node<T>* TList<T>::InsertToTail(T* val)
	{
		Node<T>* newNode = new Node<T>(val);
		if (head == nullptr)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			tail->next = newNode;
			tail = newNode;
		}
		return newNode;
	}
}
