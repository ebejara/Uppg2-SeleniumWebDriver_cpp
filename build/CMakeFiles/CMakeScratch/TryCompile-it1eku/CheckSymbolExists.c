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

int main(int argc, char** argv)
{
  (void)argv;
#ifndef ftruncate
  return ((int*)(&ftruncate))[argc];
#else
  (void)argc;
  return 0;
#endif
}
