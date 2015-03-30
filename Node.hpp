#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include "Element.hpp"

using namespace std;
 
class Node
{
	private:
		
		Element e;
		Node *firstChild;
		Node *nextSibling;
	
	public:
		
		Node(void);
		Node(Element,Node*,Node*);
		Node(const Node&);
		Element element(void);
		Node* firstChild(void);
		Node* nextSibling(void);
		void setElement(Element);
		void setFirstChild(Node*);
		void setNextSibling(Node*);
};

/* ---------------------------------------------- */
 
Node::Node(void)
{
	firstChild = NULL;
	nextSibling = NULL;
}
 
Node::Node(Element aux, Node *hi, Node *hd)
{
	e = aux;
	firstChild = hi;
	nextSibling = hd;
}
 
Node::Node(const Node &a)
{
	e = a.e;
	firstChild = a.firstChild;
	nextSibling = a.nextSibling;
}
 
Element Node::element(void)
{
	return e;
}

Node* Node::firstChild(void)
{
	return firstChild;
}
 
Node* Node::nextSibling(void)
{
	return nextSibling;
}

void Node::setElement(Element aux)
{
	e = aux;
}
 
void Node::setFirstChild(Node *hi)
{
	firstChild = hi;
}

 
void Node::setNextSibling(Node *hd)
{
	nextSibling = hd;
}

Node& Node::operator= (const Node &nodo)
{
	this->e = nodo.e;
	this->firstChild = nodo.firstChild;
	this->nextSibling = nodo.nextSibling;	
	return *this;
}

#endif
