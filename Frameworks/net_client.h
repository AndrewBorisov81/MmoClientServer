#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_tsqueue.h"
#include "net_connection.h"

namespace olc
{
  namespace net
  {
    template<typename T>
    class client_interface
    {
      template <typename T>
      class client_interface
      {
      private:
        // This is the thread safe queue of incoming messages from server
        tsqueue<owned_message<T>> m_qMessagesIn;
      }
    };
  }
}
