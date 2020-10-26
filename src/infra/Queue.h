#pragma once 

#include <deque>
#include <functional>
#include <mutex>
#include <memory>
#include <assert.h>
#include <condition_variable>
#include <chrono>

template<typename T>
class NotificationQueueLock
{
private:
  std::deque<T>     _queue;
  std::mutex                         _mutex;
  std::condition_variable            _ready;
  using lock_t = std::unique_lock<std::mutex>;
public:
  size_t size()
  {
    return _queue.size();
  }
  bool pop(T& func_)
  {
    lock_t lock {_mutex};
    if (_queue.empty())
    {
      return false;
    }
    func_ = std::move(_queue.front());
    _queue.pop_front();
    return true;
  }
  void push(T func_)
  {
    {
      lock_t lock {_mutex};
      _queue.emplace_back(std::move(func_));
    }
    _ready.notify_one();
  }
  bool isEmpty()
  {
    lock_t lock {_mutex};
    if (_queue.empty())
    {
      _ready.wait(lock);
    }
    return _queue.empty();
  }
  bool isEmptyWithin(std::chrono::microseconds ms_)
  {
    lock_t lock {_mutex};
    if (_queue.empty())
    {
      _ready.wait_for(lock, ms_);
    }
    return _queue.empty();
  }
};
