#ifndef NODEMANAGER_H
#define NODEMANAGER_H

#include <string.h>
#include <stdio.h>

template <class USER_TYPE> class FixedSizeAllocator
{
public://constants
	   //allows easy management of a double linked list class.
	enum
	{
		NODEMANAGER_DEFAULT_SIZE = 100
	};
	struct NODEMANAGER_ELEMENT
	{
		USER_TYPE UserType;

		NODEMANAGER_ELEMENT *pPrev;
		NODEMANAGER_ELEMENT *pNext;
	};

public://methods
	FixedSizeAllocator(unsigned int MaxElements = NODEMANAGER_DEFAULT_SIZE) :
		m_pFirstUsed(NULL),
		m_MaxElements(MaxElements)
	{
		//allocates memory for the maximum amount of elements.

		char *pMem = new char[m_MaxElements * sizeof(NODEMANAGER_ELEMENT)];

		m_pMemory = (NODEMANAGER_ELEMENT *)pMem;
		m_pFirstFree = m_pMemory;//sets the first pointer in the free list.

		memset(m_pMemory, 0, sizeof(NODEMANAGER_ELEMENT) * m_MaxElements);//clears memory.

		NODEMANAGER_ELEMENT *pElement = m_pFirstFree;//point to first element.

		for (unsigned int i = 0; i < m_MaxElements; i++)
		{
			pElement->pPrev = pElement - 1;
			pElement->pNext = pElement + 1;

			pElement++;
		}
		m_pFirstFree->pPrev = NULL;
		(pElement - 1)->pNext = NULL;
	}
	~FixedSizeAllocator()
	{
		delete[](char *) m_pMemory;
	}
	USER_TYPE *alloc()
	{
		NODEMANAGER_ELEMENT *pNewNode = NULL;

		if (!m_pFirstFree)
		{
			return NULL;
		}
		else
		{
			pNewNode = m_pFirstFree;
			m_pFirstFree = pNewNode->pNext;

			if (pNewNode->pNext)
			{
				pNewNode->pNext->pPrev = NULL;
			}

			pNewNode->pPrev = NULL; // the allocated node is always first in the list

			if (m_pFirstUsed == NULL)
			{
				pNewNode->pNext = NULL; // no other nodes
			}
			else
			{
				m_pFirstUsed->pPrev = pNewNode; // insert this at the head of the used list
				pNewNode->pNext = m_pFirstUsed;
			}

			m_pFirstUsed = pNewNode;

		}
		return reinterpret_cast<USER_TYPE*>(pNewNode);
	}
	void free(USER_TYPE * user_data)
	{
		NODEMANAGER_ELEMENT * pNode = reinterpret_cast<NODEMANAGER_ELEMENT*>(user_data);

		if (pNode->pPrev)
		{
			pNode->pPrev->pNext = pNode->pNext;
		}
		else
		{
			m_pFirstUsed = pNode->pNext;
		}
		if (pNode->pNext)
		{
			pNode->pNext->pPrev = pNode->pPrev;
		}
		if (m_pFirstFree == NULL)
		{
			m_pFirstFree = pNode;
			pNode->pPrev = NULL;
			pNode->pNext = NULL;
		}
		else
		{
			m_pFirstFree->pPrev = pNode;
			pNode->pNext = m_pFirstFree;
			m_pFirstFree = pNode;
		}
	}
	USER_TYPE *GetFirst()
	{
		return reinterpret_cast<USER_TYPE *>(m_pFirstUsed);
	}

	USER_TYPE *GetNext(USER_TYPE *node)
	{
		return reinterpret_cast<USER_TYPE *>
			(
				(reinterpret_cast<FSA_ELEMENT *>(node))->pNext
				);
	}
private: // data

	NODEMANAGER_ELEMENT *m_pFirstFree;
	NODEMANAGER_ELEMENT *m_pFirstUsed;
	unsigned int m_MaxElements;
	NODEMANAGER_ELEMENT *m_pMemory;

};
#endif
