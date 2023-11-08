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
		void InsertFirst( DNode<T> * const);
		void InsertLast( DNode<T> * const);
		void RemoveFirst();
		void RemoveLast();
		void Remove(const DNode<T> * const);
		bool isEmpty() const;
		DNode<T>* GetFirstElement() const;
		DNode<T>* GetLastElement() const;
		DNode<T>* FindIndex(int) const;
		template <class T, typename K>
		friend DNode<T> * FindFirstMatch(const DList <T> &,const K&, K(T::*)() const);
		template <class T, typename K>
		friend DList< DNode<T>* > * FindAll(const DList <T> &, const K&, K(T::*)() const, int&);
	private:
		DNode<T> *Head;
		DNode<T> *Tail;
};
#endif