#ifndef _DOM_TREE_H_
#define _DOM_TREE_H_

#include "Lista.hpp"
#include "Node.hpp"
#include <stack>

using namespace std;

class DOM_Tree
{
	private:
		
		// Atributo
		Node *document;

		// Metodos privados
		void Destruir(Node*);
		Node* Copiar(Node*);
		void BuscarID(DOM_Tree&, string, Node*);
        static void ImprimirArbol(Node*, int);
        static void ImprimirAtributos(list<string>);
        static void Identar(int);
        DOM_Tree Convertir(string);
	
	public:

		// Constructores
		DOM_Tree(void);
		DOM_Tree(Element);
		DOM_Tree(Element, list<Node* >);
		DOM_Tree(const DOM_Tree&);
		// Metodos publicos
		bool EsVacio(void);
		Element ObtElement(void);
		DOM_Tree ObtFirstChild(void);
		DOM_Tree childNode(int);
		void removeChild(int);
		DOM_Tree getElementByID(string);
		// Metodos sobrecargados
		void appendChild(int, DOM_Tree);
		void appendChild(DOM_Tree);
		void appendChild(int, string);
		void appendChild(string);
		void replaceChild(int, DOM_Tree);
		void replaceChild(int, string);
		// Sobrecarga de operadores
        void operator= (const DOM_Tree&);
        friend ostream& operator<< (ostream &o, const DOM_Tree &h);
        // Destructor
		~DOM_Tree(void);
};
 
/* ------------------------------------------------------ */

// Constructores

DOM_Tree::DOM_Tree(void)
{
	document = NULL;
}

