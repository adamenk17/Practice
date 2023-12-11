#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"
#include <limits.h>
#define buffer_size 100
// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
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

// Complete the main function
int main() {
    FILE *file = NULL;
    char mychar;
    int records = 0;
    char line[buffer_size];
    char file_name[buffer_size];
    int totalrecords = 0;
    int min = INT_MAX;
    

    while(1)    {
        printf("Menu Options:\n");
        printf("A: Specify the filename to be imported\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the date and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Quit\n");
        printf("Enter choice: ");

        mychar = getchar();
        while (getchar() != '\n');

        switch (mychar) {

            case 'A':
            case 'a':

            printf("Input filename: ");
            fgets(line, buffer_size, stdin);
            sscanf(line, " %s ", file_name);

            file = fopen(file_name, "r");
            if (file == NULL)   {
                printf("Error: Could not open the file.\n");
                return 1;
            }   else    {
                printf("File successfully loaded.\n");
            }
            break;


            case 'B':
            case 'b':

            rewind(file);
            int totalrecords = 0;
            while (fgets(line, buffer_size, file) != NULL)  {
                totalrecords++;
            }
            printf("Total records: %d\n", totalrecords);
            break;
            

            case 'C':
            case 'c':

            rewind(file);
            int record = 0;
            int min = INT_MAX;
            while (fgets(line, buffer_size, file) != NULL)  {
                tokeniseRecord(line, ",", fit[record].date, fit[record].time, fit[record].steps);
                int step = atoi(fit[record].steps);

                if (step < min) {
                    min = step;
                }
                record++;
                }
            for (int i = 0; i < record; i++)    {
                int steps = atoi(fit[i].steps);
                if (steps == min)   {
                    printf("Fewest steps: %s %s\n", fit[i].date, fit[i].time);
                }
            }
            break;


            case 'D':
            case 'd':

            rewind(file);
            int records = 0;
            int max= INT_MIN;
            while (fgets(line, buffer_size, file) != NULL)  {
                tokeniseRecord(line, ",", fit[records].date, fit[records].time, fit[records].steps);
                int step = atoi(fit[records].steps);

                if (step > max) {
                    max = step;
                }
                records++;
            }
            for (int i =0; i< records; i++) {
                int steps = atoi(fit[i].steps);
                if (steps == max)   {
                    printf("Largest steps %s %s\n", fit[i].date, fit[i].time);
                }
            }
            break;


            case 'E':
            case 'e':

            rewind(file);
            int count = 0;
            int totalrecord = 0;
            int mean = 0;

            while (fgets(line, buffer_size, file) != NULL)  {
                tokeniseRecord(line, ",", fit[records].date, fit[records].time, fit [records].steps);
                int step = atoi(fit[records].steps);

                count = count + step;
                totalrecord++;
            } //mean = count/totalrecord
            if (totalrecord != 0) {
                mean = (count + totalrecord / 2) / totalrecords;
            }
            
            printf("Mean step count: %d\n", mean);
            break;


            case 'F':
            case 'f':
            rewind(file);
            int longestStart = 0;
            int longestEnd = 0;
            int currentStart = 0;
            int currentEnd = 0;
            int num_recs = 0;
            int longestDuration = 0;
            int currentDuration = 0;

            while (fgets(line, buffer_size, file) != NULL)  {
                tokeniseRecord(line, ",", fit[num_recs].date, fit[num_recs].time, fit[num_recs].steps);
                int step = atoi(fit[num_recs].steps);

                if (step > 500) {
                    if (currentDuration == 0)   {
                        currentStart = num_recs;
                    }
                    currentDuration ++;
                    currentEnd = num_recs;  
                } else  {
                    if (currentDuration > longestDuration)  {
                        longestDuration = currentDuration;
                        longestStart = currentStart;
                        longestEnd = currentEnd;
                    }
                    currentDuration = 0;
                }
                num_recs++;
            }      
            if (currentDuration > longestDuration)  {
                        longestDuration = currentDuration;
                        longestStart = currentStart;
                        longestEnd = currentEnd;
            }

            printf("Longest period start: %s %s\n", fit[longestStart].date, fit[longestStart].time);
            printf("Longest period end: %s %s\n", fit[longestEnd].date, fit[longestEnd].time);
            break;


            case 'Q':
            case 'q':

            fclose(file);
            return 0;
            break;

            default:
            printf("Invalid choice. Try again.\n");
        }

    }
    fclose(file);
    return 0;

   
}









