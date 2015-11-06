#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <stdio.h>
#include <assert.h>

#include <algorithm>
#include <set>
#include <vector>
#include <cfloat>

using namespace std;
#include "NodeManager.h"

#define USE_NODEMANAGER_MEMORY 1

template <class T> class AStarState;

template <class UserState> class AStarSearch
{
public: //data
	enum
	{
		SEARCH_STATE_NOT_INITIALISED,
		SEARCH_STATE_SEARCHING,
		SEARCH_STATE_SUCCEEDED,
		SEARCH_STATE_FAILED,
		SEARCH_STATE_OUT_OF_MEMORY,
		SEARCH_STATE_INVALID
	};

public:
	class Node
	{
	public:
		Node *parent;//used to record the parent of succesor nodes.
		Node *child; //used after thr search to view the search in reverse.

		float g;//cost of this node + it's predecessors.
		float h;//estimate of distance to goal.
		float f;//sum of cost of predecessors, self and estimate.

		Node() :
			parent(0),
			child(0),
			g(0.0f),
			h(0.0f),
			f(0.0f)
		{
		}

		UserState m_UserState;
	};
	class HeapCompare_f// compares the f values of two nodes.
	{
	public:
		bool operator() (const Node *x, const Node *y)const
		{
			return x->f > y->f;
		}

	};

public://methods.

	   // constructor just initialises private data
	AStarSearch() :
		m_State(SEARCH_STATE_NOT_INITIALISED),
		m_CurrentSolutionNode(NULL),
#if USE_NODEMANAGER_MEMORY
		m_FixedSizeAllocator(1000),
#endif
		m_AllocateNodeCount(0),
		m_CancelRequest(false)
	{
	}

	AStarSearch(int MaxNodes) :
		m_State(SEARCH_STATE_NOT_INITIALISED),
		m_CurrentSolutionNode(NULL),
#if USE_NODEMANAGER_MEMORY
		m_FixedSizeAllocator(MaxNodes),
#endif
		m_AllocateNodeCount(0),
		m_CancelRequest(false)
	{
	}

	void CancelSearch()//call to cancel the search.
	{
		m_CancelRequest = true;
	}
	void SetStartAndGoalStates(UserState &Start, UserState &Goal)//sets the start and goal states.
	{
		m_CancelRequest = false;

		m_Start = AllocateNode();
		m_Goal = AllocateNode();

		assert((m_Start != NULL && m_Goal != NULL));

		m_Start->m_UserState = Start;
		m_Goal->m_UserState = Goal;

		m_State = SEARCH_STATE_SEARCHING;

		m_Start->g = 0;
		m_Start->h = m_Start->m_UserState.GoalDistanceEstimate(m_Goal->m_UserState);
		m_Start->f = m_Start->g + m_Start->h;
		m_Start->parent = 0;

		m_OpenList.push_back(m_Start);//pushes the start node onto the open list.
		push_heap(m_OpenList.begin(), m_OpenList.end(), HeapCompare_f());//sorts the element back into the heap.

		m_Steps = 0;//initialises the counter for the amount of steps.
	}
	unsigned int SearchStep()//this advances the search by one step.
	{
		assert((m_State > SEARCH_STATE_NOT_INITIALISED) && (m_State < SEARCH_STATE_INVALID));//break search is user hasn't initialised the search.

		if ((m_State == SEARCH_STATE_SUCCEEDED) || (m_State == SEARCH_STATE_FAILED))
		{
			return m_State;
		}
		if (m_OpenList.empty() || m_CancelRequest)//emptys open list if there is nothing left to search.
		{
			FreeAllNodes();
			m_State = SEARCH_STATE_FAILED;
			return m_State;
		}
		m_Steps++;//increments the step cout.

		Node *n = m_OpenList.front();//pops the best node with the lowest "f" value.
		pop_heap(m_OpenList.begin(), m_OpenList.end(), HeapCompare_f());
		m_OpenList.pop_back();

		if (n->m_UserState.IsGoal(m_Goal->m_UserState))//checks for the goal state
		{
			m_Goal->parent = n->parent;//copys the parent pointer of n.
			m_Goal->g = n->g;

			if (false == n->m_UserState.IsSameState(m_Start->m_UserState))//handles goal state if it was passed as the start state.
			{
				FreeNode(n);

				Node *nodeChild = m_Goal;//sets the child pointers in each node.
				Node *nodeParent = m_Goal->parent;

				do
				{
					nodeParent->child = nodeChild;

					nodeChild = nodeParent;
					nodeParent = nodeParent->parent;
				} while (nodeChild != m_Start);//start is the first node.
			}
			FreeUnusedNodes();

			m_State = SEARCH_STATE_SUCCEEDED;
			return m_State;
		}
		else//if not the goal state.
		{
			m_Successors.clear();//empty the vector of succesor nodes.

			bool ret = n->m_UserState.GetSuccessors(this, n->parent ? &n->parent->m_UserState : NULL);

			if (!ret)
			{
				typename vector<Node *>::iterator successor;
				for (successor = m_Successors.begin(); successor != m_Successors.end(); successor++)
				{
					FreeNode((*successor));
				}
				m_Successors.clear();//empties the vector of successor nodes.

				FreeAllNodes();
				m_State = SEARCH_STATE_OUT_OF_MEMORY;
				return m_State;
			}
			for (typename vector<Node *>::iterator successor = m_Successors.begin(); successor != m_Successors.end(); successor++)//handles successor for the current node.
			{
				float newg = n->g + n->m_UserState.GetCost((*successor)->m_UserState);

				typename vector<Node *>::iterator openlist_result;

				for (openlist_result = m_OpenList.begin(); openlist_result != m_OpenList.end(); openlist_result++)
				{
					if ((*openlist_result)->m_UserState.IsSameState((*successor)->m_UserState))
					{
						break;
					}
				}
				if (openlist_result != m_OpenList.end())
				{
					if ((*openlist_result)->g <= newg)
					{
						FreeNode((*successor));
						continue;
					}
				}
				typename vector<Node *>::iterator closedlist_result;

				for (closedlist_result = m_ClosedList.begin(); closedlist_result != m_ClosedList.end(); closedlist_result++)
				{
					if ((*closedlist_result)->m_UserState.IsSameState((*successor)->m_UserState))
					{
						break;
					}
				}
				if (closedlist_result != m_ClosedList.end())
				{
					//finds this state when closed.
					if ((*closedlist_result)->g <= newg)
					{
						FreeNode((*successor));
						continue;
					}
				}

				(*successor)->parent = n;
				(*successor)->g = newg;
				(*successor)->h = (*successor)->m_UserState.GoalDistanceEstimate(m_Goal->m_UserState);
				(*successor)->f = (*successor)->g + (*successor)->h;

				if (closedlist_result != m_ClosedList.end())//removes the successor from the closed node if it was on it.
				{
					FreeNode((*closedlist_result));//removes it from the closed list.
					m_OpenList.erase(openlist_result);
				}
				if (openlist_result != m_OpenList.end())//updates the old version of this node.
				{
					FreeNode((*openlist_result));
					m_OpenList.erase(openlist_result);
					make_heap(m_OpenList.begin(), m_OpenList.end(), HeapCompare_f());//re-makes the heap.
				}
				m_OpenList.push_back((*successor));//the heap is now unsorted.
				push_heap(m_OpenList.begin(), m_OpenList.end(), HeapCompare_f());//sorts elements back into the heap.
			}
			m_ClosedList.push_back(n);//pushes n onto "Closed"
		}
		return m_State;
	}
	bool AddSuccessor(UserState &State)//this is called to add to the list of successors.
	{
		Node *node = AllocateNode();

		if (node)
		{
			node->m_UserState = State;
			m_Successors.push_back(node);
			return true;
		}
		return false;
	}
	void FreeSolutionNodes()//frees the solution nodes.
	{
		Node *n = m_Start;
		if (m_Start->child)
		{
			do
			{
				Node *del = n;
				n = n->child;
				FreeNode(del);
				del = NULL;
			} while (n != m_Goal);

			FreeNode(n);//deletes the goal node.
		}
		else
		{
			FreeNode(m_Start);//if the start node is the solution, deletes start and goal nodes.
			FreeNode(m_Goal);
		}

	}
	UserState *GetSolutionStart()//gets the start node.
	{
		m_CurrentSolutionNode = m_Start;
		if (m_Start)
		{
			return &m_Start->m_UserState;
		}
		else
		{
			return NULL;
		}
	}
	UserState *GetSolutionNext()//gets the next node.
	{
		if (m_CurrentSolutionNode)
		{
			if (m_CurrentSolutionNode->child)
			{
				Node *child = m_CurrentSolutionNode->child;
				m_CurrentSolutionNode = m_CurrentSolutionNode->child;
				return &child->m_UserState;
			}
		}
		return NULL;
	}
	UserState *GetSolutionEnd()//gets the end node.
	{
		m_CurrentSolutionNode = m_Goal;
		if (m_Goal)
		{
			return &m_Goal->m_UserState;
		}
		else
		{
			return NULL;
		}
	}
	UserState *GetSolutionPrev()//gets the previous node.
	{
		if (m_CurrentSolutionNode)
		{
			if (m_CurrentSolutionNode->parent)
			{
				Node *parent = m_CurrentSolutionNode->parent;
				m_CurrentSolutionNode = m_CurrentSolutionNode->parent;
				return &parent->m_UserState;
			}
		}
		return NULL;
	}
	float GetSolutionCost()//gets the final cost of the solution.
	{
		if (m_Goal && m_State == SEARCH_STATE_SUCCEEDED)
		{
			return m_Goal->g;
		}
		else
		{
			return FLT_MAX;//returns this if there is no goal or solution found.
		}
	}

	int GetStepCount() { return m_Steps; }

	void EnsureMemoryFreed()
	{
#if USE_NODEMANAGER_MEMORY
		assert(m_AllocateNodeCount == 0);
#endif
	}

private://methods
	void FreeAllNodes()//iterates the list and deltes all nodes.
	{
		typename vector<Node *>::iterator iterOpen = m_OpenList.begin();
		while (iterOpen != m_OpenList.end())
		{
			Node *n = (*iterOpen);
			FreeNode(n);
			iterOpen++;
		}
		m_OpenList.clear();

		typename vector<Node *>::iterator iterClosed;//iterates the closed list and delted the unused nodes.
		for (iterClosed = m_ClosedList.begin(); iterClosed != m_ClosedList.end(); iterClosed++)
		{
			Node *n = (*iterClosed);
			FreeNode(n);
		}
		m_ClosedList.clear();
		FreeNode(m_Goal);//deletes the goal.
	}
	void FreeUnusedNodes()//deletes all the unused nodes.
	{
		typename vector<Node *>::iterator iterOpen = m_OpenList.begin();//iterates the open list and deletes the unused nodes.
		while (iterOpen != m_OpenList.end())
		{
			Node *n = (*iterOpen);
			if (!n->child)
			{
				FreeNode(n);
				n = NULL;
			}
			iterOpen++;
		}
		m_OpenList.clear();

		typename vector<Node *>::iterator iterClosed;//iterates the closed list and delted the unused nodes.
		for (iterClosed = m_ClosedList.begin(); iterClosed != m_ClosedList.end(); iterClosed++)
		{
			Node *n = (*iterClosed);
			if (!n->child)
			{
				FreeNode(n);
				n = NULL;
			}
		}
		m_ClosedList.clear();
	}
	Node *AllocateNode()//node memory management
	{
#if !USE_NODEMANAGER_MEMORY
		Node *p = new Node;
		return p;
#else
		Node *address = m_FixedSizeAllocator.alloc();
		if (!address)
		{
			return NULL;
		}
		m_AllocateNodeCount++;
		Node *p = new (address)Node;
		return p;
#endif
	}
	void FreeNode(Node *node)
	{
		m_AllocateNodeCount--;

#if !USE_NODEMANAGER_MEMORY
		delete node;
#else
		node -> ~Node();
		m_FixedSizeAllocator.free(node);
#endif
	}

private://data
	vector<Node *> m_OpenList;//heap.
	vector<Node *> m_ClosedList;//closed list.
	vector<Node *> m_Successors;//successors

	unsigned int m_State;//state
	int m_Steps;//counts steps.

	Node *m_Start;//start pointer.
	Node *m_Goal;//goal pointer.

	Node *m_CurrentSolutionNode;

#if USE_NODEMANAGER_MEMORY
	FixedSizeAllocator<Node> m_FixedSizeAllocator;
#endif

	bool m_CancelRequest;
	int m_AllocateNodeCount;

};

template <class T> class AStarState
{
public:
	virtual ~AStarState() {}
	virtual float GoalDistanceEstimate(T &nodeGoal) = 0;//computes the estimated cost to the goal node.
	virtual bool IsGoal(T &nodeGoal) = 0;//returns true if the node is the goal node.
	virtual bool GetSuccessors(AStarSearch<T> *astarsearch, T *parent_node) = 0;//retrieves all successors to this node and adds them to the search.
	virtual float GetCost(T &successor) = 0;//gets the cost of travelling from this node to the succesor node.
	virtual bool IsSameState(T &rhs) = 0;//returns true if this node is the same as the rhs node.
};

#endif

