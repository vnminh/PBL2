#ifndef DLIST_H
#define DLIST_H
#include <iostream>
#include "DNode.h"
template <class T>
class DList
{
public:
	DList();
	~DList();
	void InsertFirst(DNode<T> *const);
	void InsertLast(DNode<T> *const);
	void RemoveFirst();
	void RemoveLast();
	void Remove(const DNode<T> *const);
	bool isEmpty() const;
	void Clear();
	DNode<T> *GetFirstElement() const;
	DNode<T> *GetLastElement() const;
	template <class C>
	friend C *FindIndex(const DList<C *> &, const int &);
	template <class C, typename K>
	friend C *FindFirstMatch(const DList<C *> &, const K &, K (C::*)() const);
	template <class C, typename K>
	friend DList<C *> *FindAll(const DList<C *> &, const K &, K (C::*)() const, int &);
	template <class C, typename K>
	friend void QuickSort(DNode<C *> *, DNode<C *> *, K (C::*)() const, int);
	template <class C, typename K>
	friend DNode<C *> *Partition(DNode<C *> *, DNode<C *> *, K (C::*)() const, int);
	template <class C>
	friend void SwapNode(DNode<C *> *, DNode<C *> *);
	template <class C>
	friend void ReleaseAll(DList<C *> &);

private:
	DNode<T> *Head;
	DNode<T> *Tail;
};
#endif