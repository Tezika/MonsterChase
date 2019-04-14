#pragma once
#include "ConsolePrint.h"
#include "assert.h"

namespace Engine
{
	template<typename T>
	class Node
	{
	public:
		Node<T>( const T & );
		Node<T>( T * );
		Node<T>( const Node<T> & i_other ) : m_pData( i_other.m_pData ), m_pNext( i_other.m_pNext ) {}
		~Node<T>() {}
		Node<T> & operator=( const Node<T> & );
		Node<T> & operator=( const Node<T> * );

		inline void SetData( T * i_pData ){ m_pData = i_pData; };
		inline T * GetData(){ return m_pData; }

		inline void SetNext( Node<T> * i_pNext ){ m_pNext = i_pNext; }
		inline Node<T> * GetNext(){ return m_pNext; }

	private:
		T * m_pData;
		Node<T> * m_pNext;
	};

	template<typename T>
	inline Node<T>::Node( const T & i_other )
	{
		this->m_pData = &i_other;
		this->m_pNext = nullptr;
	}

	template<typename T>
	inline Node<T>::Node( T * i_pOther )
	{
		assert( i_pOther );
		this->m_pData = i_pOther;
		this->m_pNext = nullptr;
	}

	template<typename T>
	inline Node<T> & Engine::Node<T>::operator=( const Node<T> & i_other )
	{
		this->m_pData = i_other.m_pData;
		this->m_pNext = i_other.m_pNext;
		return *this;
	}

	template<typename T>
	inline Node<T> & Engine::Node<T>::operator=( const Node<T> * i_pOther )
	{
		assert( i_pOther );
		this->m_pData = i_pOther->m_pData;
		this->m_pNext = i_pOther->m_pNext;
		return *this;
	}

	template<typename T>
	class TList
	{
	public:
		TList( const TList & );
		TList() : m_pHead( nullptr ), m_pTail( nullptr ) { m_length = 0; }
		TList( Node<T> * i_pNode ) : m_pHead( i_pNode ), m_pTail( i_pNode ) { m_length = 1; }
		~TList();

		const size_t Length() { return m_length; }

		Node<T> * Remove( Node<T> * );
		Node<T> * Insert( T * );

		void Clear( bool i_deleteNodeData = false );

		inline Node<T> * GetHead(){ return m_pHead; }
		inline Node<T> * GetTail(){ return m_pTail; }

	private:
		Node<T> * m_pHead;
		Node<T> * m_pTail;
		size_t m_length;
	};

	template<typename T>
	inline TList<T>::TList( const TList<T> & List ) : m_pHead( nullptr ), m_pTail( nullptr )
	{
	}

	template<typename T>
	inline Node<T> * TList<T>::Remove( Node<T> * i_pNode )
	{
		assert( i_pNode );
		Node<T> * ptr = this->GetHead();
		Node<T> * ptr_previous = nullptr;
		while ( ptr != nullptr )
		{
			if ( ptr == i_pNode )
			{
				if ( ptr_previous == nullptr )
				{
					this->m_pHead = this->m_pHead->GetNext();
					delete ptr;
					ptr = this->m_pHead;
					break;
				}
				else
				{
					ptr_previous->SetNext( ptr->GetNext() );
					delete ptr;
					ptr = ptr_previous->GetNext();
					break;
				}

				//if the removed node is the tail
				if ( ptr == this->m_pTail )
				{
					this->m_pTail = ptr_previous;
				}
			}
			else
			{
				ptr_previous = ptr;
				ptr = ptr->GetNext();
			}
		}
		m_length--;
		return ptr;
	}

	template<typename T>
	inline TList<T>::~TList()
	{
		this->Clear();
	}

	template<typename T>
	inline Node<T> * TList<T>::Insert( T * i_pVal )
	{
		assert( i_pVal );
		Node<T> * newNode = new Node<T>( i_pVal );
		if ( m_pHead == nullptr )
		{
			m_pHead = newNode;
			m_pTail = newNode;
		}
		else
		{
			m_pTail->SetNext( newNode );
			m_pTail = newNode;
		}
		m_length++;
		return newNode;
	}

	template<typename T>
	void TList<T>::Clear( bool i_bDeleteNodeData )
	{
		Node<T> * ptr = m_pHead;
		T * removeData = nullptr;
		while ( ptr != nullptr )
		{
			if ( i_bDeleteNodeData )
			{
				removeData = ptr->GetData();
				assert( removeData );
				delete removeData;
			}
			ptr = this->Remove( ptr );
		}
		m_pHead = nullptr;
		m_pTail = nullptr;
	}
}
