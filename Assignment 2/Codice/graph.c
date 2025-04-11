#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"

/*************************/
/* Funzioni sugli errori */
/*************************/

/*
Funzione: graph_newError
----------
Crea una nuova struttura errore.
----------
Ritorno:
-> Puntatore a AdjacencyError in caso di successo.
-> NULL altrimenti.
*/
AdjacencyError *graph_newError()
{
    AdjacencyError *temp = (AdjacencyError *)calloc(1, sizeof(AdjacencyError));

    if (temp == NULL)
        printf("Errore in newError: impossibile allocare struttura errore.\n");
    return temp;
}

/*
Funzione: graph_setErrorCode
----------
Imposta il codice nella variabile di errore.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_setErrorCode(AdjacencyError *error, int errorCode)
{
    if (error == NULL)
    {
        printf("Errore in setErrorCode: il puntatore passato era NULL.\n");
        return 0;
    }
    else
    {
        error->genericError = errorCode;
        return 1;
    }
}

/*
Funzione: graph_getErrorCode
----------
Restituisce il codice di errore di una variabile errore.
----------
Ritorno:
-> int, codice di errore.
-> 0 altrimenti.
*/
int graph_getErrorCode(AdjacencyError *error)
{
    if (error == NULL)
    {
        printf("Errore in getErrorCode: il puntatore passato era NULL.\n");
        return 1;
    }
    else
        return error->genericError;
}

/************************/
/* Funzioni sugli archi */
/************************/

/*
Funzione: graph_setArc
----------
Setta la variabile AdjacencyArc.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_setArc(AdjacencyArc *arc, int startingKey, int destinationKey, int pathLength, int supportedWeight)
{
    if (arc == NULL)
    {
        printf("Errore in setArc: il puntatore passato era NULL.\n");
        return 0;
    }
    else
    {
        arc->startingKey = startingKey;
        arc->destinationKey = destinationKey;
        arc->pathLength = pathLength;
        arc->supportedWeight = supportedWeight;
        return 1;
    }
}

/*
Funzione: graph_getArcStartingKey
----------
Ritorna la chiave del nodo di partenza.
----------
Ritorno:
-> int, chiave del nodo.
*/
int graph_getArcStartingKey(AdjacencyArc *arc, AdjacencyError *error)
{
    if (arc == NULL)
    {
        printf("Errore in getArcStartingKey: il puntatore passato era NULL.\n");
        if (error)
            error->genericError = 1;
        return 0;
    }
    else
    {
        if (error)
            error->genericError = 0;
        return arc->startingKey;
    }
}

/*
Funzione: graph_getArcDestinationKey
----------
Ritorna la chiave del nodo di arrivo.
----------
Ritorno:
-> int, chiave del nodo.
*/
int graph_getArcDestinationKey(AdjacencyArc *arc, AdjacencyError *error)
{
    if (arc == NULL)
    {
        printf("Errore in getArcDestinationKey: il puntatore passato era NULL.\n");
        if (error)
            error->genericError = 1;
        return 0;
    }
    else
    {
        if (error)
            error->genericError = 0;
        return arc->destinationKey;
    }
}

/*
Funzione: graph_getPathLength
----------
Ritorna la lunghezza arco (ponte).
----------
Ritorno:
-> int, lunghezza arco (ponte).
*/
int graph_getPathLength(AdjacencyArc *arc, AdjacencyError *error)
{
    if (arc == NULL)
    {
        printf("Errore in getArcWeight: il puntatore passato era NULL.\n");
        if (error)
            error->genericError = 1;
        return 0;
    }
    else
    {
        if (error)
            error->genericError = 0;
        return arc->pathLength;
    }
}

/*
Funzione: graph_getSupportedWeight
----------
Ritorna il peso supportato dall'arco (ponte).
----------
Ritorno:
-> int, peso supportato dall'arco (ponte).
*/
int graph_getSupportedWeight(AdjacencyArc *arc, AdjacencyError *error)
{
    if (arc == NULL)
    {
        printf("Errore in getArcWeight: il puntatore passato era NULL.\n");
        if (error)
            error->genericError = 1;
        return 0;
    }
    else
    {
        if (error)
            error->genericError = 0;
        return arc->supportedWeight;
    }
}

/*************************************/
/* Funzioni sulle liste di adiacenza */
/*************************************/

/*
Funzione: _graph_addAdjacencyListNode
----------
Aggiunge un nodo nella lista di adiacenza con la chiave specificata.
Controlla anche che l'arco non sia già presente.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
static int _graph_addAdjacencyListNode(AdjacencyListNode **head, int key, int pathLength, int supportedWeight)
{
    if (head == NULL)
    {
        printf("Errore in addListNode: il puntatore passato era NULL.\n");
        return 0;
    }
    else if (*head)
    {
        if ((*head)->destinationKey == key)
        {
            printf("Errore in addListNode: l'arco esiste gia'.\n");
            return 0;
        }
        else
            return _graph_addAdjacencyListNode(&((*head)->next), key, pathLength, supportedWeight);
    }
    else /*if (*head == NULL)*/
    {
        *head = (AdjacencyListNode *)calloc(1, sizeof(AdjacencyListNode));
        if (!*head)
        {
            printf("Errore in addListNode: impossibile allocare nodo lista di adiacenza.\n");
            return 0;
        }
        else
        {
            (*head)->destinationKey = key;
            (*head)->pathLength = pathLength;
            (*head)->supportedWeight = supportedWeight;
            return 1;
        }
    }
}

/*
Funzione: _graph_printAdjacencyList
----------
Stampa la lista dei nodi di adiacenza.
----------
Ritorno: nessuno.
*/
static void _graph_printAdjacencyList(AdjacencyListNode *head)
{
    if (head == NULL)
        return;
    else
    {
        printf("%d ", head->destinationKey);
        _graph_printAdjacencyList(head->next);
    }
}

