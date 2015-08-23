#include "GitCommit.hpp"


gitz::GitCommit::GitCommit(QString message, QStringList files, bool amend)
    : message{message}, files{files}, amend{amend} {}
