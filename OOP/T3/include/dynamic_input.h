

#include <stdio_ext.h>
#include <sys/ioctl.h>
#include <termios.h>
namespace dynIn {
static struct termios term;
static const int STDIN = 0;
static int initialized = 0;
char Input();
void ResetTermios();
}  // namespace dynIn