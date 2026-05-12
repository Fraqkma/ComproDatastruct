#ifndef BLOCK_H
#define BLOCK_H

#define MAX_BLOCKED_NODES 100

void initBlockedNodes(void);
int blockNode(int node);
int unblockNode(int node);
int isNodeBlocked(int node);
void clearBlockedNodes(void);
void printBlockedNodes(void);

#endif