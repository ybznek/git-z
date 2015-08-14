#ifndef GITFILELIST_HPP
#define GITFILELIST_HPP
#include <QVector>
#include "GitFile.hpp"
namespace gitz {
  using GitFileList = QVector<GitFile>;
  /*class GitFileList:public QVector<GitFile>
  {
  public:
      GitFileList(){}
  };*/
}
#endif // GITFILELIST_HPP
