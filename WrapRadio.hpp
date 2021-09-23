#ifndef WRAPRADIO_HPP
#define WRAPRADIO_HPP

#include <RF24.h>

#include "Defines.hpp"

#define DEBUG_RADIO

class WrapRadio
{
  public:
    RF24* radio = NULL;

    uint8_t pipeNum = 0;
    uint8_t ack_msg = 0;

    WrapRadio();
    ~WrapRadio();

    void init();
    bool sendTimer(const void* data, void* ack, uint32_t ms);

  private:
    uint32_t prev_ms_send = 0;
};
#endif // WRAPRADIO_HPP
