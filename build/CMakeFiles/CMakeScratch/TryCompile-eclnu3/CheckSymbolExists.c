/* */
#include <windows.h>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utime.h>
#include <fcntl.h>
#include <io.h>
#include <libgen.h>
#include <locale.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
  (void)argv;
#ifndef inet_pton
  return ((int*)(&inet_pton))[argc];
#else
  (void)argc;
  return 0;
#endif
}
