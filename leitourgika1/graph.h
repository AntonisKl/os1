/*graph.h*/
#ifndef _GRAPH_H_
#define _GRAPH_H_

/* Adjacency list node*/
typedef struct node
{
    int vertex;                /*Index to adjacency list array*/
    struct node *next; /*Pointer to the next node*/
}node, *nodeP;

/* Adjacency list */
typedef struct adjlist
{
    int num_members;           /*number of members in the list (for future use)*/
    node *head;      /*head of the adjacency linked list*/
}list, *listP;

/* Graph structure. A graph is an array of adjacency lists.
   Size of array will be number of vertices in graph*/
typedef struct graph
{
    int num_vertices;         /*Number of vertices*/
    listP adjListArr;     /*Adjacency lists' array*/
}graph, *graphP;

#endif