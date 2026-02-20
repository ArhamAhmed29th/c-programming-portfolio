#include <stdio.h>
#include <math.h>

void print_distance(float d)
{
    int whole = (int)d;
    int decimals = (int)((d - whole) * 100 + 0.5f);

    if (decimals == 100) {
        whole++;
        decimals = 0;
    }

    if (whole >= 1000) {
        printf("%d,%03d.%02d", whole / 1000, whole % 1000, decimals);
    } else {
        printf("%d.%02d", whole, decimals);
    }
}


int main(void)
{
    float A1, A2, B1, B2, C1, C2, distance_1_2, distance_2_3, distance_1_3;

    printf("Point 1: ");
    if (scanf(" (%f, %f)", &A1, &A2 ) != 2) return 1;
    printf("Point 2: ");
    if (scanf(" (%f, %f)", &B1, &B2 ) != 2) return 1;
    printf("Point 3: ");
    if (scanf(" (%f, %f)", &C1, &C2 ) != 2) return 1;


    float dx = B1-A1;
    float dy = B2-A2;
    distance_1_2 = sqrtf((dx*dx) + (dy*dy));
    float dx1 = C1-B1;
    float dy1 = C2-B2;
    distance_2_3 = sqrtf((dx1*dx1) + (dy1*dy1));
    float dx2 = C1-A1;
    float dy2 = C2-A2;
    distance_1_3 = sqrtf((dx2*dx2) + (dy2*dy2));

    if (distance_1_2 < distance_1_3 && distance_1_2 < distance_2_3 ){
        printf("P1<->P2: ");
        print_distance(distance_1_2);
        printf("\n");
    }
    else if (distance_1_3 < distance_1_2 && distance_1_3 < distance_2_3 ){
        printf("P1<->P3: ");
        print_distance(distance_1_3);
        printf("\n");
    }
    else if (distance_2_3 < distance_1_2 && distance_2_3 < distance_1_3){
        printf("P2<->P3: ");
        print_distance(distance_2_3);
        printf("\n");
    }
    else if (distance_1_3 == distance_2_3 && distance_1_2 == distance_2_3 && distance_1_2 == distance_1_3) {
        printf("\nAll points are equal distance: ");
        print_distance(distance_1_3);
        printf("\n"); 
    
    }
    else if (distance_1_2 == distance_1_3){
        printf("P1<->P2: ");
        print_distance(distance_1_2);
        printf("\n"); 
        printf("P1<->P3: ");
        print_distance(distance_1_3);
        printf("\n"); }

    else if (distance_1_2 == distance_2_3){
        printf("P1<->P2: ");
        print_distance(distance_1_2);
        printf("\n"); 
        printf("P2<->P3: ");
        print_distance(distance_2_3);
        printf("\n"); 
    }
     else if (distance_1_3 == distance_2_3){
        printf("P1<->P3: ");
        print_distance(distance_1_3);
        printf("\n"); 
        printf("P2<->P3: ");
        print_distance(distance_2_3);
        printf("\n"); 
    }
    return 0;
}