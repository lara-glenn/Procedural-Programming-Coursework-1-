#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


//function that runs when A is called - will use sscanf on user input to import correct file
FILE* importfile()
{


    int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];
    printf("Input filename:");


    fgets(line, buffer_size, stdin);


    sscanf(line, "%s", filename);


    FILE *input = open_file(filename, "r");

    return input;


    //fclose(input);
}



//function that counts the number of records in the file and returns it 
void totalrecords(FILE *filerecords)
{
    //rewind used if user wants to see total records again so pointer starts counting from beginning of text file
    rewind(filerecords);
    FITNESS_DATA data[1000];



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

        //counter keeps track of the number of lines in the data file
        counter++;
    }


    printf("Number of records in file: %d\n", counter);
}

//function that calculate the mean of the step count and returns it
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

        //convert steps from string to int so mathematical operations can be completed on the data
        int numSteps = atoi(steps);


        num += numSteps;


        i++;
    }

    float mean =(float) num/i;
    //0.5 added to mean to round value
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
    int index;
    int i=0;
    //setting the value of minsteps to the maximum possible value so that the function will be able to calcualte the minimum steps taken correctly 
    int minSteps = __INT_MAX__;
    int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];

    while (fgets(line, buffer_size, filefew)){
        tokeniseRecord(line, ",", date, time, steps);

        //converting steps to an integer value
        int currentSteps = atoi(steps);

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

        //if the step count on the current line is a greater value than the highest step count currently stored in maxSteps, then maxSteps is replaced with the current step count
        if (currentSteps > maxSteps) {
            maxSteps = currentSteps;
            //the index of the maximum steps is saved so the line with other information about date and time can be returned
            index = i;
            strcpy(data[i].date, date);
            strcpy(data[i].time, time);
        }
        
        i++;
        
    }

    printf("Largest steps: %s %s\n", data[index].date, data[index].time);
   
}

void longestperiod (FILE *longestperiodfile)
{
    rewind(longestperiodfile);

    FITNESS_DATA data[1000];
    char date[1000];
    char time[500];
    char steps[500];
    
    int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];

    //starting at -1 as 0 index has data at it
    int start = -1;
    int currentIndex = 0;
    int longestStart = -1;
    int longestEnd = -1;


    while (fgets(line, buffer_size, longestperiodfile)){
        tokeniseRecord(line, ",", date, time, steps);
        strcpy(data[counter].date, date);
        strcpy(data[counter].time, time);

        int stepcount = atoi(steps);

        if (stepcount > 500 && start == -1){
            start = currentIndex;

        }

        else if (stepcount <= 500 && start != -1){

            if (currentIndex - start > longestEnd - longestStart){
                longestStart = start;
                longestEnd = currentIndex -1;
            }
            start = -1;
        }

        currentIndex++;
        counter++;

    }

    printf("Longest period starts: %s %s\n", data[longestStart].date, data[longestStart].time);
    printf("Longest period ends: %s %s\n", data[longestEnd].date, data[longestEnd].time);
    
}

// Complete the main function
int main() {
    FILE *input = NULL;


    FITNESS_DATA data[1000];
    int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];
    char chosen_option;
    char upper_char;


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
        printf("Enter choice:");


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
            
            case 'F':
            case 'f':
                longestperiod(input);
                break;
            case 'Q':
            case 'q':
                return 0;
                break;
            default:
            printf("Invalid choice. Try again.\n");

    }
    
           
    }  
   
    return 0;
   
}