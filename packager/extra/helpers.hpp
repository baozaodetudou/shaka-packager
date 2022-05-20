// includes some common functions to avoid redundancy

#include <signal.h>
#include "indicators.hpp" // indicators already includes windows.h, so no need to repeat

using namespace indicators;

/* want this on windows for idiots that don't use the utf-8 codepage,
   will set the codepage of the shell that executes the packager to utf-8
   even if system cp is different */
inline void set_console_codepage()
{
    #ifdef WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
}

/* Prevents the shell from breaking after sudden termination with ctrl+c and such.
   Works well enough, unless cancelled too fast, for some reason then a few chars in the progress bar may turn white,
   or in rare instances the terminal will not be reset to original color (the issue applies to windows only) */
static inline void exit_handler(int sig)
{
  show_console_cursor(true);
  std::cout << termcolor::reset;
  std::cout << std::endl;
  std::cout.setstate(std::ios_base::failbit); // disallow any more output, should prevent weird cases of random chars from the bar being printed after cancelling
  exit(sig);
}

inline void set_handlers()
{
  signal(SIGTERM, exit_handler);
  signal(SIGSEGV, exit_handler);
  signal(SIGINT, exit_handler);
  signal(SIGABRT, exit_handler);
}

/* gotta use indicators here too, easier for cross platform handling;
   windows doesn't seem to understand ansi escape sequences */ 
inline void error_handler()
{
  std::cout << termcolor::red; // want error to be highlighted in red, will be reset to normal after printing
  show_console_cursor(true);
}