///
/// \file ReadyFifo.h
/// \author Pascal Boeschoten
///

#pragma once

#include <cstdint>

namespace AliceO2 {
namespace Rorc {

static constexpr int CRORC_NUMBER_OF_PAGES = 128;

/// Class representing CRORC readyFifo
class ReadyFifo
{
  public:
    class Entry
    {
      public:
        volatile int32_t length;
        volatile int32_t status;

        inline void reset()
        {
          length = -1; // temp magic value for debugging
          status = -1; // temp magic value for debugging
        }
    };

    inline void reset()
    {
      for (auto& e : entries) {
        e.reset();
      }
    }

    std::array<Entry, CRORC_NUMBER_OF_PAGES> entries;
};

} // namespace Rorc
} // namespace AliceO2