#pragma once
#include <chrono>
namespace chrono = std::chrono;

#define OP_EQUALS(type1, type2, op)            \
  type1 &operator op##=(const type2 & other) { \
    *this = operator op(other);                \
    return *this;                              \
  }

class TimePoint;

class Duration {
private:
  chrono::milliseconds duration;
  friend class TimePoint;

public:
  Duration(const chrono::milliseconds &ms) : duration(ms) {}
  Duration() : duration(chrono::milliseconds::max()) {}

  inline int getMs() const {
    return duration.count();
  }
  inline float getSecs() const {
    return float(duration.count()) * 1e-3;
  }

  inline Duration operator+(const Duration &other) {
    return Duration(chrono::milliseconds(duration.count() + other.duration.count()));
  }

  inline Duration operator-(const Duration &other) {
    return Duration(chrono::milliseconds(duration.count() + other.duration.count()));
  }

  OP_EQUALS(Duration, Duration, +)
  OP_EQUALS(Duration, Duration, -)
};

class TimePoint {
private:
  chrono::high_resolution_clock::time_point point;
  friend class Clock;

public:
  TimePoint(const chrono::high_resolution_clock::time_point &time) : point(time) {}
  TimePoint() : point(chrono::high_resolution_clock::time_point::min()) {}

  static TimePoint now() {
    return TimePoint(chrono::high_resolution_clock::now());
  }

  // end-start
  Duration operator-(const TimePoint &other) const {
    return Duration(chrono::duration_cast<chrono::milliseconds>(point - other.point));
  }

  TimePoint operator+(const Duration &other) const {
    return TimePoint(point + other.duration);
  }

  TimePoint operator-(const Duration &other) const {
    return TimePoint(point - other.duration);
  }

  OP_EQUALS(TimePoint, Duration, +)
  OP_EQUALS(TimePoint, Duration, -)
};

extern int   getMsSince(const TimePoint &point);
extern float getSecsSince(const TimePoint &point);

class Clock {
private:
  TimePoint start_of_time;
  bool      ticking = false;

public:
  void  restart();
  int   getMs() const;
  float getSecs() const;
};