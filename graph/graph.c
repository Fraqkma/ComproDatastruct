#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "utils.h"

struct Graph* graph=NULL;

struct Node* createNode(int dest,int weight){
    struct Node* newNode=malloc(sizeof(struct Node));
    newNode->dest=dest;
    newNode->weight=weight;
    newNode->next=NULL;
    return newNode;
}

void initGraph(int vertices){
    graph = malloc(sizeof(struct Graph));
    graph->V=vertices;
    graph->adjList=malloc(vertices *sizeof(struct Node*));

    for(int i=0;i<vertices;i++){
        graph->adjList[i]=NULL;
    }
}

void addEdge(int src,int dest,int weight){
    struct Node* newNode=createNode(dest,weight);
    newNode->next=graph->adjList[src];
    graph->adjList[src]=newNode;

    struct Node* reverseNode=createNode(dest,weight);
    reverseNode->next=graph->adjList[src];
    graph->adjList[src]=reverseNode;
}

void printGraph(){
    for(int i=0;i<graph->V;i++){
        struct Node* temp=graph->adjList[i];
        if(temp==NULL){
            continue;
        }

        printf("%s -> ",getNodeName(i));
        while(temp){
            printf("(%s,%d) ", getNodeName(temp->dest), temp->weight);
            temp=temp->next;
        }
        printf("\n");
    }
}

