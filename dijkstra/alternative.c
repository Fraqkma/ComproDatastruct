#include <stdio.h>
#include <string.h>
#include "alternative.h"
#include "mapping.h"
#include "utils.h"

struct AlternativeName {
    char alias[ALTERNATIVE_NAME_SIZE];
    int node;
    int used;
};

struct AlternativeName alternativeTable[ALTERNATIVE_TABLE_SIZE];

// Turns a label into a table index so we can find it quickly later.
int hashName(char name[]) {
    int hash = 0;

    for (int i = 0; name[i] != '\0'; i++) {
        hash = (hash * 31 + name[i]) % ALTERNATIVE_TABLE_SIZE;
    }

    return hash;
}

// Clears the whole label table before loading fresh data.
void initAlternativeNames(void) {
    for (int i = 0; i < ALTERNATIVE_TABLE_SIZE; i++) {
        alternativeTable[i].used = 0;
        alternativeTable[i].node = -1;
        alternativeTable[i].alias[0] = '\0';
    }
}

// Adds a new label, or updates it if the same label already exists.
int addAlternativeName(char alias[], char nodeName[]) {
    int node = findNodeByName(nodeName);
    int firstAvailable = -1;

    if (node == -1) {
        return 0;
    }

    int index = hashName(alias);

    for (int i = 0; i < ALTERNATIVE_TABLE_SIZE; i++) {
        int current = (index + i) % ALTERNATIVE_TABLE_SIZE;

        if (alternativeTable[current].used == 1 &&
            strcmp(alternativeTable[current].alias, alias) == 0) {
            alternativeTable[current].node = node;
            return 1;
        }

        if (alternativeTable[current].used != 1 && firstAvailable == -1) {
            firstAvailable = current;
        }

        if (alternativeTable[current].used == 0) {
            break;
        }
    }

    if (firstAvailable != -1) {
        strcpy(alternativeTable[firstAvailable].alias, alias);
        alternativeTable[firstAvailable].node = node;
        alternativeTable[firstAvailable].used = 1;
        return 1;
    }

    return 0;
}

// Removes a label but keeps the probing chain alive for other labels.
int removeAlternativeName(char alias[]) {
    int index = hashName(alias);

    for (int i = 0; i < ALTERNATIVE_TABLE_SIZE; i++) {
        int current = (index + i) % ALTERNATIVE_TABLE_SIZE;

        if (alternativeTable[current].used == 0) {
            return 0;
        }

        if (alternativeTable[current].used == 1 &&
            strcmp(alternativeTable[current].alias, alias) == 0) {
            alternativeTable[current].used = 2;
            alternativeTable[current].node = -1;
            alternativeTable[current].alias[0] = '\0';
            return 1;
        }
    }

    return 0;
}

// Looks up a label and returns the real node number behind it.
int findAlternativeNode(char name[]) {
    int index = hashName(name);

    for (int i = 0; i < ALTERNATIVE_TABLE_SIZE; i++) {
        int current = (index + i) % ALTERNATIVE_TABLE_SIZE;

        if (alternativeTable[current].used == 0) {
            return -1;
        }

        if (alternativeTable[current].used == 1 &&
            strcmp(alternativeTable[current].alias, name) == 0) {
            return alternativeTable[current].node;
        }
    }

    return -1;
}

// Prints every saved label in a friendly list.
void printAlternativeNames(void) {
    int found = 0;

    printf("\n--- Alternative Location Names ---\n");

    for (int i = 0; i < ALTERNATIVE_TABLE_SIZE; i++) {
        if (alternativeTable[i].used == 1) {
            printf("%s -> %s\n", alternativeTable[i].alias, getNodeName(alternativeTable[i].node));
            found = 1;
        }
    }

    if (!found) {
        printf("No alternative names added.\n");
    }
}

// Loads labels from a text file, one label and one node name per line.
int loadAlternativeNames(char filename[]) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        return 0;
    }

    char alias[ALTERNATIVE_NAME_SIZE];
    char nodeName[10];
    int loaded = 0;

    while (fscanf(file, " %29s %9s", alias, nodeName) == 2) {
        if (addAlternativeName(alias, nodeName)) {
            loaded++;
        }
    }

    fclose(file);
    return loaded;
}

// Saves active labels back to the text file so they survive after closing.
int saveAlternativeNames(char filename[]) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        return 0;
    }

    for (int i = 0; i < ALTERNATIVE_TABLE_SIZE; i++) {
        if (alternativeTable[i].used == 1) {
            fprintf(file, "%s %s\n", alternativeTable[i].alias, getNodeName(alternativeTable[i].node));
        }
    }

    fclose(file);
    return 1;
}
