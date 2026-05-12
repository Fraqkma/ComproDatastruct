#include <stdio.h>
#include "menu.h"
#include "graph.h"
#include "dijkstra.h"
#include "alternative.h"
#include "block.h"
#include "mapping.h"
#include "utils.h"

void showMenu(){
    printf("\n---Navigating System---\n");
    printf("0 | Exit\n");
    printf("1 | Show Graph\n");
    printf("2 | Find Shortest Path\n");
    printf("3 | Show All Locations\n");
    printf("4 | Block Location\n");
    printf("5 | Unblock Location\n");
    printf("6 | Show Blocked Locations\n");
    printf("7 | Clear Blocked Locations\n");
    printf("Choose: ");
}

void interactMenu(int choice){
    char src[10],dest[10],name[10];
    int node;

    switch (choice){
        case 1:
            printGraph();
            break;
        case 2:
            printf("Enter start position: ");
            scanf("%s",src);
            printf("Enter destination: ");
            scanf("%s",dest);
            int u = findNodeByName(src);
            int v = findNodeByName(dest);

            if (u == -1) {
                u = findAlternativeNode(src);
            }

            if (v == -1) {
                 v = findAlternativeNode(dest);
            }

            if (u == -1 || v == -1) {
                printf("Location not found.\n");
                break;
            }

            dijkstra(u, v);
            break;
        
        case 3:
            showAllLocations();
            break;

        case 4:
            printf("Enter location to block: ");
            scanf("%s", name);

            node = findNodeByName(name);

            if (node == -1) {
                node = findAlternativeNode(name);
            }

            if (node == -1) {
                printf("Location not found.\n");
                break;
            }

            blockNode(node);
            printf("%s is now blocked.\n", name);
            break;

        case 5:
            printf("Enter location to unblock: ");
            scanf("%s", name);

            node = findNodeByName(name);

            if (node == -1) {
                printf("Location not found.\n");
                break;
            }

            unblockNode(node);
            printf("%s is now unblocked.\n", name);
            break;

        case 6:
            printBlockedNodes();
            break;

        case 7:
            clearBlockedNodes();
            printf("All blocked locations cleared.\n");
            break;

        case 0:
            printf("Exiting");
            break;
    }
}