#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "stack.c"

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

/* 
 * Function to print the graph
 * Format is: node: \t edges that start from the node \n
 */
void displayGraph(graphP graph){
    int i;
    listP tempList = graph->adjList;
    while(tempList != NULL){
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

/* Function to create a graph node*/
int createNode(graphP myGraph, char *nodeIdentifier){
    if(!newNode)
        err_exit("Unable to allocate memory for new node");

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

    strcpy(tempList->nodeId, nodeIdentifier);
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

/*
 * Function that deletes a top-level node from the graph,
 * together with its edges
 */
listP nodeDelete(listP currP, char *id)
{
  /* See if we are at end of list. */
  if (currP == NULL)
    return NULL;
  if (!strcmp(currP->nodeId, id)) {
    listP tempNextP;
    edgeP currEdge = currP->head;
    edgeP nextEdge;
    //Free each edge that belongs to that node
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
        if( !strcmp(tempList->nodeId, nodeId) ){
            edgeP tempEdge = tempList->head;
            edgeP nextEdge;
            while(tempEdge != NULL){
                if( !strcmp(tempEdge->edgeId, edgeId) && tempEdge->edgeWeight == weight ){
                    nextEdge = tempEdge->next;
                    tempList->head = nextEdge;
                    free(tempEdge);
                    tempEdge = nextEdge;                    
                    return 1;
                }
                tempEdge = tempEdge->next;
            }
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

int traceFlow( graphP myGraph, char *nodeIdStart, char *nodeIdEnd, int maxRouteLength, int total_cost){
    listP tempList = myGraph->adjList;
    listP testNode = NULL;
    edgeP testEdge = NULL;
    while(tempList){
        if(!strcmp(tempList->nodeId, nodeIdStart)){
            testNode = tempList;
            if( maxRouteLength == 1 ){
                edgeP tempEdge = tempList->head;
                while(tempEdge){
                    if( !strcmp(tempEdge->edgeId, nodeIdEnd) ){
                        testEdge = tempEdge;
                        total_cost += tempEdge->edgeWeight;
                        printf("Route found with total cost %d ", total_cost);
                    }
                    tempEdge = tempEdge->next;
                }
            }
            else{
                edgeP tempEdge = tempList->head;
                while(tempEdge){
                    traceFlow(myGraph, tempEdge->edgeId, nodeIdEnd, maxRouteLength-1, total_cost+tempEdge->edgeWeight);
                    tempEdge = tempEdge->next;
                }
            }
        }
        tempList = tempList->next;
    }
    if(testNode == NULL){
        printf("Node %s does not exist", nodeIdStart);
        return 1;
    }
    if(testEdge == NULL){
        printf("Node %s does not exist", nodeIdEnd);
        return 1;
    }
}

int circleFind(graphP myGraph, char *nodeId,  struct StackNode *path){
    listP tempList = myGraph->adjList;
    
    while(tempList){
        if( !strcmp(tempList->nodeId, nodeId)){

            edgeP tempEdge = tempList->head;

            while(tempEdge){
                //printf("stack %s", tempEdge->edgeId);
                if(exists(path, tempEdge->edgeId)){
                    printf("Circle Found:");
                    while(!isEmpty(path))
                        printf("%s -> ", pop(&path));
                    printf("\n");
                    return 1;
                }
                else{
                    push(&path, tempEdge->edgeId);
                    circleFind(myGraph, tempEdge->edgeId, path);
                }
                path = NULL;
                tempEdge = tempEdge->next;
            }
        }
        tempList = tempList->next;
    }
}

int findCircles(graphP myGraph, char *nodeId, char *firstNode, int minWeight, struct StackNode* path){

    listP tempList = myGraph->adjList;
    
    while(tempList){
        if( !strcmp(tempList->nodeId, nodeId)){

            edgeP tempEdge = tempList->head;

            while(tempEdge){
                //printf("stack %s", tempEdge->edgeId);
                if(exists(path, firstNode) && tempEdge->edgeWeight >= minWeight){
                    printf("Circle Found:");
                    while(!isEmpty(path))
                        printf("%s -> ", pop(&path));
                    printf("\n");
                    return 1;
                }
                else{
                    if( tempEdge->edgeWeight >= minWeight ){
                        push(&path, tempEdge->edgeId);
                        findCircles(myGraph, tempEdge->edgeId, firstNode, minWeight, path);
                    }
                }
                path = NULL;
                tempEdge = tempEdge->next;
            }
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
    edgeP sourceNode = NULL;
    while(tempList){
        if( !strcmp(tempList->nodeId, idDest) )
            destNode = tempList->head;
        if( !strcmp(tempList->nodeId, idSource))
            sourceNode = tempList->head;
        tempList = tempList->next;
    }
    if( destNode == NULL){
        printf("%s does not exist as a node. Inserting node then returning to edge insertion.\n", idDest);
        createNode(graph, idDest);
    }
    if( sourceNode == NULL){
        printf("%s does not exist as a node. Inserting node then returning to edge insertion.\n", idSource);
        createNode(graph, idSource);
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


