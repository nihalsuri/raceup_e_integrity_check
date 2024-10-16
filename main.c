#include "./integrity_check_db.h"
#include "stdio.h"
#include "time.h"

// Function to check and log integrity conditions
void check_and_log(FILE *file) {
    
    // Set current time variables 
    time_t t;
    struct tm *currentTime;

    // Open the log file
    file = fopen("integrity_log.json", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Start the JSON object 
    fprintf(file, "{\n \"integrity_checks\": [\n");
    // Integrity check loop
    while (1) {
        //Get current time for each iteration 
        t = time(NULL);
        currentTime = localtime(&t);

        // Check if we need to close the previous JSON object 
        long file_position = ftell(file);  // Get the current position in the file
        
        // A new JSON object per iteration 
        fprintf(file, "  {\n");

        // Add timestamp 
        fprintf(file, "     \"timestamp\": \"%02d/%02d/%04d %02d:%02d:%02d\", \n", 
            currentTime->tm_mday, currentTime->tm_mon + 1, 
            currentTime->tm_year + 1900, currentTime->tm_hour, 
            currentTime->tm_min, currentTime->tm_sec);

        // THROTTLE (gas) check
        fprintf(file, "      \"gas\": \"%s\",\n", (gas >= 0 && gas <= 100 && !(brk1 > 50 && gas >= 20)) ? "OK" : "ERROR");

        // BRAKE (brk1) check
        fprintf(file, "      \"brk1\": \"%s\",\n", (brk1 >= 0.0f && brk1 < 99.9f) ? "OK" : "ERROR");

        // STEERING WHEEL ANGLE (steering_wheel) check
        fprintf(file, "      \"steering_wheel\": \"%s\",\n", (steering_wheel >= 0.0 && steering_wheel <= 180.0) ? "OK" : "ERROR");

        // BRAKE PRESSURE (brk_pressure) check
        fprintf(file, "      \"brk_pressure\": \"%s\",\n", (brk_pressure >= 0.0f && brk_pressure <= 100.0f && !(brk1 < 10.0f && brk_pressure >= 50.0f)) ? "OK" : "ERROR");

        // MOTOR POSITION (motor_pos[3]): All values must be positive or negative at the same time
        int motor_pos_all_positive = 1, motor_pos_all_negative = 1;
        for (int i = 0; i < 3; i++) {
            if (motor_pos[i] >= 0) {
                motor_pos_all_negative = 0;
            } else {
                motor_pos_all_positive = 0;
            }
        }

        fprintf(file, "      \"motor_pos\": \"%s\",\n", (motor_pos_all_positive || motor_pos_all_negative) ? "OK" : "ERROR");

        // VOLTAGE LEVELS (voltage_level[8]): Every value must be over 10
        int voltage_ok = 1;
        for (int i = 0; i < 8; i++) {
            if (voltage_level[i] < 10) {
                voltage_ok = 0;
                break;
            }
        }

        fprintf(file, "      \"voltage_level\": \"%s\",\n", (voltage_ok) ? "OK" : "ERROR");


        // GENERIC SENSORS (sensors[13]): Payload < 120, size > 10, and spec > 10 for each sensor
        int sensors_ok = 1;
        for (int i = 0; i < 13; i++) {
            if (sensors[i].payload >= 120.0f || sensors[i].size <= 10 || sensors[i].spec <= 10) {
                sensors_ok = 0;
                break;
            }
        }
        fprintf(file, "      \"sensors\": \"%s\"\n", sensors_ok ? "OK" : "ERROR");

        // Close the JSON object for this iteration
        fprintf(file, "    }");

        // Check for valid position to insert comma (if necessary)
        if (ftell(file) > file_position + 50) {  // Roughly ensuring there's enough space
            fprintf(file, ",\n"); // Append comma for subsequent entries
        } else {
            fprintf(file, "\n");  // No comma for the last entry
        }

        // Flush the file to ensure data is written out
        fflush(file);
        

    }

    fclose(file);
}

int main()
{
    generate_values();

    //add here your code

    //Log file 
    FILE *file = NULL;

    //start the integrity check and logging 
    check_and_log(file);

    return 0;
}
