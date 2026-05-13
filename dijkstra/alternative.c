#include <stdio.h>
#include <string.h>
#include "alternative.h"
#include "mapping.h"

struct AlternativeName {
    char alias[ALTERNATIVE_NAME_SIZE];
    int node;
    int used;
};

struct AlternativeName alternativeTable[ALTERNATIVE_TABLE_SIZE];

int hashName(char name[]) {
    int hash = 0;

    for (int i = 0; name[i] != '\0'; i++) {
        hash = (hash * 31 + name[i]) % ALTERNATIVE_TABLE_SIZE;
    }

    return hash;
}

void initAlternativeNames(void) {
    for (int i = 0; i < ALTERNATIVE_TABLE_SIZE; i++) {
        alternativeTable[i].used = 0;
        alternativeTable[i].node = -1;
        alternativeTable[i].alias[0] = '\0';
    }
}

int addAlternativeName(char alias[], char nodeName[]) {
    int node = findNodeByName(nodeName);

    if (node == -1) {
        return 0;
    }

    int index = hashName(alias);

    for (int i = 0; i < ALTERNATIVE_TABLE_SIZE; i++) {
        int current = (index + i) % ALTERNATIVE_TABLE_SIZE;

        if (!alternativeTable[current].used ||
            strcmp(alternativeTable[current].alias, alias) == 0) {
            strcpy(alternativeTable[current].alias, alias);
            alternativeTable[current].node = node;
            alternativeTable[current].used = 1;
            return 1;
        }
    }

    return 0;
}

int findAlternativeNode(char name[]) {
    int index = hashName(name);

    for (int i = 0; i < ALTERNATIVE_TABLE_SIZE; i++) {
        int current = (index + i) % ALTERNATIVE_TABLE_SIZE;

        if (!alternativeTable[current].used) {
            return -1;
        }

        if (strcmp(alternativeTable[current].alias, name) == 0) {
            return alternativeTable[current].node;
        }
    }

    return -1;
}

void printAlternativeNames(void) {
    int found = 0;

    printf("\n--- Alternative Location Names ---\n");

    for (int i = 0; i < ALTERNATIVE_TABLE_SIZE; i++) {
        if (alternativeTable[i].used) {
            printf("%s -> node %d\n", alternativeTable[i].alias, alternativeTable[i].node);
            found = 1;
        }
    }

    if (!found) {
        printf("No alternative names added.\n");
    }
}
