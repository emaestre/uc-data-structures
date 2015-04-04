#ifndef _LISTA_H_
#define _LISTA_H_

#include "Nodo.hpp"
#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

template  <class T> 
class Lista
{
	private:
		
		int longitud;
		Nodo<T> *prim;

	public:	

		Lista(void);
		Lista(const Lista<T>&);
		bool es_vacia(void) const;
		int obtlongitud(void) const;
		int acumular(int) const;
		int localizar(T) const;
		T consultar(int) const;
		void OcurrMayor(int&,int&);
		Lista<T> ordenar(void);		
		Lista<T> unir(Lista<T>);		
		void insertar(int,T);
		void eliminar(int);
		void modificar(T,int);
		void invertir(void);
		void separar(Lista<T>&,Lista<T>&);
		void separar(Lista<T>&,int);
		void mezclar(Lista<T>&,Lista<T>&);
		void vaciar(void);	        
		Lista<T> compactar(Lista<T>&, Lista<T>&);
		void descompactar(Lista<int>&,Lista<int>&);
		bool esta(T);
		Lista<T>& operator= (const Lista<T>&);
		bool operator== (const Lista<T>) const;
		bool operator!= (const Lista<T>) const;
		template<class A> friend ostream& operator<< (ostream&,const Lista<A>&);	
		template<class B> friend istream& operator>> (istream&,Lista<B>&);		
		~Lista(void);

	private:

		void copiar(const Lista<T>&);
		Nodo<T>* obtprim(void) const;
		void modificarprim(Nodo<T>*);
		void modificarlongitud(int);
};

template <class T> 
Lista<T>::Lista(void)
{
	//Inicializacion de los atributos
	longitud = 0;
	prim = NULL;
}

template <class T> 
Lista<T>::Lista(const Lista<T> &l)
{
	//LLamada al metodo para copiar una lista en otra
	copiar(l);
}

template <class T> 
bool Lista<T>::es_vacia(void) const
{
	//Retornar la pregunta para saber si la lista es vacia
	return prim == NULL;
}

template <class T> 
int Lista<T>::obtlongitud(void) const
{
	//Retorno de la longitud
	return longitud;
}

template <class T> 
int Lista<T>::acumular(int pos) const
{
	Nodo<T> *aux;
	int acum,i;

	aux = prim;
	acum = 0;

	if(aux != NULL)
	{
		for( i = 1; i <= pos; i++)
		{
			acum = acum + aux->consultarinfo();
			aux = aux->consultarprox();
		}
	}

	return acum;
}

//Desarrollo de el metodo consultor localizar
template <class T> 
int Lista<T>::localizar(T e) const
{	
	//Variables locales necesarias para poder localizar un elemento
	Nodo<T> *aux;
	int i;
	
	//Se busca desde el inicio de la lista
	aux = prim;
	
	i = 1;
	//Ciclo para recorrer la lista y buscar nodo por nodo el elemento soliscitado
	while(aux != NULL and aux->consultarinfo() != e)
	{
		aux = aux->consultarprox();
		i++;
	}
	
	//Consicional para saber si se encontro o no el elemento
	if(aux == NULL)
		i = -1;

	return i;
}

template <class T> 
T Lista<T>::consultar(int pos) const
{
	Nodo<T> *aux;
	T dato;	
	int i;

	if(pos > 0 and pos <= longitud)
	{		
		aux = prim;
		for(i = 1; i < pos; i++)
			aux = aux->consultarprox();
		dato = aux->consultarinfo();	
	}
		
	return dato; 	
}

template <class T>  
Lista<T> Lista<T>::unir(Lista<T> l)
{
	Nodo<T> *aux;
	Lista<T> l1;

	aux = prim;

	if(aux != NULL)
	{
		while(aux->consultarprox() != NULL)
			aux = aux->consultarprox();
		aux->modificarprox(l.prim);
	}

	l1.prim = prim;
	l1.longitud = l.longitud + longitud; 

	return l1;
}

