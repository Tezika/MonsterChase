#pragma once
#include "SmartPtr.h"
#include "ReferenceCounter.h"
#include "Assert.h"

namespace Engine
{
	struct ReferenceCounter;

	template<class T>
	class SmartPtr;

	template<class T>
	class WeakPtr
	{
		template<class U>
		friend class SmartPtr;
		template<class U>
		friend class WeakPtr;
	public:
		// Default Constructor
		WeakPtr();

		// Copy Constructors
		WeakPtr( const WeakPtr<T> & i_other );

		WeakPtr( const SmartPtr<T> & i_other );

		template<class U>
		WeakPtr( const SmartPtr<U> & i_other );

		template<class U>
		WeakPtr( const WeakPtr<U> & i_ohter );

		// Destructor
		~WeakPtr();

		// Create an Smart Pointer from this Weak Pointer
		SmartPtr<T> AcquireOwnership();

		// Assignment operators
		WeakPtr & operator=( const WeakPtr<T> & i_other );

		template<class U>
		WeakPtr & operator=( const WeakPtr<U> & i_other );

		WeakPtr & operator=( const SmartPtr<T> & i_other );

		template<class U>
		WeakPtr & operator=( const SmartPtr<U> & i_other );

		WeakPtr<T> & operator=( std::nullptr_t i_null );

		// Equality comparison operators
		inline bool operator==( const WeakPtr<T> & i_other ) const { return m_ptr == i_other.m_ptr; };

		template<class U>
		inline bool operator==( const SmartPtr<U> & i_other ) const { return m_ptr == i_other.m_ptr; };
		template<class U>
		inline bool operator==( const WeakPtr<U> & i_other ) const { return m_ptr == i_other.m_ptr; };
		inline bool operator==( const SmartPtr<T> & i_other ) const { return m_ptr == i_other.ptr; };
		inline bool operator==( T * i_ptr ) const { return m_ptr == i_ptr; };
		template<class U>
		inline bool operator==( U * i_ptr ) const { return m_ptr == i_ptr; };

		// Inequality comparison operators
		inline bool operator!=( const SmartPtr<T> & i_other ) const { return m_ptr != i_other.m_ptr; };
		template<class U>
		inline bool operator!=( const SmartPtr<U> & i_other ) const { return m_ptr != i_other.m_ptr; };
		inline bool operator!=( const WeakPtr & i_other ) const { return m_ptr != i_other.m_ptr; };
		template<class U>
		inline bool operator!=( const WeakPtr<U> & i_other ) const{ return m_ptr != i_other.m_ptr; };

		inline bool operator!=( T * i_ptr ) const { return m_ptr != i_ptr; };

		template<class U>
		inline bool operator!=( U * i_ptr ) const { return m_ptr != i_ptr; };

		// bool operator
		inline operator bool() const { return m_ptr != nullptr; };

	private:
		void ReleaseReference();
		void AcquireNewReference( T * i_ptr, ReferenceCounter * i_pCounter );
		template<class U>
		void AcquireNewReference( U * i_ptr, ReferenceCounter * i_pCounter );
		T * m_ptr;
		ReferenceCounter * m_pRefCounter;
	};

	template<class T>
	inline WeakPtr<T>::WeakPtr() :
		m_ptr( nullptr ),
		m_pRefCounter( nullptr )
	{
	}

	template<class T>
	inline WeakPtr<T>::WeakPtr( const WeakPtr<T> & i_other ) :
		m_ptr( i_other.m_ptr ),
		m_pRefCounter( i_other.m_pRefCounter )
	{
		if ( m_pRefCounter != nullptr )
		{
			++m_pRefCounter->weakCount;
		}
	}

	template<class T>
	template<class U>
	inline WeakPtr<T>::WeakPtr( const WeakPtr<U> & i_other ) :
		m_ptr( reinterpret_cast<T*> ( i_other.m_ptr ) ),
		m_pRefCounter( i_other.m_pRefCounter )
	{
		if ( m_pRefCounter != nullptr )
		{
			++m_pRefCounter->weakCount;
		}
	}

