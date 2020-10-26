#pragma once

#include "Queue.h"
#include "variant"
#include <iostream>
#include <chrono>

template<typename EventTy>
struct Handler
{
  virtual void handleEvent(EventTy) = 0;
};

template<typename... EventTy>
struct Dispatcher
{
  NotificationQueueLock<std::variant<EventTy ...>> _queue;

  std::tuple<Handler<EventTy>* ...> _handlers;

  template<typename HandlerEventTy>
  void registerHandler(Handler<HandlerEventTy>* handler)
  {
    std::get<Handler<HandlerEventTy>*>(_handlers) = handler;
  }

  template<typename T>
  void dispatchEvent(T event_)
  {
    _queue.push(event_);
    // std::cout << "dispatching " << (void*)this << ", size " << _queue.size() << std::endl;
  }

  template<typename ForEventTy>
  Handler<ForEventTy>* getHandlerForEvent(ForEventTy)
  {
    typedef typename std::remove_cv<ForEventTy>::type TY;
    //std::cout << "event: " << typeid(TY).name() << std::endl;
    return std::get<Handler<TY>*>(_handlers);
  }

  void startLoop()
  {
    using namespace std::chrono_literals;

    while (true)
    {
      std::cout << "looping "  << (void*)this << ", size " << _queue.size() << std::endl;
      if (!_queue.isEmptyWithin(1000000us))
      {
        std::variant<EventTy ...> event;
        if (_queue.pop(event))
        {
          std::visit([&event, this](auto&& arg)
          {
            auto* handler = this->getHandlerForEvent(arg);
            if (handler)
            {
              std::cout << "ctor " << (void*)handler << std::endl;
              handler->handleEvent(arg);
            }
            else
            {
              std::abort();
            }
          }, event);
        }
      }
    }
  }
};