/*
Funzione: _graph_deleteAdjacencyList
----------
Dealloca la lista dei nodi di adiacenza.
----------
Ritorno: nessuno.
*/
static void _graph_deleteAdjacencyList(AdjacencyListNode *head)
{
    if (head == NULL)
        return;
    else
    {
        _graph_deleteAdjacencyList(head->next);
        free(head);
    }
}

/*
Funzione: _graph_deleteAdjacencyListNode
----------
Elimina il nodo dalla lista di adiacenza con a chiave specificata (se esiste).
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
static int _graph_deleteAdjacencyListNode(AdjacencyListNode **head, int key)
{
    if ((head == NULL) || (*head == NULL))
        return 0;
    else
    {
        if ((*head)->destinationKey == key)
        {
            AdjacencyListNode *temp = *head;

            *head = (*head)->next;
            free(temp);
            return 1;
        }
        else
            return _graph_deleteAdjacencyListNode(&((*head)->next), key);
    }
}

/*********************/
/* Funzioni sui nodi */
/*********************/

/*
Funzione: _graph_verifyNodeExstence
----------
Verifica l'esistenza del nodo indicato con la chiave.
----------
Ritorno:
-> 1 se il nodo esiste.
-> 0 altrimenti.
*/
static int _graph_verifyNodeExstence(AdjacencyGraphNode **array, unsigned arrayLength, int key)
{
    if (array == NULL)
    {
        printf("Errore in _verifyNodeExstence: il puntatore passato era NULL.\n");
        return 0;
    }
    else
    {
        for (int i = 0; i < arrayLength; i++)
        {
            if (array[i])
                if (array[i]->key == key)
                    return 1;
        }
        return 0;
    }
}

/*
Funzione: _graph_findFirstEmptyArrayNodePosition
----------
Restituisce la prima posizione vuota nell'array dei nodi.
Nel caso l'array passato sia pieno viene impostato l'errore nella variabile AdjacencyError.
Altri errori vengono impostati nella variabile AdjacencyError.
----------
Ritorno:
-> unsigned, posizione nell'array.
*/
static unsigned _graph_findFirstEmptyArrayNodePosition(AdjacencyGraphNode **array, unsigned arrayLenth,
                                                       AdjacencyError *error)
{
    if (array == NULL)
    {
        if (error)
            error->genericError = 1;
        printf("Errore in _findFirstEmptyNodePosition: il puntatore passato era NULL.\n");
        return 0;
    }
    else
    {
        for (int i = 0; i < arrayLenth; i++)
        {
            if (array[i] == NULL)
            {
                if (error)
                    error->genericError = 0;
                return i;
            }
        }
        printf("Errore in _findFirstEmptyNodePosition: l'array passato e' pieno.\n");
        error->genericError = 1;
        return 0;
    }
}

/*
Funzione: graph_findPositionByKey
----------
Restituisce la posizione dove si trova il nodo con la chiave specificata.
Gli errori vengono impostati nella variabile AdjacencyError.
----------
Ritorno:
-> unsigned, posizione nell'array.
*/
unsigned graph_findPositionByKey(AdjacencyGraphNode **array, unsigned arrayLength, int keyToFind,
                                         AdjacencyError *error)
{
    if (array == NULL)
    {
        printf("Errore in _findPositionByKey: il puntatore passato era NULL.\n");
        if (error)
            error->genericError = 1;
        return 0;
    }
    else
    {
        for (int i = 0; i < arrayLength; i++)
        {
            if (array[i])
                if (array[i]->key == keyToFind)
                {
                    if (error)
                        error->genericError = 0;
                    return i;
                }
        }
        printf("Attenzione: nodo del grafo non trovato con la chiave specificata.\n");
        error->genericError = 1;
        return 0;
    }
}

/*
Funzione: graph_isNull
----------
Verifica se il puntatore del grafo è NULL.
----------
Ritorno:
-> 1 nel caso il puntatore sia NULL.
-> 0 altrimenti.
*/
int graph_isNull(AdjacencyGraph *graph)
{
    return graph == NULL;
}

/*
Funzione: graph_isEmpty
----------
Verifica se il grafo è vuoto.
----------
Ritorno:
-> 1 nel caso il grafo sia vuoto.
-> 0 altrimenti.
*/
int graph_isEmpty(AdjacencyGraph *graph)
{
    return graph->nodeArray == NULL;
}

/*
Funzione: graphlist_newGraph
----------
Alloca una nuova struttura grafo con un numero di nodi specificato [0 a ...].
----------
Ritorno:
-> Puntatore a AdjacencyGraph in caso di successo.
-> NULL altrimenti.
*/
AdjacencyGraph *graph_newGraph(unsigned initialNumberoOfNodes)
{
    AdjacencyGraph *tempGraph = NULL;
    AdjacencyGraphNode **tempArray = NULL;

    if (initialNumberoOfNodes > 0)
    {
        tempArray = (AdjacencyGraphNode **)calloc(initialNumberoOfNodes, sizeof(AdjacencyGraphNode *));
        if (tempArray == NULL)
        {
            printf("Errore in newGraph: impossibile allocare array di nodi.\n");
            return NULL;
        }
    }
    tempGraph = (AdjacencyGraph *)calloc(1, sizeof(AdjacencyGraph));
    if (tempGraph == NULL)
    {
        printf("Errore in newGraph: impossibile allocare grafo.\n");
        if (tempArray)
            free(tempArray);
        return NULL;
    }
    tempGraph->nodeArray = tempArray;
    tempGraph->arrayLength = initialNumberoOfNodes;
    return tempGraph;
}

