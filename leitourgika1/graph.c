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
int createNode(graphP myGraph, char *nodeIdentifier){
    listP newNode = (listP)malloc(sizeof(list));
    if(!newNode)
        err_exit("Unable to allocate memory for new node");

    listP tempList = myGraph->adjList;

    while(tempList->next != NULL){
        if( !strcmp(tempList->head->nodeId, nodeIdentifier) ){
            printf("Node %s already exists. Aborting insertion operation and returning to option selection.\n", nodeIdentifier);
            return -1;
        }
        tempList = tempList->next;
    }

    newNode->head->nodeId = nodeIdentifier;
    newNode->next = NULL;
    tempList->next = newNode;
    myGraph->num_vertices++;

    return 1;
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
    graph->adjList->head = NULL;
    graph->adjList->next = NULL;
    graph->adjList->num_members = 0;
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
int addEdge(graph *graph, char *idSource, char *idDest){
    /* Add an edge from src to dst in the adjacency list*/
    listP tempList = graph->adjList;
    nodeP destNode = NULL;
    while(tempList){
        if( !strcmp(tempList->head->nodeId, idDest) )
            destNode = tempList->head;
        tempList = tempList->next;
    }
    if( destNode == NULL){
        printf("%s does not exist as a node. Aborting insert edge operation and returning to option select.\n", idDest);
        return -1;
    }
    tempList = graph->adjList;
    while(tempList){
        if( !strcmp(tempList->head->nodeId, idSource) ){
            nodeP tempNode = tempList->head;
            //Add Edge
        }
        tempList = tempList->next;
    }
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
