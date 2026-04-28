#ifndef GRAPH_H
#define GRAPH_H

struct Node{
    int dest;
    int weight;
    struct Node* next;
};

struct Graph {
    int V;
    struct Node** adjList;
}

extern struct Graph* graph; //make struct to global struct that can use in any files

void initGraph(int vertices);
void addEdge(int src,int dest,int weight);
void printfGraph();

#endif //end all if condition if it has