#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/* 
    A graph is comprised of a list (in our case, the nodes) 
    of lists (in our case, the edges). 
    Each node has an identifier (a string), which is used as an argument 
    for when the user wants to add a new edge between two nodes. 
*/

/* Exit function to handle fatal errors*/
void err_exit(char* msg){
    printf("Error: %s \nExiting...\n", msg);
    exit(1);
}

/* Function to create an adjacency list node*/
nodeP createNode(graphP myGraph, char *nodeIdentifier){
    listP newNode = (listP)malloc(sizeof(list));
    if(!newNode)
        err_exit("Unable to allocate memory for new node");

    listP tempList = myGraph->adjList;

    while(tempList->next != NULL){
        tempList = tempList->next;
    }

    newNode->head->data = nodeIdentifier;
    newNode->next = NULL;
    tempList->next = newNode;
    myGraph->num_vertices++;

    return newNode;
}

/* Function to create a graph with n vertices*/
graphP createGraph(){
    //Allocate space for the graph
    graphP graph = (graphP)malloc(sizeof(graph));
    if(!graph)
        err_exit("Unable to allocate memory for graph");

    //Store number of vertices
    graph->num_vertices = 0;

    //Initialize adjacency list nodes
    graph->adjList.head = NULL;
    graph->adjList.next = NULL;
    graph->adjList.num_members = 0;
    return graph;
}

/*Destroys the graph*/
void destroyGraph(graphP graph){
    if(graph){
        if(graph->adjList){
            /*Free up the nodes*/
            listP tempList = graph->adjList;
            while(tempList){
                nodeP adjListPtr = graph->adjList->head;
                while (adjListPtr){
                    nodeP tmp = adjListPtr;
                    adjListPtr = adjListPtr->next;
                    free(tmp);
                }
                listP freeList = tempList;
                tempList = tempList->next;
                free(freeList);
            }
            /*Free the adjacency list array*/
            free(graph->adjList);
        }
        /*Free the graph*/
        free(graph);
    }
}

/* Adds an edge to a graph*/
void addEdge(graph *graph, int idSource, int idDest){
    /* Add an edge from src to dst in the adjacency list*/
    nodeP newNode = createNode(dest);
    newNode->next = graph->adjListArr[src].head;
    graph->adjListArr[src].head = newNode;
    graph->adjListArr[src].num_members++;
}

/* Function to print the adjacency list of graph*/
void displayGraph(graphP graph){
    int i;
    for (i = 0; i < graph->num_vertices; i++){
        nodeP adjListPtr = graph->adjListArr[i].head;
        printf("\n%d: ", i);
        while (adjListPtr){
            printf("%d->", adjListPtr->vertex);
            adjListPtr = adjListPtr->next;
        }
        printf("NULL\n");
    }
}
