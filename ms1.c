// includes go here
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

void welcome(void) {
     printf("---=== Grocery Inventory System ===---\n\n");
}

void prnTitle(void) {
    printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
    printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}

void prnFooter(double gTotal) {
    printf("--------------------------------------------------------+----------------\n");
    if (gTotal > 0) {
        printf("                                           Grand Total: |%12.2lf\n", gTotal);
    }
}

void clrKyb(void) {
    char input;
    scanf("%c", &input);
    while (strcmp(&input, "\n") != 0) {
        scanf("%c", &input);
    }
}

void pause(void) {
    printf("Press <ENTER> to continue...");
    clrKyb();
    //scanf("%c", &isEmpty);
}

int getInt(void) {
    int i;
    char c;
    // Get a valid integer from the keyboard and return it. If it isn't valid, return an error message until it is
    scanf("%d%c", &i, &c);
    if (c != '\n') {
        //print error message
        while (c != '\n') {
            printf("Invalid integer, please try again: ");
            clrKyb();
            scanf("%d%c", &i, &c);
        }
    }
    return i;
}

int getIntLimited(int lowerLimit, int upperLimit) {
    int i = getInt();
    // If integer is not within the limits, print an error message
    do {
       printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
       //clrKyb();
       scanf("%d", &i);
    } while (i < lowerLimit || i > upperLimit);
    return i;
}

double getDbl(void) {
    double d;
    char c;
    // Get a valid integer from the keyboard and return it. If it isn't valid, return an error message until it is
    scanf("%lf%c", &d, &c);
    if ( c != '\n') {
        //print error message
        do {
            printf("Invalid number, please try again: ");
            clrKyb();
            scanf("%lf%c", &d, &c);
        } while (c != '\n');
    }
    return d;
}

double getDblLimited(double lowerLimit, double upperLimit) {
    double d = getDbl();
    // If number is not within the limits, print an error message
    do {
        printf("Invalid value, %lf< value < %lf: ", lowerLimit, upperLimit);
        scanf("%lf", &d);
    } while (d < lowerLimit || d > upperLimit);
    return d;
}
