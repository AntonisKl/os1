#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "stack.h"
#include "shared.h"
//test
FILE *fptrWrite;

/* 
    A graph is comprised of a list (in our case, the nodes) 
    of lists (in our case, the edges). 
    Each node has an identifier (a string), which is used as an argument 
    for when the user wants to add a new edge between two nodes. 
*/

/*
 * Exit function to handle fatal errors
 */
void err_exit(char* msg){
    printf("Error: %s \nReturning...\n", msg);
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
        fprintf(fptrWrite, "%s: \t", tempList->nodeId);
        while (adjListPtr != NULL){
            fprintf(fptrWrite, "%s/%d ->", adjListPtr->edgeId, adjListPtr->edgeWeight);
            adjListPtr = adjListPtr->next;
        }
        fprintf(fptrWrite, "\n");
        tempList = tempList->next;
    }
}

/*
 * Function to create a graph node
 */
int createNode(graphP myGraph, char *nodeIdentifier){
    if(!newNode)
        err_exit("Unable to allocate memory for new node");

    listP tempList = myGraph->adjList;

    while(tempList != NULL){
        if( !strcmp(tempList->nodeId, nodeIdentifier) ){
            fprintf(fptrWrite, "Node |%s| Exists;\n", nodeIdentifier);
            return -1;
        }
        if(tempList->next != NULL){            
            tempList = tempList->next;
        }
        else
            break;
    }
    //Allocate space for the new node and initialize it
    strcpy(tempList->nodeId, nodeIdentifier);
    tempList->head = (edgeP)malloc(sizeof(edge));
    tempList->head->edgeId = (char*)malloc(10*sizeof(char));
    tempList->next = (listP)malloc(sizeof(list));
    tempList->next->nodeId = (char*)malloc(sizeof(char));

    myGraph->num_vertices++;
    fprintf(fptrWrite, "- Inserted |%s|\n",nodeIdentifier);
    return 1;
}

/*
 * Function that deletes a top-level node from the graph,
 * together with its edges
 */
