#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getIntLimited(int lowerLimit, int upperLimit);


void clrKyb() {
    /*
    char ch;
    do {
        ch = getchar();
    }
    while (ch != '\n');
    */
    while(getchar() != '\n');
}

int menu(void) {
    int option;
    printf("1- List all items\n");
    printf("2- Search by SKU\n");
    printf("3- Checkout an item\n");
    printf("4- Stock an item\n");
    printf("5- Add new item or update item\n");
    printf("6- delete item\n");
    printf("7- Search by name\n");
    printf("0- Exit program\n");
    printf("> ");
    option = getIntLimited(0,7);
    return option;
}

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

void pause(void) {
  printf("Press <ENTER> to continue...");
  clrKyb();
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
    //int i = getInt();
    // If integer is not within the limits, print an error message
    int i;
    scanf("%d", & i);
    while (i < lowerLimit || i > upperLimit){
        printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
        //clrKyb();
        scanf("%d", & i);
    }
    clrKyb();
    return i;
}

double getDbl(void) {
  double d;
  char c;
  // Get a valid integer from the keyboard and return it. If it isn't valid, return an error message until it is
  scanf("%lf%c", & d, & c);
  if (c != '\n') {
    //print error message
    do {
      printf("Invalid number, please try again: ");
      clrKyb();
      scanf("%lf%c", & d, & c);
    } while (c != '\n');
  }
  return d;
}

double getDblLimited(double lowerLimit, double upperLimit) {
  double d = getDbl();
  // If number is not within the limits, print an error message
  do {
    printf("Invalid value, %lf< value < %lf: ", lowerLimit, upperLimit);
    scanf("%lf", & d);
  } while (d < lowerLimit || d > upperLimit);
  return d;
}

int yes(void) {
    return 0;
}

void GrocInvSys() {
    int selection;
    int done = 0;
    welcome();
    do {
        selection = menu();
        switch(selection) {
            case 1 :
                printf("List Items!\n");
                pause();
                //GrocInvSys();
                break;
            case 2 :
                printf("Search Items!\n");
                pause();
                //GrocInvSys();
                break;
            case 3 :
                printf("Checkout Item!\n");
                pause();
                //GrocInvSys();
                break;
            case 4 :
                printf("Stock Item!\n");
                pause();
                //GrocInvSys();
                break;
            case 5 :
                printf("Add/Update Item!\n");
                pause();
                //GrocInvSys();
                break;
            case 6 :
                printf("Delete Item!\n");
                pause();
                //GrocInvSys();
                break;
            case 7 :
                printf("Search by name!\n");
                pause();
                //GrocInvSys();
                break;
            case 0 :
                //clrKyb();
                printf("Exit the program? (Y)es/(N)o : ");
                char ch = getchar();
                //char ch;
                //scanf("%c", &ch);
                //printf("ch=%c\n", ch);
                if (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n') {
                    do {
                        clrKyb();
                        printf("Only (Y)es or (N)o are acceptable: ");
                        ch = getchar();
                        //scanf("%c", &ch);
                    } while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
                }

                if (ch == 'Y' || ch == 'y') {
                    done = 1;
                    break;
                } 
                //else if (ch == 'N' || ch == 'n') {
                //    GrocInvSys();
                //}
        }
   } while (done != 1); 
}
