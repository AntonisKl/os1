/*graph.h*/
#ifndef _GRAPH_H_
#define _GRAPH_H_

/* Adjacency list node*/
typedef struct node
{
	char *nodeId;
	char *destId = NULL;
	int edgeWeight;
    struct node *next; /*Pointer to the next node*/
}node, *nodeP;

/* Adjacency list */
typedef struct adjlist
{
    int num_members;           /*number of members in the list (for future use)*/
    node *head;      /*head of the adjacency linked list*/
    adjlist *next;
}list, *listP;

/* Graph structure. A graph is a list of adjacency lists. */
typedef struct graph
{
    int num_vertices;         /*Number of vertices*/
    listP adjList;     /*Adjacency lists' array*/
}graph, *graphP;

#endif