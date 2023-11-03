#ifndef DLIST_H
#define DLIST_H
#include <iostream>
#include "DNode.h"
template <class T>
class DList
{
	template<class K>
	friend std::ostream& operator<< (std::ostream& out, const DList<K> &l);
	public:
		DList();
		~DList();
		void InsertFirst(const T);
		void InsertLast(const T);
		void RemoveFirst();
		void RemoveLast();
		void Remove(const DNode<T> * const);
		bool isEmpty() const;
		void Release();
		DNode<T> *GetFirstElement() const;
		DNode<T> *GetLastElement() const;
		DNode<T> * FindIndex(int) const;
		template <typename K>
		DNode<T> * FindFirstMatch(const K&, K (T::*)() const) const;
		template <typename K>
		DList<T> * FindAll(const K&, K (T::*)() const, int&) const;
	private:
		DNode<T> *Head;
		DNode<T> *Tail;
};
#endif