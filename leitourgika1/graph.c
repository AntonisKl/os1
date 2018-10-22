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
        edgeP adjListPtr = tempList->head;
        printf("%s: \t", tempList->nodeId);
        while (adjListPtr != NULL){
            printf("%s/%d ->", adjListPtr->edgeId, adjListPtr->edgeWeight);
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

    newNode->head = (edgeP)malloc(sizeof(edge));
    newNode->nodeId = (char*)malloc(10*sizeof(char));

    listP tempList = myGraph->adjList;

    while(tempList != NULL){
        if( !strcmp(tempList->nodeId, nodeIdentifier) ){
            printf("Node %s already exists. Aborting insertion operation and returning to option selection.\n", nodeIdentifier);
            return -1;
        }
        if(tempList->next != NULL){
            tempList = tempList->next;
        }
        else
            break;
    }

    strcpy(newNode->nodeId, nodeIdentifier);
    newNode->next = NULL;

    strcpy(tempList->nodeId, newNode->nodeId);
    tempList->head = (edgeP)malloc(sizeof(edge));
    tempList->head->edgeId = (char*)malloc(10*sizeof(char));
    tempList->next = (listP)malloc(sizeof(list));
    tempList->next->nodeId = (char*)malloc(sizeof(char));

    myGraph->num_vertices++;

    return 1;
}

// listP edgeDelete(listP currP, char *nodeId, char *edgeId, int weight){
//   /* See if we are at end of list. */
//   if (currP == NULL)
//     return NULL;
//   if (!strcmp(currP->nodeId, nodeId)) {
//     listP tempNextP;
//     edgeP currEdge = currP->head;
//     edgeP nextEdge;
//     while(currEdge!=NULL){
        // if( !strcmp(currEdge->edgeId, edgeId) && currEdge->edgeWeight == weight ){
        //     nextEdge = currEdge->next;
        //     free(currEdge);
        //     currEdge = nextEdge;
        // }
        // currEdge = currEdge->next;
//     }
//   }
//   currP->next = edgeDelete(currP->next, nodeId, edgeId, weight);
//   return currP;
// }

listP nodeDelete(listP currP, char *id)
{
  /* See if we are at end of list. */
  if (currP == NULL)
    return NULL;
  if (!strcmp(currP->nodeId, id)) {
    listP tempNextP;
    edgeP currEdge = currP->head;
    edgeP nextEdge;
    while(currEdge!=NULL){
        nextEdge = currEdge->next;
        free(currEdge);
        currEdge = nextEdge;
    }
    tempNextP = currP->next;
    free(currP);
    return tempNextP;
  }
  currP->next = nodeDelete(currP->next, id);
  return currP;
}

int deleteEdge(graphP myGraph, char *nodeId, char *edgeId, int weight){
    //myGraph->adjList = edgeDelete(myGraph->adjList, nodeId, edgeId, weight);
    listP tempList = myGraph->adjList;
    while(tempList != NULL){
        edgeP tempEdge = tempList->head;
        edgeP nextEdge;
        while(tempEdge != NULL){
            if( !strcmp(tempEdge->edgeId, edgeId) && tempEdge->edgeWeight == weight ){
                nextEdge = tempEdge->next;
                free(tempEdge);
                tempEdge = nextEdge;
            }
            tempEdge = tempEdge->next;
        }
        tempList = tempList->next;
    }
}

int modifyWeight( graphP myGraph, char *nodeId, char *edgeId, int oldWeight, int newWeight){
    listP tempList = myGraph->adjList;
    while(tempList != NULL){
        edgeP tempEdge = tempList->head;
        while(tempEdge != NULL){
            if( !strcmp(tempEdge->edgeId, edgeId) && tempEdge->edgeWeight == oldWeight ){
                tempEdge->edgeWeight = newWeight;
                return 1;
            }
            tempEdge = tempEdge->next;
        }
        tempList = tempList->next;
    }
}

/* Function to delete an adjacency list node*/
int deleteNode(graphP myGraph, char *nodeIdentifier){
    myGraph->adjList = nodeDelete(myGraph->adjList, nodeIdentifier);
    return 1;
}

int showTransactions(graphP myGraph, char *receivingNodeId){
    listP tempList = myGraph->adjList;
    while(tempList){
        edgeP tempEdge = tempList->head;
        while(tempEdge){
            if(!strcmp(tempEdge->edgeId, receivingNodeId)){
                printf("Node %s is receiving a transaction weighing %d from node %s\n", 
                tempEdge->edgeId, tempEdge->edgeWeight, tempList->nodeId);
            }
            tempEdge = tempEdge->next;
        }
        tempList = tempList->next;
    } 
}

/* Function to create a graph with n vertices*/
graphP createGraph(){    
    //Allocate space for the graph
    graphP graph = (graphP)malloc(sizeof(graph));
    if(!graph)
        err_exit("Unable to allocate memory for graph");

    graph->adjList = (listP)malloc(sizeof(list));
    graph->adjList->nodeId = (char*)malloc(10*sizeof(char));
    // graph->adjList->head->nodeId = "gweoij";
    graph->adjList->head = (edgeP)malloc(sizeof(edge));
    graph->adjList->head->next = (edgeP)malloc(sizeof(edge));
    graph->adjList->next = NULL;
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
                edgeP adjListPtr = graph->adjList->head;
                while (adjListPtr){
                    edgeP tmp = adjListPtr;
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
    edgeP destNode = NULL;
    while(tempList){
        if( !strcmp(tempList->nodeId, idDest) )
            destNode = tempList->head;
        tempList = tempList->next;
    }
    if( destNode == NULL){
        printf("%s does not exist as a node. Aborting insert edge operation and returning to option select.\n", idDest);
        return -1;
    }
    tempList = graph->adjList;
    while(tempList){
        if( !strcmp(tempList->nodeId, idSource) ){
            edgeP tempEdge = tempList->head;
            while(tempEdge != NULL){
                if(tempEdge->next != NULL){
                    tempEdge = tempEdge->next;
                }
                else
                    break; 
            }
            //Add Edge
            strcpy(tempEdge->edgeId, idDest);
            tempEdge->edgeWeight = weight;
            tempEdge->next = (edgeP)malloc(sizeof(edge));
            tempEdge->next->edgeId = (char*)malloc(sizeof(char));
        }
        tempList = tempList->next;
    }

    graph->adjList->num_members++;
}


