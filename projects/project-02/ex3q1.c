#include <stdio.h>

int main(int argc, char *argv[])
{  
    if (argc != 5) return 1;
    FILE *saveFile = fopen(argv[1], "r");
    FILE *outFile = fopen(argv[2], "w");
    FILE *brokenFile = fopen(argv[3], "w");
    FILE *mapFile = fopen(argv[4], "r");

    if (saveFile == NULL || outFile == NULL || brokenFile == NULL || mapFile == NULL) return 1;

    int num_rows, num_cols, saves_num, time_stamps;
    if (fscanf(mapFile, " %d , %d", &num_rows, &num_cols) != 2) return 1;
    if (fscanf(saveFile, " %d", &saves_num) != 1) return 1;


    int valid_time[1000], valid_health[1000], valid_x[1000], valid_y[1000], valid_grade[1000], broken_time[1000];
    int valid_count = 0, broken_count = 0;

    for (int i = 0; i < saves_num; i++) {
        if (fscanf(saveFile, " %d", &time_stamps) != 1) return 1;
        char rest[200];
        int rest_index = 0;
        int characters;

        do {
            characters = fgetc(saveFile);
            if (characters != '\n' && characters != EOF && rest_index < 199) {
            rest[rest_index] = (char)characters;
            rest_index++;
            }
        } while (characters != '\n' && characters != EOF);

        rest[rest_index] = '\0';

        int health, x_loc, y_loc, grade;
        int spell_check = sscanf(rest," {\"health\": %d, \"x_loc\": %d, \"y_loc\": %d, \"grade\": %d}",&health, &x_loc, &y_loc, &grade);

        int is_valid = 1;

        if (spell_check != 4) {
            is_valid = 0;
        } else {
            if (health < 0 || health > 5) is_valid = 0;
            if (x_loc < 0 || x_loc >= num_cols) is_valid = 0;
            if (y_loc < 0 || y_loc >= num_rows) is_valid = 0;
            if (grade < 50 || grade > 104) is_valid = 0;
        }

        if (is_valid) {
            valid_time[valid_count] = time_stamps;
            valid_health[valid_count] = health;
            valid_x[valid_count] = x_loc;
            valid_y[valid_count] = y_loc;
            valid_grade[valid_count] = grade;
            valid_count++;
        } else {
            broken_time[broken_count] = time_stamps;
            broken_count++;
        }

    }

    for (int i = 0; i < broken_count - 1; i++) {
        for (int j = 0; j < broken_count - 1 - i; j++) {
            if (broken_time[j] > broken_time[j + 1]) {
                int tmp = broken_time[j];
                broken_time[j] = broken_time[j + 1];
                broken_time[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < valid_count - 1; i++) {
        for (int j = 0; j < valid_count - 1 - i; j++) {
            if (valid_time[j] > valid_time[j + 1]) {
                int tmp;

                tmp = valid_time[j];
                valid_time[j] = valid_time[j + 1];
                valid_time[j + 1] = tmp;

                tmp = valid_health[j];
                valid_health[j] = valid_health[j + 1];
                valid_health[j + 1] = tmp;

                tmp = valid_x[j];
                valid_x[j] = valid_x[j + 1];
                valid_x[j + 1] = tmp;

                tmp = valid_y[j];
                valid_y[j] = valid_y[j + 1];
                valid_y[j + 1] = tmp;

                tmp = valid_grade[j];
                valid_grade[j] = valid_grade[j + 1];
                valid_grade[j + 1] = tmp;
            }
        }
    }
    for (int i = 0; i < valid_count; i++) {
        fprintf(outFile, "%d {\"health\": %d, \"x_loc\": %d, \"y_loc\": %d, \"grade\": %d}\n",
                valid_time[i], valid_health[i], valid_x[i], valid_y[i], valid_grade[i]);
    }
    for (int i = 0; i < broken_count; i++) {
        fprintf(brokenFile, "%d\n", broken_time[i]);
    }

    fclose(saveFile);
    fclose(outFile);
    fclose(brokenFile);
    fclose(mapFile);

    return 0;
}
