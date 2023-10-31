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
		void InsertFirst(const T&);
		void InsertLast(const T&);
		void RemoveFirst();
		void RemoveLast();
		void Remove(const DNode<T> * const);
		bool isEmpty() const;
		void Release();
		//template <typename K>
		/*DNode<T> * Find(K, void (T::*)());*/
	private:
		DNode<T> *Head;
		DNode<T> *Tail;
};
#endif