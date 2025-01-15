

typedef struct consumable
{
    char* name;
    char* description;
    int (*action)();
};