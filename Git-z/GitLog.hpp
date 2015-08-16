#ifndef GITGRAPH_HPP
#define GITGRAPH_HPP

#include <QString>
#include "GitLogFormat.hpp"
#include "GitLogItem.hpp"
#include <QDebug>
#include <GitLogItemList.hpp>
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

    void operator=(const QString& str){
        data = str;
        items.clear();
        int lastPos = 0;
        while(true) {
                int start = data.indexOf(separator,lastPos);
                if (start == -1) break;
                start += separator_length;
                GitLogItem &item = items.append();
                    for (int i=0;i<GitLogItem::_max_items_;++i){
                    int newPos = data.indexOf(separator,lastPos);
                    QStringRef str=data.midRef(lastPos,newPos-lastPos -1);
                    qDebug() << str;
                    item.items[i]=str;
                    lastPos+=newPos+separator_length;
                }

                item.pack();
        }

    }
    const QString & getFormat(){ return format;}

protected:
    const QString separator="@|@|@";
    const int separator_length=separator.length();
    QString format;
    QString data;
    GitLogItemList items;
};

}
#endif // GITGRAPH_HPP
