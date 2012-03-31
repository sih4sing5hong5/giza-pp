#include "util/assert.h"

#include "port/stl_helper.h"
#include <iostream>
#include <fstream>

namespace util {
namespace {

const char* g_log_filename = NULL;
std::ostream* g_log_stream = NULL;

} // namespace

void Logging::myerror(int line,const char *file,const char *expression) {
  std::cerr << "Assertion failed: '" << expression <<  "' ::: b "
            << file << ":" << line << std::endl;
}

void Logging::imyerror(int line,const char *file,const char *expression) {
  std::cerr << "Error: '" << expression <<  "' ::: in Source " << file
            << ":" << line << std::endl;
}

bool Logging::InitLogger(const char* filename,
                         std::ios_base::openmode mode) {
  g_log_filename = filename;

  std::ofstream log_stream;
  log_stream.open(filename, mode);
  if (!log_stream.good()) {
    std::cerr << "Failed to open " << filename << std::endl;
    return false;
  }
  util::Logging::SetLogger(&log_stream);
  return true;
}

void Logging::SetLogger(std::ostream* os) {
  g_log_stream = os;
}

std::ostream& Logging::GetLogger() {
  if (g_log_stream == NULL) {
    return std::cerr;
  } else {
    return *g_log_stream;
  }
}

} // namespace util
