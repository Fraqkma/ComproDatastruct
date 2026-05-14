#include <stdio.h>
#include "menu.h"
#include "graph.h"
#include "utils.h"
#include "block.h"
#include "dijkstra/alternative.h"

// Starts the map system, loads saved labels, then keeps the menu running.
int main() {

    initGraph(100);
    initBlockedNodes();

    loadFromFile("data/kmuttmap.txt");

    initAlternativeNames();
    loadAlternativeNames("data/label.txt");

    int choice;
    do{
        showMenu();
        scanf("%d",&choice);
        interactMenu(choice);
    }while(choice!=0);
    
    return 0;
}
