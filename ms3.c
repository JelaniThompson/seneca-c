#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0

/* ms1 prototypes*/
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
    while(getchar() != '\n');
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

double getDbl(void) {
    double d;
    char c;
    // Get a valid integer from the keyboard and return it. If it isn't valid, return an error message until it is
    scanf("%lf%c", &d, &c);
    if (c != '\n') {
        //print error message
        do {
            printf("Invalid number, please try again: ");
            clrKyb();
            scanf("%lf%c", &d, &c);
        } while (c != '\n');
    }
    return d;
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

double getDblLimited(double lowerLimit, double upperLimit) {
    double d = getDbl();
    // If number is not within the limits, print an error message
    do {
        printf("Invalid value, %lf< value < %lf: ", lowerLimit, upperLimit);
        scanf("%lf", & d);
    } while (d < lowerLimit || d > upperLimit);
    return d;
}

/* ipc_ms2 prototype*/
int yes(void) {
    char ch = getchar();
    if (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n') {
        do {
            clrKyb();
            printf("Only (Y)es or (N)o are acceptable: ");
            ch = getchar();
            //scanf("%c", &ch);
        } while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n');
    }
    
    if (ch == 'Y' || ch == 'y') {
        return 1;
    } else { return 0; }
}

struct Item {
   double price;
   int sku;
   int isTaxed;
   int quantity;
   int minQuantity;
   char name[21];
};

/* ms3 prototypes*/

double totalAfterTax(struct Item item) {
    double taxedTotal = item.price * item.quantity;
    return taxedTotal;
}

int isLowQty(struct Item item) {
    if (item.quantity < item.minQuantity) {
        return 1;
    } else { return 0; }
}

struct Item itemEntry(int sku) {
    struct Item inputEnter;
    printf("        SKU: %d", &sku);
    printf("       Name: ");
    scanf("%20[^\n]", &inputEnter.name);
    clrKyb();
    
    printf("      Price: ");
    double price_value = getDbl();
    inputEnter.price = price_value;
    
    printf("   Quantity: ");
    inputEnter.quantity = getInt();
    
    printf("Minimum Qty: ");
    inputEnter.minQuantity = getInt();
    
    printf("   Is Taxed: ");
    inputEnter.isTaxed = yes();
}

void dspItem(struct Item item, int linear) {
    if (LINEAR) {
        if (item.isTaxed && item.quantity > item.minQuantity) {
            printf("|%d|%-20s|%8.2lf|  Yes | %3d | %12.2lf|");
        } else if (item.isTaxed && item.quantity <= item.minQuantity) {
            printf("|%d|%-20s|%8.2lf|  Yes | %3d | %12.2lf|***");
        }
    }

    if(FORM) {
        printf("        SKU: %d", item.sku);
        printf("       Name: %c", item.name);
        printf("      Price: %lf", item.price);
        printf("   Quantity: %d", item.quantity);
        printf("Minimum Qty: %d", item.minQuantity);
        printf("   Is Taxed: No");
    } else {
        printf("        SKU: %d", item.sku);
        printf("       Name: %c", item.name);
        printf("      Price: %lf", item.price);
        printf("   Quantity: %d", item.quantity);
        printf("Minimum Qty: %d", item.minQuantity);
        printf("   Is Taxed: Yes");
        printf("WARNING: Quantity low, please order ASAP!!!");
    }
}

void listItems(const struct Item item[], int NoOfItems) {
    int counter;
    double grandTotal = 0;
    prnTitle();
    for (counter; counter < NoOfItems; counter++) {
        printf("%-4d", counter);
        LINEAR = 1;
        grandTotal += item[counter].price;
        prnFooter(grandTotal);
    }
}

int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index) {
    int i = 0;
    // Set index to the index of the item element the sku is found in
    for (i; i < NoOfRecs; i++) {
        index = item[i];
        if (item[i].sku == sku) {
            return 1;
        } else {
            return 0;
        }
    }
}

/* Constant double TAX value */
const double TAX = 0.13;

