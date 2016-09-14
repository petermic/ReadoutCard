///
/// \file Util.cxx
/// \author Pascal Boeschoten (pascal.boeschoten@cern.ch)
///

#include "Util.h"
#include <signal.h>
#include <cstring>
#include <fstream>
#include <memory>
#include <sstream>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

namespace AliceO2 {
namespace Rorc {
namespace Util {

namespace b = boost;
namespace bfs = boost::filesystem;

void setSigIntHandler(void(*function)(int))
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = function;
  sigfillset(&sa.sa_mask);
  sigaction(SIGINT, &sa, NULL);
}

bool isSigIntHandlerSet()
{
  struct sigaction sa;
  sigaction(SIGINT, NULL, &sa);
  return sa.sa_flags != 0;
}

void makeParentDirectories(const bfs::path& path)
{
  /// TODO Implement using boost::filesystem
  auto parent = path.parent_path();
  system(b::str(b::format("mkdir -p %s") % parent).c_str());
}

void touchFile(const bfs::path& path)
{
  std::ofstream ofs(path.c_str(), std::ios::app);
}

std::string executeCommand(const std::string& command)
{
  std::shared_ptr<FILE> input(popen(command.c_str(), "r"), pclose);

  if(!input.get()){
    BOOST_THROW_EXCEPTION(std::runtime_error("Call to popen failed"));
  }

  std::vector<char> buffer(128);
  std::ostringstream oss;
  while(fgets(buffer.data(), buffer.size(), input.get()) != NULL){
    oss << buffer.data();
  }

  return oss.str();
}

std::string getFileSystemType(const boost::filesystem::path& path)
{
  std::string type {""};
  std::string result = executeCommand(b::str(b::format("df --output=fstype %s") % path.c_str()));

  // We need the second like of the output (first line is a header)
  std::vector<std::string> splitted;
  boost::split(splitted, result, boost::is_any_of("\n"));
  if (splitted.size() == 2) {
    type = splitted.at(1);
  }

  return type;
}

std::pair<bool, std::string> isFileSystemTypeAnyOf(const boost::filesystem::path& path,
    const std::set<std::string>& types)
{
  auto type = getFileSystemType(path);
  return {types.count(type), type};
}

} // namespace Util
} // namespace Rorc
} // namespace AliceO2
