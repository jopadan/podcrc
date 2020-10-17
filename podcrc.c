#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ccitt32_crc.h"

int main(int argc, char** argv)
{
	struct stat sb;
	FILE*       fp = NULL;
	uint32_t crc = 0;
	size_t size;

	if(argc > 1)
	{
		if(stat(argv[1], &sb) == -1)
		{
			fprintf(stderr, "ERROR: could not read file stats %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		size = sb.st_size;
		fp = fopen(argv[1], "rb");
		if(!fp)
		{
			fprintf(stderr,"ERROR: could not open file: %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		uint8_t* data = calloc(1, size);
		if(!data)
		{
			fprintf(stderr, "ERROR: could not allocate %u bytes for file %s\n", size, argv[1]);
			fclose(fp);
			exit(EXIT_FAILURE);
		}
		size_t read = fread(data, 1, size, fp);
		printf("file: %s size: %u read: %u\n", argv[1], size, read);	
		if(read != size)
		{
			fprintf(stderr, "ERROR: could not read file: %s\n", argv[1]);
			fclose(fp);
			exit(EXIT_FAILURE);
		}
		fclose(fp);
		crc = ccitt32_updcrc(0xffffffff, data, size);
		printf("file: %s\nchecksum: %u\n", argv[1], crc);
	}
	exit(EXIT_SUCCESS);
}
