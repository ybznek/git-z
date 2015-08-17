#ifndef LOCKHOLDER_HPP
#define LOCKHOLDER_HPP
#include <QMutex>
#include <QDebug>
namespace gitz {


  template <typename X>
  /**
   * Provide access to internal structure via locked object
   */
  class LockHolder {
  public:
    inline LockHolder(QMutex &mtx, X &val) : mtx{mtx}, val{val} { mtx.lock(); }
    inline X *operator->() { return &val; }
    inline const X *operator->() const { return &val; }

    inline const auto begin() const { return val.begin(); }
    inline const auto end() const { return val.end(); }

    inline auto begin() { return val.begin(); }
    inline auto end() { return val.end(); }

    const X &operator[](int index) const { return val[index]; }
    X &operator[](int index) { return val[index]; }

    inline ~LockHolder() { mtx.unlock(); }

  private:
    QMutex &mtx;
    X &val;
  };
}
#endif // LOCKHOLDER_HPP
