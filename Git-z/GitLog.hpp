#ifndef GITGRAPH_HPP
#define GITGRAPH_HPP

#include <QString>
#include <QList>
#include "GitLogFormat.hpp"
#include "GitLogItem.hpp"
namespace gitz{

class GitLog
{
protected:
    using GF=GitLogFormat;
        public:
            GitLog(){
                format+= separator + GF::commitHash();
                format+= separator + GF::authorName();
                format+= separator + GF::subject();
                format+= separator;

    }

    enum{};
    void operator=(const QString& str){
        data = str;
        items.clear();
        int lastPos = 0;
        while(true) {
                int start = data.indexOf(separator,lastPos);
                if (start == -1) break;
                start += separator_length;
                GitLogItem item;
                for (int i=0;i<GitLogItem::_max_items_;++i){
                    int newPos = data.indexOf(separator,lastPos);
                    item.items[i]=data.midRef(lastPos,newPos-lastPos -1);
                    lastPos+=newPos+separator_length;
                }

                item.pack();
                items.append(item);
        }

    }
    const QString & getFormat(){ return format;}

protected:
    const QString separator="@|@|@";
    int separator_length=separator.length();
    QString format;
    QString data;
    QList<GitLogItem> items;
};

}
#endif // GITGRAPH_HPP
