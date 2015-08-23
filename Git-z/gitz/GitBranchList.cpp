#include "GitBranchList.hpp"


void gitz::GitBranchList::setSelected(int selected) { this->selected = selected; }

int gitz::GitBranchList::getSelected() const { return selected; }
