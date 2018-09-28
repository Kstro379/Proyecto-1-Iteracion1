#ifndef LISTASIMPLE
#define LISTASIMPLE

#include <iostream>

template<class DATO>
class Lista {
  private:
   //// Clase local de Lista para Nodo de Lista:
   template<class DATON>
   class Nodo {
     public:
      // Constructor:
      Nodo(const DATON dat, Nodo<DATON> *sig) : dato(dat), siguiente(sig) {}
      // Miembros:
      DATON dato;
      Nodo<DATON> *siguiente;
   };

   // Punteros de la lista, para cabeza y nodo actual:
   Nodo<DATO> *primero;
   Nodo<DATO> *actual;

  public:
   // Constructor y destructor b�sicos:
   Lista() : primero(NULL), actual(NULL) {}
   ~Lista();
   // Funciones de inserci�n:
   void InsertarFinal(const DATO dat);
   void InsertarPrincipio(const DATO dat);
   bool InsertarActual(const DATO dat);
   void Insertar(const DATO dat);
   // Funciones de borrado:
   void BorrarActual();


   // Comprobar si la lista est� vac�a:
   bool Vacia() { return primero==NULL; }
   // Devolver referencia al dato del nodo actual:
   DATO &ValorActual() { return actual->dato; }
   // Hacer que el nodo actual sea el primero:
   void Primero() { actual = primero; }
   // Comprobar si el nodo actual es v�lido:
   bool Actual() { return actual != NULL; }
   // Moverse al siguiente nodo de la lista:
   void Siguiente() {
      if(actual) {

         actual = actual->siguiente;
      }
   }
   // Sobrecargar operator++ en forma sufija para los mismo:
   void operator++(int) { Siguiente(); }
   // Aplicar una funci�n a cada elemento de la lista:
   void ParaCada(void (*func)(DATO&));
   DATO get_Dato(int pos);
   void insertar_pos(const DATO dat,int pos);
   void cambiarDatPos(const DATO dat, int pos);
};

//////// Implementaci�n:

// Destructor
template<class DATO>
Lista<DATO>::~Lista()
{
   while(!Vacia()) {
      actual = primero;
      primero = primero->siguiente;
      delete actual;
   }
}

template<class DATO>
void Lista<DATO>::InsertarFinal(const DATO dat)
{
   Nodo<DATO> *ultimo;

   // Si la lista est� vac�a, insertar al principio:
   if(Vacia()) InsertarPrincipio(dat);
   else { // Si no lo est�:
      // Buscar el �ltimo nodo:
      ultimo = primero;
      while(ultimo->siguiente) ultimo = ultimo->siguiente;
      // Insertar a continuaci�n:
      ultimo->siguiente = new Nodo<DATO>(dat, NULL);
   }
}

template<class DATO>
void Lista<DATO>::InsertarPrincipio(const DATO dat)
{
   primero = new Nodo<DATO>(dat, primero);
}

template<class DATO>
bool Lista<DATO>::InsertarActual(const DATO dat)
{
   // S�lo si la lista no est� vac�a y actual es v�lido:
   if(!Vacia() && actual) {
      actual->siguiente = new Nodo<DATO>(dat, actual->siguiente);
      return true;
   }
   // Si no se puede insertar, retornar con false:
   return false;
}

// Insertar ordenadamente:
template<class DATO>
void Lista<DATO>::Insertar(const DATO dat)
{
   Nodo<DATO> *temp = primero;
   Nodo<DATO> *anterior = NULL;

   // Si la lista est� vac�a, insertar al principio:
   if(Vacia()) InsertarPrincipio(dat);
   else {
      // Buscar el nodo anterior al primer nodo con un dato mayor qur 'dat'
      while(temp && temp->dato < dat) {
         anterior = temp;
         temp = temp->siguiente;
      }
      // Si no hay anterior, insertar al principio,
      // nuestro valor es el menor de la lista:
      if(!anterior)
         InsertarPrincipio(dat);
      else // Insertar:
         anterior->siguiente = new Nodo<DATO>(dat, temp);
   }
}

template<class DATO>
void Lista<DATO>::BorrarActual()
{
   Nodo<DATO> *anterior;

   // Si el nodo actual es el primero:
   if(actual && actual == primero) {
      // El primer nodo ser� ahora el segundo:
      // Sacar el nodo actual de la lista:
      primero = actual->siguiente;
      // Borrarlo:
      delete actual;
      actual = NULL;
   } else
   if(actual && !Vacia()) {
      // Buscar el nodo anterior al actual:
      anterior = primero;
      while(anterior && anterior->siguiente != actual)
         anterior = anterior->siguiente;
      // Sacar el nodo actual de la lista:
      anterior->siguiente = actual->siguiente;
      // Borrarlo:
      delete actual;
      actual = NULL;
   }
}

// Aplicar una funci�n a cada nodo de la lista:
template<class DATO>
void Lista<DATO>::ParaCada(void (*func)(DATO&))
{
   Nodo<DATO> *temp = primero;

   // Recorrer la lista:
   while(temp) {
      // Aplicar la funci�n:
      func(temp->dato);
      temp = temp->siguiente;
   }
}
template <class DATO>
DATO Lista<DATO>::get_Dato(int pos){
   Nodo<DATO> *temp = primero;
   int i=0;
   while(temp){
      if(i==pos){
         return temp->dato;
      }else{
         temp=temp->siguiente;

      }i++;

   }

}
template <class DATO>
void Lista<DATO>::insertar_pos(const DATO dat,int pos) {

   int i=0;
   this->Primero();
   while(i<pos-1){

      this->Siguiente();

      i++;
   }InsertarActual(dat);
}

template <class DATO>
void Lista<DATO>::cambiarDatPos(const DATO dat, int pos) {
    int i=0;
    this->Primero();
    while(i<pos){

        this->Siguiente();

        i++;
    }
    InsertarActual(dat);
    BorrarActual();
}


#endif

