#include <stdio.h>
#include "block.h"
#include "utils.h"

int blockedNodes[MAX_BLOCKED_NODES];

// Resets every location so nothing is blocked at startup.
void initBlockedNodes(void) {
    for (int i = 0; i < MAX_BLOCKED_NODES; i++) {
        blockedNodes[i] = 0;
    }
}

// Marks one location as blocked so routes cannot pass through it.
void blockNode(int node) {
    if (node < 0 || node >= MAX_BLOCKED_NODES) {
        printf("Invalid node.\n");
        return;
    }

    blockedNodes[node] = 1;
}

// Opens one blocked location again.
void unblockNode(int node) {
    if (node < 0 || node >= MAX_BLOCKED_NODES) {
        printf("Invalid node.\n");
        return;
    }

    blockedNodes[node] = 0;
}

// Checks if a location is blocked before using it in a route.
int isNodeBlocked(int node) {
    if (node < 0 || node >= MAX_BLOCKED_NODES) {
        return 1;
    }

    return blockedNodes[node];
}

// Clears all blocked locations in one go.
void clearBlockedNodes(void) {
    for (int i = 0; i < MAX_BLOCKED_NODES; i++) {
        blockedNodes[i] = 0;
    }
}

// Shows every location that is currently blocked.
void printBlockedNodes(void) {
    int found = 0;

    printf("\nBlocked nodes: ");

    for (int i = 0; i < MAX_BLOCKED_NODES; i++) {
        if (blockedNodes[i]) {
            printf("%s ", getNodeName(i));
            found = 1;
        }
    }

    if (!found) {
        printf("None");
    }

    printf("\n");
}
