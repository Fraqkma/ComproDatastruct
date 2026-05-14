#include <stdio.h>
#include <string.h>
#include "graph.h"

#define MAX_NODES 100

char nodeNames[MAX_NODES][10];
int nodeCount=0;

// Finds an existing node name, or creates a new index for a new name.
int getNodeIndex(char* name){
    for(int i=0;i<nodeCount;i++){
        if(strcmp(nodeNames[i],name)==0){
            return i;
        }
    }
    strcpy(nodeNames[nodeCount],name);
    return nodeCount++;
}

// Gets the saved name for a node index.
char *getNodeName(int index){
    return nodeNames[index];
}

// Reads the map text file and turns each line into graph edges.
void loadFromFile(char* filename){
    FILE* file=fopen(filename,"r");

    if(file==NULL){
        printf("Cannot open map file: %s\n",filename);
        return;
    }

    char src[10],dest[10];
    int weight;

    while(fscanf(file," %9[^,],%9[^,],%d",src,dest,&weight)==3){
        int u=getNodeIndex(src);
        int v=getNodeIndex(dest);
        addEdge(u,v,weight);       
    }
    
    fclose(file);
}
