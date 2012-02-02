#ifndef BASE_PTIME_H__
#define BASE_PTIME_H__

#include <sys/time.h>

namespace detail {
// return in milliseconds
inline double timeval_sub(const struct timeval *t1, const struct timeval *t2) {
  return (double)((t2->tv_sec * 1000000 + t2->tv_usec)
    - (t1->tv_sec * 1000000 + t1->tv_usec))/1000;
}
} // detail

class ptime {
public:
  explicit ptime() {
    gettimeofday(&wall_clock_, 0);
  }

  double wall_clock() const {
    struct timeval end;
    gettimeofday(&end, 0);

    return detail::timeval_sub(&wall_clock_, &end);
  }

protected:
  struct timeval wall_clock_;
};

#endif // BASE_PTIME_H__