template <class T>  
Lista<T> Lista<T>::ordenar(void)
{
	Lista<T> l1,l2,l3;
	Nodo<T> *aux;	

	if(longitud > 1)
	{
		separar(l1,l2);
		l1 = l1.ordenar();
		l2 = l2.ordenar();
		l3.mezclar(l1,l2);
	}
	else
	{
		aux = new Nodo<T>;
		aux->modificarinfo(prim->consultarinfo());
		aux->modificarprox(NULL);
		l3.modificarprim(aux);
		l3.modificarlongitud(1);
	}

	return l3;
}

template <class T>  
void Lista<T>::insertar(int pos, T e)
{
	Nodo<T> *aux2;
	Nodo<T> *aux = new Nodo<T>;
	int i;

	if(pos > 0 and pos <= longitud+1)
	{
		aux->modificarinfo(e);
		aux2 = prim;
		
		if(pos == 1)
		{
			aux->modificarprox(aux2);
			prim = aux;
		}
		else
		{
			for(i = 1; i < pos-1; i++)
				aux2 = aux2->consultarprox();
			aux->modificarprox(aux2->consultarprox());
			aux2->modificarprox(aux);
		}
	
		longitud++;
	}
}

template <class T> 
void Lista<T>::eliminar(int pos)
{
	Nodo<T> *aux,*aux2;
	int i;

	if(pos > 0 and pos <= longitud)
	{
		if(pos == 1)
		{
			aux = prim;
			prim = aux->consultarprox();
		}
		else
		{
			aux2 = prim;
			for(i = 1; i < pos-1; i++)
				aux2 = aux2->consultarprox();
			aux = aux2->consultarprox();
			aux2->modificarprox(aux->consultarprox());
		}
		
		longitud--;
		delete aux;
	}
}

template <class T> 
void Lista<T>::modificar(T e,int pos)
{
	Nodo<T> *aux;
	int i;

	aux = prim;
	for(i = 1; i < pos; i++)
		aux = aux->consultarprox();
	aux->modificarinfo(e);
}

template <class T> 
void Lista<T>::separar(Lista<T> &l1, Lista<T> &l2)
{
	Nodo<T> *aux,*a,*b,*c;
	int i,j;

	j = 0;
	aux = prim;
	a = NULL;
	b = NULL;	

	for(i = 1; i <= longitud/2; i++)
	{
		c = new Nodo<T>;
		c->modificarinfo(aux->consultarinfo());
		c->modificarprox(a);
		a = c;
		aux = aux->consultarprox();
		delete prim;
		prim = aux;
	}

	while(prim != NULL)
	{
		c = new Nodo<T>;
		c->modificarinfo(aux->consultarinfo());
		c->modificarprox(b);
		b = c;
		aux = aux->consultarprox();
		delete prim;
		prim = aux;
		j++;
	}

	l1.modificarprim(a);
	l2.modificarprim(b);
	l1.modificarlongitud(i-1);
	l2.modificarlongitud(j);
}

template <class T> 
void Lista<T>::separar(Lista<T> &l1, int pos)
{
	Nodo<T> *aux,*a,*c;
	int i;

	aux = prim;
	a = NULL;

	for(i = 1; i < pos; i++)
	{
		c = new Nodo<T>;
		c->modificarinfo(aux->consultarinfo());
		c->modificarprox(a);
		a = c;
		aux = aux->consultarprox();
		delete prim;
		prim = aux;
		longitud--;
	}
	
	aux = aux -> consultarprox();
	delete prim;
	prim = aux;
	longitud--;

	l1.modificarprim(a);
	l1.modificarlongitud(i-1);
	l1.invertir();
}

template <class T> 
void Lista<T>::OcurrMayor(int &mayor, int &cont)
{
	Nodo<T> *aux2;	
	int aux;

	if(prim != NULL)
	{
		aux = prim->consultarinfo();
		aux2 = prim;
		prim = prim->consultarprox();
		delete aux2;

		if(aux > mayor)
			mayor = aux;

		OcurrMayor(mayor,cont);

		if(mayor == aux)
			cont++;
		
		aux2 = new Nodo<T>;
		aux2->modificarinfo(aux);	
		aux2->modificarprox(prim);
		prim = aux2;
	}
}


