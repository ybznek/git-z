#include "GraphItem.hpp"


gitz::widget::GraphItem::GraphType gitz::widget::GraphItem::operator[](int index) { return list[index]; }

int gitz::widget::GraphItem::length() const { return list.size(); }

void gitz::widget::GraphItem::allocate(int length) { list.allocate(length); }
