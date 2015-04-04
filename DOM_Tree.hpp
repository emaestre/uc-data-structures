#ifndef _DOM_TREE_H_
#define _DOM_TREE_H_

#include "Lista.hpp"
#include "Cola.hpp"
#include "Node.hpp"
 
class DOM_Tree
{
	protected:
		
		Node *raiz;

		void Destruir(Node*);
		Node* Copiar(Node*);
	
	public:
		
		DOM_Tree(void);
		DOM_Tree(Element, list<Node* >);
		DOM_Tree(const DOM_Tree &a)
		bool EsVacio(void);
		Element Raiz(void);
		DOM_Tree Obt_hijiz(void);
		DOM_Tree Obt_herde(void);
		DOM_Tree& operator=(const DOM_Tree&);
		~DOM_Tree(void);
};
 
/* ------------------------------------------------------ */

DOM_Tree::DOM_Tree(void)
{
	raiz = NULL;
}

DOM_Tree::DOM_Tree(Element e, list<Node* > lista)
{
	Node *aux;

	raiz->setElement(e);
	raiz->setFirstChild(NULL);
	raiz->setNextSibling(NULL);

	if(lista.empty())
	{
		raiz->setFirstChild(Copiar(lista.front()));
		lista.pop_front();
		aux = raiz->firstChild();
		while(!lista.empty())
		{
			aux->setNextSibling(Copiar(lista.front()));
			lista.pop_front();
			aux = aux->nextSibling();
		}
	}
}

DOM_Tree::DOM_Tree(const DOM_Tree &a)
{
	raiz = Copiar(a.raiz);
}
 
bool DOM_Tree::EsVacio(void)
{
	return raiz == NULL;
}
 
Element DOM_Tree::Raiz(void)
{
	return raiz->element();
}
 
DOM_Tree DOM_Tree::Obt_hijiz(void)
{
	DOM_Tree A;
	
	A.raiz = raiz->firstChild();
	return A;
}
 
DOM_Tree DOM_Tree::Obt_herde(void)
{
	DOM_Tree A;
	
	A.raiz = raiz->nextSibling();
	return A;
}
   
Node* DOM_Tree::Copiar(Node *r)
{
	Node *aux = NULL;
	
	if(r != NULL)
	{
		aux = new Node;
		aux->element(r->element());
		aux->firstChild(Copiar(r->firstChild()));
		aux->nextSibling(Copiar(r->nextSibling()));
	}
	return aux;
} 
 
void DOM_Tree::Destruir(Node *r)
{
	if(r != NULL)
	{
		Destruir(r->firstChild());
		Destruir(r->nextSibling());
		delete r;
	}
}
  
DOM_Tree& DOM_Tree::operator=(const DOM_Tree &A)
{
	raiz = Copiar(A.raiz);
	return *this;
}
 
DOM_Tree::~DOM_Tree(void)
{
	Destruir(raiz);
}

#endif
