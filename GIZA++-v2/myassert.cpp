#include "myassert.h"

#include "port/stl_helper.h"
#include <iostream>

namespace util {

void Logging::myerror(int line,const char *file,const char *expression) {
  std::cerr << "Assertion failed: '" << expression <<  "' ::: b "
            << file << ":" << line << std::endl;
}
void Logging::imyerror(int line,const char *file,const char *expression) {
  std::cerr << "Error: '" << expression <<  "' ::: in Source " << file
            << ":" << line << std::endl;
}

} // namespace util
