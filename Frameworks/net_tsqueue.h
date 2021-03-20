#pragma once
#include "net_common.h"

namespace olc
{
  namespace net
  {
     template<typename T>
     class tsqueue
     {
     public:
         tsqueue() = default;
         tsqueue(const tsqueue<T>&) = delete;
         virtual ~tsqueue() { clear(); }
         
     public:
         // Returns and maintains item at front of Queue
         const T& front()
         {
             std::scoped_lock lock(muxQueue);
             return deqQueue.front();
         }
         
         // Adds an item to back of Queue
         void push_back(const T& item)
         {
             std::scoped_lock lock(muxQueue);
             deqQueue.emplace_back(std::move(item));
         }
         
         // Returns number of items in Queue
         size_t count()
         {
             std::scoped_lock lock(muxQueue);
             return deqQueue.size();
         }
         
         // Clears Queue
         void clear()
         {
             std::scoped_lock lock(muxQueue);
             deqQueue.clear();
         }
         
         // Removes and returns item from front of Queue
         T pop_front()
         {
             std::scoped_lock lock(muxQueue);
             auto t = std::move(dequeQueue.front());
             deqQueue.pop_front();
             return t;
         }
         
     protected:
         std::mutex muxQueue;
         std::deque<T> deqQueue;
     }
  }
}
