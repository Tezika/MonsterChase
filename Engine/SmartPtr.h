#pragma once
#include "WeakPtr.h"
#include "ReferenceCounter.h"
#include "Assert.h"

namespace Engine
{
	struct ReferenceCounter;

	template<class T>
	class WeakPtr;

	template<class T>
	class SmartPtr
	{
		template<class U>
		friend class WeakPtr;

		template<class U>
		friend class SmartPtr;

	public:
		// Constructor
		SmartPtr();
		explicit SmartPtr( T * i_ptr );

		// Constructor for nullptr
		SmartPtr( std::nullptr_t i_null );

		// Copy Constructor for the same type
		SmartPtr( const SmartPtr<T>& i_other );

		// Copy Constructor For inheritance
		template<class U>
		SmartPtr( const SmartPtr<U> & i_other );

		// Copy Constructor for weak pointers
		SmartPtr( const WeakPtr<T> & i_other );
		template<class U>
		SmartPtr( const WeakPtr<U> & i_other );

		// Assignment operator for the same type
		SmartPtr & operator=( const SmartPtr<T> & i_other );

		// Assignment operator for the inheritance
		template<class U>
		SmartPtr & operator=( const SmartPtr<U> & i_other );

		// Assignment operator for weak pointers
		SmartPtr & operator=( const WeakPtr<T> & i_other );
		template<class U>
		SmartPtr & operator=( const WeakPtr<U> & i_other );

		// Assignment operator for null
		SmartPtr & operator=( std::nullptr_t i_null );

		// Assignment operator for the raw pointer
		SmartPtr & operator=( T * i_ptr );

		~SmartPtr();

		// Inline operator functions
		// Operator == 
		inline bool operator==( const SmartPtr & i_other ) const { return m_ptr == i_other.m_ptr; };
		template<class U>
		inline bool operator==( const SmartPtr<U> & i_other ) const { return m_ptr == i_other.m_ptr; };
		inline bool operator==( const WeakPtr<T> & i_other ) const { return m_ptr == i_other.m_ptr; };
		template<class U>
		inline bool operator==( const WeakPtr<U> & i_other ) const { return m_ptr == i_other.m_ptr; };
		// Equality comparison operator directly to pointer 
		inline bool operator==( T * i_ptr ) const { return m_ptr == i_ptr; };
		// Equality comparison operator directly to pointer (of polymorphic type)
		template<class U>
		inline bool operator==( U * i_ptr ) const { return m_ptr == i_ptr; };
		// Equality comparison operator for nullptr
		inline bool operator==( std::nullptr_t nullp ) const { return m_ptr == nullp; };

		// Operator !=
		inline bool operator!=( const SmartPtr & i_other ) const { return m_ptr != i_other.m_ptr; };
		template<class U>
		inline bool operator!=( const SmartPtr<U> & i_other ) const { return m_ptr != i_other.m_ptr; };
		inline bool operator!=( const WeakPtr<T> & i_other ) const { return m_ptr != i_other.m_ptr; };
		template<class U>
		inline bool operator!=( const WeakPtr<U> & i_other ) const { return m_ptr != i_other.m_ptr; };

		// Inequality comparison operator directly to pointer 
		inline bool operator!=( T * i_ptr ) const { return m_ptr != i_ptr; };
		// Inequality comparison operator directly to pointer (of polymorphic type)
		template<class U>
		inline bool operator!=( U * i_ptr ) const { return m_ptr != i_ptr; };
		// Inequality comparison operator for nullptr
		inline bool operator!=( std::nullptr_t nullp ) const { return m_ptr != nullp; };

		// Access operator
		inline T * operator->() const { return m_ptr; };
		inline T & operator*() const { return *m_ptr; };

		// self-control operator
		inline SmartPtr & operator++() { m_ptr++; return *this; };

		inline operator bool() { return m_ptr != nullptr; };

	private:
		void AcquireNewReference( T * i_ptr, ReferenceCounter * i_pCounter );
		template<class U>
		void AcquireNewReference( U * i_ptr, ReferenceCounter * i_pCounter );
		void ReleaseReference();
		T * m_ptr;
		ReferenceCounter * m_pRefCounter;
	};

	template<class T>
	inline SmartPtr<T>::SmartPtr() :
		m_ptr( nullptr ),
		m_pRefCounter( nullptr )
	{
	}

	template<class T>
	inline SmartPtr<T>::SmartPtr( std::nullptr_t i_null ) :
		m_ptr( nullptr ),
		m_pRefCounter( nullptr )
	{
	}

