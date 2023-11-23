#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
    int counter = 0;
    int i;  
    int integer_steps;
// Global variables for filename and FITNESS_DATA array


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }

FILE* importfile()
{

	int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];
	printf("Input filename:");

    fgets(line, buffer_size, stdin);

    sscanf(line, "%s", filename);

    FILE *input = open_file(filename, "r");

    printf("File opened\n");

    return input;

    //fclose(input);
}


void totalrecords(FILE *filerecords)
{
    rewind(filerecords);
	FITNESS_DATA data[1000];
	int counter = 0;


	char date[1000];
    char time[500];
    char steps[500];

	int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];

	while (fgets(line, buffer_size, filerecords)){
        tokeniseRecord(line, ",", date, time, steps);

        strcpy(data[counter].date, date);
        strcpy(data[counter].time, time);
        strcpy(data[counter].steps, steps);

        counter++;
    }

    printf("Number of records in file: %d\n", counter); 
}

// Complete the main function
int main() {
    FILE *input = NULL;

    FITNESS_DATA data[1000];
    int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];
    char chosen_option; 

    while(1)
    {
        printf("Menu Options\n");
        printf("A: Specify the filename to be imported\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the date and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Quit\n");

    

    chosen_option = getchar();

    while (getchar() != '\n');

    switch(chosen_option){
        case 'A':
        case 'a':
            input = importfile(); 
            break;

        case 'B':
        case 'b':
            totalrecords(input);
            break;
        case 'Q':
        case 'q':
            return 0;
            break;

    }

        

            
    }

    
    
    return 0;
   
}


