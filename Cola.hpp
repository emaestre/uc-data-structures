#ifndef _COLA_H_
#define _COLA_H_

#include "Nodo.hpp"
#include <iostream>

using namespace std;

template <class T> 
class Cola
{
	private:
		
		Nodo<T> *prim, *ult;
	
	public:
		
		Cola(void);
		Cola(const Cola<T>&);
		bool es_vacia(void) const; 
		T frente(void) const;
		void encolar(T);
		void desencolar(void);
		Cola<T>& operator= (const Cola<T>&);
		bool operator== (const Cola<T>) const;
		bool operator!= (const Cola<T>) const;
		template<class A> friend ostream& operator<< (ostream&,const Cola<A>&);
		template<class B> friend istream& operator>> (istream&,Cola<B>&);
		~Cola(void);
	
	private:
		
		void copiar(const Cola<T>&);
		Nodo<T>* obtprim(void) const;
};

template <class T> 
Cola<T>::Cola(void)
{
	prim = NULL;
	ult = NULL;
}

template <class T> 
Cola<T>::Cola(const Cola<T> &c)
{
	copiar(c);
}

template <class T> 
bool Cola<T>::es_vacia(void) const
{
	return prim == NULL;
}

template <class T> 
T Cola<T>::frente(void) const
{
	return prim->consultarinfo();
}

template <class T> 
void Cola<T>::encolar(T e)
{
	Nodo<T> *aux2;

	aux2 = new Nodo<T>;
	aux2->modificarinfo(e);

	if(prim == NULL)
	{
		prim = aux2;
		aux2->modificarprox(ult);
	}
	else
	{
		aux2->modificarprox(ult->consultarprox());
		ult->modificarprox(aux2);
	}
	ult = aux2;
}

template <class T> 
void Cola<T>::desencolar(void)
{
	Nodo<T> *aux;

	if(prim != NULL)
	{
		aux = prim;
		prim = prim->consultarprox();
		delete aux;
	}
}

template <class T> 
Cola<T>& Cola<T>::operator= (const Cola<T> &c)
{
	copiar(c);
	return *this;
}

template <class T> 
bool Cola<T>::operator== (const Cola<T> c) const
{
	Nodo<T> *aux,*aux2;
	bool band;

	aux = c.obtprim();
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
bool Cola<T>::operator!= (const Cola<T> c) const
{
	Nodo<T> *aux,*aux2;
	bool band;

	aux = c.obtprim();
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

template<class A> ostream& operator<< (ostream& co,const Cola<A> &c)
{
	Nodo<A> *aux;

	aux = c.obtprim();

	while(aux != NULL)
	{		
		co << aux->consultarinfo() << endl;
		aux = aux->consultarprox();
	}
	co << endl;

	return co;
}

template<class B> istream& operator>> (istream &ci,Cola<B> &l)
{
	int i,j;

	system("clear");

	cout << "Igrese la cantidad de valores a guardar en la cola: ";
	ci >> i;
	cout << endl;
	
	for(j = 1; j <= i; j++)
	{
		B k;		

		cout << "Ingrese el valor "<< j << ":" << endl;
		ci >> k;		
		l.encolar(k);
	}
	
	system("clear");

	return ci;		
}


template <class T>  
Cola<T>::~Cola(void)
{
	Nodo<T> *aux;

	while(prim != NULL)
	{
		aux = prim;
		prim = prim->consultarprox();
		delete aux;
	}
}

template <class T> 
void Cola<T>::copiar(const Cola<T> &c)
{
	Nodo<T> *aux,*aux2,*aux3;

	aux = c.obtprim();
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
		ult = aux3;
	}
}

template <class T> 
Nodo<T>* Cola<T>::obtprim(void) const
{
	return prim;
}

#endif
