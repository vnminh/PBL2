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
		void Clear();
		DNode<T>* GetFirstElement() const;
		DNode<T>* GetLastElement() const;
		template <typename T>
		friend T* FindIndex(const DList<T*> &, const int&);
		template <class T, typename K>
		friend T* FindFirstMatch(const DList <T*> &, const K&, K(T::*)() const);
		template <class T, typename K>
		friend DList< T* > * FindAll(const DList <T*> &, const K&, K(T::*)() const, int&);
		template <class T, typename K>
		friend void QuickSort(DNode<T*>*, DNode<T*>*, K(T::*)() const, int);
		template <class T, typename K>
		friend DNode<T*>* Partition(DNode<T*>*, DNode<T*>*, K(T::*)() const, int);
		template <class T>
		friend void SwapNode(DNode<T*>*, DNode<T*>*);
		template<class T>
		friend void ReleaseAll(DList<T*>&);
	private:
		DNode<T> *Head;
		DNode<T> *Tail;
};
#endif