/*
Funzione: graph_reallocNodeArray
----------
Rialloca, aumentandone la dimesione, l'array dei nodi contenuto nel grafo.
Attenzione: questa funzione non rimpicciolisce né compatta l'array.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_reallocNodeArray(AdjacencyGraph *graph, unsigned newLength)
{
    AdjacencyGraphNode **tempArray = NULL;

    if (newLength <= graph->arrayLength)
    {
        printf("Errore in reallocNodeArray: la nuova dimensione deve essere maggiore di quella precedente.\n");
        return 0;
    }
    else
    {
        tempArray = (AdjacencyGraphNode **)calloc(newLength, sizeof(AdjacencyGraphNode *));
        if (tempArray == NULL)
        {
            printf("Errore in reallocNodeArray: il nuovo array non puo' essere allocato.\n");
            return 0;
        }
        else
        {
            for (int i = 0; i < graph->arrayLength; i++)
                tempArray[i] = graph->nodeArray[i];
            free(graph->nodeArray);
            graph->nodeArray = tempArray;
            graph->arrayLength = newLength;
            return 1;
        }
    }
}

/*
Funzione: graph_addNode
----------
Aggiunge un nuovo nodo al grafo con la chiave specificata.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_addNode(AdjacencyGraph *graph, int key)
{
    if (graph_isNull(graph))
    {
        printf("Errore in addNode: il puntatore passato era NULL.\n");
        return 0;
    }
    if (graph->nodeArray == NULL) //Caso array vuoto.
    {
        graph->nodeArray = (AdjacencyGraphNode **)calloc(1, sizeof(AdjacencyGraphNode *));
        if (graph->nodeArray == NULL)
        {
            printf("Errore in addNode: impossibile allocare array di nodi.\n");
            return 0;
        }
        else
        {
            graph->nodeArray[0] = (AdjacencyGraphNode *)calloc(1, sizeof(AdjacencyGraphNode));
            if (graph->nodeArray[0] == NULL)
            {
                printf("Errore in addNode: impossibile allocare nodo nell'array, posizione 0.\n");
                return 0;
            }
            else
            {
                graph->nodeArray[0]->key = key;
                graph->arrayLength = 1;
                graph->numberOfNodes++;
                return 1;
            }
        }
    }
    else //Caso array esistente.
    {
        AdjacencyGraphNode *newNode = NULL;

        if (_graph_verifyNodeExstence(graph->nodeArray, graph->arrayLength, key))
        {
            printf("Errore in addNode: il nodo con chiave %d esiste gia'.\n", key);
            return 0;
        }
        newNode = (AdjacencyGraphNode *)calloc(1, sizeof(AdjacencyGraphNode));
        if (newNode == NULL)
        {
            printf("Errore in addNode: impossibile allocare nuovo nodo.\n");
            return 0;
        }
        newNode->key = key;
        if (graph->numberOfNodes == graph->arrayLength) //Caso array pieno => riallocazione.
        {
            if (graph_reallocNodeArray(graph, graph->arrayLength + 1))
            {
                graph->nodeArray[graph->arrayLength - 1] = newNode;
                graph->numberOfNodes++;
                return 1;
            }
            else
                return 0;
        }
        else //Caso array con buchi.
        {
            AdjacencyError *error = graph_newError();
            unsigned freePosition;

            if (error == NULL)
            {
                free(newNode);
                return 0;
            }
            freePosition = _graph_findFirstEmptyArrayNodePosition(graph->nodeArray, graph->arrayLength, error);
            graph->nodeArray[freePosition] = newNode;
            graph->numberOfNodes++;
        }
        return 1;
    }
}

/*
Funzione: graph_addNode
----------
Aggiunge un nuovo nodo al grafo con la chiave specificata.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_addNodeWithName(AdjacencyGraph *graph, int key, char *name)
{
    if (graph_isNull(graph))
    {
        printf("Errore in addNode: il puntatore passato era NULL.\n");
        return 0;
    }
    if (graph->nodeArray == NULL) //Caso array vuoto.
    {
        graph->nodeArray = (AdjacencyGraphNode **)calloc(1, sizeof(AdjacencyGraphNode *));
        if (graph->nodeArray == NULL)
        {
            printf("Errore in addNode: impossibile allocare array di nodi.\n");
            return 0;
        }
        else
        {
            graph->nodeArray[0] = (AdjacencyGraphNode *)calloc(1, sizeof(AdjacencyGraphNode));
            if (graph->nodeArray[0] == NULL)
            {
                printf("Errore in addNode: impossibile allocare nodo nell'array, posizione 0.\n");
                return 0;
            }
            else
            {
                graph->nodeArray[0]->key = key;
                graph->nodeArray[0]->name = strdup(name);
                graph->arrayLength = 1;
                graph->numberOfNodes++;
                return 1;
            }
        }
    }
    else //Caso array esistente.
    {
        AdjacencyGraphNode *newNode = NULL;

        if (_graph_verifyNodeExstence(graph->nodeArray, graph->arrayLength, key))
        {
            printf("Errore in addNode: il nodo con chiave %d esiste gia'.\n", key);
            return 0;
        }
        newNode = (AdjacencyGraphNode *)calloc(1, sizeof(AdjacencyGraphNode));
        if (newNode == NULL)
        {
            printf("Errore in addNode: impossibile allocare nuovo nodo.\n");
            return 0;
        }
        newNode->key = key;
        newNode->name = strdup(name);
        if (graph->numberOfNodes == graph->arrayLength) //Caso array pieno => riallocazione.
        {
            if (graph_reallocNodeArray(graph, graph->arrayLength + 1))
            {
                graph->nodeArray[graph->arrayLength - 1] = newNode;
                graph->numberOfNodes++;
                return 1;
            }
            else
                return 0;
        }
        else //Caso array con buchi.
        {
            AdjacencyError *error = graph_newError();
            unsigned freePosition;

            if (error == NULL)
            {
                free(newNode);
                return 0;
            }
            freePosition = _graph_findFirstEmptyArrayNodePosition(graph->nodeArray, graph->arrayLength, error);
            graph->nodeArray[freePosition] = newNode;
            graph->numberOfNodes++;
        }
        return 1;
    }
}

/*
Funzione: graph_deleteNode
----------
Dealloca il nodo specificato con la chiave e pone il puntatore nell'array a NULL.
Elimina gli archi dagli altri nodi se presenti.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_deleteNode(AdjacencyGraph *graph, int keyToDelete)
{
    if (graph_isNull(graph))
    {
        printf("Errore in deleteNode: il puntatore passato era NULL.\n");
        return 0;
    }
    else if (graph_isEmpty(graph))
    {
        printf("Errore in deleteNode: il grafo e' vuoto.\n");
        return 0;
    }
    else
    {
        AdjacencyError error;
        unsigned positionToDelete = graph_findPositionByKey(graph->nodeArray, graph->arrayLength, keyToDelete,
                                                             &error);

        if (graph_getErrorCode(&error))
        {
            printf("Errore in deleteNode: impossibile eliminare il nodo specificato.\n");
            return 0;
        }
        else
        {
            for (int i = 0; i < graph->arrayLength; i++)
            {
                if (graph->nodeArray[i])
                    if (graph->nodeArray[i]->key != keyToDelete)
                        if (_graph_deleteAdjacencyListNode(&(graph->nodeArray[i]->adjacencyListHead), keyToDelete))
                            graph->nodeArray[i]->numberOfOutArches--;
            }
            _graph_deleteAdjacencyList(graph->nodeArray[positionToDelete]->adjacencyListHead);
            if (graph->nodeArray[positionToDelete]->name)
                free(graph->nodeArray[positionToDelete]->name);
            free(graph->nodeArray[positionToDelete]);
            graph->nodeArray[positionToDelete] = NULL;
            graph->numberOfNodes--;
            return 1;
        }
    }
}

/*
Funzione: graph_disableNode
----------
Disabilita il nodo specificato con la chiave e lo rende dispobibile per nuove allocazioni.
Elimina gli archi dagli altri nodi se presenti.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_disableNode(AdjacencyGraph *graph, int keyToDisable)
{
    if (graph_isNull(graph))
    {
        printf("Errore in deleteNode: il puntatore passato era NULL.\n");
        return 0;
    }
    else if (graph_isEmpty(graph))
    {
        printf("Errore in deleteNode: il grafo e' vuoto.\n");
        return 0;
    }
    else
    {
        AdjacencyError error;
        unsigned positionToDisable = graph_findPositionByKey(graph->nodeArray, graph->arrayLength, keyToDisable,
                                                              &error);

        if (graph_getErrorCode(&error))
        {
            printf("Errore in deleteNode: impossibile eliminare il nodo specificato.\n");
            return 0;
        }
        else
        {
            for (int i = 0; i < graph->arrayLength; i++)
            {
                if (graph->nodeArray[i])
                    if (graph->nodeArray[i]->key != keyToDisable)
                        if (_graph_deleteAdjacencyListNode(&(graph->nodeArray[i]->adjacencyListHead), keyToDisable))
                            graph->nodeArray[i]->numberOfOutArches--;
            }
            graph->nodeArray[positionToDisable]->isDisabled = 1;
            graph->numberOfNodes--;
            return 1;
        }
    }
}

/*
Funzione: graph_deleteGraph
----------
Dealloca l'intero grafo specificato.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_deleteGraph(AdjacencyGraph **graph)
{
    if ((graph == NULL) || (*graph == NULL))
    {
        printf("Errore in deleteGraph: il puntatore passato era NULL.\n");
        return 0;
    }
    else
    {
        if (!graph_isEmpty(*graph))

        {
            for (int i = 0; i < (*graph)->arrayLength; i++)
            {
                if ((*graph)->nodeArray[i])
                {
                    _graph_deleteAdjacencyList((*graph)->nodeArray[i]->adjacencyListHead);
                    if ((*graph)->nodeArray[i]->name)
                        free((*graph)->nodeArray[i]->name);
                    free((*graph)->nodeArray[i]);
                }
            }
        }
        free(*graph);
        *graph = NULL;
        return 1;
    }
}

/*
Funzione: graph_printGraph
----------
Stampa il grafo
----------
Ritorno: nessuno.
*/
void graph_printGraph(AdjacencyGraph *graph)
{
    if (graph_isNull(graph))
    {
        printf("Errore in printGraph: il puntatore passato era NULL.\n");
        return;
    }
    else if (graph_isEmpty(graph))
    {
        printf("Il grafo e' vuoto.\n");
        return;
    }
    else
    {
        printf("Il grafo ha %u nodi.\n", graph->numberOfNodes);
        printf("--------------------\n");
        for (int i = 0; i < graph->arrayLength; i++)
        {
            if (graph->nodeArray[i])
            {
                if (graph->nodeArray[i]->isDisabled)
                    printf("Nodo: %d, DISABILITATO.\n", i);
                else
                {
                    printf("Nodo: %u, Chiave: %d, Nome: %s, Num. archi in: %u, Num. archi out: %u, Archi: ", i,
                           graph->nodeArray[i]->key, graph->nodeArray[i]->name, graph->nodeArray[i]->numberOfInArches,
                           graph->nodeArray[i]->numberOfOutArches);
                    _graph_printAdjacencyList(graph->nodeArray[i]->adjacencyListHead);
                    printf("\n");
                }
            }
            else
                printf("Nodo: %u, NULL.\n", i);
        }
    }
}

