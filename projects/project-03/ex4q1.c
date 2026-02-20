#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int seed, w_grid, h_grid, num_cities;

    scanf("%d", &seed);
    srand(seed);
    w_grid = (rand() % 1000) + 1;
    h_grid = (rand() % 1000) + 1;
    fprintf(stderr, "W=%d H=%d\n", w_grid, h_grid);

    
    scanf("%d", &num_cities);
    if (num_cities > w_grid*h_grid){
        return 0;
    }

    int i = 0, x, y, city_x[num_cities], city_y[num_cities];
    while (i < num_cities){
        scanf(" (%d, %d)", &x, &y);
        if (x<0 || y<0 || x>=w_grid || y>=h_grid){
            return 0;
        }
        city_x[i] = x;
        city_y[i] = y;
        i++; 
    }

    int current_x[num_cities], current_y[num_cities];
    for (int i = 0; i < num_cities; i++){
        current_x[i] = city_x[i];
        current_y[i] = city_y[i];
    }

    double distance_traveled[num_cities];
    for (int i = 0; i < num_cities; i++){
        distance_traveled[i] = 0.0;
    }
    
    int cities_visited[num_cities];
    for (int i = 0; i < num_cities; i++){
        cities_visited[i] = 1;
    }

    int visiting_check[num_cities][num_cities];
    for (int row = 0; row < num_cities; row++){
        for (int col = 0; col < num_cities; col++){
            if (row == col){
                visiting_check[row][col] = 1;
            }
            else if (row != col){
                visiting_check[row][col] = 0;
            }}}

    int sn, dx, dy;
    while (1) {

    char command_type;
    command_type = getchar();
        while (command_type == ' ' || command_type == '\n') {
            command_type = getchar();
        }
        if (command_type == 'm') {
            scanf(" %d : (%d, %d)", &sn, &dx, &dy);
            current_x[sn] += dx;
            current_x[sn] = ((current_x[sn] % w_grid) + w_grid) % w_grid;
            current_y[sn] += dy;
            current_y[sn] = ((current_y[sn] % h_grid) + h_grid) % h_grid;
            distance_traveled[sn] += sqrt((double)dx*dx+(double)dy*dy);
            
            for (int i = 0; i < num_cities; i++){
                if (current_x[sn] == city_x[i] && current_y[sn] == city_y[i]){
                    if (visiting_check[sn][i] == 0){
                        visiting_check[sn][i] = 1;
                        cities_visited[sn]++;
                    }}}}

        else if (command_type == 'l') {
            char sub_command_type = getchar();

            while (sub_command_type == ' ' || sub_command_type == '\n') {
                sub_command_type = getchar();
            }
            if (sub_command_type == 'c') {
                int order[num_cities];
                for (int i = 0; i < num_cities; i++) {
                    order[i] = i;
                }
                for (int a = 0; a < num_cities; a++) {
                    int best = a;
                    for (int b = a + 1; b < num_cities; b++) {
                        int id1 = order[best];
                        int id2 = order[b];

                        if (cities_visited[id2] > cities_visited[id1] ||
                        (cities_visited[id2] == cities_visited[id1] && id2 < id1)) {
                            best = b;
                        }
                    }
                    int tmp = order[a];
                    order[a] = order[best];
                    order[best] = tmp;
                }
                printf("+-------+-------------+----------------+--------------------+\n");
                printf("| Place | Salesperson | Cities Visited | Distance Travelled |\n");
                printf("|-------+-------------+----------------+--------------------|\n");


                int rows = (num_cities < 10) ? num_cities : 10;
                int place = 1;
                for (int k = 0; k < rows; k++) {
                    int id = order[k];
                    if (k > 0) {
                        int prev_id = order[k - 1];
                        if (cities_visited[id] != cities_visited[prev_id]) {
                            place = k + 1;
                        }}

                    printf("|%5d. | %-11d | %-14d | %-18.1f |\n",
                        place,
                        id,
                        cities_visited[id],
                        distance_traveled[id]);
                }
                printf("+-------+-------------+----------------+--------------------+\n");
            }
            else if (sub_command_type == 'd') {

                int order[num_cities];
                for (int i = 0; i < num_cities; i++) {
                    order[i] = i;
                }
                for (int a = 0; a < num_cities; a++) {
                    int best = a;
                    for (int b = a + 1; b < num_cities; b++) {
                        int id1 = order[best];
                        int id2 = order[b];

                        if (distance_traveled[id2] > distance_traveled[id1] ||
                        (distance_traveled[id2] == distance_traveled[id1] && id2 < id1)) {
                            best = b;
                        }}
                    int tmp = order[a];
                    order[a] = order[best];
                    order[best] = tmp;
                }
                printf("+-------+-------------+----------------+--------------------+\n");
                printf("| Place | Salesperson | Cities Visited | Distance Travelled |\n");
                printf("|-------+-------------+----------------+--------------------|\n");


                int rows = (num_cities < 10) ? num_cities : 10;
                int place = 1;

                for (int k = 0; k < rows; k++) {
                    int id = order[k];
                    if (k > 0) {
                        int prev_id = order[k - 1];
                        if (distance_traveled[id] != distance_traveled[prev_id]) {
                            place = k + 1;
                        }}
                    printf("|%5d. | %-11d | %-14d | %-18.1f |\n",
                        place,
                        id,
                        cities_visited[id],
                        distance_traveled[id]);
                }
                printf("+-------+-------------+----------------+--------------------+\n");
            }}

        else if (command_type == 'e') {

            int max_cities = cities_visited[0];
            for (int i = 1; i < num_cities; i++) {
                if (cities_visited[i] > max_cities) {
                    max_cities = cities_visited[i];
                }}

            printf("Winners:\n");
            printf("Cities Visited     : ");

            int first = 1;
            for (int i = 0; i < num_cities; i++) {
                if (cities_visited[i] == max_cities) {
                    if (!first) {
                        printf(", ");
                    }
                    printf("%d", i);
                    first = 0;
                }}
            printf(" with %d\n", max_cities);

            double max_dist = distance_traveled[0];
            for (int i = 1; i < num_cities; i++) {
                if (distance_traveled[i] > max_dist) {
                    max_dist = distance_traveled[i];
                }}
            printf("Distance Travelled : ");
            first = 1;
            for (int i = 0; i < num_cities; i++) {
                if (distance_traveled[i] == max_dist) {
                    if (!first) {
                        printf(", ");
                    }
                    printf("%d", i);
                    first = 0;
                }}
            printf(" with %.1f\n", max_dist);
            return 0;
        }}

    return 0;
}