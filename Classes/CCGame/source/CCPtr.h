#pragma once

NS_CC_BEGIN

#define COMPARE(_op_)									\
	inline bool operator _op_ (const CCPtr<T>& o) const	\
	{													\
		return m_ptr _op_ o.m_ptr;						\
	}													\
	template<class U>									\
	inline bool operator _op_ (const U& ptr) const		\
	{													\
		return (void*)m_ptr _op_ (void*)ptr;			\
	}

template<class T>
class CCPtr
{
public:
	explicit CCPtr(T* other = 0)
		: m_ptr(other)
	{
		CC_SAFE_RETAIN(m_ptr);
	}

	explicit CCPtr(CCPtr<T> const & other)
		: m_ptr(other.get())
	{
		CC_SAFE_RETAIN(m_ptr);
	}

	template<class U>
	CCPtr(CCPtr<U>& other)
		: m_ptr(other.get())
	{
		CC_SAFE_RETAIN(m_ptr);
	}

	~CCPtr()
	{
		CC_SAFE_RELEASE(m_ptr);
	}

	CCPtr<T>& operator=(CCPtr<T>& other)
	{
		T* ptr = other.get();
		CC_SAFE_RETAIN(ptr);
		CC_SAFE_RELEASE(m_ptr);
		m_ptr = ptr;

		return (*this);
	}

	CCPtr<T>& operator=(T* other)
	{
		CC_SAFE_RETAIN(other);
		CC_SAFE_RELEASE(m_ptr);
		m_ptr = other;

		return (*this);
	}

	template<class U>
	CCPtr<T>& operator=(CCPtr<U>& other)
	{
		U* ptr = other.get();
		CC_SAFE_RETAIN(ptr);
		CC_SAFE_RELEASE(m_ptr);
		m_ptr = ptr;

		return (*this);
	}

	template<class U>
	CCPtr<T>& operator=(U* other)
	{
		CC_SAFE_RETAIN(other);
		CC_SAFE_RELEASE(m_ptr);
		m_ptr = other;

		return (*this);
	}

	inline T& operator* () const  { return *m_ptr; }
	inline T* operator-> () const { return m_ptr; }
	inline T* get() const         { return m_ptr; }

	COMPARE( == )
	COMPARE( != )
	COMPARE( > )
	COMPARE( < )
	COMPARE( <= )
	COMPARE( >= )

private:
	T *m_ptr {nullptr};	// the wrapped object pointer
};

#undef COMPARE

NS_CC_END