/*
Funzione: graphlist_addDirectionalArc
----------
Aggiunge un arco direzionale.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_addDirectionalArc(AdjacencyGraph *graph, AdjacencyArc *arc)
{
    if (graph_isNull(graph))
    {
        printf("Errore in addDirectionalArc: il puntatore passato era NULL.\n");
        return 0;
    }
    else if (graph_isEmpty(graph))
    {
        printf("Errore in addDirectionalArc: il grafo e' vuoto.\n");
        return 0;
    }
    else
    {
        AdjacencyError error1, error2;
        unsigned startingNodePosition, destinationNodePosition;

        if ((!_graph_verifyNodeExstence(graph->nodeArray, graph->arrayLength, arc->startingKey)) ||
            (!_graph_verifyNodeExstence(graph->nodeArray, graph->numberOfNodes, arc->destinationKey)))
        {
            printf("Errore in addDirectionalArc: il nodo di partenza e/o il nodo di arrivo non esiste.\n");
            return 0;
        }
        else
        {
            startingNodePosition = graph_findPositionByKey(graph->nodeArray, graph->arrayLength, arc->startingKey,
                                                                &error1);
            destinationNodePosition = graph_findPositionByKey(graph->nodeArray, graph->arrayLength,
                                                                   arc->destinationKey, &error2);
            if ((graph_getErrorCode(&error1)) || (graph_getErrorCode(&error2)))
                return 0;
            else if (_graph_addAdjacencyListNode(&(graph->nodeArray[startingNodePosition]->adjacencyListHead),
                                                  arc->destinationKey, arc->pathLength, arc->supportedWeight))
            {
                graph->nodeArray[startingNodePosition]->numberOfOutArches++;
                graph->nodeArray[destinationNodePosition]->numberOfInArches++;
                return 1;
            }
            else
                return 0;
        }
    }
}

/*
Funzione: graph_addBidrectionalArc
----------
Aggiunge un arco bidirezionale.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_addBidirectionalArc(AdjacencyGraph *graph, AdjacencyArc *arc)
{
    if (graph_isNull(graph))
    {
        printf("Errore in addBidirectionalArc: il puntatore passato era NULL.\n");
        return 0;
    }
    else if (graph_isEmpty(graph))
    {
        printf("Errore in addBidirectionalArc: il grafo e' vuoto.\n");
        return 0;
    }
    else
    {
        AdjacencyError error1, error2;
        unsigned nodePosition1, nodePosition2;

        if ((!_graph_verifyNodeExstence(graph->nodeArray, graph->arrayLength, arc->startingKey)) ||
            (!_graph_verifyNodeExstence(graph->nodeArray, graph->numberOfNodes, arc->destinationKey)))
        {
            printf("Errore in addBidirectionalArc: il nodo di partenza e/o il nodo di arrivo non esiste.\n");
            return 0;
        }
        else
        {
            nodePosition1 = graph_findPositionByKey(graph->nodeArray, graph->arrayLength, arc->startingKey,
                                                     &error1);
            nodePosition2 = graph_findPositionByKey(graph->nodeArray, graph->arrayLength, arc->destinationKey,
                                                     &error2);
            if ((graph_getErrorCode(&error1)) || (graph_getErrorCode(&error2)))
                return 0;
            else if ((_graph_addAdjacencyListNode(&(graph->nodeArray[nodePosition1]->adjacencyListHead),
                                                  arc->destinationKey, arc->pathLength, arc->supportedWeight)) &&
                     (_graph_addAdjacencyListNode(&(graph->nodeArray[nodePosition2]->adjacencyListHead),
                                                  arc->startingKey, arc->pathLength, arc->supportedWeight)))
            {
                graph->nodeArray[nodePosition1]->numberOfOutArches++;
                graph->nodeArray[nodePosition1]->numberOfInArches++;
                graph->nodeArray[nodePosition2]->numberOfOutArches++;
                graph->nodeArray[nodePosition2]->numberOfInArches++;

                return 1;
            }
            else
                return 0;
        }
    }
}

/*
Funzione: graph_deleteBidrectionalArc
----------
Elimina un arco bidirezionale.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_deleteBidirectionalArc(AdjacencyGraph *graph, AdjacencyArc *arc)
{
    if (graph_isNull(graph))
    {
        printf("Errore in deleteBidirectionalArc: il puntatore passato era NULL.\n");
        return 0;
    }
    else if (graph_isEmpty(graph))
    {
        printf("Errore in deleteBidirectionalArc: il grafo e' vuoto.\n");
        return 0;
    }
    else
    {
        AdjacencyError error1, error2;
        unsigned nodePosition1, nodePosition2;

        if ((!_graph_verifyNodeExstence(graph->nodeArray, graph->arrayLength, arc->startingKey)) ||
            (!_graph_verifyNodeExstence(graph->nodeArray, graph->numberOfNodes, arc->destinationKey)))
        {
            printf("Errore in deleteBidirectionalArc: il nodo di partenza e/o il nodo di arrivo non esiste.\n");
            return 0;
        }
        else
        {
            nodePosition1 = graph_findPositionByKey(graph->nodeArray, graph->arrayLength, arc->startingKey,
                                                     &error1);
            nodePosition2 = graph_findPositionByKey(graph->nodeArray, graph->arrayLength, arc->destinationKey,
                                                     &error2);
            if ((graph_getErrorCode(&error1)) || (graph_getErrorCode(&error2)))
                return 0;
            else if ((_graph_deleteAdjacencyListNode(&(graph->nodeArray[nodePosition1]->adjacencyListHead),
                                                     arc->destinationKey)) &&
                     (_graph_deleteAdjacencyListNode(&(graph->nodeArray[nodePosition2]->adjacencyListHead),
                                                     arc->startingKey)))
            {
                graph->nodeArray[nodePosition1]->numberOfOutArches--;
                graph->nodeArray[nodePosition1]->numberOfInArches--;
                graph->nodeArray[nodePosition2]->numberOfOutArches--;
                graph->nodeArray[nodePosition2]->numberOfInArches--;
                return 1;
            }
            else
                return 0;
        }
    }
}

/*
Funzione: graph_getNumberOfGraphNodes
----------
Ritorna il numero di nodi (vertici) del grafo.
----------
Ritorno:
-> unsigned, numero dei nodi del grafo.
*/
unsigned graph_getNumberOfGraphNodes(AdjacencyGraph *graph)
{
    if (graph_isNull(graph))
    {
        printf("Errore in getNumberOfGraphNodes: il puntatore passato era NULL.\n");
        return 0;
    }
    else
        return graph->numberOfNodes;
}

