
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	char steps[1000];
} FITNESS_DATA;

// Define any additional variables here
    int counter = 0;
    int i;  
    int integer_steps;

    
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

// Complete the main function
int main() {

    FITNESS_DATA data[1000];
    int buffer_size = 1000;
    char line[buffer_size];
    


    char* filename = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    char date[1000];
    char time[500];
    char steps[500];


    while (fgets(line, buffer_size, file)){
        tokeniseRecord(line, ",", date, time, steps);

        //creates a copy of the data in each line and saves the different values to their respective arrays

        strcpy(data[counter].date, date);
        strcpy(data[counter].time, time);
        strcpy(data[counter].steps, steps);


        //counter increments so it is able to keep track of how many lines there are as the csv file is read

        counter++;
    
    }
    //prints the value of counter, which will allow the user to see the number of records in the csv file
    printf("Number of records in file: %d\n", counter);
    //printf("%s\n", data[0].date);
    //printf("%s\n", data[3].steps);



    //for loop that prints the first 3 values from the date,time and steps arrays and prints them out with a slash between them
     for (i=0; i<3; i++){
            integer_steps = atoi(data[i].steps);

            printf("%s/%s/%d\n", data[i].date, data[i].time, integer_steps);

        } 

  
    //printf("%ls\n", data);
    //printf("%d\n", *steps);

    return 0;


}