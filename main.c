#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "consts.h"

struct batteryInfo {
    int level;
    float health;
    char status[20];
    int cycle_count;

};

struct batteryInfo read_battery(int battery_num){
    char battery_path[255], buffer[1024];
    sprintf(battery_path, BATTERY_INFO_PATH, battery_num);


    FILE* filePtr = fopen(battery_path, "r");
    if(filePtr == NULL) {
        printf("Failed to open file (%s)", battery_path);
        exit(1);
    }

    struct batteryInfo bat;
    bat.level = 0;
    bat.health = 100;
    bat.cycle_count = 0;
    strcpy(bat.status, "NO STATUS");


    char key[255], value[255];
    while (fscanf(filePtr, "%[^=]=%s\n", key, value) != EOF) {
        if      (strcmp(key, "POWER_SUPPLY_STATUS")             == 0)   strcpy(bat.status, value);
        else if (strcmp(key, "POWER_SUPPLY_CYCLE_COUNT")        == 0)   bat.cycle_count = atoi(value);
        else if (strcmp(key, "POWER_SUPPLY_CHARGE_FULL_DESIGN") == 0)   bat.health /= atof(value);
        else if (strcmp(key, "POWER_SUPPLY_CHARGE_FULL")        == 0)   bat.health *= atof(value);
        else if (strcmp(key, "POWER_SUPPLY_CAPACITY")           == 0)   bat.level = atoi(value);
    }

    fclose(filePtr);

    return bat;
}

int main() {
    struct batteryInfo bInfo = read_battery(0);
    //printf("%f %i %i %s\n", bInfo.health, bInfo.level, bInfo.cycle_count, bInfo.status);

    FILE* batteryLogFilePtr = fopen(BATTERY_LOG_PATH, "r");

    if (batteryLogFilePtr == NULL) {
        printf("The log file doesn't exist, creating...");
        //fclose(batteryLogFilePtr);

        batteryLogFilePtr = fopen(BATTERY_LOG_PATH, "w");

        fputs("timestamp, level, health\n", batteryLogFilePtr);


    }
    else {
        fclose(batteryLogFilePtr);
        batteryLogFilePtr = fopen(BATTERY_LOG_PATH, "a");
    }

    time_t current_time = time(NULL);
    struct tm tm = *localtime(&current_time);



    if (strcmp(bInfo.status, "Discharging") == 0) {
        char line[255];
        sprintf(line, "%02d-%02d-%02d %02d:%02d, %i\%, %f\%\n", tm.tm_year + 1900, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, bInfo.level, bInfo.health);
        fputs(line, batteryLogFilePtr);
        printf("%s", line);
    }
    fclose(batteryLogFilePtr);
    return 0;
}
