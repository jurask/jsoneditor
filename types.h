#ifndef TYPES_H
#define TYPES_H
#include <QMetaType>

enum class ItemType:char{
    Null = 0,
    Object = 1,
    Array = 2,
    Double = 3,
    String = 4,
    Bool = 5
};

Q_DECLARE_METATYPE(ItemType);

#endif // TYPES_H
