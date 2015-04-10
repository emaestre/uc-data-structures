#ifndef _NODE_H_
#define _NODE_H_

#include "Element.hpp"

using namespace std;
 
class Node
{
	private:
		
		Element e;
		Node *FirstChild;
		Node *NextSibling;
	
	public:
		
		// Constructores
		Node(void);
		Node(Element);
		Node(Element,Node*,Node*);
		// Constructor copia
		Node(const Node&);
		// Metodos observadores
		Element element(void);
		Node* firstChild(void);
		Node* nextSibling(void);
		// Metodos modificadores
		void setElement(Element);
		void setFirstChild(Node*);
		void setNextSibling(Node*);
		// Sobrecarga
		void operator= (const Node&);
};

/* ---------------------------------------------- */
 
Node::Node(void)
{
	FirstChild = NULL;
	NextSibling = NULL;
}

Node::Node(Element aux)
{
	e = aux;
}

Node::Node(Element aux, Node *hi, Node *hd)
{
	e = aux;
	FirstChild = hi;
	NextSibling = hd;
}
 
Node::Node(const Node &a)
{
	e = a.e;
	FirstChild = a.FirstChild;
	NextSibling = a.NextSibling;
}
 
Element Node::element(void)
{
	return e;
}

Node* Node::firstChild(void)
{
	return FirstChild;
}
 
Node* Node::nextSibling(void)
{
	return NextSibling;
}

void Node::setElement(Element aux)
{
	e = aux;
}
 
void Node::setFirstChild(Node *hi)
{
	FirstChild = hi;
}

 
void Node::setNextSibling(Node *hd)
{
	NextSibling = hd;
}

void Node::operator= (const Node &nodo)
{
	this->e = nodo.e;
	this->FirstChild = nodo.FirstChild;
	this->NextSibling = nodo.NextSibling;	
}

#endif
