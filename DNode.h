#ifndef DNODE_H
#define DNODE_H
template<class T>
class DNode
{
	public:
		DNode(const T&);
		~DNode();
		T data;
		DNode *next;
		DNode *pre;
};
#endif