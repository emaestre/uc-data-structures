#ifndef _DOM_TREE_H_
#define _DOM_TREE_H_

#include "Lista.hpp"
#include "Node.hpp"

class DOM_Tree
{
	protected:
		
		Node *document;

		void Destruir(Node*);
		Node* Copiar(Node*);
		void NodosH(Node*, Lista<Node* >&);
		Node* getElementByID(string, Node*, Node*);
	
	public:
		
		DOM_Tree(void);
		DOM_Tree(Element, list<Node* >);
		DOM_Tree(const DOM_Tree&);
		bool EsVacio(void);
		Element ObtElement(void);
		DOM_Tree ObtFirstChild(void);
		Node* childNode(int);
		void appendChild(int, DOM_Tree);
		void appendChild(DOM_Tree);
		void removeChild(int);
		void replaceChild(int, DOM_Tree);
		Node* getElementByID(string);
		DOM_Tree& operator= (const DOM_Tree&);
		~DOM_Tree(void);
};
 
/* ------------------------------------------------------ */

DOM_Tree::DOM_Tree(void)
{
	document = NULL;
}

DOM_Tree::DOM_Tree(Element e, list<Node* > lista)
{
	Node *aux;

	document->setElement(e);
	document->setFirstChild(NULL);
	document->setNextSibling(NULL);

	if(lista.empty())
	{
		document->setFirstChild(Copiar(lista.front()));
		lista.pop_front();
		aux = document->firstChild();
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
	document = Copiar(a.document);
}
 
bool DOM_Tree::EsVacio(void)
{
	return document == NULL;
}

Element DOM_Tree::ObtElement(void)
{
	return document->element();
}

DOM_Tree DOM_Tree::ObtFirstChild(void)
{
	DOM_Tree A;
	
	A.document = document->firstChild();
	return A;
}
    
Node* DOM_Tree::Copiar(Node *r)
{
	Node *aux = NULL;
	
	if(r != NULL)
	{
		aux = new Node;
		aux->setElement(r->element());
		aux->setFirstChild(Copiar(r->firstChild()));
		aux->setNextSibling(Copiar(r->nextSibling()));
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

void DOM_Tree::NodosH(Node *a, Lista<Node* > &l)
{
	if(a != NULL)
	{
		if(a->firstChild() == NULL and a->nextSibling() == NULL)
			l.insertar(1, a);
		else
		{
			NodosH(a->firstChild(), l);
			NodosH(a->nextSibling(), l);
		}
	}
}

Node* DOM_Tree::childNode(int p)
{
	Node *child;
	Lista<Node* > hijos;

	NodosH(document, hijos);
	hijos.invertir();
	child = hijos.consultar(p);

	return child;
}

void DOM_Tree::appendChild(int p, DOM_Tree child)
{
	Node *aux, *aux1;
	int i;

	if(p == 1)
	{
		if(document->firstChild() == NULL)
		{
			document->setFirstChild(Copiar(child.document));
		}
		else
		{
			aux = document->firstChild();
			document->setFirstChild(Copiar(child.document));
			document->firstChild()->setNextSibling(aux);
		}
	}
	else
	{
		aux = document->firstChild();
		for(i = 2; i <= (p - 1); i++)
		{
			aux = aux->nextSibling();
		}
		aux1 = aux->nextSibling();
		aux->setNextSibling(Copiar(child.document));
		aux->nextSibling()->setNextSibling(aux1);
	}
}

void DOM_Tree::appendChild(DOM_Tree child)
{
	Node *aux;

	aux = document->firstChild();
	while(aux->nextSibling() != NULL)
	{
		aux = aux->nextSibling();
	}
	aux->setNextSibling(Copiar(child.document));	
}

void DOM_Tree::removeChild(int p)
{
	Node *aux, *elim;
	int i;

	if(p == 1)
	{
		elim = document->firstChild();
		document->setFirstChild(document->firstChild()->nextSibling());
	}
	else
	{
		aux = document->firstChild();
		for(i = 2; i <= (p - 1); i++)
		{
			aux = aux->nextSibling();
		}
		elim = aux->nextSibling();
		aux->setNextSibling(aux->nextSibling()->nextSibling());
	}
	elim->setNextSibling(NULL);
	Destruir(elim);
}

void DOM_Tree::replaceChild(int p, DOM_Tree child)
{
	Node *aux, *aux1;
	int i;

	if(p == 1)
	{
		aux = document->firstChild();
		aux1 = aux->nextSibling();
		document->setFirstChild(Copiar(child.document));
		document->firstChild()->setNextSibling(aux1);
		Destruir(aux);
	}
	else
	{
		aux = document->firstChild();
		for(i = 2; i <= (p - 1); i++)
		{
			aux = aux->nextSibling();
		}
		aux1 = aux->nextSibling();
		aux->setNextSibling(Copiar(child.document));
		aux->nextSibling()->setNextSibling(aux1->nextSibling());
		Destruir(aux1);
	}
}

Node* DOM_Tree::getElementByID(string ID)
{
	Node *sub = NULL;

	getElementByID(ID, NULL, sub);
	return sub;
}

Node* DOM_Tree::getElementByID(string ID, Node *aux, Node *sub)
{
	aux = document;

	if(aux->element().getInnerHTML() == ID)
		sub = Copiar(aux);
	
	getElementByID(ID, aux->firstChild(), sub);
	getElementByID(ID, aux->nextSibling(), sub);

}
   
DOM_Tree& DOM_Tree::operator= (const DOM_Tree &A)
{
	this->document = Copiar(A.document);
	return *this;
}

DOM_Tree::~DOM_Tree(void)
{
	Destruir(document);
}

#endif
