#ifndef graphlist_h
#define graphlist_h

/********** COSTANTS **********/

#define GRAPH_DB_PATH "db/"
#define GRAPH_DB_EXTENSION ".txt"
#define GRAPH_MAX_DB_NAME_LENGTH 20
#define GRAPH_MAX_DB_PATH_LENGTH 28 //Percorso[db/] + nome[20 char] + estensione[.txt] + '\0'.
#define GRAPH_MAX_RECORD_LENGTH 100
#define GRAPH_FILE_DELIMETER "<END>\n"

/********** TYPES **********/

//Struttura per errori
typedef struct AdjacencyError
{
    int genericError;
} AdjacencyError;

//Struttura per arco
typedef struct AdjacencyArc
{
    int startingKey;
    int destinationKey;
    int pathLength;
    int supportedWeight;
} AdjacencyArc;

//Struttura del nodo della lista di adiacenza.
typedef struct AdjacencyListNode
{
    int destinationKey;
    int pathLength;
    int supportedWeight;
    struct AdjacencyListNode *next;
} AdjacencyListNode;

//Struttura del nodo del grafo.
typedef struct AdjacencyGraphNode
{
    int key;
    int isDisabled;
    int isVisited;
    int predecessorPosition;
    int distance;
    char *name;
    unsigned numberOfInArches;
    unsigned numberOfOutArches;
    AdjacencyListNode *adjacencyListHead;
} AdjacencyGraphNode;

//Struttura della testa del grafo.
typedef struct AdjacencyGraph
{
    unsigned arrayLength;
    unsigned numberOfNodes;
    AdjacencyGraphNode **nodeArray;
} AdjacencyGraph;

/********** PROTOTYPES **********/

/* Prototipi sugli errori */

AdjacencyError *graphlist_newError();
int graph_setErrorCode(AdjacencyError *error, int errorCode);
int graph_getErrorCode(AdjacencyError *error);

/* Prototipi sugli archi */

int graph_setArc(AdjacencyArc *arc, int startingKey, int destinationKey, int pathLength, int supportedWeight);
int graph_getArcStartingKey(AdjacencyArc *arc, AdjacencyError *error);
int graph_getArcDestinationKey(AdjacencyArc *arc, AdjacencyError *error);
int graph_getPathLength(AdjacencyArc *arc, AdjacencyError *error);

/* Prototipi sui nodi */

unsigned graph_findPositionByKey(AdjacencyGraphNode **array, unsigned arrayLength, int keyToFind,
                                         AdjacencyError *error);
int graph_isNull(AdjacencyGraph *graph);
int graph_isEmpty(AdjacencyGraph *graph);
AdjacencyGraph *graph_newGraph(unsigned initialNumberoOfNodes);
int graph_reallocNodeArray(AdjacencyGraph *graph, unsigned newLength);
int graph_addNode(AdjacencyGraph *graph, int key);
int graph_addNodeWithName(AdjacencyGraph *graph, int key, char *name);
int graph_deleteNode(AdjacencyGraph *graph, int keyToDelete);
int graph_disableNode(AdjacencyGraph *graph, int keyToDisable);
int graph_deleteGraph(AdjacencyGraph **graph);
void graph_printGraph(AdjacencyGraph *graph);
int graph_addDirectionalArc(AdjacencyGraph *graph, AdjacencyArc *arc);
int graph_addBidirectionalArc(AdjacencyGraph *graph, AdjacencyArc *arc);
int graph_deleteBidirectionalArc(AdjacencyGraph *graph, AdjacencyArc *arc);
unsigned graph_getNumberOfGraphNodes(AdjacencyGraph *graph);
unsigned graph_getNodeGrade(AdjacencyGraph *graph, int key);
int graph_findDijkstraPath(AdjacencyGraph *graph, int startKey, int destinationKey, int driverWeight);

/* Prototipi sui file */

FILE *graph_createNewDb(char *dbName);
FILE *graph_openDbToAppend(char *dbName);
FILE *graph_openDbToRead(char *dbName);
int graph_closeDb(FILE **dbFile);
int graph_deleteDb(char *dbName);
int graph_writeGraphOnDb(FILE *db, AdjacencyGraph *graph, unsigned *numberOfWriteNodes, unsigned *numberOfWriteArches);
int graph_loadGraphFromDb(FILE *db, AdjacencyGraph *graph, unsigned *numberOfLoadNodes, unsigned *numberOfLoadArches);

#endif