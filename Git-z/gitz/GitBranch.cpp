#include "GitBranch.hpp"


gitz::GitBranch::GitBranch(QString name) : name{name} {}

const QString &gitz::GitBranch::getName() const { return name; }
