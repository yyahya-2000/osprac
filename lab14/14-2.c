#include <signal.h>

int main(void) {
  //
  // Set the process response to the SIGINT signal to ignore
  //
  (void)signal(SIGINT, SIG_IGN);
  //
  // Set the process response to the SIGQUIT signal to ignore
  //
  (void)signal(SIGQUIT, SIG_IGN);
  //
  // From this point, the process will ignore the occurrence of SIGINT and SIGQUIT signals.
  //
  while(1);
  return 0;
}
