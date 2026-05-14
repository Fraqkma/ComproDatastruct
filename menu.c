#include <stdio.h>
#include "menu.h"
#include "graph.h"
#include "dijkstra.h"
#include "alternative.h"
#include "block.h"
#include "mapping.h"
#include "utils.h"

// Shows the main commands the user can choose from.
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
    printf("8 | Manage Location Labels\n");
    printf("Choose: ");
}

// Handles adding, deleting, and viewing custom location labels.
void manageLabels(void) {
    int choice;
    char alias[ALTERNATIVE_NAME_SIZE];
    char nodeName[10];

    do {
        printf("\n--- Location Label Manager ---\n");
        printf("0 | Back\n");
        printf("1 | Add or Update Label\n");
        printf("2 | Delete Label\n");
        printf("3 | Show Labels\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter new label: ");
                scanf("%29s", alias);
                printf("Enter real location name: ");
                scanf("%9s", nodeName);

                if (!addAlternativeName(alias, nodeName)) {
                    printf("Cannot add label. Location may not exist or label table is full.\n");
                    break;
                }

                if (!saveAlternativeNames("data/label.txt")) {
                    printf("Label added, but could not save to file.\n");
                    break;
                }

                printf("Label saved: %s -> %s\n", alias, nodeName);
                break;

            case 2:
                printf("Enter label to delete: ");
                scanf("%29s", alias);

                if (!removeAlternativeName(alias)) {
                    printf("Label not found.\n");
                    break;
                }

                if (!saveAlternativeNames("data/label.txt")) {
                    printf("Label deleted, but could not save to file.\n");
                    break;
                }

                printf("Label deleted: %s\n", alias);
                break;

            case 3:
                printAlternativeNames();
                break;

            case 0:
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 0);
}

// Runs the command selected from the main menu.
void interactMenu(int choice){
    char src[10],dest[10],name[10];
    int node;

    switch (choice){
        case 1:
            printGraph();
            break;
        case 2:
            printf("Enter start position: ");
            scanf("%9s",src);
            printf("Enter destination: ");
            scanf("%9s",dest);
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
            scanf("%9s", name);

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
            scanf("%9s", name);

            node = findNodeByName(name);

            if (node == -1) {
                node = findAlternativeNode(name);
            }

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

        case 8:
            manageLabels();
            break;

        case 0:
            printf("Exiting");
            break;

        default:
            printf("Invalid choice.\n");
            break;
    }
}
