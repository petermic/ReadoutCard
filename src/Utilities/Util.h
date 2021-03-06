// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \file Util.h
/// \brief Definition of various useful utilities that don't really belong anywhere in particular
///
/// \author Pascal Boeschoten (pascal.boeschoten@cern.ch)
/// \author Kostas Alexopoulos (kostas.alexopoulos@cern.ch)

#ifndef ALICEO2_SRC_READOUTCARD_UTILITIES_UTIL_H_
#define ALICEO2_SRC_READOUTCARD_UTILITIES_UTIL_H_

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <bitset>

namespace AliceO2
{
namespace roc
{
namespace Utilities
{

/// Is x a multiple of y
template <typename T1, typename T2>
bool isMultiple(const T1& x, const T2& y)
{
  return (x >= y) && ((x % y) == 0);
}

inline uint32_t getLower32Bits(uint64_t x)
{
  return x & 0xFfffFfff;
}

inline uint32_t getUpper32Bits(uint64_t x)
{
  return (x >> 32) & 0xFfffFfff;
}

template <typename T>
T getBit(T x, int index)
{
  return (x >> index) & 1;
}

template <typename T>
void setBit(T& bits, int index, bool value)
{
  if (value) {
    bits |= T(1) << index;
  } else {
    bits &= ~(T(1) << index);
  }
}

template <typename T>
void setBits(T& bits, int index, int width, uint32_t value)
{
  uint32_t mask = ~(~T(0) << width) << index;
  bits = (bits & ~mask) | ((value << index) & mask);
}

template <typename T>
T getBits(T x, int lsb, int msb)
{
  assert(lsb < msb);
  return (x >> lsb) & ~(~T(0) << (msb - lsb + T(1)));
}

template <typename T>
int getWidth(T x)
{
  int length = 0;
  while (x & T(1)) {
    length += 1;
    x >>= 1; // !
  }
  return length;
}

/// Offset a pointer by a given amount of bytes
template <typename T>
T* offsetBytes(T* pointer, size_t bytes)
{
  return reinterpret_cast<T*>(reinterpret_cast<char*>(pointer) + bytes);
}

/// Calculate difference in bytes between two pointers
template <typename T>
ptrdiff_t pointerDiff(T* a, T* b)
{
  return reinterpret_cast<char*>(a) - reinterpret_cast<char*>(b);
}

/// Get a range from std::rand()
inline int getRandRange(int min, int max)
{
  return (std::rand() % max - min) + min;
}

inline bool checkAlignment(void* address, uint64_t alignment)
{
  return (uint64_t(address) % alignment) == 0;
}

// Converts a number to a string with enforced precision
template <typename T>
std::string toPreciseString(T flo, int precision = 2)
{
  std::ostringstream precisionEnforcer;
  precisionEnforcer << std::fixed;
  precisionEnforcer << std::setprecision(precision);
  precisionEnforcer << flo;
  return precisionEnforcer.str();
}

template <typename T>
std::string toHexString(T num)
{
  std::stringstream ss;
  ss << std::hex << "0x" << num;
  return ss.str();
}

} // namespace Utilities
} // namespace roc
} // namespace AliceO2

#endif // ALICEO2_SRC_READOUTCARD_UTILITIES_UTIL_H_
