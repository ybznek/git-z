#ifndef COMMITHASH_HPP
#define COMMITHASH_HPP

#include <string.h>
#include <QStringRef>

#include <ctype.h>

namespace gitz {
  /*class CommitHash
  {
  protected:
          enum {
              strHashLength = 40,
              rawHashLength = strHashLength / 2,
          };
  public:
      CommitHash(const QStringRef & str){
          Q_ASSERT(str.length()== (sizeof(data)*2));
          for (int i=0;i<strHashLength;){
                  char chr = str.at(i).toLatin1();
                  ++i;
                  char chr2 = str.at(i).toLatin1();
                  ++i;
                  data[i >> 1]= (chr2 << 4) | chr;

          }
      }

      inline bool operator ==(const CommitHash & c){
         return (memcmp(data,c.data,rawHashLength) == 0);
      }
  protected:
      char valueOf(char chr) const;
      char data[rawHashLength];
  };*/
}
#endif // COMMITHASH_HPP