/*
Funzione: graph_getNodeGrade
----------
Ritorna il grado del nodo specificato.
----------
Ritorno:
-> unsigned, grado del nodo.
*/
unsigned graph_getNodeGrade(AdjacencyGraph *graph, int key)
{
    if (graph_isNull(graph))
    {
        printf("Errore in getNodeGrade: il puntatore passato era NULL.\n");
        return 0;
    }
    else
    {
        if (graph_isEmpty(graph))
            return 0;
        else
        {
            AdjacencyError error;
            unsigned nodePosition = graph_findPositionByKey(graph->nodeArray, graph->arrayLength, key, &error);

            if (graph_getErrorCode(&error))
            {
                printf("Errore in getNodeGrade: la chiave specificata non e' presente.\n");
                return 0;
            }
            else
                return graph->nodeArray[nodePosition]->numberOfOutArches;
        }
    }
}

/*
Parte della successiva funzione graph_findDijkstraPath.
Inizializza tutti i nodi del grafo per permettere l'applicazione dell'algoritmo di Dijkstra.
*/
static void _graph_inizializeDijkstra(AdjacencyGraphNode **array, int arrayLength, int startKey)
{
    for (int i = 0; i < arrayLength; i++)
    {
        if ((array[i]) && (!array[i]->isDisabled))
        {
            array[i]->isVisited = 0;
            array[i]->predecessorPosition = 0;
            if (array[i]->key == startKey)
                array[i]->distance = 0;
            else
                array[i]->distance = INT_MAX;
        }
    }
}

