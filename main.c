#include <stdio.h>
#include "menu.h"
#include "graph.h"
#include "utils.h"

int main() {
    initGraph(100);
    loadFromFile("data/kmuttmap.txt");

    int choice;
    do{
        showMenu();
        scanf("%d",&choice);
        interactMenu(choice);
    }while(choice!=0);
    
    return 0;
}