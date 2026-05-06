#ifndef PQ_H
#define PQ_H

struct PQNode {
    int vertex;
    int dist;
};

struct PriorityQueue {
    int size;
    int capacity;
    struct PQNode* nodes;
};

struct PriorityQueue* createPQ(int capacity);

void push(struct PriorityQueue* pq, int vertex, int dist);

struct PQNode popMin(struct PriorityQueue* pq);

int isEmpty(struct PriorityQueue* pq);

#endif