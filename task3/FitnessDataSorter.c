#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;




// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps, int *isEmpty ){
    char *pointer = strtok(record, &delimiter);
    if (pointer != NULL || strlen (pointer) == 0) {
        *isEmpty = 1;
            return;
        }

    strcpy(date, pointer);
    pointer = strtok(NULL, &delimiter);
        
    if (pointer != NULL || strlen (pointer) == 0) {
        *isEmpty = 1;
        return;
            
        }

    strcpy(time, pointer);
    pointer = strtok(NULL, &delimiter);
        
    if (pointer != NULL || strlen (pointer) == 0) {
        *isEmpty = 1;
        return;
        }

    *steps = atoi(pointer);

        
    
}

FILE *open_file(char *filename, char *mode,int *isEmpty )
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

FILE* importfile(int *isEmpty )
{


    int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];
    printf("Enter filename:");


    fgets(line, buffer_size, stdin);


    sscanf(line, "%s", filename);


    FILE *input = open_file(filename, "r", isEmpty);
    char delimiter  = ',';

    while (fgets(line, buffer_size, input)){

        char date[1000];
        char time[500];
        int steps[1000];

        tokeniseRecord(line, delimiter, date, time, steps, isEmpty);
    
    }

    if (*isEmpty == 1) {
        printf("Error: invalid file");
        exit (1);
    }


    return input;


}


int main() {

    int isEmpty = 0;
    FILE *input = importfile(&isEmpty);
    return 0;
}