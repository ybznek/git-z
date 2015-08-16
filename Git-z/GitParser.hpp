#ifndef GITPARSER_HPP
#define GITPARSER_HPP

namespace gitz {
  class GitParser {
  public:
    virtual void parse() = 0;
  };
}
#endif // GITPARSER_HPP
