#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;
    this = (LinkedList*) malloc(sizeof(LinkedList));
    if(this!=NULL)
    {
        this->size = 0;
        this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    int i;
    Node* pNode = NULL;
    if(this != NULL && nodeIndex < ll_len(this) && nodeIndex >= 0)
    {
        pNode = this->pFirstNode;
        if(pNode != NULL)
        {
            for(i = 0; i < nodeIndex; i++)
            {
                pNode = pNode->pNextNode;
            }
        }
    }

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* prev;
    Node* next;
    Node* nuevoNodo;

    if(this != NULL && nodeIndex <= ll_len(this) && nodeIndex >= 0)
    {
        nuevoNodo = (Node*) malloc(sizeof(Node));
        if(nuevoNodo != NULL)
        {
            //guarda el pElement y el siguiente nodo
            nuevoNodo->pElement = pElement;
            if(nodeIndex == 0)
            {
                //guarda el pElement y el nodo actual
                nuevoNodo->pNextNode = getNode(this, nodeIndex);
                this->pFirstNode = nuevoNodo;
                //la posicion del siguiente ya queda enganchada con el anterior
                next = nuevoNodo->pNextNode;
            } else
            {
                //guardar el nodo anterior
                prev = getNode(this, nodeIndex-1);
                prev->pNextNode = nuevoNodo;
                //la posicion del siguiente ya queda enganchada con el anterior
                next = getNode(this, nodeIndex+1);
                nuevoNodo->pNextNode = next;
            }
            returnAux = 0;
            //aumentar el size
            this->size++;
        }
    }

    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        //si la lista no es nula llama al addNode que agrega nodo al final
        if(addNode(this, ll_len(this), pElement) == 0)
        {
            returnAux = 0;
        }
    }

    return returnAux;
}
//  ******* OJO CORREGIR *******************
/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int nodeIndex)
{
    void* returnAux = NULL;
    Node* auxNode;

    if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))
    {
        //guardo en un nodo auxiliar el nodo que esta en la posicion de nodeIndex
        auxNode = getNode(this, nodeIndex);
        if(auxNode != NULL)
        {
            //si es diferente de null lo que retorna la funcion sera igual al pElement del nodo de la posicion
            //nodeIndex
            returnAux = auxNode->pElement;
        }
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* actual;
    if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))
    {
        //en la posicion que obtengo el nodo reemplazo el valor de pElement por el que me pasan
        //por parametro
        actual = getNode(this, nodeIndex);
        if(actual != NULL)
        {
            actual->pElement = pElement;
            returnAux = 0;
        }
    }


    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int nodeIndex)
{
    int returnAux = -1;
    Node* prev;
    Node* next;
    Node* current;

    if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))
    {
        current = getNode(this, nodeIndex);
        if(current != NULL)
        {
            if(nodeIndex == 0)
            {
                    prev = this->pFirstNode;
                    this->pFirstNode = prev->pNextNode;
            } else
            {
                prev = getNode(this, nodeIndex-1);
                next = getNode(this, nodeIndex+1);
                prev->pNextNode = next;
            }
        }
        free(current);
        //disminuye el size
        this->size--;
        returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;
    if(this != NULL)
    {
        for(i = 0; i < ll_len(this); i++)
        {
            if(ll_remove(this, i) == 0)
            {
                returnAux = 0;
            }
        }
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        if(ll_clear(this) == 0)
        {
            free(this);
            returnAux = 0;
        }
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    if(this != NULL)
    {
        for(i = 0; i < ll_len(this); i++)
        {
            if(pElement == ll_get(this, i))
            {
                returnAux = i;
                break;
            }
        }
    }


    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        returnAux = 1;
        if(ll_len(this))
        {
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int nodeIndex, void* pElement)
{
    int returnAux = -1;
    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
        if(addNode(this, nodeIndex, pElement) == 0)
        {
            returnAux = 0;
        }
    }


    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int nodeIndex)
{
    void* returnAux = NULL;
    Node* nodo;
    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
        nodo = getNode(this, nodeIndex);
        if(nodo != NULL)
        {
            if(ll_remove(this, nodeIndex) == 0)
            {
                returnAux = nodo->pElement;
            }
        }
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int founded;
    if(this != NULL)
    {
        returnAux = 0;
        founded = ll_indexOf(this, pElement);
        if(founded != -1)
        {
            returnAux = 1;
        }
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int i;
    int founded;
    void* pContain;
    if(this != NULL && this2 != NULL)
    {
        returnAux = 1;
        for(i = 0; i < ll_len(this2); i++)
        {
            pContain = ll_get(this2, i);
            founded = ll_contains(this, pContain);
            if(pContain != NULL)
            {
                if(founded == -1 || founded == 0)
                {
                    returnAux = 0;
                    break;
                }
            }
        }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int i;
    void* pElement;
    if(this != NULL && from >= 0 && from < ll_len(this))
    {
        if(to > from && to <= ll_len(this))
        {
            cloneArray = ll_newLinkedList();
            if(cloneArray != NULL)
            {
                for(i = from; i < to; i++)
                {
                    pElement = ll_get(this, i);
                    if(pElement != NULL)
                    {
                        ll_add(cloneArray, pElement);
                    }
                }
            }
        }
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int i;
    void* pElement;
    if(this != NULL)
    {
        cloneArray = ll_newLinkedList();
        if(cloneArray != NULL)
        {
            for(i = 0; i < ll_len(this); i++)
            {
                pElement = ll_get(this, i);
                if(pElement != NULL)
                {
                    ll_add(cloneArray, pElement);
                }
            }
        }
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    void* firstParam;
    void* secondParam;
    int i;
    int j;
    int result;
    if(this != NULL && pFunc != NULL)
    {
        if(order == 0 || order == 1)
        {
            for(i = 0; i < ll_len(this)-1; i++)
            {
                for(j = i+1; j < ll_len(this); j++)
                {
                    firstParam = ll_get(this, i);
                    secondParam = ll_get(this, j);
                    result = pFunc(firstParam, secondParam);
                    if(order == 0)
                    {
                        if(result == -1)
                        {
                            ll_set(this, i, secondParam);
                            ll_set(this, j, firstParam);
                        }
                    } else
                    {
                        if(result == 1)
                        {
                            ll_set(this, i, secondParam);
                            ll_set(this, j, firstParam);
                        }
                    }
                }
            }
            returnAux = 0;
        }
    }
    return returnAux;
}

