#ifndef ITEMS_H
#define ITEMS_H

class Consumable
{
    private:
        const char* name;
        const char* description;
    public:
        Consumable(const char* name, const char* description) : name(name), description(description) {}
};


#endif