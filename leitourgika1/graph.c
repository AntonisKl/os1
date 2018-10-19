#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

/* Function to print the adjacency list of graph*/
void displayGraph(graphP graph){
    int i;
    listP tempList = graph->adjList;
    while(tempList->next != NULL){
        nodeP adjListPtr = tempList->head;
        printf("%s: ", adjListPtr->nodeId);
        while (adjListPtr->next != NULL){
            //printf("\t%s\n", adjListPtr->nodeId);
            adjListPtr = adjListPtr->next;
        }
        printf("\n");
        tempList = tempList->next;
    }
}

/* Function to create an adjacency list node*/
int createNode(graphP myGraph, char *nodeIdentifier){
    //displayGraph(myGraph);
    listP newNode = (listP)malloc(sizeof(list));
    if(!newNode)
        err_exit("Unable to allocate memory for new node");

    newNode->head = (nodeP)malloc(sizeof(node));
    newNode->head->nodeId = (char*)malloc(10*sizeof(char));
    newNode->head->destId = (char*)malloc(10*sizeof(char));

    listP tempList = myGraph->adjList;

    while(tempList != NULL){
        if( !strcmp(tempList->head->nodeId, nodeIdentifier) ){
            printf("Node %s already exists. Aborting insertion operation and returning to option selection.\n", nodeIdentifier);
            return -1;
        }
        if(tempList->next != NULL){
            tempList = tempList->next;
        }
        else
            break;
    }

    strcpy(newNode->head->nodeId, nodeIdentifier);
    newNode->next = NULL;

    strcpy(tempList->head->nodeId, newNode->head->nodeId);

    tempList->head->destId = newNode->head->destId;
    tempList->head->next = (nodeP)malloc(sizeof(node));
    tempList->head->next->nodeId = (char*)malloc(sizeof(char));
    tempList->next = (listP)malloc(sizeof(list));
    tempList->next->head = (nodeP)malloc(sizeof(node));
    tempList->next->head->nodeId = (char*)malloc(sizeof(char));

    printf("templist %s", tempList->head->nodeId );
    myGraph->num_vertices++;

    return 1;
}

/* Function to delete an adjacency list node*/
int createNode(graphP myGraph, char *nodeIdentifier){

    listP tempList = myGraph->adjList;

    while(tempList != NULL){
        if( !strcmp(tempList->head->nodeId, nodeIdentifier) ){
            printf("Node %s already exists. Aborting insertion operation and returning to option selection.\n", nodeIdentifier);
            return -1;
        }
        if(tempList->next != NULL){
            tempList = tempList->next;
        }
        else
            break;
    }

    printf("templist %s", tempList->head->nodeId );
    myGraph->num_vertices++;

    return 1;
}

/* Function to create a graph with n vertices*/
graphP createGraph(){    
    //Allocate space for the graph
    graphP graph = (graphP)malloc(sizeof(graph));
    if(!graph)
        err_exit("Unable to allocate memory for graph");

    graph->adjList = (listP)malloc(sizeof(list));
    graph->adjList->head = (nodeP)malloc(sizeof(node));
    graph->adjList->head->nodeId = (char*)malloc(10*sizeof(char));
    // graph->adjList->head->nodeId = "gweoij";
    graph->adjList->head->next = (nodeP)malloc(sizeof(node));
    graph->adjList->head->next = NULL;
    graph->adjList->next = (listP)malloc(sizeof(list));
    graph->adjList->next = NULL;
    //Store number of vertices
    graph->num_vertices = 0;

    //Initialize adjacency list nodes
    graph->adjList->num_members = 0;
    displayGraph(graph);
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
int addEdge(graph *graph, char *idSource, char *idDest, int weight){
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
    //newNode->next = graph->adjList->head;
    //graph->adjList->head = newNode;
    graph->adjList->num_members++;
}


