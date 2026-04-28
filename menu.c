#include <stdio.h>
#include "menu.h"
#include "graph.h"
#include "dijkstra.h"
#include "utils.h"

void showMenu(){
    printf("\n---Navigating System---\n");
    printf("0 | Exit\n");
    printf("1 | Show Graph\n");
    printf("2 | Find Shortest Path\n");
    printf("Choose: ");
}

void interactMenu(int choice){
    char src[10],dest[10];

    switch (choice){
        case 1:
            printGraph();
            break;
        case 2:
            printf("Enter start position: ");
            scanf("%s",src);
            printf("Enter destination: ");
            scanf("%s",dest);
            int u = getNodeIndex(src);
            int v = getNodeIndex(dest);
            dijkstra(u, v);
            break;
        case 0:
            printf("Exiting");
            break;
    }
}