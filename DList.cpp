#include <iostream>
#include "DList.h"
using namespace std;
template<class T>
DList<T>::DList()
	:Head(NULL), Tail(NULL)
{}
template<class T>
DList<T>::~DList()
{}
template<class T>
bool DList<T>::isEmpty() const
{
	return this->Head == NULL;
}
template <class T>
void DList<T>::Release()
{
	while (!isEmpty())
	{
		RemoveLast();
	}
}
template <class T>
void DList<T>::InsertFirst(const T& data)
{
	DNode<T> *Newptr = new DNode<T>(data);
	Newptr->next = this->Head;
	if (this->Tail == NULL)
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
void DList<T>::InsertLast(const T& data)
{
	DNode<T> *Newptr = new DNode<T>(data);
	Newptr->pre = this->Tail;
	if (this->Head == NULL)
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
	if (this->Head != NULL)
	{
		DNode<T>*tempptr = this->Head;
		this->Head = tempptr->next;
		if (this->Head == NULL)
		{
			this->Tail = NULL;
		}
		else
		{
			(this->Head)->pre = NULL;
		}
		delete tempptr;
	}
}
template<class T>
void DList<T>::RemoveLast()
{
	if (this->Head != NULL)
	{
		DNode<T>*tempptr = this->Tail;
		this->Tail = tempptr->pre;
		if (this->Tail == NULL)
		{
			this->Head = NULL;
		}
		else
		{
			(this->Tail)->next = NULL;
		}
		delete tempptr;
	}
}
template<class T>
void DList<T>::Remove(const DNode<T> *ptr)
{
	if (ptr->next == NULL)
	{
		RemoveLast();
	}
	else if (ptr->pre == NULL)
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
//template<class T> 
//template<class K>
//DNode<T> * DList<T>::Find(K data, void (T::*ptr)())
//{
//	DNode<T> *curptr = this->Head;
//	while (curptr == NULL && (curptr->data).*ptr() != data)
//	{
//		curptr = curptr->next;
//	}
//	return curptr;
//}
template<class K>
ostream& operator<< (ostream& out, const DList<K> & l)
{
	if (l.Head != NULL)
	{
		DNode<K> * curptr = l.Head;
		while (curptr != NULL)
		{
			out << curptr->data << '\n';
			curptr = curptr->next;
		}
	}
	return out;
}