#include <stdio.h>
#include "menu.h"
#include "graph.h"
#include "utils.h"
#include "block.h"
#include "dijkstra/alternative.h"


int main() {

    initGraph(100);
    initBlockedNodes();

    loadFromFile("data/kmuttmap.txt");

    initAlternativeNames();

    addAlternativeName("MainGate", "n1");
    addAlternativeName("Library", "n10");
    addAlternativeName("Canteen", "n20");
    addAlternativeName("BuildingA", "n5");
    addAlternativeName("Parking", "n44");

    int choice;
    do{
        showMenu();
        scanf("%d",&choice);
        interactMenu(choice);
    }while(choice!=0);
    
    return 0;
}