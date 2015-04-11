#ifndef _DOM_TREE_H_
#define _DOM_TREE_H_

#include "Node.hpp"
#include <stack>
#include <vector>

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
      	static void ImprimirHastaTag(string&, string&, string, int);
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
	   DOM_Tree& operator= (const DOM_Tree&);
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
    Node* hermano, *hijo;
    string tag, inner;

    if(document != NULL)
    {

        hermano = NULL;
        hijo = NULL;
        inner = document->element().getInnerHTML();
        hermano=document->firstChild();
        hijo= document->firstChild();



            if( document->firstChild() != NULL)
            {
                    Identar(esp);
                    cout << "<" << document->element().getTagName();
                    ImprimirAtributos(document->element().attributeList());
                    cout << ">" << endl;


                    while(!inner.empty())
                    {
                        ImprimirHastaTag(inner, tag, document->element().getTagName(), esp); /***/
                        cout << endl;

                        if(hijo!=NULL)
                        {
                            ImprimirArbol(hijo, esp+1);
                            hijo=hijo->firstChild();
                        }
                        ImprimirHastaTag(inner, tag, document->element().getTagName(), esp); /***/
                        cout << endl;
                        if( hermano->nextSibling() != NULL)
                        {
                            ImprimirArbol(hermano->nextSibling(), esp+1);
                            hermano = hermano->nextSibling();
                        }

                    }
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
        cout << "    ";
    }
}

void DOM_Tree::ImprimirHastaTag(string &h, string &tag, string tagdocument, int esp)
{
    string tagaux;
    unsigned int error = -1, i, j;

    i = h.find('<');
    j = h.find('>');
    if(i != error and j != error)
    {
        Identar(esp+1);
        cout << h.substr(0, i);
        tag = h.substr(i+1, j-i-1);
        h.erase(0, j+1);
        if( ('/' + tag)!= tagdocument)
        {
            tagaux = '/' + tag;
            i= h.find(tagaux);
            h.erase(0, i+1+tagaux.length());
        }

    }
    else
    {
        Identar(esp+1);
        cout << h;
        h.erase();
    }
}

DOM_Tree DOM_Tree::Convertir(string h)
{
    unsigned int error = -1, j, k, i;
    Element e;
    DOM_Tree aux;
    string n1, n2, inn, tag, atr;
    list<string> atrb;
    vector<DOM_Tree> a;


    while(!h.empty())
    {
        atrb = list<string>();
        k = h.find('<');
        j = h.find('>');
        if(k != error and j != error)
        {
            n1 = h.substr(k+1, j-k-1);
            if(n1.find(' ') != error)
            {
                i = n1.find(' ');
                tag = n1.substr(0, i);
                n1.erase(0, i+1);
                while(!n1.empty())
                {
                    if(n1.find(' ') != error)
                    {
                        i = n1.find(' ');
                        atr = n1.substr(0, i);
                        atrb.push_back(atr);
                        n1.erase(0, i+1);
                    }
                    else
                    {
                        atrb.push_back(n1);
                        n1.clear();
                    }
                }
                n1 = tag;
            }
            n2 = "</" + n1 + '>';
            h.erase(0, j+1);
            k = h.find(n2);
            inn = h.substr(0, k);
            h.erase(k, n2.size());
        }
        else
        {
            inn = h;
            h.clear();
        }

        e = Element(n1, atrb, inn);
        if(!e.attributeList().empty())
            cout << e.attributeList().front() << endl;
        
        aux = DOM_Tree(e);
        a.insert(a.begin(), aux);
    }
    a.erase(a.begin());

    while(!a.empty())
    {
        aux = a[0];
        a.erase(a.begin()+0);
        if(!a.empty())
        {
            i = 0;
            while(a[i].document->element().getInnerHTML().find(aux.document->element().getInnerHTML())==error)
                i++;
            
            a[i].appendChild(1, aux);
        }
    }
    return (aux);
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

DOM_Tree& DOM_Tree::operator= (const DOM_Tree &h)
{
	this->document = Copiar(h.document);
	return *this;
}

ostream& operator<< (ostream &o, const DOM_Tree &h)
{
	Node *aux;

    if(h.document != NULL)
    {
  		if(h.document->element().getTagName() == "html");
        o << "<" << "!document type" << ">" << endl;
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
