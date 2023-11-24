#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "FitnessDataStruct.h"


// Struct moved to header file


// Define any additional variables here

int integer_steps;
// Global variables for filename and FITNESS_DATA array
FITNESS_DATA data[1000];
int counter = 0;




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


float calculatemean(FILE *filemean)
{
    rewind(filemean);

    FITNESS_DATA data[1000];
    char date[1000];
    char time[500];
    char steps[500];
    int num = 0;
    int i=0;
    int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];


    while (fgets(line, buffer_size, filemean)){
        tokeniseRecord(line, ",", date, time, steps);


        int numSteps = atoi(steps);


        num += numSteps;


        i++;
    }

    float mean =(float) num/i;
    int result = mean + 0.5;


    //printf("Mean step count: %.2f\n", mean);
    printf("Mean step count: %d\n", result);
    return result;
    return mean;

}

void fewestSteps(FILE *filefew)
{
    rewind(filefew);

    FITNESS_DATA data[1000];
    char date[1000];
    char time[500];
    char steps[500];
    int currentSteps;
    int index;
    int i=0;
    int minSteps = __INT_MAX__;
    int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];

    while (fgets(line, buffer_size, filefew)){
        tokeniseRecord(line, ",", date, time, steps);

        currentSteps = atoi(steps);

        if (currentSteps < minSteps) {
            minSteps = currentSteps;
            index = i;
            strcpy(data[i].date, date);
            strcpy(data[i].time, time);
        }
        
        i++;
        
    }

    printf("Fewest steps: %s %s\n", data[index].date, data[index].time);

}

void largestSteps(FILE *filelarge) 
{
    rewind(filelarge);

    FITNESS_DATA data[1000];
    char date[1000];
    char time[500];
    char steps[500];
    int index;
    int i=0;
    int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];

    int currentSteps;
    int maxSteps = 0;


    while (fgets(line, buffer_size, filelarge)){
        tokeniseRecord(line, ",", date, time, steps);

        currentSteps = atoi(steps);

        if (currentSteps > maxSteps) {
            maxSteps = currentSteps;
            index = i;
            strcpy(data[i].date, date);
            strcpy(data[i].time, time);
        }
        
        i++;
        
    }

    printf("Largest steps: %s %s\n", data[index].date, data[index].time);
   
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
        case 'C':
        case 'c':
            fewestSteps(input);
            break;
        case 'D':
        case 'd':
            largestSteps(input);
            break;

        case 'E':
        case 'e':
            calculatemean(input);

            break;
        case 'Q':
        case 'q':
            return 0;
            break;


    }


       


           
    }


   
   
    return 0;
   
}







