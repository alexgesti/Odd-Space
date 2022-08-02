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

    Item(ItemType type) : Entity(EntityType::RANDITEM), itemType(type) {}

    int GetSubtype() { return (int)itemType; }

public:

    ItemType itemType;
};

#endif // __ITEM_H__