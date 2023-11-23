
#ifndef FITNESS_DATA_STRUCT_H
#define FITNESS_DATA_STRUCT_H

#include <stdio.h>


// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	char steps[1000];
} FITNESS_DATA;


// Helper function prototypes
void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, char *steps);

#endif // FITNESS_DATA_STRUCT_H
FILE *open_file(char *filename, char *mode)
{
	FILE *input = fopen(filename, mode);
	if (!input)
	{
		printf("Error: could not open file\n");
		return NULL;
	}

	return input;

}


