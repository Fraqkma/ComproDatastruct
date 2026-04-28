#include <stdio.h>
#include "graph.h"
#include "utils.h"
#define INF 1000000000 

extern struct Graph* graph;

void printPath(int parent[],int j){
    if(parent[j]==-1){
        printf("%s ",getNodeName(j));
        return;
    }
    printPath(parent,parent[j])
    printf("%s ",getNodeName(j));
}

void dijkstra(int src,int dest){
    int dist[100];
    int visited[100]={0};
    int parent[100];

    for(int i=0;i<graph->V;i++){
        dist[i]=INF;
        parent[i]=-1;
    }
    dist[src]=0;

    for(int i=0;i<graph->V -1;i++){
        int u=-1,min=INF;
        for(int j=0;j<graph->V;j++){
            if(!visited[j]&&dist[j]<min){
                min=dist[j];
                u=j;
            }
        }
        if(u==-1){
            break;
        }
        visited[u]=1;

        struct Node* temp=graph->adjList[u];
        while(temp){
            int v=temp->dest;
            int weight=temp->weight;

            if(!visited[v]&& dist[u]+weight<dist[v]){
                dist[v]=dist[u]+weight;
                parent[v]=u;
            }
            temp=temp->next;
        }
    }
    printf("Shortest distance: %d\n",dist[dest]);
    printf("Path: ");
    printPath(parent,dest);
    printf("\n");
}
