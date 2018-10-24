/*graph.h*/
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "stack.c"

/* Adjacency list node*/
typedef struct edge
{
	char *edgeId;
	int edgeWeight;
    struct edge *next; /*Pointer to the next node*/
}edge, *edgeP;

/* Adjacency list */
typedef struct adjlist
{
    int num_members;           /*number of members in the list (for future use)*/
    char *nodeId;
    edge *head;
    struct adjlist *next;
}list, *listP;

/* Graph structure. A graph is a list of adjacency lists. */
typedef struct graph
{
    int num_vertices;         /*Number of vertices*/
    listP adjList;     /*Adjacency lists' array*/
}graph, *graphP;

void err_exit(char* msg);
void displayGraph(graphP graph);
int createNode(graphP myGraph, char *nodeIdentifier);
listP nodeDelete(listP currP, char *id);
int deleteEdge(graphP myGraph, char *nodeId, char *edgeId, int weight);
int modifyWeight( graphP myGraph, char *nodeId, char *edgeId, int oldWeight, int newWeight);
int deleteNode(graphP myGraph, char *nodeIdentifier);
int showTransactions(graphP myGraph, char *receivingNodeId);
int traceFlow( graphP myGraph, char *nodeIdStart, char *nodeIdEnd, int maxRouteLength, int total_cost);
int circleFind(graphP myGraph, char *nodeId,  struct StackNode *path);
int findCircles(graphP myGraph, char *nodeId, char *firstNode, int minWeight, struct StackNode* path);
graphP createGraph();
void destroyGraph(graphP graph);
int addEdge(graph *graph, char *idSource, char *idDest, int weight);
int deleteEdgeWithoutWeight(graphP myGraph, char *nodeId, char *edgeId);

#endif