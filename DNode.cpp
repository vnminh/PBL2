#include "DNode.h"
template<class T>
DNode<T>::DNode(const T & data)
	:data(data), next(nullptr), pre(nullptr)
{}
template<class T>
DNode<T>::~DNode()
{}

