#include <stdio.h>
#include <string.h>
#include "graph.h"

#define MAX_NODES 100

char NodeNames[MAX_NODES][10];
int nodeCount=0;

int getNodeIndex(char* name){
    for(int i=0;i<nodeCount;i++){
        if(strcmp(nodeNames[i],name)==0){
            return i;
        }
    }
    strcpy(nodeNames[nodeCount],name);
    return NodeCount++;
}

char *getNodeName(int index){
    return nodeNames[index];
}

void loadFromfile(char* filename){
    FILE* file=fopen(filename,"r");

    char src[10],dest[10];
    int weight;

    while(fscanf(file,"%[^,],%[^,],%d\n",src,dest,&weight)!=EOF){ //EOF = End of file so basically just loop untils not found this one optimized by chatGPT
        int u=getNodeIndex(src);
        int v=getNodeIndex(dest);
        addEdge(u,v,weight);       
    }
    
    fclose(file);
}