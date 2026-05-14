#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "utils.h"
#include "block.h"
#include "pq.h"
#define INF 1000000000 

extern struct Graph* graph;

// Prints the final route by walking backward through the parent array.
void printPath(int parent[],int j){
    if(parent[j]==-1){
        printf("%s ",getNodeName(j));
        return;
    }
    printPath(parent,parent[j]);
    printf("%s ",getNodeName(j));
}

// Finds the shortest available path while skipping blocked locations.
void dijkstra(int src,int dest){
    int dist[100];
    int visited[100]={0};
    int parent[100];
    int pqCapacity;
    struct PriorityQueue* pq;

    if (isNodeBlocked(src)) {
        printf("Start node is blocked. Cannot find path.\n");
        return;
    }

    if (isNodeBlocked(dest)) {
        printf("Destination node is blocked. Cannot find path.\n");
        return;
    }

    for(int i=0;i<graph->V;i++){
        dist[i]=INF;
        parent[i]=-1;
    }
    dist[src]=0;

    pqCapacity = graph->V * graph->V;
    pq = createPQ(pqCapacity);
    push(pq, src, 0);

    while(!isEmpty(pq)){
        struct PQNode current = popMin(pq);
        int u = current.vertex;

        if(u == -1){
            break;
        }

        if(visited[u]){
            continue;
        }

        if(isNodeBlocked(u)){
            continue;
        }

        visited[u]=1;

        if(u == dest){
            break;
        }

        struct Node* temp=graph->adjList[u];
        while(temp){
            int v=temp->dest;
            int weight=temp->weight;

            if (isNodeBlocked(v)) {
                temp = temp->next;
                continue;
            }


            if(!visited[v]&& dist[u]+weight<dist[v]){
                dist[v]=dist[u]+weight;
                parent[v]=u;
                push(pq, v, dist[v]);
            }
            temp=temp->next;
        }
    }

    free(pq->nodes);
    free(pq);

    if (dist[dest] == INF) {
        printf("No available path found.\n");
        return;
    }

    printf("Shortest distance: %d\n",dist[dest]);
    printf("Path: ");
    printPath(parent,dest);
    printf("\n");
}