/*
Parte ricordiva della successiva funzione graph_findDijkstraPath.
Esegue la stampa del percorso trovato con l'algoritmo di Dijkstra.
*/
static void _graph_printDijkstra(AdjacencyGraphNode **array, unsigned initialPosition, unsigned destinationPosition)
{
    if (destinationPosition == initialPosition)
    {
        printf("\n    %s\n", array[destinationPosition]->name);
        return;
    }
    else
    {
        _graph_printDijkstra(array, initialPosition, array[destinationPosition]->predecessorPosition);
        printf("    %s\n", array[destinationPosition]->name);
    }
}


/*
Parte della successiva funzione graph_findDijkstraPath.
Esegue l'algoritmo di Dikjstra su grafo.
*/
static int _graph_runDijkstra(AdjacencyGraphNode **array, unsigned arrayLength, unsigned initialPosition,
                              unsigned destinationPosition, int driverWeight)
{
    int minDistance = INT_MAX;
    unsigned minPosition;
    int isNotEmpty = 1;
    unsigned sonPosition;

    while (isNotEmpty)
    {
        for (int i = 0; i < arrayLength; i++)
            if (array[i] && !array[i]->isDisabled)
                if (array[i]->isVisited == 0)
                    if (array[i]->distance < minDistance)
                    {
                        minDistance = array[i]->distance;
                        minPosition = i;
                    }

        array[minPosition]->isVisited = 1;

        if (minPosition == destinationPosition) //Condizione di uscita normale => nodo raggiunto.
            break;
        if (minDistance == INT_MAX) //Condizione di uscita anormale => nodo irrgiungibile.
            break;

        AdjacencyListNode *son = array[minPosition]->adjacencyListHead;
        while (son)
        {
            sonPosition = graph_findPositionByKey(array, arrayLength, son->destinationKey, NULL);

            if (((array[minPosition]->distance + son->pathLength) < array[sonPosition]->distance) &&
                (son->supportedWeight >= driverWeight))
            {
                array[sonPosition]->distance = (array[minPosition]->distance + son->pathLength);
                array[sonPosition]->predecessorPosition = minPosition;
            }
            son = son->next;
        }

        for (int i = 0; i < arrayLength; i++)
            if (array[i] && !array[i]->isDisabled)
            {
                if (!array[i]->isVisited)
                {
                    isNotEmpty = 1;
                    break;
                }
                else
                    isNotEmpty = 0;
            }

        minDistance = INT_MAX;
    }

    printf("Percorso: ");
    if (destinationPosition == minPosition)
    {
        _graph_printDijkstra(array, initialPosition, minPosition);
        printf("\n");
        return 1;
    }
    else
    {
        printf("    La posizione selezionata non e' raggiungibile.");
        printf("\n");
        return 0;
    }
}

