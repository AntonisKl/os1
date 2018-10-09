#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/* Exit function to handle fatal errors*/
void err_exit(char* msg){
    printf("Error: %s \nExiting...\n", msg);
    exit(1);
}

/* Function to create an adjacency list node*/
nodeP createNode(int v){
    nodeP newNode = (nodeP)malloc(sizeof(node));
    if(!newNode)
        err_exit("Unable to allocate memory for new node");

    newNode->vertex = v;
    newNode->next = NULL;

    return newNode;
}

/* Function to create a graph with n vertices*/
graphP createGraph(int n){
    //Allocate space for the graph
    graphP graph = (graphP)malloc(sizeof(graph));
    if(!graph)
        err_exit("Unable to allocate memory for graph");
    //Store number of vertices
    graph->num_vertices = n;

    /* Create an array of adjacency lists*/
    graph->adjListArr = (listP)malloc(n * sizeof(list));
    if(!graph->adjListArr)
        err_exit("Unable to allocate memory for adjacency list array");

    for(int i = 0; i < n; i++){
        //Initialize adjacency list nodes
        graph->adjListArr[i].head = NULL;
        graph->adjListArr[i].num_members = 0;
    }
    return graph;
}

/*Destroys the graph*/
void destroyGraph(graphP graph){
    if(graph){
        if(graph->adjListArr){
            /*Free up the nodes*/
            for (int i = 0; i < graph->num_vertices; i++){
                nodeP adjListPtr = graph->adjListArr[i].head;
                while (adjListPtr){
                    nodeP tmp = adjListPtr;
                    adjListPtr = adjListPtr->next;
                    free(tmp);
                }
            }
            /*Free the adjacency list array*/
            free(graph->adjListArr);
        }
        /*Free the graph*/
        free(graph);
    }
}

/* Adds an edge to a graph*/
void addEdge(graph *graph, int src, int dest){
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

// int main(){
//     graphP undir_graph = createGraph(5);
//     addEdge(undir_graph, 0, 1);
//     addEdge(undir_graph, 0, 4);
//     addEdge(undir_graph, 1, 2);
//     addEdge(undir_graph, 1, 3);
//     addEdge(undir_graph, 1, 4);
//     addEdge(undir_graph, 2, 3);
//     addEdge(undir_graph, 3, 4);
//     addEdge(undir_graph, 4, 0);

//     printf("\nDIRECTED GRAPH");
//     displayGraph(undir_graph);
//     destroyGraph(undir_graph);

//     return 0;
// }

