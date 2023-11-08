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
DNode<T>* DList<T>::FindIndex(int index) const
{
	int i = 1;
	DNode <T>* curptr = this->Head;
	while (i != index)
	{
		i++;
		curptr = curptr->next;
	}
	return curptr;
}
template <class T, typename K>
DNode<T>* FindFirstMatch(const DList <T> &list, const K &data_lookup, K(T::*ptr)() const)
{
	DNode<T> *curptr = list.Head;
	while (curptr != nullptr && ((curptr->data).*ptr)() != data_lookup)
	{
		curptr = curptr->next;
	}
	return curptr;
}
template <class T, typename K>
DList< DNode<T> * >* FindAll(const DList <T> &list, const K &data_lookup, K(T::*ptr)() const, int& cnt)
{
	static DList<DNode<T>*> AnsList;
	DNode<T> * curptr = list.Head;
	while (curptr != nullptr)
	{
		if (((curptr->data).*ptr)() == data_lookup)
		{
			AnsList.InsertLast(new DNode<DNode<T>*> (curptr));
			cnt++;
		}
		curptr = curptr->next;
	}
	return &AnsList;
}