/*
Funzione: graph_findDijkstraPath
----------
Trova e stampa il percorso tra 2 nodi del grafo tramite l'algoritmo di Dijkstra.
----------
Ritorno:
-> 1 nel caso di successo.
-> 0 nel caso di insuccesso e/o errore.
*/
int graph_findDijkstraPath(AdjacencyGraph *graph, int startKey, int destinationKey, int driverWeight)
{
    if (graph_isNull(graph))
    {
        printf("Errorre in findDijkstraPath: il puntatore passato era NULL.\n");
        return 0;
    }
    else if (graph_isEmpty(graph))
    {
        printf("Attenzione: il grafo e' vuoto.\n");
        return 0;
    }
    else
    {
        if (_graph_verifyNodeExstence(graph->nodeArray, graph->arrayLength, startKey) &&
            _graph_verifyNodeExstence(graph->nodeArray, graph->arrayLength, destinationKey))
        {
            unsigned initialPosition = graph_findPositionByKey(graph->nodeArray, graph->arrayLength, startKey, NULL);
            unsigned destinationPosition = graph_findPositionByKey(graph->nodeArray, graph->arrayLength, destinationKey, NULL);

            _graph_inizializeDijkstra(graph->nodeArray, graph->arrayLength, startKey);
            return _graph_runDijkstra(graph->nodeArray, graph->arrayLength, initialPosition, destinationPosition, driverWeight);
        }
        else
        {
            printf("Errorre in findDijkstraPath: nodo/i non esistente/i.\n");
            return 0;
        }
    }
}

/*********************/
/* Funzioni sui file */
/*********************/

/*
Funzione: _graph_dbNamePathConverter
----------
Controlla che il nome del db sia di GRAPH_MAX_DB_NAME_LENGTH caratteri e compone il percorso completo del file con
l'estensione.
----------
Ritorno:
-> 0 nel caso il nome sia troppo lungo.
-> 1 nel caso di successo.
*/
static int _graph_dbNamePathConverter(char *dbName, char *destinationString)
{
    if (strlen(dbName) > GRAPH_MAX_DB_NAME_LENGTH)
    {
        printf("Errore in _dbNamePathConverter: il nome del file e' troppo lungo. [Max %d caratteri]\n",
               GRAPH_MAX_DB_NAME_LENGTH);
        return 0;
    }
    else
    {
        strcat(destinationString, GRAPH_DB_PATH);
        strcat(destinationString, dbName);
        strcat(destinationString, GRAPH_DB_EXTENSION);
        return 1;
    }
}

/*
Funzione: _graph_checkFileExistence
----------
Controlla l'esistenza del file indicato.
----------
Ritorno:
-> 0 nel caso il file non esista.
-> 1 nel caso il file esista.
*/
// static int _graph_checkFileExistence(char *filePath)
// {
//     FILE *temp = fopen(filePath, "r");

//     if(temp)
//     {
//         fclose(temp);
//         return 1;
//     }
//     else
//         return 0;
// }

/*
Funzione: graph_createNewDb
----------
Crea un nuovo file di dati.
Lunghezza massima del nome accettato e' di GRAPH_MAX_DB_NAME (20) caratteri.
ATTENZIONE: se è già presente un file con lo stesso nome, esso verrà sovrascritto.
----------
Ritorno:
-> Puntatore a FILE in caso di successo.
-> Puntatore NULL nel caso non sia stato possibile creare il file.
-> Puntatore NULL nel caso il file sia gia' esistente.
*/
FILE *graph_createNewDb(char *dbName)
{
    FILE *temp = NULL;
    char *finalDbPath = (char *)calloc(GRAPH_MAX_DB_PATH_LENGTH, sizeof(char));

    if (!_graph_dbNamePathConverter(dbName, finalDbPath))
    {
        free(finalDbPath);
        return NULL;
    }
    else
    {
        temp = fopen(finalDbPath, "w");
        free(finalDbPath);
        return temp;
    }
}

/*
Funzione: graph_openDbToAppend
----------
Apre il file indicato in modalità "append".
Lunghezza massima del nome accettato e' di GRAPH_MAX_DB_NAME (20) caratteri.
----------
Ritorno:
-> Puntatore a FILE in caso di successo.
-> Puntatore NULL nel caso non sia stato possibile creare il file.
*/
FILE *graph_openDbToAppend(char *dbName)
{
    FILE *temp = NULL;
    char *finalDbName = (char *)calloc(GRAPH_MAX_DB_PATH_LENGTH, sizeof(char));

    if (!_graph_dbNamePathConverter(dbName, finalDbName))
    {
        free(finalDbName);
        return NULL;
    }
    else
    {
        temp = fopen(finalDbName, "a");
        free(finalDbName);
        return temp;
    }
}

/*
Funzione: graph_openDbToRead
----------
Apre il file indicato in modalità "read".
Lunghezza massima del nome accettato e' di GRAPH_MAX_DB_NAME (20) caratteri.
----------
Ritorno:
-> Puntatore a FILE in caso di successo.
-> Puntatore NULL nel caso non sia stato possibile creare il file.
*/
FILE *graph_openDbToRead(char *dbName)
{
    FILE *temp = NULL;
    char *finalDbName = (char *)calloc(GRAPH_MAX_DB_PATH_LENGTH, sizeof(char));

    if (!_graph_dbNamePathConverter(dbName, finalDbName))
    {
        free(finalDbName);
        return NULL;
    }
    else
    {
        temp = fopen(finalDbName, "r");
        free(finalDbName);
        return temp;
    }
}

/*
Funzione: graph_closeDb
----------
Chiude il file specificato e imposta la variabile a NULL.
----------
Ritorno:
-> 0 in caso di successo.
-> 1 in caso di insuccesso.
*/
int graph_closeDb(FILE **dbFile)
{
    if ((dbFile == NULL) || (*dbFile == NULL))
        return 0;
    else
    {
        fclose(*dbFile);
        *dbFile = NULL;
        return 1;
    }
}

