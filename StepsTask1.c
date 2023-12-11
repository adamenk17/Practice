#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

// Define any additional variables here

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Outputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);

    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {
        strcpy(date, token);
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
    // Open file
    FILE *file = fopen("FitnessData_2023.csv", "r");
    
    // Array to hold records
    FITNESS_DATA data[200];
    int recordCount = 0;

    // Character array to store each line 
    char line[50];

    while (fgets(line, sizeof(line), file) != NULL) { // Read each line of the file until there are no more
        char date[11], time[6], steps[7]; // Arrays to store values
       
        tokeniseRecord(line, ",", date, time, steps); // Call function to split line into date, time, and steps
        strncpy(data[recordCount].date, date, 11); // Copy date values into array
        strncpy(data[recordCount].time, time, 6); // Copy time values into array
        data[recordCount].steps = atoi(steps); // Convert steps value from string to integer & copy values into array

        recordCount++; // Increment record count
    }

    // Close file
    fclose(file);

    // Print no. of records: 
    printf("Number of records in file: %d\n", recordCount);

    // Print  first 3 records
    for (int i = 0; i < 3 && i < recordCount; i++) {
        printf("%s/%s/%d\n", data[i].date, data[i].time, data[i].steps);
    }

    return 0;
}