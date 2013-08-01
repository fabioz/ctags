/**
Blog post: http://codesuppository.blogspot.com.br/2007_01_01_archive.html
License: zlib/libpng License (same as tinyxml)

Here is a genuinely useful code snippet. The purpose of this code is to allow you to rapidly refactor a library that performs direct file-IO so that it can support reading and writing to and from a buffer in memory.

The best way to describe its usefulness is in the case I used it for. I suppose many of your are familiar with TinyXML. This is a superb open source XML parser that is very fast, stable, and robust.

The only small problem with TinyXML is that is assumes you are loading a file from disk. However, often times your XML resource is simply something you have loaded into a buffer in memory.

Using this code snippet 'FileInterface.h' you can rapidly refactor massive amounts of source code by performing a find replace on all of the STDIO file routines (fopen, fclose, fwrite, fread, fprintf etc.)

The only routines you have to do additional work on is 'fopen'. The refactored fopen has an option for you to pass in a buffer in memory and a length. If you do not pass this in, then the interface will do standard file IO. If you do pass a buffer then all reads or writes will happen relative to that buffer.

There is an additional option for write access whereby you can choose not pass a destination buffer but rather one will be allocated and grown for you.

To access this feature you open the file with the option "wmem".

Here is an example usage:

FILE_INTERFACE *fph = fi_fopen("test", "wmem" );
fi_fprintf(fph,"This is a test.");
fi_fclose(fph);

To retrieve the buffer that was created you call 'fi_getMemBuffer' before the file is closed.

size_t len;
void *mem = fi_getMemBuffer(fph,len);

To read from a buffer in memory you would use this pattern:

FILE_INTERFACE *fph = fi_fopen("test,", "rb", mem, len);

To read from a file on disk, simply don't pass the memory buffer.

I have found this snippet to be quite useful, I hope you do to.

Here is the header file: FileInterface.h
Here is the implementation: FileInterface.cpp*/
#ifndef FILE_INTERFACE_H

#define FILE_INTERFACE_H

class FILE_INTERFACE;


FILE_INTERFACE * fi_fopen(const char *fname,const char *spec,void *mem=0,size_t len=0);
void             fi_fclose(FILE_INTERFACE *file);
size_t           fi_fread(void *buffer,size_t size,size_t count,FILE_INTERFACE *fph);
size_t           fi_fwrite(const void *buffer,size_t size,size_t count,FILE_INTERFACE *fph);
size_t           fi_fprintf(FILE_INTERFACE *fph,const char *fmt,...);
size_t           fi_fflush(FILE_INTERFACE *fph);
size_t           fi_fseek(FILE_INTERFACE *fph,size_t loc,size_t mode);
size_t           fi_ftell(FILE_INTERFACE *fph);
size_t           fi_fputc(char c,FILE_INTERFACE *fph);
size_t           fi_fputs(const char *str,FILE_INTERFACE *fph);
size_t           fi_feof(FILE_INTERFACE *fph);
size_t           fi_ferror(FILE_INTERFACE *fph);
void *           fi_getMemBuffer(FILE_INTERFACE *fph,size_t &outputLength);  // return the buffer and length of the file.


#endif