/*
Funzione: graph_deleteDb
----------
Elimina il file di dati del grafo.
Lunghezza massima del nome accettato e' di GRAPH_MAX_DB_NAME (20) caratteri.
----------
Ritorno:
-> 0 in caso di successo.
-> Altro valore in caso di insuccesso.
*/
int graph_deleteDb(char *dbName)
{
    char *finalDbName = (char *)calloc(GRAPH_MAX_DB_PATH_LENGTH, sizeof(char));

    if (!_graph_dbNamePathConverter(dbName, finalDbName))
    {
        free(finalDbName);
        return -1;
    }
    else
    {
        int result = remove(finalDbName);
        free(finalDbName);
        return result;
    }
}

/*
Prima parte ricorsiva della successiva funzione graph_writeGraphOnDb.
Scrive su file i nodi del grafo.
*/
static unsigned _graph_writeGraphNodesOnDb(FILE *db, AdjacencyGraphNode **array, unsigned arrayLenth,
                                           unsigned currentPosition)
{
    if (currentPosition >= arrayLenth)
        return 0;
    else if ((array[currentPosition]) && (!array[currentPosition]->isDisabled))
    {
        fprintf(db, "%d;%s;\n", array[currentPosition]->key, array[currentPosition]->name);
        return 1 + _graph_writeGraphNodesOnDb(db, array, arrayLenth, currentPosition + 1);
    }
    else
        return _graph_writeGraphNodesOnDb(db, array, arrayLenth, currentPosition + 1);
}

/*
Seconda parte ricorsiva della successiva funzione graph_writeGraphOnDb.
Scrive su file gli archi del grafo.
*/
static unsigned _graph_writeGraphNodesAdjListOnDb(FILE *db, AdjacencyGraphNode **array, unsigned arrayLength,
                                                  unsigned currentPosition)
{
    if (currentPosition >= arrayLength)
        return 0;
    else if ((array[currentPosition]) && (!array[currentPosition]->isDisabled))
    {
        AdjacencyListNode *temp = array[currentPosition]->adjacencyListHead;
        unsigned numberOfArches = 0;

        while (temp)
        {
            fprintf(db, "%d;%d;%d;%d;\n", array[currentPosition]->key, temp->destinationKey, temp->pathLength,
                    temp->supportedWeight);
            temp = temp->next;
            numberOfArches++;
        }
        return numberOfArches + _graph_writeGraphNodesAdjListOnDb(db, array, arrayLength, currentPosition + 1);
    }
    else
        return _graph_writeGraphNodesAdjListOnDb(db, array, arrayLength, currentPosition + 1);
}

/*
Funzione: graph_writeGraphOnDb
----------
Scrive su file il grafo specificato.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_writeGraphOnDb(FILE *db, AdjacencyGraph *graph, unsigned *numberOfWriteNodes, unsigned *numberOfWriteArches)
{
    if (graph_isNull(graph))
    {
        printf("Errore in writeNodeListOnDb: il puntatore passato era NULL.\n");
        return 0;
    }
    else if (graph_isEmpty(graph))
    {
        printf("Attenzione: il grafo e' vuoto.\n");
        return 0;
    }
    else
    {
        unsigned numberOfNodes, numberOfArhes;

        numberOfNodes = _graph_writeGraphNodesOnDb(db, graph->nodeArray, graph->arrayLength, 0);
        fprintf(db, "%s\n", GRAPH_FILE_DELIMETER);
        numberOfArhes = _graph_writeGraphNodesAdjListOnDb(db, graph->nodeArray, graph->arrayLength, 0);

        if (numberOfWriteNodes)
            *numberOfWriteNodes = numberOfNodes;
        if (numberOfWriteArches)
            *numberOfWriteArches = numberOfArhes;
        return 1;
    }
}

/*
Funzione: graph_loadGraphFromDb
----------
Carica in memoria il grafo specificato.
----------
Ritorno:
-> 1 in caso di successo.
-> 0 altrimenti.
*/
int graph_loadGraphFromDb(FILE *db, AdjacencyGraph *graph, unsigned *numberOfLoadNodes, unsigned *numberOfLoadArches)
{
    if ((db == NULL) || (graph == NULL))
    {
        printf("Errore in loadGraphDb: il puntatore passato era NULL.\n");
        return 0;
    }
    else if (!graph_isEmpty(graph))
    {
        printf("Errore in loadGraphDb: il grafo passato non e' vuoto.\n");
        return 0;
    }
    else
    {
        char tempRecord[GRAPH_MAX_RECORD_LENGTH];
        char *token;
        int tempKey;
        char *tempName;
        AdjacencyArc tempArc;
        int tempDestinationKey;
        int tempPathLength;
        int tempSupportedWeight;

        while (fgets(tempRecord, GRAPH_MAX_RECORD_LENGTH, db))
        {
            if (!strcmp(tempRecord, GRAPH_FILE_DELIMETER))
                break;
            token = strtok(tempRecord, ";");
            tempKey = atoi(token);
            token = strtok(NULL, ";");
            tempName = strdup(token);
            graph_addNodeWithName(graph, tempKey, tempName);
            free(tempName);
        }

        while (fgets(tempRecord, GRAPH_MAX_RECORD_LENGTH, db))
        {
            // printf("TempRecord -> %s\n", tempRecord);
            token = strtok(tempRecord, ";");
            tempKey = atoi(token);
            token = strtok(NULL, ";");
            tempDestinationKey = atoi(token);
            token = strtok(NULL, ";");
            tempPathLength = atoi(token);
            token = strtok(NULL, ";");
            tempSupportedWeight = atoi(token);

            graph_setArc(&tempArc, tempKey, tempDestinationKey, tempPathLength, tempSupportedWeight);
            // graph_addBidirectionalArc(graph, &tempArc);
            graph_addDirectionalArc(graph, &tempArc);
        }

        return 1;
    }
}