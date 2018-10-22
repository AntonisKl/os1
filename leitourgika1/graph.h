/*graph.h*/
#ifndef _GRAPH_H_
#define _GRAPH_H_

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

#endif