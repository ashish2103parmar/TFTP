
#ifndef FILE_HANDLER
#define FILE_HANDLER 0

int openfile(char *fname, int rdonly);
int readfile(int fd, uint8 *data);
int writefile(int fd, uint8 *data, uint32 dsize);

#endif
