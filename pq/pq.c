#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

void swap(struct PQNode *a,struct PQNode *b){
    struct PQNode temp= *a;
    *a=*b;
    *b=temp;
}

struct PriorityQueue *createPQ(int capacity){
    struct PriorityQueue* pq=malloc(sizeof(struct PriorityQueue));

    pq->size=0;
    pq->capacity=capacity;
    pq->nodes=malloc((size_t)capacity*sizeof(struct PQNode));
    return pq;
}

void heapUp(struct PriorityQueue *pq,int idx){
    while (idx && pq->nodes[(idx - 1)/2].dist > pq->nodes[idx].dist) {
        swap(&pq->nodes[(idx - 1)/2], &pq->nodes[idx]);
        idx = (idx - 1)/2;
    }
}
void push(struct PriorityQueue *pq,int vertex ,int dist){
    if (pq->size >= pq->capacity) {
        printf("Priority queue is full.\n");
        return;
    }

    pq->nodes[pq->size].vertex=vertex;
    pq->nodes[pq->size].dist=dist;

    heapUp(pq,pq->size);

    pq->size++;
}
void heapDown(struct PriorityQueue *pq,int idx){
    int smallest=idx;

    int left=2*idx+1;
    int right=2*idx+2;

    if(left<pq->size && pq->nodes[left].dist < pq->nodes[smallest].dist){
        smallest=left;
    }
    if(right<pq->size && pq->nodes[right].dist < pq->nodes[smallest].dist){
        smallest=right;
    }
    if(smallest!=idx){
        swap(&pq->nodes[idx],&pq->nodes[smallest]);
        heapDown(pq,smallest);
    }
}
struct PQNode popMin(struct PriorityQueue *pq){
    if (isEmpty(pq)) {
        struct PQNode emptyNode = {-1, -1};
        return emptyNode;
    }

    struct PQNode root=pq->nodes[0];

    pq->nodes[0]=pq->nodes[pq->size-1];
    pq->size--;

    heapDown(pq,0);

    return root;
}
int isEmpty(struct PriorityQueue *pq){
    return pq->size==0;
}
