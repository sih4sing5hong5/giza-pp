#ifndef GIZAPP_UTIL_ASSERT_H_
#define GIZAPP_UTIL_ASSERT_H_

#include <ostream>

namespace util {

class Logging {
 public:
  static void myerror(int line, const char *file, const char *expression);

  static void imyerror(int line, const char *file, const char *expression);

  static bool InitLogger(const char* filename,
                         std::ios_base::openmode mode = std::ios_base::out);

  static void SetLogger(std::ostream* os);

  static std::ostream& GetLogger();

 private:
  Logging() {}
  ~Logging() {}
};

} // namespace util

#define IASSERT(expression) \
  do {if (!(expression)) \
    { util::Logging::imyerror(__LINE__, __FILE__, #expression);}} while (0)

#define MASSERT(expr) do {} while(0)

#define VASSERT(expr) do {} while(0)

#endif  // GIZAPP_UTIL_ASSERT_H_