	template<class T>
	inline WeakPtr<T>::WeakPtr( const SmartPtr<T> & i_other ) :
		m_ptr( i_other.m_ptr ),
		m_pRefCounter( i_other.m_pRefCounter )
	{
		if ( m_pRefCounter != nullptr )
		{
			++m_pRefCounter->weakCount;
		}
	}

	template<class T>
	template<class U>
	inline WeakPtr<T>::WeakPtr( const SmartPtr<U> & i_other ) :
		m_ptr( reinterpret_cast<T*> ( i_other.m_ptr ) ),
		m_pRefCounter( i_other.m_pRefCounter )
	{
		if ( m_pRefCounter != nullptr )
		{
			++m_pRefCounter->weakCount;
		}
	}

	// Assignment operators
	template<class T>
	WeakPtr<T> & WeakPtr<T>::operator=( const WeakPtr<T> & i_other )
	{
		this->ReleaseReference();
		this->AcquireNewReference( i_other.m_ptr, i_other.m_pRefCounter );
		return *this;
	}

	template<class T>
	template<class U>
	WeakPtr<T> & WeakPtr<T>::operator=( const WeakPtr<U> & i_other )
	{
		this->ReleaseReference();
		this->AcquireNewReference( i_other.m_ptr, i_other.m_pRefCounter );
		return *this;
	}

	template<class T>
	WeakPtr<T> & WeakPtr<T>::operator=( const SmartPtr<T> & i_other )
	{
		this->ReleaseReference();
		this->AcquireNewReference( i_other.m_ptr, i_other.m_pRefCounter );
		return *this;
	}

	template<class T>
	template<class U>
	WeakPtr<T> & WeakPtr<T>::operator=( const SmartPtr<U> & i_other )
	{
		this->ReleaseReference();
		this->AcquireNewReference( i_other.m_ptr, i_other.m_pRefCounter );
		return *this;
	}

	template<class T>
	WeakPtr<T> &  WeakPtr<T>::operator=( std::nullptr_t i_null )
	{
		this->ReleaseReference();
		this->AcquireNewReference( i_null, i_null );
		return *this;
	}

	template<class T>
	WeakPtr<T>::~WeakPtr()
	{
		this->ReleaseReference();
	}

	template<class T>
	void WeakPtr<T>::ReleaseReference()
	{
		if ( m_pRefCounter == nullptr )
		{
			return;
		}

		if ( m_pRefCounter->weakCount > 0 )
		{
			--m_pRefCounter->weakCount;
		}

		if ( m_pRefCounter->weakCount == 0 )
		{
			if ( m_pRefCounter->refCount == 0 )
			{
				delete m_pRefCounter;
			}
			m_pRefCounter = nullptr;
		}
	}

	template<class T>
	void WeakPtr<T>::AcquireNewReference( T * i_ptr, ReferenceCounter * i_pCounter )
	{
		m_ptr = i_ptr;
		m_pRefCounter = i_pCounter;
		if ( m_pRefCounter != nullptr )
		{
			++m_pRefCounter->weakCount;
		}
	}

	template<class T>
	template<class U>
	void WeakPtr<T>::AcquireNewReference( U * i_ptr, ReferenceCounter * i_pCounter )
	{
		m_ptr = reinterpret_cast<T*> ( i_ptr );
		m_pRefCounter = i_pCounter;
		if ( m_pRefCounter != nullptr )
		{
			++m_pRefCounter->weakCount;
		}
	}

	template<class T>
	SmartPtr<T> WeakPtr<T>::AcquireOwnership()
	{
		if ( this->m_pRefCounter == nullptr || m_pRefCounter->refCount == 0 )
		{
			return SmartPtr<T>( nullptr );
		}
		return SmartPtr<T>( *this );
	}
}