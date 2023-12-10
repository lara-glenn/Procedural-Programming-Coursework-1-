#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    char steps[1000];
} FitnessData;


int counter = 0;
int i;


// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, char *steps, int *isEmpty ){
    char *pointer = strtok(record, &delimiter);


    if (pointer == NULL || strlen (pointer) == 0) {
        *isEmpty = 1;
            return;
        }


    strcpy(date, pointer);
    pointer = strtok(NULL, &delimiter);
       
    if (pointer == NULL || strlen (pointer) == 0) {
        *isEmpty = 1;
        return;
           
        }
    else{
        strcpy(time, pointer);

    }


    pointer = strtok(NULL, &delimiter);
       
    if (pointer == NULL) {
        *isEmpty = 1;
        return;
    }
    else if (strlen (pointer) == 0) {
        *isEmpty = 1;
        return;
        }

    else {
        strcpy(steps, pointer);

    }


    pointer = strtok(NULL, &delimiter);
    if (record[strlen(record)-1] == ',') {
        *isEmpty = 1;
        return; 
    }
   
}


FILE *open_file(char *filename, char *mode,int *isEmpty )
{
    FILE *input = fopen(filename, mode);

    if (input == NULL ){
        printf("Error: could not load file\n");
        *isEmpty = 1;
        exit(1);
    }


    return input;


}


FILE* importfile(int *isEmpty )
{


    FitnessData data[1000];
    int buffer_size = 1000;
    char line[buffer_size];
    char filename[buffer_size];

    printf("Enter filename:");
    fgets(line, buffer_size, stdin);
    sscanf(line, "%s", filename);

    FILE *input = open_file(filename, "r", isEmpty);
    char delimiter  = ',';
    int counter = 0;

    while (fgets(line, buffer_size, input)){


        char date[1000];
        char time[500];
        char steps[500];


        tokeniseRecord(line, delimiter, date, time, steps, isEmpty);

        // if there is empty data in the csv file then an error is returned 
        if (*isEmpty == 1){
            printf("Error: invalid file\n");
            fclose(input);
            exit (1);
        }
        

        strcpy(data[counter].date, date);
        strcpy(data[counter].time, time);
        strcpy(data[counter].steps, steps);


        counter++;
    }

    fclose(input);

//Sorting data

//I based this on an idea I found here: https://www.geeksforgeeks.org/bubble-sort/
//Bubble sort is used to sort the csv data into descending order
    int i = 0;
    int j = 0;
    FitnessData temp;
    for (i=0; i < counter; i++){
        for (j = 0; j < counter -1 ; j++){
            if (atoi(data[j].steps) < atoi(data[j+1].steps)) {
            temp = data[j];
            data[j] = data[j+1];
            data[j+1] = temp;
        }
        }
    }

//creating new array for the new tsv filename
    char tsvFile[1000];
    //strcpy used to keep the original filename so .tsv can be added to the end of it
    strcpy(tsvFile, filename);
    //.tsv added to the end of the original filename
    strcat(tsvFile, ".tsv");
    //printf("%s", tsvFile);

    //opens new file in write mode
    FILE *newFile = fopen(tsvFile, "w");

    if (newFile == NULL) {
        printf("Error");
        exit (1);
    }

    //copies sorted csv data into the new file with tab spacing
    for (int i = 0; i < counter; i++) {
        fprintf(newFile, "%s\t%s\t%s", data[i].date, data[i].time, data[i].steps);

    }
    fclose(newFile);

    printf("Data sorted and written to %s\n", tsvFile);

    return(newFile);

}


int main() {

    int isEmpty = 0;
    FILE *input = importfile(&isEmpty);
    return 0;
}