template <class T> 
void Lista<T>::mezclar(Lista<T> &l1, Lista<T> &l2)
{
	Nodo<T> *aux3,*a,*b,*c;
	T aux, aux2;

	a = l1.obtprim();
	b = l2.obtprim();
	l1.modificarprim(NULL);
	l2.modificarprim(NULL);

	while(a != NULL or b != NULL)
	{
		if(a != NULL)
			aux = a->consultarinfo();
		else
			aux = INT_MAX;
		
		if(b != NULL)
			aux2 = b->consultarinfo();
		else
			aux2 = INT_MAX;

		aux3 = new Nodo<T>; 		
		aux3->modificarprox(prim);		
		
		if(aux > aux2)
		{
			aux3->modificarinfo(aux2);
			c = b;
			b = b->consultarprox();
		}
		else
		{
			aux3->modificarinfo(aux);
			c = a;
			a = a->consultarprox();
		}
		
		prim = aux3;
		longitud++;
		delete c;
	}


	a = prim;
	a = a->consultarprox();
	b = a;		
	prim->modificarprox(NULL);

	while(a != NULL)
	{
		a = a->consultarprox();
		b->modificarprox(prim);
		prim = b;
		b = a;
	}
}

template <class T> 
void Lista<T>::vaciar(void)
{
	Nodo<T> *aux;

	while(prim != NULL)
	{
		aux = prim;
		prim = prim->consultarprox();
		delete aux;
	}
	longitud = 0;
}

template <class T> 
Lista<T> Lista<T>::compactar(Lista<T> &l1, Lista<T> &l2)
{
	Nodo<T> *aux, *aux2, *a, *b, *c;
	Lista<T> l;
	int i;
		
	aux = l1.obtprim();
	aux2 = l2.obtprim();
	b = NULL;

	i = 0;
	while(aux != NULL)
	{
		a = new Nodo<T>;
		a->modificarprox(b);
		a->modificarinfo(aux->consultarinfo());
		b = a;
		i++;
		aux2->modificarinfo(aux2->consultarinfo()-1);
		
		if(aux2->consultarinfo() == 0)
		{
			c = aux2;
			aux2 = aux2->consultarprox();
			delete c;
			c = aux;
			aux = aux->consultarprox();
			delete c;		
		}

	}

	l.modificarprim(b);
	l.modificarlongitud(i-1);
	l = l.ordenar();

	return l;
}

template <class T> 
void Lista<T>::descompactar(Lista<int> &l1, Lista<int> &l2)
{
	Nodo<T> *aux, *aux2, *a, *b; 
	int k,i,j;
	bool band;

	band = false;
	aux = l1.obtprim();
	aux2 = l2.obtprim();
	j = 0;

	while(prim != NULL)
	{
		k = prim->consultarinfo();	
		i = 0;

		a = new Nodo<T>;
		a->modificarprox(aux2);
		a->modificarinfo(k);
		aux2 = a;
		j++; 

		while(!band && k == prim->consultarinfo())
		{
			i++;
			b = prim;
			prim = prim->consultarprox();
			delete b;

			if(longitud == 1)
				k = INT_MAX;

			if(prim == NULL)
				band = true;
		}
		
		a = new Nodo<T>;
		a->modificarprox(aux);
		a->modificarinfo(i);
		aux = a;
	}

	l1.modificarprim(aux);
	l2.modificarprim(aux2);
	l1.modificarlongitud(j);
	l2.modificarlongitud(j);
}

template <class T> 
void Lista<T>::invertir(void)
{
	Nodo<T> *aux,*aux2;

	if(prim != NULL)
	{
		aux = prim;
		aux = aux->consultarprox();
		aux2 = aux;		
		prim->modificarprox(NULL);

		while(aux != NULL)
		{
			aux = aux->consultarprox();
			aux2->modificarprox(prim);
			prim = aux2;
			aux2 = aux;
		}
	}
}

