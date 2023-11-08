#ifndef DNODE_H
#define DNODE_H
template<typename T>
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