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

public:

    ItemType itemType;
    int quantity;
};

#endif // __ITEM_H__