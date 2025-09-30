#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>

#ifndef DATA_WORK_HEADER
#define DETA_WORK_HEADER 

#define MASK_V 4
#define MASK_I 2
#define MASK_F 1

#define MAX_PATH_LEN 128

char parse(int argc, char* argv[]);

int safe_open(const char* pathname, int flags, int mode);

void safe_close(int fd);

ssize_t safe_read(int fd, char* buf, size_t buf_sz);

ssize_t safe_write(int fd, const char* buf, size_t size);


bool file_exists(const char* pathname);

size_t get_file_size(const char* pathname);

mode_t get_file_mode(const char* pathname);


int copy(int fd_from, int fd_to);

void transfer(const char* path_from, const char* path_to, char opts, int mode);

void configure_and_transfer(const char* path_from, const char* path_to, char opts);

#endif
