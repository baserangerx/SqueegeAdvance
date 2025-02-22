#ifndef ITEMS_H
#define ITEMS_H

typedef struct item
{
    char* name;
    char* description;
    void (*action)();
} item;

extern item inventory[];

item createItem(char*,char*);
void addItem(item*);

#endif