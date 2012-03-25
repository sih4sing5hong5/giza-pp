/*
  EGYPT Toolkit for Statistical Machine Translation

  Written by Yaser Al-Onaizan, Jan Curin, Michael Jahr, Kevin Knight, John Lafferty, Dan Melamed, David Purdy, Franz Och, Noah Smith, and David Yarowsky.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
  USA.
*/

#ifndef GIZAPP_PORT_FILE_SPEC_H_
#define GIZAPP_PORT_FILE_SPEC_H_

#include <ctime>
#include <cstdlib>
#include <string>
#include <cstdio>

namespace port {

/*
  This function returns a string, locally called file_spec. This
  string is the concatenation of the date and time of execution
  and the user who is performing the execution.

  Originally implemented in C by Yaser Al-Onaizan;
  editions for C++ and formatting by Noah A. Smith, 9 July 1999
*/
std::string GetFileSpec() {
  struct tm *local;
  time_t t;
  char *user;
  char time_stmp[64];
  std::string res;

  t = time(NULL);
  local = localtime(&t);

  std::snprintf(time_stmp, sizeof(time_stmp), "%02d-%02d-%02d.%02d%02d%02d.",
                local->tm_year, (local->tm_mon + 1), local->tm_mday, local->tm_hour,
                local->tm_min, local->tm_sec);
  res.append(time_stmp);

  user = getenv("USER");
  if (user == NULL) {
    std::fprintf(stderr, "Unknown environment variables.");
    std::exit(1);
  }
  res.append(user);
  return res;
}
} // namespace port

#endif  // GIZAPP_PORT_FILE_SPEC_H_
