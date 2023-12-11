#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"
#include <limits.h>

#define buffer_size 100

// Change steps to an integer in your FITNESS_DATA struct
char filename[buffer_size];
FITNESS_DATA fit[100];
int recordCount = 0;


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


int main() {
    FILE *file = NULL;
    char mychar;
    char line[buffer_size];
    char file_name[buffer_size];
    int totalrecords = 0;
    int min = INT_MAX;
    int max = INT_MIN;
    int count = 0;
    int mean = 0;  // Move the declaration of mean outside of the switch statement

    while(1) {
        printf("Menu Options:\n");
        printf("A: Specify the filename to be imported:\n");
        printf("B: Display the total number of records in the file:\n");
        printf("C: Find the date & time of the timeslot with the fewest steps:\n");
        printf("D: Find the date & time of the timeslot with the largest number of steps:\n");
        printf("E: Find the mean step count of all the records in the file:\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps:\n");
        printf("Q: Exit\n");
        printf("Enter choice: \n");

        mychar = getchar();
        while (getchar() != '\n');

        switch (mychar) {
            case 'A':
            case 'a':
                printf("Input filename: ");
                fgets(line, buffer_size, stdin);
                sscanf(line, " %s ", file_name);

                file = fopen(file_name, "r");
                if (file == NULL) {
                    printf("Error: Could not find or open the file.\n");
                    return 1;
                } else {
                    printf("File successfully loaded.\n");
                }
                break;

            case 'B':
            case 'b':
                printf("Total records: %d\n", totalrecords);
                break;

            case 'C':
            case 'c':
                printf("Fewest steps: %d\n", min);
                break;

            case 'D':
            case 'd':
                printf("Largest steps: %d\n", max);
                break;

            case 'E':
            case 'e':
                mean = totalrecords ? (count + totalrecords / 2) / totalrecords : 0;
                printf("Mean step count: %d\n", mean);
                break;

            case 'Q':
            case 'q':
                printf("Exiting...\n");
                if (file) fclose(file);
                return 0;

            default:
                printf("Invalid option. Please try again.\n");
        }

        if (mychar == 'A' || mychar == 'a') {
            while (fgets(line, buffer_size, file) != NULL) {
                tokeniseRecord(line, ",", fit[recordCount].date, fit[recordCount].time, &fit[recordCount].steps);
                count += fit[recordCount].steps;
                totalrecords++;
                if (fit[recordCount].steps < min) {
                    min = fit[recordCount].steps;
                }
                if (fit[recordCount].steps > max) {
                    max = fit[recordCount].steps;
                }
                recordCount++;
            }
        }
    }
}