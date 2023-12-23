#include <iostream>
#include "DList.h"
using namespace std;
template<class T>
DList<T>::DList()
	:Head(nullptr), Tail(nullptr)
{}
template<class T>
DList<T>::~DList()
{
	while (!(this->isEmpty()))
	{
		this->RemoveLast();
	}
}
template<class T>
bool DList<T>::isEmpty() const
{
	return this->Head == nullptr;
}
template <class T>
void DList<T>::InsertFirst(DNode<T> * const Newptr)
{
	Newptr->next = this->Head;
	if (this->Tail == nullptr)
	{
		this->Tail = Newptr;
	}
	else
	{
		(this->Head)->pre = Newptr;
	}
	this->Head = Newptr;
}
template <class T>
void DList<T>::InsertLast( DNode<T> * const Newptr)
{
	Newptr->pre = this->Tail;
	if (this->Head == nullptr)
	{
		this->Head = Newptr;
	}
	else
	{
		(this->Tail)->next = Newptr;
	}
	this->Tail = Newptr;
}
template <class T>
void DList<T>::RemoveFirst()
{
	if (this->Head != nullptr)
	{
		DNode<T>*tempptr = this->Head;
		this->Head = tempptr->next;
		if (this->Head == nullptr)
		{
			this->Tail = nullptr;
		}
		else
		{
			(this->Head)->pre = nullptr;
		}
		delete tempptr;
	}
}
template<class T>
void DList<T>::RemoveLast()
{
	if (this->Head != nullptr)
	{
		DNode<T>*tempptr = this->Tail;
		this->Tail = tempptr->pre;
		if (this->Tail == nullptr)
		{
			this->Head = nullptr;
		}
		else
		{
			(this->Tail)->next = nullptr;
		}
		delete tempptr;
	}
}
template<class T>
void DList<T>::Remove(const DNode<T> * const ptr)
{
	if (ptr->next == nullptr)
	{
		RemoveLast();
	}
	else if (ptr->pre == nullptr)
	{
		RemoveFirst();
	}
	else
	{
		DNode<T> *before = ptr->pre;
		DNode<T> *after = ptr->next;
		before->next = ptr->next;
		after->pre = ptr->pre;
		delete ptr;
	}
}
template <class T>
void DList<T>::Clear()
{
	while (!(this->isEmpty()))
	{
		this->RemoveLast();
	}
}
template <class T>
DNode<T> * DList<T>::GetFirstElement() const
{
	return this->Head;
}
template <class T>
DNode<T> * DList<T>::GetLastElement() const
{
	return this->Tail;
}
template <class T>
T* FindIndex(const DList<T*>&list, const int &index)
{
	int i = 0;
	DNode <T*>* curptr = list.Head;
	while (curptr!=nullptr)
	{
		if (!((curptr->data)->Deleted())) i++;
		if (i == index) break;
		curptr = curptr->next;
	}
	return curptr->data;
}
template <class T, typename K>
T* FindFirstMatch(const DList <T*> &list, const K &data_lookup, K(T::*ptr)() const)
{
	DNode<T*> *curptr = list.Head;
	while (curptr != nullptr && ( ((curptr->data)->Deleted)() || ((curptr->data)->*ptr)() != data_lookup ) )
	{
		curptr = curptr->next;
	}
	if (curptr == nullptr) return nullptr;
	else return curptr->data;
}
template <class T, typename K>
DList< T* >* FindAll(const DList <T*> &list, const K &data_lookup, K(T::*ptr)() const, int& cnt)
{
	DList < T* >  *ptrAnsList = new DList < T* > ;
	DNode < T* >  *curptr = list.Head;
	while (curptr != nullptr)
	{
		if (!((curptr->data)->Deleted()) &&  ((curptr->data)->*ptr)() == data_lookup)
		{
			ptrAnsList->InsertLast(new DNode < T* >(curptr->data));
			cnt++;
		}
		curptr = curptr->next;
	}
	return ptrAnsList;
}
template <class T>
void SwapNode(DNode<T*>* a, DNode<T*>* b)
{
	T* temp = a->data;
	a->data = b->data;
	b->data = temp;
}
template <class T, typename K>
DNode<T*>* Partition(DNode<T*>* Left, DNode<T*>* Right, K(T::* ptr)() const, int sign)
{
	DNode<T*>* pivot = Right;
	K pivot_Data = ((pivot->data)->*ptr)();
	DNode<T*>* cur = Left;
	DNode<T*>* bound = nullptr;
	while (cur != Right)
	{
		if (((cur->data)->*ptr)() * sign <= pivot_Data * sign)
		{
			if (bound != nullptr)
				bound = bound->next;
			else bound = Left;
			SwapNode(bound, cur);
		}
		cur = cur->next;
	}
	if (bound == nullptr)
	{
		SwapNode(Left, pivot);
		return Left;
	}
	else
	{
		SwapNode(bound->next, pivot);
		return bound->next;
	}
}
template <class T, typename K>
void QuickSort(DNode<T*> *Left, DNode<T*> *Right, K(T::*ptr)() const, int sign)
{
	if (Left == nullptr || Right == nullptr || Left == Right || Left->pre == Right || Right->next == Left) return;
	else
	{
		DNode<T*>* p = Partition(Left, Right, ptr,sign);
		QuickSort(Left, p->pre, ptr,sign);
		QuickSort(p->next, Right, ptr,sign);
	}
}
template<class T>
void ReleaseAll(DList<T*>&List)
{
	while (!List.isEmpty())
	{
		if (List.Head != nullptr)
		{
			DNode<T*>*tempptr = List.Tail;
			List.Tail = tempptr->pre;
			if (List.Tail == nullptr)
			{
				List.Head = nullptr;
			}
			else
			{
				(List.Tail)->next = nullptr;
			}
			delete tempptr->data;
			delete tempptr;
		}
	}
}