template <class T> 
Lista<T>& Lista<T>::operator= (const Lista<T> &l)
{
	copiar(l);
	return *this;
}

template <class T> 
bool Lista<T>::operator== (const Lista<T> l) const
{
	Nodo<T> *aux,*aux2;
	bool band;

	aux = l.obtprim();
	aux2 = prim;
	band = true;

	while(aux2 != NULL and aux != NULL and band)
	{
		if(aux2->consultarinfo() != aux->consultarinfo())
			band = false;
		aux2 = aux2->consultarprox();
		aux = aux->consultarprox();
	}

	if((aux2 == NULL and aux != NULL) or (aux2 != NULL and aux == NULL))
		band = false;

	return band;
}

template <class T> 
bool Lista<T>::operator!= (const Lista<T> l) const
{
	Nodo<T> *aux,*aux2;
	bool band;

	aux = l.obtprim();
	aux2 = prim;
	band = false;

	while(aux2 != NULL and aux != NULL and !band)
	{
		if(aux2->consultarinfo() != aux->consultarinfo())
			band = true;
		aux2 = aux2->consultarprox();
		aux = aux->consultarprox();
	}

	if((aux2 == NULL and aux != NULL) or (aux2 != NULL and aux == NULL))
		band = true;

	return band;
}

template<class A> ostream& operator<< (ostream& co ,const Lista<A> &l)
{
	Nodo<A> *aux;

	aux = l.obtprim();

	while(aux != NULL)
	{		
		co << aux->consultarinfo() <<" ";
		aux = aux->consultarprox();
	}
	co << endl;	

	return co;
}

template<class B> istream& operator>> (istream &ci,Lista<B> &l)
{
	int i,j;

	//system("clear");

	cout << "Igrese la cantidad de valores a guardar en la lista: ";
	ci >> i;
	cout << endl;
	
	for(j = 1; j <= i; j++)
	{
		B k;

		cout << "Ingrese el valor a guardar en la posicion "<< j << ":" << endl;
		ci >> k;		
		l.insertar(j,k);
	}
	
	system("clear");

	return ci;		
}

template <class T> 
Lista<T>::~Lista(void)
{
	Nodo<T> *aux;

	while(prim != NULL)
	{
		aux = prim;
		prim = prim->consultarprox();
		delete aux;
	}
	longitud = 0;
}

template <class T> 
void Lista<T>::copiar(const Lista<T> &l)
{
	Nodo<T> *aux,*aux2,*aux3;

	aux = l.obtprim();
	if(aux != NULL)
	{	
		aux2 = new Nodo<T>;
		aux2->modificarinfo(aux->consultarinfo());
		prim = aux2;
		aux3 = aux2;
	
		while(aux->consultarprox() != NULL)
		{
			aux = aux->consultarprox();
			aux2 = new Nodo<T>;
			aux2->modificarinfo(aux->consultarinfo());
			aux2->modificarprox(aux3->consultarprox());
			aux3->modificarprox(aux2);
			aux3 = aux3->consultarprox();
		}
		longitud = l.obtlongitud();
	}
	else
	{
		prim = NULL;
		longitud = 0;
	}
}

template <class T> 
Nodo<T>* Lista<T>::obtprim(void) const
{
	return prim;
}

template <class T> 
void Lista<T>::modificarprim(Nodo<T> *n)
{
	prim = n;
}

template <class T> 
void Lista<T>::modificarlongitud(int n)
{
	longitud = n;
}

template <class T>
bool Lista<T>::esta(T data_)
{
    Nodo<T> *temp = prim;
    bool esta = false;

    while (temp != NULL && !esta) 
    {
        if (temp->consultarinfo() == data_) 
            esta = true;
        
        temp = temp->consultarprox();
    }

    return (esta);
}

#endif
