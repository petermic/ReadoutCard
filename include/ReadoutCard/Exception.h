// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \file Exception.h
/// \brief Definition of the RORC exceptions and related functions.
///
/// \author Pascal Boeschoten (pascal.boeschoten@cern.ch)

#ifndef ALICEO2_INCLUDE_READOUTCARD_EXCEPTION_H_
#define ALICEO2_INCLUDE_READOUTCARD_EXCEPTION_H_

#include <Common/Exceptions.h>
#include <stdexcept>
#include <boost/exception/exception.hpp>

namespace AliceO2
{
namespace roc
{

//// RORC exception definitions
struct Exception : Common::Exception {
};

// General exception definitions
struct PdaException : virtual Exception {
};
struct MemoryMapException : virtual Exception {
};
struct ParameterException : virtual Exception {
};
struct ParseException : virtual Exception {
};
struct InvalidParameterException : virtual ParameterException {
};
struct OutOfRangeException : virtual Exception {
};
struct LockException : virtual Exception {
};
struct FileLockException : virtual LockException {
};
struct SocketLockException : virtual LockException {
};
struct DeviceFinderException : virtual Exception {
};
struct SharedStateException : virtual Exception {
};
struct SharedObjectNotFoundException : virtual Exception {
};
struct TimeoutException : virtual Exception {
};
struct UnsafeAccess : virtual Exception {
};
struct UnsafeReadAccess : virtual UnsafeAccess {
};
struct UnsafeWriteAccess : virtual UnsafeAccess {
};
struct InvalidLinkId : virtual Exception {
};

// C-RORC exception definitions
struct CrorcException : virtual Exception {
};
struct CrorcArmDataGeneratorException : virtual CrorcException {
};
struct CrorcArmDdlException : virtual CrorcException {
};
struct CrorcInitDiuException : virtual CrorcException {
};
struct CrorcCheckLinkException : virtual CrorcException {
};
struct CrorcSiuCommandException : virtual CrorcException {
};
struct CrorcDiuCommandException : virtual CrorcException {
};
struct CrorcSiuLoopbackException : virtual CrorcException {
};
struct CrorcFreeFifoException : virtual CrorcException {
};
struct CrorcStartDataGeneratorException : virtual CrorcException {
};
struct CrorcStartTriggerException : virtual CrorcException {
};
struct CrorcStopTriggerException : virtual CrorcException {
};
struct CrorcDataArrivalException : virtual CrorcException {
};

// CRU exception definitions
struct CruException : virtual Exception {
};

// Utility exception definition
struct UtilException : virtual boost::exception, virtual std::exception {
};
struct ProgramOptionException : virtual UtilException {
};
struct InvalidOptionValueException : virtual ProgramOptionException {
};
struct OptionRequiredException : virtual ProgramOptionException {
};

} // namespace roc
} // namespace AliceO2

#endif // ALICEO2_INCLUDE_READOUTCARD_EXCEPTION_H_