int main() {
   struct Item I[21] = {
      { 4.4,275,0,10,2,"Royal Gala Apples" },
      { 5.99,386,0,20,4,"Honeydew Melon" },
      { 3.99,240,0,30,5,"Blueberries" },
      { 10.56,916,0,20,3,"Seedless Grapes" },
      { 2.5,385,0,5,2,"Pomegranate" },
      { 0.44,495,0,100,30,"Banana" },
      { 0.5,316,0,123,10,"Kiwifruit" },
      { 4.49,355,1,20,5,"Chicken Alfredo" },
      { 5.49,846,1,3,5,"Veal Parmigiana" },
      { 5.29,359,1,40,5,"Beffsteak Pie" },
      { 4.79,127,1,30,3,"Curry Checken" },
      { 16.99,238,1,10,2,"Tide Detergent" },
      { 10.49,324,1,40,5,"Tide Liq. Pods" },
      { 10.99,491,1,50,5,"Tide Powder Det." },
      { 3.69,538,1,1,5,"Lays Chips S&V" },
      { 3.29,649,1,15,5,"Joe Org Chips" },
      { 1.79,731,1,100,10,"Allen's Apple Juice" },
      { 6.69,984,1,30,3,"Coke 12 Pack" },
      { 7.29,350,1,50,5,"Nestea 12 Pack" },
      { 6.49,835,1,20,2,"7up 12 pack" }
   };
   double val;
   int ival;
   int searchIndex;
   val = totalAfterTax(I[0]);
   printf("totalAfterTax: yours=%lf, program's=44.000000\n", val);
   val = totalAfterTax(I[7]);
   printf("totalAfterTax: yours=%lf, program's=101.474000\n", val);
   ival = isLowQty(I[0]);
   printf("isLowQty: yours=%d, program's=0\n",ival);
   ival = isLowQty(I[14]);
   printf("isLowQty: yours=%d, program's=1\n",ival);
   pause();
   printf("itemEntry, enter the following values:\n");
   printf("        SKU: 999\n"
      "       Name: Red Apples\n"
      "      Price: 4.54\n"
      "   Quantity: 50\n"
      "Minimum Qty: 5\n"
      "   Is Taxed: n\n");
   printf("Enter the values:\n");
   I[20] = itemEntry(999);
   printf("dspItem, Linear:\nYours: ");
   dspItem(I[20], LINEAR);
   printf(" Prog: |999|Red Apples          |    4.54|   No|  50 |   5 |      227.00|\n");
   printf("dspItem, Form:\nYours:\n");
   dspItem(I[20], FORM);
   printf("Programs: \n");
   printf("        SKU: 999\n"
      "       Name: Red Apples\n"
      "      Price: 4.54\n"
      "   Quantity: 50\n"
      "Minimum Qty: 5\n"
      "   Is Taxed: No\n");
   I[20].quantity = 2;
   I[20].isTaxed = 1;
   pause();
   printf("dspItem, Linear with low value and taxed:\nYours: ");
   dspItem(I[20], LINEAR);
   printf(" Prog: |999|Red Apples          |    4.54|  Yes|   2 |   5 |       10.26|***\n");
   printf("dspItem, Form with low value:\nYours:\n");
   dspItem(I[20], FORM);
   printf("Programs: \n");
   printf("        SKU: 999\n"
      "       Name: Red Apples\n"
      "      Price: 4.54\n"
      "   Quantity: 2\n"
      "Minimum Qty: 5\n"
      "   Is Taxed: Yes\n"
      "WARNING: Quantity low, please order ASAP!!!\n");
   pause();
   printf("Listing Items: \n");
   listItems(I, 21);
   pause();
   printf("Locate Item, successful search:\n");
   printf("program: Found the item 999 at index: 20\n");
   printf("  Yours: ");
   if (locateItem(I, 21, 999, &searchIndex)) {
      printf("Found the item 999 at index: %d\n", searchIndex);
   }
   else {
      printf("No item with the sku 999 is in the array!\n");
   }

   printf("Locae Item, unsuccessful search:\n");
   printf("Progam: No item with the sku 732 is in the array!\n");
   printf(" Yours: ");
   if (locateItem(I, 21, 732, &searchIndex)) {
      printf("Found the item at index: %d\n", searchIndex);
   }
   else {
      printf("No item with the sku 732 is in the array!\n");
   }
   return 0;
}

/*   item entry output 
        SKU: 999
       Name: Red Apples
      Price: 4.54
   Quantity: 50
Minimum Qty: 5
   Is Taxed: n

        SKU: 999
       Name: Red Apples
      Price: 4.54
   Quantity: 50
Minimum Qty: 5
   Is Taxed: No
WARNING: Quantity low, please order ASAP!!!
   

*/

/*  dspItems
|999|Red Apples          |    4.54|   No|  50 |   5 |      227.00|

        SKU: 999
       Name: Red Apples
      Price: 4.54
   Quantity: 50
Minimum qty: 5
   Is Taxed: No

*/


/*ms1 and 2 functions: */
