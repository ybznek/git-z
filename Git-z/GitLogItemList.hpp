#ifndef GITLOGITEMLIST_HPP
#define GITLOGITEMLIST_HPP
#include "GitLogItem.hpp"
#include <QList>

namespace gitz {
/**
 * List reuse old memory
 */
class GitLogItemList
{
protected:
    using tList = QList<GitLogItem>;
public:
    GitLogItemList() {prereserve();}
    inline void clear(){        internalLength = 0;    }

    GitLogItem & append();

    inline int length() const {return internalLength; }

    GitLogItem & operator[](int index){return items[index];}

    inline tList::Iterator begin() {return items.begin();}
    inline tList::Iterator end() { return items.begin()+internalLength;}

    inline tList::ConstIterator begin() const {return items.constBegin();}
    inline tList::ConstIterator end() const { return items.constBegin()+internalLength;}


protected:
    inline void prereserve(){items.reserve(internalLength+100);}
    int internalLength = 0;
    tList items;
};

}

#endif // GITLOGITEMLIST_HPP
