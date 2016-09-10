/*
 * Public domain
 */
#ifndef MEASUREMENT_KIT_PORTABLE_UNISTD_H
#define MEASUREMENT_KIT_PORTABLE_UNISTD_H

#ifndef _WIN32
#include <unistd.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern char *optarg;
extern int optind;
extern int optopt;
extern int opterr;
extern int optreset;

int getopt(int argc, char *const argv[], const char *optstring);

#ifdef __cplusplus
}
#endif
#endif