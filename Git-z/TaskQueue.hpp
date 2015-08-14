#ifndef TASKQUEUE_HPP
#define TASKQUEUE_HPP
#include "TaskItem.hpp"
namespace gitz {
  using TaskQueue = QQueue<TaskItem>;
}
#endif // TASKQUEUE_HPP
