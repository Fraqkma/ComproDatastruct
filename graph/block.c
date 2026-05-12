#include <stdio.h>
#include "block.h"
#include "utils.h"

static int blockedNodes[MAX_BLOCKED_NODES];

void initBlockedNodes(void) {
    for (int i = 0; i < MAX_BLOCKED_NODES; i++) {
        blockedNodes[i] = 0;
    }
}

void blockNode(int node) {
    if (node < 0 || node >= MAX_BLOCKED_NODES) {
        printf("Invalid node.\n");
        return;
    }

    blockedNodes[node] = 1;
}

void unblockNode(int node) {
    if (node < 0 || node >= MAX_BLOCKED_NODES) {
        printf("Invalid node.\n");
        return;
    }

    blockedNodes[node] = 0;
}

int isNodeBlocked(int node) {
    if (node < 0 || node >= MAX_BLOCKED_NODES) {
        return 1;
    }

    return blockedNodes[node];
}

void clearBlockedNodes(void) {
    for (int i = 0; i < MAX_BLOCKED_NODES; i++) {
        blockedNodes[i] = 0;
    }
}

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