DOM_Tree::DOM_Tree(Element e)
{ 
	document = new Node(e); 
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

// Metodos privados

void DOM_Tree::Destruir(Node *r)
{
	if(r != NULL)
	{
		Destruir(r->firstChild());
		Destruir(r->nextSibling());
		delete r;
	}
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

void DOM_Tree::BuscarID(DOM_Tree &h, string id, Node *p)
{
    if(p != NULL)
    {
        if((p->element()).getTagName() == id)
            h.document = Copiar(p);

        BuscarID(h, id, p->firstChild());
        BuscarID(h, id, p->nextSibling());
    }
}

void DOM_Tree::ImprimirArbol(Node *document, int esp)
{
    Node *aux;

    if(document != NULL)
    {
    	if(document->firstChild() != NULL)
	    {
	    	Identar(esp);
	        cout << "<" << document->element().getTagName();
	        ImprimirAtributos(document->element().attributeList());
	        cout << ">" << endl;
	        ImprimirArbol(document->firstChild(), esp+1);
	        Identar(esp);
	        cout << "</" << document->element().getTagName() << ">" << endl;
	    }
	    else
	    {
	        Identar(esp);
	        cout << "<" << document->element().getTagName();
	        ImprimirAtributos(document->element().attributeList());
	        cout << ">";
	        cout << document->element().getInnerHTML() << "</" << document->element().getTagName() << ">" << endl;
		}
	    ImprimirArbol(document->nextSibling(), esp);
    }

}

void DOM_Tree::ImprimirAtributos(list<string> atributos)
{
    while(!atributos.empty())
    {
        cout << " " << atributos.front();
        atributos.pop_front();
    }
}


void DOM_Tree::Identar(int cont)
{
    int i;

    for(i = 0; i < cont; i++)
    {
    	cout << "     ";
    }
}

DOM_Tree DOM_Tree::Convertir(string h)
{
    int i, j, k;
    Element e;
    DOM_Tree arb, aux;
    string name, inn, tag, atr;
    list<string> atrb;
    stack<Element> a, b;
    stack<string> inners;

    while(!h.empty())
    {
        if(h[0] == '<')
        {
            j = h.find('>');
            if(h[1] != '/')
            {
                name = h.substr(1, j-1);
                if(name.find(' ') != -1)
                {
                    i = name.find(' ');
                    tag = name.substr(0, i);
                    name.erase(0, i+1);
                    while(!name.empty())
                    {
                        if(name.find(' ') != -1)
                        {
                            i = name.find(' ');
                            atr = name.substr(0, i);
                            atrb.push_back(atr);
                            name.erase(0, i+1);
                        }
                        else
                        {
                            atrb.push_back(name);
                            name.clear();
                        }
                    }
                }
                else
                    tag=name;
                
                e = Element(tag, atrb, inn);
                b.push(e);
                h.erase(0, j+1);
            }
            else
            {
                e = b.top();
                b.pop();
                e.setInnerHTML(inners.top());
                a.push(e);
                inners.pop();
                if(h[j+1] != '<')
                {
                    h.erase(0, j+1);
                    if(!h.empty())
                    {
                        k = h.find('<');
                        inn = inners.top();
                        inn += h.substr(0, k);
                        h.erase(0, k);
                        inners.pop();
                        inners.push(inn);
                    }
                }
                else
                    h.erase(0, j+1);
            }
        }
        else
        {
            k = h.find('<');
            inn = h.substr(0, k);
            h.erase(0, k);
            inners.push(inn);
        }
    }
    while(!a.empty())
    {
        aux = DOM_Tree(a.top());
        arb.appendChild(aux);
        a.pop();
    }
    return (arb);
}

// Metodos publicos

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

DOM_Tree DOM_Tree::childNode(int pos)
{
    DOM_Tree arbol;
	Node *aux1;
    int i;

    if(document != NULL)
    {
        if(pos != 0)
        {
            if(pos == 1)
            {
               aux1 = document->firstChild();
               aux1->setNextSibling(NULL);
               arbol.document = Copiar(aux1);
               Destruir(aux1);
            }
            else
            {
                aux1 = document->firstChild();
                for(i = 2; i <= pos; i++)
                    aux1 = aux1->nextSibling();
               
                if(aux1 != NULL)
                {
                    aux1->setNextSibling(NULL);
                    arbol.document = Copiar(aux1);
                    Destruir(aux1);
                }
                else
                    cout << "Error: pos invalida" << endl;
            }
        }
        else
            cout << "Error: pos invalida" << endl;
    }
    else
        cout << "Error: arbol vacio" << endl;

    return (arbol);
}

void DOM_Tree::removeChild(int p)
{
	Node *aux, *elim;
	int i;

	if(document != NULL)
	{	
		if(p != 0)
		{
			if(p == 1)
			{
				elim = document->firstChild();
				document->setFirstChild(document->firstChild()->nextSibling());
				elim->setNextSibling(NULL);
				Destruir(elim);
			}
			else
			{
				aux = document->firstChild();
				for(i = 2; i <= (p - 1); i++)
				{
					aux = aux->nextSibling();
				}
				if(aux != NULL)
				{
					elim = aux->nextSibling();
					if (elim != NULL)
					{
						aux->setNextSibling(aux->nextSibling()->nextSibling());
						elim->setNextSibling(NULL);
						Destruir(elim);
					}
					else
						cout << "Error: pos invalida" << endl;
				}
				else
					cout << "Error: pos invalida" << endl;
			}
			
		}
		else
			cout << "Error: pos invalida" << endl;	
	}
	else
		cout << "Error: arbol vacio" << endl;
}

DOM_Tree DOM_Tree::getElementByID(string id)
{
    DOM_Tree arbol;

    BuscarID(arbol, id, document);
    return (arbol);
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

void DOM_Tree::appendChild(int pos, string h)
{
    DOM_Tree a;
    a = Convertir(h);
    appendChild(pos, a);
}

void DOM_Tree::appendChild(string h)
{
    DOM_Tree a;
    a = Convertir(h);
    appendChild(a);
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

void DOM_Tree::replaceChild(int pos, string h)
{
    DOM_Tree arb;

    arb = Convertir(h);
    replaceChild(pos, arb);
}

// Sobrecarga de operadores

void DOM_Tree::operator= (const DOM_Tree &h)
{
	this->document = Copiar(h.document);
}

ostream& operator<< (ostream &o, const DOM_Tree &h)
{
    Node *aux;

    if(h.document != NULL)
    {
        o << "<" << h.document->element().getTagName() << ">" << endl;
        aux = h.document->firstChild();
		DOM_Tree::ImprimirArbol(aux, 0);
    }

    return o;
}

// Destructor 

DOM_Tree::~DOM_Tree(void)
{
	Destruir(document);
}

#endif
