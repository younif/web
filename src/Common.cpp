//
// Created by youni on 22-6-14.
//

#include "Common.h"
#include <cstdio>
#include <cstdlib>

void fatal_error(const char *syscall) {
  perror(syscall);
  exit(1);
}
