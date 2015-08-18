#ifndef LOCKABLEOBJECT_HPP
#define LOCKABLEOBJECT_HPP
#include <QMutex>
#include "LockHolder.hpp"
namespace gitz {

  template <class X> class LockableObject {
  public:
    inline LockableObject() { ; }
    inline LockableObject(X &&obj) : obj{obj} {}
    inline LockableObject(X &&obj, QMutex &&mtx)
        : obj{obj}, mtx{mtx} {} // todo check constructors if no extra copy...

    inline void lock() { mtx.lock(); }
    inline void unlock() { mtx.unlock(); }
    inline LockHolder<X> getLock() { return LockHolder<X>{mtx, obj}; }
    inline operator X &() { return obj; }
    X obj;
    QMutex mtx;
  };
}

#endif // LOCKABLEOBJECT_HPP