listP nodeDelete(listP currP, char *id){
  /* See if we are at end of list. */
  if (currP == NULL){
    fprintf(fptrWrite, "Node |%s| does not exist - abort-d;\n", id);
    return NULL;
  }
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

/*
 * Function used to delete an edge between two nodes given the edge's weight
 */
int deleteEdgeWithoutWeight(graphP myGraph, char *nodeId, char *edgeId){
    listP tempList = myGraph->adjList;
    edgeP countEdge = NULL;
    listP countNode = NULL;
    //Traverse big list
    while(tempList != NULL){
        if( !strcmp(tempList->nodeId, nodeId) ){
            edgeP tempEdge = tempList->head;
            edgeP nextEdge;
            //Traverse sub-lists
            while(tempEdge != NULL){
                if( !strcmp(tempEdge->edgeId, edgeId)){
                    //Free memory
                    nextEdge = tempEdge->next;
                    tempList->head = nextEdge;
                    free(tempEdge);
                    tempEdge = nextEdge;
                    countEdge = tempEdge;
                    fprintf(fptrWrite, "- Del-all-vertex |%s|->|%s|", nodeId, edgeId);
                }
                tempEdge = tempEdge->next;
            }
            if(countEdge == NULL){
                fprintf(fptrWrite, "|%s| does not exist - abort-l;\n", edgeId);
                return 1;
            }
            countNode = tempList;
        }
        tempList = tempList->next;
    }
    if(countNode == NULL){
        fprintf(fptrWrite, "|%s| does not exist - abort-l;\n", nodeId);
        return 1;
    }
}

/*
 * Function used to delete an edge between two nodes given the edge's weight
 */
int deleteEdge(graphP myGraph, char *nodeId, char *edgeId, int weight){
    listP tempList = myGraph->adjList;
    edgeP countEdge = NULL;
    listP countNode = NULL;
    //Traverse big list
    while(tempList != NULL){
        if( !strcmp(tempList->nodeId, nodeId) ){
            edgeP tempEdge = tempList->head;
            edgeP nextEdge;
            //Traverse sub-lists
            while(tempEdge != NULL){
                if( !strcmp(tempEdge->edgeId, edgeId) && tempEdge->edgeWeight == weight ){
                    //Free memory
                    nextEdge = tempEdge->next;
                    tempList->head = nextEdge;
                    free(tempEdge);
                    tempEdge = nextEdge;
                    countEdge = tempEdge;
                    fprintf(fptrWrite, "- Del-vertex |%s|->%d->|%s|", nodeId, weight, edgeId);
                    return 1;
                }
                tempEdge = tempEdge->next;
            }
            if(countEdge == NULL){
                fprintf(fptrWrite, "|%s| does not exist - abort-l;\n", edgeId);
                return 1;
            }
            countNode = tempList;
        }
        tempList = tempList->next;
    }
    if(countNode == NULL){
        fprintf(fptrWrite, "|%s| does not exist - abort-l;\n", nodeId);
        return 1;
    }
}


/*
 * Function used to modify the weight of an edge between two nodes
 */
int modifyWeight( graphP myGraph, char *nodeId, char *edgeId, int oldWeight, int newWeight){
    listP tempList = myGraph->adjList;
    int countWeight = 0;
    edgeP countEdge = NULL;
    listP countNode = NULL;
    //Traverse big list
    while(tempList != NULL){
        if(!strcmp(tempList->nodeId, nodeId)){
            edgeP tempEdge = tempList->head;        
            //Traverse sub-lists
            while(tempEdge != NULL){
                if( !strcmp(tempEdge->edgeId, edgeId)){
                    if (tempEdge->edgeWeight == oldWeight ){
                        //Modify the weight
                        tempEdge->edgeWeight = newWeight;
                        fprintf(fptrWrite, "- Mod-vertex |%s|->%d->|%s|\n", nodeId, newWeight, edgeId);
                        return 1;
                    }
                    else{
                        countWeight++;
                    }
                }
                else{
                    countEdge++;
                }
                tempEdge = tempEdge->next;
                if(countWeight == tempList->num_members){
                    fprintf(fptrWrite, "- |%s|->%d->|%s| does not exist - abort-m;\n", nodeId, oldWeight, edgeId);
                    return 1;
                }
            }
            //Check if edge passed as argument exists
            if(countEdge == NULL){
                fprintf(fptrWrite, "- |%s| does not exist - abort-m;\n", edgeId);
                return 1;
            }
        }
        tempList = tempList->next;       
    }
    //Check if node passed as argument exists
    if(countNode == NULL){
        fprintf(fptrWrite, "- |%s| does not exist - abort-m;\n", nodeId);
        return 1;
    } 
}

/* 
 * Function to delete an adjacency list node
 */
int deleteNode(graphP myGraph, char *nodeIdentifier){
    myGraph->adjList = nodeDelete(myGraph->adjList, nodeIdentifier);
    fprintf(fptrWrite, "Deleted |%s|\n", nodeIdentifier);
    return 1;
}

/*
 * Function used to show receiving transactions of a node in the graph
 */
int showTransactions(graphP myGraph, char *receivingNodeId){
    listP tempList = myGraph->adjList;
    int countNodes = 0;
    fprintf(fptrWrite, "- No-rec-edges %s\n", receivingNodeId);
    fprintf(fptrWrite, "- Rec-edges ");
    //Traverse big list and sub-lists
    while(tempList){        
        edgeP tempEdge = tempList->head;
        while(tempEdge){
            //Whenever you find an edge with the argument ID print it
            if(!strcmp(tempEdge->edgeId, receivingNodeId)){
                fprintf(fptrWrite, "|%s|->%d->|%s|\n", tempList->nodeId, tempEdge->edgeWeight, tempEdge->edgeId);
                countNodes--;
            }
            else{
                countNodes++;
            }
            tempEdge = tempEdge->next;
        }
        tempList = tempList->next;
        if(countNodes == myGraph->num_vertices){
            fprintf(fptrWrite, "- |%s| does not exist - abort-r;\n", receivingNodeId);
            return 0;
        }
    } 
}

/*
 * Function used to trace cash flow between two graph nodes
 */
int traceFlow( graphP myGraph, char *nodeIdStart, char *nodeIdEnd, int maxRouteLength, int total_cost){
    listP tempList = myGraph->adjList;
    listP testNode = NULL;
    edgeP testEdge = NULL;
    while(tempList){
        if(!strcmp(tempList->nodeId, nodeIdStart)){
            testNode = tempList;
            //Recursively check paths, for each recursive call subtract one off the route length.
            //When it reaches one (edge is inside the node's sublist), check the node sublists for 
            // the end node ID
            if( maxRouteLength == 1 ){
                edgeP tempEdge = tempList->head;
                while(tempEdge){
                    if( !strcmp(tempEdge->edgeId, nodeIdEnd) ){
                        testEdge = tempEdge;
                        total_cost += tempEdge->edgeWeight;
                        fprintf(fptrWrite, "- Tra-found %d", total_cost);
                        return 1;
                    }                    
                    tempEdge = tempEdge->next;
                }
                if(testEdge == NULL){
                    fprintf(fptrWrite, "|%s| does not exist - abort-l;\n", nodeIdEnd);
                    return 1;
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
    //Check if node1 and node2 passed as arguments exist
    if(testNode == NULL){
        fprintf(fptrWrite, "|%s| does not exist - abort-l;\n", nodeIdStart);
        return 1;
    }
    else{
        fprintf(fptrWrite, "- No-trace from |%s| to |%s|\n", nodeIdStart, nodeIdEnd);
        return 1;
    }
}

/*
 * Function used to find simple circles in graph
 */
int circleFind(graphP myGraph, char *nodeId,  struct StackNode *path){
    listP tempList = myGraph->adjList;
    edgeP countEdge = NULL;
    //Traverse all lists and recursively push nodes in a stack (just like a dfs algorithm)
    //If you find the initial symbol, stop and check stack. If stack contains more than two identical IDs
    //then it's not a simple cycle. Else print the path.
    while(tempList){
        if( !strcmp(tempList->nodeId, nodeId)){
            edgeP tempEdge = tempList->head;
            while(tempEdge){
                if(exists(path, tempEdge->edgeId)){
                    fprintf(fptrWrite, "- Cir-found");
                    while(!isEmpty(path))
                        fprintf(fptrWrite, "|%s|->%d->", pop(&path), tempEdge->edgeWeight);
                    fprintf(fptrWrite, "\n");
                    countEdge = tempEdge;
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
    if(countEdge == NULL){
        fprintf(fptrWrite, "- |%s| does not exist - abort-c;", nodeId);
    }
}

int findCircles(graphP myGraph, char *nodeId, char *firstNode, int minWeight, struct StackNode* path){
    //Works like circleFind (dfs/recursive stack implementation) but you also chekc for the edge minWeight
    listP tempList = myGraph->adjList;
    edgeP countEdge = NULL;
    while(tempList){
        if( !strcmp(tempList->nodeId, nodeId)){
            edgeP tempEdge = tempList->head;
            while(tempEdge){
                if(exists(path, firstNode) && tempEdge->edgeWeight >= minWeight){
                    fprintf(fptrWrite, "- Cir-found");
                    while(!isEmpty(path))
                        fprintf(fptrWrite, "%s -> ", pop(&path));
                    fprintf(fptrWrite, "\n");
                    countEdge = tempEdge;
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
    if(countEdge == NULL){
       fprintf(fptrWrite, "- |%s| does not exist - abort-f;\n", nodeId);
    }
    fprintf(fptrWrite, "- No-circle-found involving |%s| %d\n", nodeId, minWeight);

}

/* Function to create a graph with n vertices*/
graphP createGraph(){    
    //Allocate space for the graph
    graphP graph = (graphP)malloc(sizeof(graph));
    if(!graph)
        err_exit("Unable to allocate memory for graph");

    graph->adjList = (listP)malloc(sizeof(list));
    graph->adjList->nodeId = (char*)malloc(10*sizeof(char));
    graph->adjList->head = (edgeP)malloc(sizeof(edge));
    graph->adjList->head->next = (edgeP)malloc(sizeof(edge));
    graph->adjList->next = NULL;
    graph->adjList->next = (listP)malloc(sizeof(list));
    graph->adjList->next = NULL;
    //Store number of vertices
    graph->num_vertices = 0;

    //Initialize adjacency list nodes
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
                edgeP adjListPtr = tempList->head;
                while (adjListPtr){
                    edgeP tmp = adjListPtr;
                    adjListPtr = adjListPtr->next;
                    free(tmp);
                }
                listP freeList = tempList;
                tempList = tempList->next;
                free(freeList);
            }
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
    //Check if the nodes exist. If they don't, create them.
    if( destNode == NULL){
        createNode(graph, idDest);
    }
    if( sourceNode == NULL){
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
    fprintf(fptrWrite, "- Inserted |%s|->%d->|%s|\n", idSource, weight, idDest);
    graph->adjList->num_members++;
}