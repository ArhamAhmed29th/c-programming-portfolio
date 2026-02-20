#include <stdio.h>

int main(void)
{
    float apples_max = 7.20, carrots_max = 4.10, apples_cost = 5.99, carrot_cost = 3.99, chips_cost = 2.99, candy_cost = 1.50, apples, carrots, total_apples, total_carrots, total_chips, total_candy, discount_candy, total_total_candy, entire_discount;
    int chips_max = 9, candy_max = 3, chips, candy, discounted_candies;

    printf("Apples     (7.20  kg) : ");
    if (scanf("%f", &apples) != 1) return 1;
    if (apples < 0 || apples > apples_max)return 1;

    printf("Carrots    (4.10  kg) : ");
    if (scanf("%f", &carrots) != 1) return 1;
    if (carrots < 0 || carrots > carrots_max)return 1;

    printf("Chips      (9  units) : ");
    if (scanf("%d", &chips) != 1) return 1;
    if (chips < 0 || chips > chips_max)return 1;

    printf("Candy      (3  units) : ");
    if (scanf("%d", &candy) != 1) return 1;
    if (candy < 0 || candy > candy_max)return 1;

    if (apples == 0 && carrots == 0 && chips == 0 && candy == 0){
        return 1;
    }

    total_apples = apples * apples_cost;
    total_carrots = carrots * carrot_cost;
    total_chips = chips * chips_cost;
    total_candy = candy * candy_cost;

    discounted_candies = chips / 2;
    if (discounted_candies > candy) discounted_candies = candy;
    discount_candy = discounted_candies * (candy_cost * 0.5f);

    if (apples>=1 && carrots>=1 && chips>=1 && candy>=1){
        entire_discount = 0.1f;
    }
    else {entire_discount = 0.0f;}  

    printf("\n-------------------------------------------------------------------\n");
    printf("| Item     | Quantity     | Cost       | Discount    | Total      |\n");
    if (apples != 0){
        printf("| Apples   | %-10.2fkg | $%9.2f | -$%9.2f | $%9.2f |\n", apples, total_apples, 0.0f, total_apples);
    }
    if (carrots != 0){
        printf("| Carrots  | %-10.2fkg | $%9.2f | -$%9.2f | $%9.2f |\n", carrots, total_carrots, 0.0f, total_carrots);
    }
    if (chips != 0){
        printf("| Chips    | %-13d| $%9.2f | -$%9.2f | $%9.2f |\n", chips, total_chips, 0.0f, total_chips);
    }
    if (candy != 0){
        printf("| Candy    | %-13d| $%9.2f | -$%9.2f | $%9.2f |\n", candy, total_candy, discount_candy, total_total_candy = total_candy - discount_candy);
    }
    printf("-------------------------------------------------------------------\n");

    float sub_total = total_apples + total_carrots + total_chips + total_total_candy;
    float total_discounted = sub_total * entire_discount;
    float total_total = sub_total - total_discounted;
    float tax = total_total * 0.05;
    float total_after_tax = total_total + tax;

    if (entire_discount != 0){
        printf("\nSubtotal        : $%.2f - $%.2f = $%.2f\n", sub_total, total_discounted, total_total);
        printf("Tax (5%%)        : $%.2f\n", tax);
        printf("----------------------------------------------------\n");
        printf("Total           : $%.2f\n", total_after_tax);
    }
    else if (entire_discount == 0.0){
        printf("\nSubtotal        : $%.2f\n", sub_total);
        printf("Tax (5%%)        : $%.2f\n", tax);
        printf("----------------------------------------------------\n");
        printf("Total           : $%.2f\n", total_after_tax);
    }
    

    return 0;
}
