#ifndef LOCKHOLDER_HPP
#define LOCKHOLDER_HPP
#include <QMutex>
namespace gitz {
  namespace generic {


    template <typename X>
    /**
     * Provide access to internal structure via locked object
     */
    class LockHolder {
    public:
      inline LockHolder(QMutex &mtx, X &obj) : mtx{mtx}, obj{obj} { mtx.lock(); }
      inline X *operator->() { return &obj; }
      inline const X *operator->() const { return &obj; }

      inline X &operator*() { return obj; }
      inline const X &operator*() const { return obj; }

      inline const auto begin() const { return obj.begin(); }
      inline const auto end() const { return obj.end(); }

      inline auto begin() { return obj.begin(); }
      inline auto end() { return obj.end(); }

      inline const X &operator[](int index) const { return obj[index]; }
      inline X &operator[](int index) { return obj[index]; }

      inline operator X &() { return obj; }
      inline operator const X &() const { return obj; }

      inline ~LockHolder() { mtx.unlock(); }

    private:
      QMutex &mtx;
      X &obj;
    };
  }
}
#endif // LOCKHOLDER_HPP
