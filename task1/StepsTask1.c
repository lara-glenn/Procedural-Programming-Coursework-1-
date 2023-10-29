
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[110];
	char time[60];
	char steps[1000];
} FITNESS_DATA;

// Define any additional variables here
    
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
    int counter = 0;
    int i;


    char* filename = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    //char pos[50];
    char date[1000];
    char time[500];
    char steps[500];

    while (fgets(line, buffer_size, file)){
        tokeniseRecord(line, ",", date, time, steps);

        strcpy(data[counter].date, date);
        strcpy(data[counter].time, time);
        strcpy(data[counter].steps, steps);

        counter++;

    }

    printf("Number of records in file: %d\n", counter);

    //printf("%s\n", FITNESS_DATA.steps);
    
    



    return 0;


}