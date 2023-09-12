# LINUX 标准IO

Linux标准io库是一个广泛使用的C语言库，它提供了一组可移植的函数，用于在应用程序和操作系统之间进行输入和输出操作。这些函数提供了一种标准的IO接口，可以在不同的操作系统上进行移植和使用。

## 操作符定义

是一个结构体

```c
/* The tag name of this struct is _IO_FILE to preserve historic
   C++ mangled names for functions taking FILE* arguments.
   That name should not be used in new code.  */
struct _IO_FILE
{
  int _flags;		/* High-order word is _IO_MAGIC; rest is flags. */

  /* The following pointers correspond to the C++ streambuf protocol. */
  char *_IO_read_ptr;	/* Current read pointer */
  char *_IO_read_end;	/* End of get area. */
  char *_IO_read_base;	/* Start of putback+get area. */
  char *_IO_write_base;	/* Start of put area. */
  char *_IO_write_ptr;	/* Current put pointer. */
  char *_IO_write_end;	/* End of put area. */
  char *_IO_buf_base;	/* Start of reserve area. */
  char *_IO_buf_end;	/* End of reserve area. */

  /* The following fields are used to support backing up and undo. */
  char *_IO_save_base; /* Pointer to start of non-current get area. */
  char *_IO_backup_base;  /* Pointer to first valid character of backup area */
  char *_IO_save_end; /* Pointer to end of non-current get area. */

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
  int _flags2;
  __off_t _old_offset; /* This used to be _offset but it's too small.  */

  /* 1+column number of pbase(); 0 is unknown. */
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  _IO_lock_t *_lock;
#ifdef _IO_USE_OLD_IO_FILE
};

struct _IO_FILE_complete
{
  struct _IO_FILE _file;
#endif
  __off64_t _offset;
  /* Wide character stream stuff.  */
  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  size_t __pad5;
  int _mode;
  /* Make sure we don't get into trouble again.  */
  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};

typedef struct _IO_FILE FILE;
```

## 主要函数 
下面是一些常用的Linux标准io函数：
1. fopen()：打开文件并返回与该文件关联的文件指针。
```c
#include <stdio.h>

FILE *fopen(const char *pathname, const char *mode);
FILE *fdopen(int fd, const char *mode);
FILE *freopen(const char *pathname, const char *mode, FILE *stream);

Feature Test Macro Requirements for glibc (see feature_test_macros(7)):
fdopen(): _POSIX_C_SOURCE
/* pathname为要操作或创建的文件路径及文件名 */
/* mode的值：
                ┌─────────────┬───────────────────────────────┐
                │fopen() mode │ open() flags                  │
                ├─────────────┼───────────────────────────────┤
                │     r       │ O_RDONLY                      │
                ├─────────────┼───────────────────────────────┤
                │     w       │ O_WRONLY | O_CREAT | O_TRUNC  │
                ├─────────────┼───────────────────────────────┤
                │     a       │ O_WRONLY | O_CREAT | O_APPEND │
                ├─────────────┼───────────────────────────────┤
                │     r+      │ O_RDWR                        │
                ├─────────────┼───────────────────────────────┤
                │     w+      │ O_RDWR | O_CREAT | O_TRUNC    │
                ├─────────────┼───────────────────────────────┤
                │     a+      │ O_RDWR | O_CREAT | O_APPEND   │
                └─────────────┴───────────────────────────────┘

r      Open text file for reading.  The stream is positioned at the beginning of the file.

r+     Open for reading and writing.  The stream is positioned at the beginning of the file.

w      Truncate file to zero length or create text file for writing.  The stream is positioned at the beginning of the file.

w+     Open for reading and writing.  The file is created if it does not exist, otherwise it is truncated.  The stream is positioned at the beginning of the file.

a      Open for appending (writing at end of file).  The file is created if it does not exist.  The stream is positioned at the end of the file.

a+     Open for reading and appending (writing at end of file).  The file is created if it does not exist.  Output is always appended to the end of the file.  POSIX is silent on what the initial read position is when using this mode.  For glibc, the initial file position for reading is at the beginning of the file, but for Android/BSD/MacOS, the initial file position for reading is at the end of the file.
 */

```

1. fclose()：关闭文件。
```c
#include <stdio.h>

int fclose(FILE *stream);
```

2. fread()：从文件中读取数据到指定缓冲区。
```c
#include <stdio.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

// size_t fwrite(const void *ptr, size_t size, size_t nmemb,
//             FILE *stream);
```

3. fwrite()：将指定缓冲区中的数据写入文件。
```c
#include <stdio.h>

// size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

size_t fwrite(const void *ptr, size_t size, size_t nmemb,
            FILE *stream);
```

4. fseek()：将文件指针移动到指定位置。
```c
#include <stdio.h>

int fseek(FILE *stream, long offset, int whence);

long ftell(FILE *stream);

void rewind(FILE *stream);

int fgetpos(FILE *stream, fpos_t *pos);

int fsetpos(FILE *stream, const fpos_t *pos);
```

5. ftell()：返回当前文件指针的位置。

6. fflush()：刷新文件缓冲区，将缓冲区中的数据写入磁盘。
```c
#include <stdio.h>

int fflush(FILE *stream);
```

7. fgets()：从文件中读取一行数据。
```C
#include <stdio.h>

int fgetc(FILE *stream);

char *fgets(char *s, int size, FILE *stream);

int getc(FILE *stream);

int getchar(void);

int ungetc(int c, FILE *stream);
```

8.  fputs()：将指定字符串写入文件。
```C
#include <stdio.h>

int fputc(int c, FILE *stream);

int fputs(const char *s, FILE *stream);

int putc(int c, FILE *stream);

int putchar(int c);

int puts(const char *s);
```


9.  fprintf()：将格式化的字符串写入文件。
```C
#include <stdio.h>

int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int dprintf(int fd, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);
```

10. fscanf()：从文件中读取格式化的数据。
```C
#include <stdio.h>

int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
int sscanf(const char *str, const char *format, ...);

```

这些函数可以用于读取和写入文件、标准输入和输出（stdin、stdout、stderr），以及其他数据流，例如网络套接字。标准io库为这些数据流提供了一个统一的接口，使得应用程序可以无需考虑底层细节，就可以进行输入和输出操作。

此外，标准io库还提供了一组与文件描述符相关的函数，例如fdopen()、fileno()、popen()和pclose()等，这些函数提供了对底层文件描述符的访问和操作。
总之，Linux标准io库提供了一组可移植的、易于使用的函数，用于进行输入和输出操作。它提供了标准的IO接口，使得应用程序可以无需考虑底层细节，就可以进行数据读写。