	template<class T>
	inline SmartPtr<T>::SmartPtr( T * i_ptr ) :
		m_ptr( i_ptr )
	{
		if (i_ptr == nullptr)
		{
			m_pRefCounter = nullptr;
		}
		else
		{
			m_pRefCounter = new ReferenceCounter( 0, 1 );
		}
	}

	template<class T>
	inline SmartPtr<T>::SmartPtr( const SmartPtr<T> & i_other ) :
		m_ptr( i_other.m_ptr ),
		m_pRefCounter( i_other.m_pRefCounter )
	{
		if (m_pRefCounter != nullptr)
		{
			++m_pRefCounter->refCount;
		}
	}

	template<class T>
	template<class U>
	inline SmartPtr<T>::SmartPtr( const SmartPtr<U> & i_other ) :
		m_ptr( reinterpret_cast< T* > (i_other.m_ptr) ),
		m_pRefCounter( i_other.m_pRefCounter )
	{
		if (m_pRefCounter != nullptr)
		{
			++m_pRefCounter->refCount;
		}
	}
	template<class T>
	inline SmartPtr<T>::SmartPtr( const WeakPtr<T> & i_other ) :
		m_ptr( i_other.m_ptr ),
		m_pRefCounter( i_other.m_pRefCounter )
	{
		if (m_pRefCounter != nullptr)
		{
			++m_pRefCounter->refCount;
		}
	}

	template<class T>
	template<class U>
	inline SmartPtr<T>::SmartPtr( const WeakPtr<U> & i_other ) :
		m_ptr( reinterpret_cast< T* > (i_other.m_ptr) ),
		m_pRefCounter( i_other.m_pRefCounter )
	{
		if (m_pRefCounter != nullptr)
		{
			++m_pRefCounter->refCount;
		}
	}

	template<class T>
	SmartPtr<T> & SmartPtr<T>::operator=( const SmartPtr<T> & i_other )
	{
		this->ReleaseReference();
		this->AcquireNewReference( i_other.m_ptr, i_other.m_pRefCounter );
		return *this;
	}

	template<class T>
	SmartPtr<T> & SmartPtr<T>::operator=( std::nullptr_t i_null )
	{
		this->ReleaseReference();
		this->AcquireNewReference( i_null, i_null );
		return *this;
	}

	template<class T>
	SmartPtr<T> & SmartPtr<T>::operator=( T * i_ptr )
	{
		this->ReleaseReference();
		this->AcquireNewReference( i_ptr, new ReferenceCounter( 0, 1 ) );
		return *this;
	}

	template<class T>
	SmartPtr<T> & SmartPtr<T>::operator=( const WeakPtr<T> & i_other )
	{
		this->ReleaseReference();
		this->AcquireNewReference( i_other.m_ptr, i_other.m_pRefCounter );
		return *this;
	}

	template<class T>
	template<class U>
	SmartPtr<T> & SmartPtr<T>::operator=( const WeakPtr<U> & i_other )
	{
		this->ReleaseReference();
		this->AcquireNewReference( i_other.m_ptr, i_other.m_pRefCounter );
		return *this;
	}

	template<class T>
	void SmartPtr<T>::AcquireNewReference( T * i_ptr, ReferenceCounter * i_pCounter )
	{
		m_ptr = i_ptr;
		m_pRefCounter = i_pCounter;
		if (m_pRefCounter != nullptr)
		{
			++m_pRefCounter->refCount;
		}
	}

	template<class T>
	template<class U>
	void SmartPtr<T>::AcquireNewReference( U * i_ptr, ReferenceCounter * i_pCounter )
	{
		m_ptr = reinterpret_cast< T* > (i_ptr);
		m_pRefCounter = i_pCounter;
		if (m_pRefCounter != nullptr)
		{
			++m_pRefCounter->refCount;
		}
	}

	template<class T>
	void SmartPtr<T>::ReleaseReference()
	{
		if (m_pRefCounter == nullptr)
		{
			return;
		}
		if (--m_pRefCounter->refCount == 0)
		{
			delete m_ptr;
			m_ptr = nullptr;
			if (m_pRefCounter->weakCount == 0)
			{
				delete m_pRefCounter;
			}
			m_pRefCounter = nullptr;
		}
	}

	template<class T>
	SmartPtr<T>::~SmartPtr()
	{
		this->ReleaseReference();
	}
}