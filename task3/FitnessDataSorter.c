#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

FILE *open_file(char *filename, char *mode)
{
	FILE *input = fopen(filename, mode);
	if (input == NULL) {
        printf("Error: invalid file\n");
        exit (1);
        
    }
	
	else {
        printf("File successfully loaded.\n");

	}

	return input;

}


// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    int isEmpty = 0;
    char *pointer = strtok(record, &delimiter);
    if (pointer != NULL) {
        if (strlen (pointer) > 0){
            strcpy(date, pointer);

        }
        pointer = strtok(NULL, &delimiter);
        if (pointer != NULL) {
            strcpy(time, pointer);
            pointer = strtok(NULL, &delimiter);
            if (pointer != NULL) {
                *steps = atoi(pointer);
            }
        }
    }
}

FILE* importfile()
{


    int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];
    printf("Enter filename:");


    fgets(line, buffer_size, stdin);


    sscanf(line, "%s", filename);


    FILE *input = open_file(filename, "r");



    return input;


}


int main() {

    FILE *input = NULL;


    input = importfile();
}