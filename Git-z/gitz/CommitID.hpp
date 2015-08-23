#ifndef COMMITID_HPP
#define COMMITID_HPP
#include <QString>
namespace gitz {

  using CommitID = QString;
  /*class CommitID {
   public:
    inline CommitID(QString&& str) : id{str} {}
    inline CommitID(const QString& str) : id{str} {}
    inline CommitID(const char* str):id{str}{}
    inline operator const QString (){return id;}

   protected:
    QString id;
  };*/
}
#endif // COMMITID_HPP
