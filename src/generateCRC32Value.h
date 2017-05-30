#ifndef generateCRC32Value_H
#define generateCRC32Value_H

# include <stdio.h>
# include <stdlib.h>

# define CRC_BUFFER_SIZE  8192

int Crc32_ComputeFile(FILE *file, unsigned long *outCrc32);

#endif // generateCRC32Value_H
