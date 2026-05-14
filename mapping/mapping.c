#include <stdio.h>
#include <string.h>
#include "mapping.h"
#include "graph.h"
#include "utils.h"

// Checks if a node number points to a real loaded location.
int isValidNode(int node) {
    if (graph == NULL) {
        return 0;
    }

    if (node < 0 || node >= graph->V) {
        return 0;
    }

    if (getNodeName(node)[0] == '\0') {
        return 0;
    }

    return 1;
}

// Finds the node index that matches a location name.
int findNodeByName(char name[]) {
    if (graph == NULL) {
        return -1;
    }

    for (int i = 0; i < graph->V; i++) {
        if (getNodeName(i)[0] != '\0' && strcmp(getNodeName(i), name) == 0) {
            return i;
        }
    }

    return -1;
}

// Prints one location in a simple index and name format.
void printLocation(int node) {
    if (!isValidNode(node)) {
        printf("Invalid location.\n");
        return;
    }

    printf("%d | %s\n", node, getNodeName(node));
}

// Shows all locations that were loaded from the map file.
void showAllLocations(void) {
    int found = 0;

    printf("\n--- Available Locations ---\n");

    if (graph == NULL) {
        printf("Map has not been loaded.\n");
        return;
    }

    for (int i = 0; i < graph->V; i++) {
        if (getNodeName(i)[0] != '\0') {
            printf("%d | %s\n", i, getNodeName(i));
            found = 1;
        }
    }

    if (!found) {
        printf("No locations found.\n");
    }
}
