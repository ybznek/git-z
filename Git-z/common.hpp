#ifndef COMMON_HPP
#define COMMON_HPP

#include <functional>
namespace gitz {
  using tGitCallback = std::function<void()>;
  const tGitCallback tGitCallback_NONE = ([]() { ; });

  enum edit_parsing_characters {
    FILE_CHAR = '*',
    END_FILE_CHAR = '>',
    INPUT_FILE = '<',
  };
}
#endif // COMMON_HPP
