#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"


enum class ItemType
{
    RAWMEAT,
    LARGERAWMEAT,
    COOKEDPLATE,
    ELABORATEDPLATE,
    PINT,
    JUG,
    STRONGRON
};

class Item : public Entity
{
public:

    Item(ItemType type) : Entity(EntityType::ITEM), itemType(type) {}

    virtual void ItemFunction(int* HP, int* SP, int maxHP, int maxSP) {}

public:

    ItemType itemType;
    int quantity = 0;
};

#endif // __ITEM_H__