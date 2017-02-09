/********************************************************************
 
	Copyright (c) AM-Studio. All rights reserved.
	
	filename: 	FastQueue.hpp
	author:		HuangYi(notlingfeng@163.com)
	purpose:	

	history: 	2010/05/21 revision 1.0.0.0 

*********************************************************************/


#ifndef __FAST_QUEUE_HY_
#define __FAST_QUEUE_HY_



/** dummy lock to use a non-locked queue.
*/
class DummyLock
{
public:
	void Acquire() { }
	void Release() { }
};

/** linked-list style queue
 */
template<class T, class LOCK>
class FastQueue
{
	struct node
	{
		T _element;
		node * _pNext;
	};

	node * m_pLast;
	node * m_pFirst;
	LOCK m_lock;

public:

	FastQueue()
	{
		m_pLast = 0;
		m_pFirst = 0;
	}

	~FastQueue()
	{
		Clear();
	}

	void Clear()
	{
		// clear any elements
		while(m_pLast != 0)
		{
			Pop_front();
		}
	}

	void Push(T elem)
	{
		m_lock.Acquire();
		node * n = new node;
		if(m_pLast)
		{
			m_pLast->_pNext = n;
		}
		else
		{
			m_pFirst = n;
		}

		m_pLast = n;
		n->_pNext = 0;
		n->_element = elem;
		m_lock.Release();
	}

	T Pop()
	{
		m_lock.Acquire();
		if(m_pFirst == 0)
		{
			m_lock.Release();
			return reinterpret_cast<T>(0);
		}
        
		T ret = m_pFirst->_element;
		node * td = m_pFirst;
		m_pFirst = td->_pNext;
		if(!m_pFirst)
		{
			m_pLast = 0;
		}

		delete td;
		m_lock.Release();
		return ret;
	}

	T Front()
	{
		m_lock.Acquire();
		if(m_pFirst == 0)
		{
			m_lock.Release();
			return reinterpret_cast<T>(0);
		}

		T ret = m_pFirst->_element;
		m_lock.Release();
		return ret;
	}

	void Pop_front()
	{
		m_lock.Acquire();
		if(m_pFirst == 0)
		{
			m_lock.Release();
			return;
		}

		node * td = m_pFirst;
		m_pFirst = td->_pNext;
		if(!m_pFirst)
		{
			m_pLast = 0;
		}

		delete td;
		m_lock.Release();
	}

	bool HasItems()
	{
		bool ret;
		m_lock.Acquire();
		ret = (m_pFirst != 0);
		m_lock.Release();
		return ret;
	}
};

#endif		// __FAST_QUEUE_HY_
