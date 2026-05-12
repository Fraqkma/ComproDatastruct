#ifndef ALTERNATIVE_H
#define ALTERNATIVE_H

#define ALTERNATIVE_TABLE_SIZE 101
#define ALTERNATIVE_NAME_SIZE 30

void initAlternativeNames(void);
int addAlternativeName(char alias[], char nodeName[]);
int findAlternativeNode(char name[]);
void printAlternativeNames(void);

#endif
