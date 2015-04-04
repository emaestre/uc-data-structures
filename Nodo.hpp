#ifndef _NODO_H_
#define _NODO_H_

#include <iostream>

using namespace std;

template <class T> 
class Nodo
{
	private:
		
		T info;
		Nodo<T> *prox;

	public:

		Nodo<T>(void);
		Nodo<T>* consultarprox(void);
		T consultarinfo(void);
		void modificarprox(Nodo<T>*);
		void modificarinfo(T);

};

template <class T> 
Nodo<T>::Nodo(void)
{
	prox = NULL;
}

template <class T> 
Nodo<T>* Nodo<T>::consultarprox(void)
{
	return prox;
}

template <class T> 
T Nodo<T>::consultarinfo(void)
{
	return info;
}

template <class T> 
void Nodo<T>::modificarprox(Nodo<T> *n)
{
	prox = n;
}

template <class T> 
void Nodo<T>::modificarinfo(T n)
{
	info = n;
}

#endif
