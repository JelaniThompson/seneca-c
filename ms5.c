#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item {
   double price;
   int sku;
   int isTaxed;
   int quantity;
   int minQuantity;
   char name[21];
};




/********************************************************************
Milestones 1 to 4  prototypes, definitions and etc...*/

#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0
//#define MAX_ITEM_NO 21
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100

const double TAX = 0.13;

/* ipc_ms1 prototypes*/
void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
void pause(void);
void clrKyb(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);

/* ipc_ms2 prototype*/
int menu(void); 
void GrocInvSys(void);
int yes(void);

/* ipc_ms3 prototypes*/
double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);

/* ipc_ms4 prototypes*/
void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);

/********************************************************************
End of milestone 1 to 4 stuff
*********************************************************************/



/********************************************************************
Milestone 5 prototypes*/


#define MAX_ITEM_NO 500   
#define DATAFILE "ipc_ms5_short.txt" 

void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(struct Item* item, char fileName[], int NoOfRecs);
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr);
void failSaveItems(struct Item* item, char fileName[], int NoOfRecs);

/*End of milestone 5 prototypes
*********************************************************************/




/**************************************************************************
    TTTTTTTTT   EEEEEEEE   SSSSSSSS   TTTTTTTTTT   EEEEEEEEE   RRRRRRRR                                                      
       TT       EE         SS             TT       EE          RR     RR          
       TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RRRRRRRR
       TT       EE               SS       TT       EE          RR  RR
       TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RR    RR
***************************************************************************
Tester for saveItem, loadItem, saveItems and loadItems:
uncomment this to test your functions prior to putting all the code together by adding a * and / here: 



void prnFile() {
   FILE* tp = fopen("test.txt", "r");
   char ch;
   if (tp) {
      for (; fscanf(tp,"%c", &ch) == 1; putchar(ch));
      fclose(tp);
   }
   else {
      printf("text.txt not found\n");
   }
}


int main(void) {
   int i, n;
   struct Item GI[3] = {
      { 4.4,275,0,10,2,"Royal Gala Apples" },
      { 5.99,386,0,20,4,"Honeydew Melon" },
      { 3.99,240,0,30,5,"Blueberries" },
   };
   struct Item I;
   struct Item IN[3];
   printf("***********Testing saveItem:\n");
   printf("Your saveItem saved the following in test.txt: \n");
   FILE* tp = fopen("test.txt", "w");
   if (tp) {
      for (i = 0; i < 3; i++) saveItem(GI[i], tp);
      fclose(tp);
      prnFile();
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("275,10,2,4.40,0,Royal Gala Apples\n");
   printf("386,20,4,5.99,0,Honeydew Melon\n");
   printf("240,30,5,3.99,0,Blueberries\n");
   printf("***********END Testing saveItem!\n\n\n");
   pause();
   printf("***********Testing loadItem:\n");
   printf("Your loadItem loaded the following from test.txt: \n");
   tp = fopen("test.txt", "r");
   if (tp) {
      for (i = 0; i < 3; i++) {
         loadItem(&I, tp);
         dspItem(I, LINEAR);
      }
      fclose(tp);
      tp = fopen("test.txt", "w");
      fclose(tp);
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
   printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
   printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
   printf("***********END Testing loadItem!\n\n\n");
   pause();
   printf("***********Testing saveItems:\n");
   printf("Your saveItems saved the following in test.txt: \n");
   saveItems(GI, "test.txt", 3);
   prnFile();
   printf("*******************************\nThey have to match the following:\n");
   printf("275,10,2,4.40,0,Royal Gala Apples\n");
   printf("386,20,4,5.99,0,Honeydew Melon\n");
   printf("240,30,5,3.99,0,Blueberries\n");
   printf("***********END Testing saveItems!\n\n\n");
   pause();
   printf("***********Testing loadItems:\n");
   printf("Your loadItems loaded the following from test.txt: \n");
   loadItems(IN, "test.txt", &n);
   for (i = 0; i < n; i++) {
      dspItem(IN[i], LINEAR);
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
   printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
   printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
   printf("***********END Testing loadItems!\n\n\n");
   pause();
   printf("Done!\n");
   return 0;
}

/* End MS5 functions' tester
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/


/********************************************************************
Main function to run the application
uncomment this to test your functions after putting all the code together by adding a * and / here: */

int main(void) {
GrocInvSys();
return 0;
}

/* End Main function
********************************************************************/





/********************************************************************
Milestone 5 functions*/
void saveItem(struct Item item, FILE* dataFile){
    fprintf(dataFile, "%d, %d, %d, %.2lf, %d, %s\n",
                        item.sku,
                        item.quantity,
                        item.minQuantity,
                        item.price,
                        item.isTaxed,
                        item.name);
}

int loadItem(struct Item* item, FILE* dataFile){
    int found = 0;
    char fs;

    if(fscanf(dataFile, "%d%c%d%c%d%c%lf%c%d%c%[^\n]",
                            &item->sku,
                            &fs,
                            &item->quantity,
                            &fs,
                            &item->minQuantity,
                            &fs,
                            &item->price,
                            &fs,
                            &item->isTaxed,
                            &fs,
                            item->name) > 0)
    {
        found = 1;
    }
    return found;
}

int saveItems(struct Item* item, char fileName[], int NoOfRecs){
    int found = 0;
    int i;
    FILE *tp = fopen(fileName, "w");

    if(tp){
        found = 1;

        for(i=0; i<NoOfRecs; i++){
            saveItem(item[i], tp);
        }
        fclose(tp);
    }
    return found;
}

int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr){
    int found = 0;
    FILE *tp = fopen(fileName, "r");
    
    if(tp){
        *NoOfRecsPtr = 0;

        while(loadItem(&item[*NoOfRecsPtr], tp)){
            *NoOfRecsPtr = *NoOfRecsPtr + 1;
        }
        found = 1;
        fclose(tp);
    }
    return found;
}

void failSaveItems(struct Item* item, char fileName[], int NoOfRecs){
    if(!(saveItems(item, fileName, NoOfRecs))){
        printf("could not update data file %s\n", DATAFILE);
    }
}

/*End of milestone 5 functions
*********************************************************************/

/********************************************************************
Milestones 1  to 4 functions*/

/*******************************************************************/
/* ms1 prototypes*/
void welcome(void){
    printf("---=== Grocery Inventory System ===---\n\n");
    return;
};
void prnTitle(void){
    printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
    printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
    return;
};
void prnFooter(double gTotal){
    printf("--------------------------------------------------------+----------------\n");
    if (gTotal > 0){
        printf("                                           Grand Total: |%12.2lf\n", gTotal);
    }
    return;
};
void clrKyb(void){
    while (getchar() != '\n');
    return;
};
void pause(void){
    printf("Press <ENTER> to continue...");
    clrKyb();
    return;
};
int getInt(void){
    int Value;
    char NL = 'x';
    while (NL != '\n'){
        scanf("%d%c", &Value, &NL);

        if (NL != '\n'){
            clrKyb();
            printf("Invalid integer, please try again: ");
        }

    }
    return Value;
};
double getDbl(void){
    double Value;
    char NL = 'x';
    while (NL != '\n'){
        scanf("%lf%c", &Value, &NL);
       
        if (NL != '\n'){
            clrKyb();
            printf("Invalid number, please try again: ");
        }
    }
    return  Value;
};
int getIntLimited(int lowerLimit, int upperLimit){
    int Value;
    do
    {
        Value = getInt();
        if (Value < lowerLimit || Value > upperLimit){
            printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
        }
    }while(Value < lowerLimit || Value > upperLimit);
    return Value;
};
double getDblLimited(double lowerLimit, double upperLimit){
    double Value;
    do
    {
        Value = getDbl();
        if (Value < lowerLimit || Value > upperLimit){
            printf("Invalid value, %.6lf< value < %.6lf: ", lowerLimit, upperLimit);
        }
    }while(Value < lowerLimit || Value > upperLimit);
    return Value;
};

/************************************************************/
/* ipc_ms2 prototype*/
int yes(void){  // ms2
    char CH;
    int RET = 0;
    do {
        scanf("%c", &CH);
        clrKyb();
        if (!((CH == 'y') || (CH == 'Y') || (CH == 'n') || (CH == 'N'))){
            printf("Only (Y)es or (N)o are acceptable: ");
        }
    }while(!((CH == 'y') || (CH == 'Y') || (CH == 'n') || (CH == 'N')));
    
    if((CH == 'y') || (CH == 'Y')){
        RET = 1;
    }
    return RET;
};

int menu(void)
{

    int select;

    printf("1- List all items\n");
    printf("2- Search by SKU\n");
    printf("3- Checkout an item\n");
    printf("4- Stock an item\n");
    printf("5- Add new item or update item\n");
    //printf("6- delete item\n");
    //printf("7- Search by name\n");
    printf("0- Exit program\n");
    printf("> ");
    do {
        scanf("%d",&select);
        clrKyb();
        if (select < 0 || select > 7){
            printf("Invalid value, 0 < value < 7: ");
        }
    }while (select < 0 || select > 7);
    return select;
};

void GrocInvSys(void)
{
    int choice;
    int found = 0;
    int NoOfRecs; // ipc_ms5
    struct Item ms5[MAX_ITEM_NO]; // ipc-ms5
    welcome();

    if(!(loadItems(ms5, DATAFILE, &NoOfRecs))){
        printf("Could not read from %s.\n", DATAFILE);
    }else while (found == 0){
        choice = menu();

        switch (choice){
            case 1:
                listItems(ms5, NoOfRecs);
                pause();
                break;

            case 2:
                search(ms5, NoOfRecs);
                pause();
                break;

            case 3:
                adjustQty(ms5, NoOfRecs, CHECKOUT);
                failSaveItems(ms5, DATAFILE, NoOfRecs);
                pause();
                break;

            case 4:
                adjustQty(ms5, NoOfRecs, STOCK);
                failSaveItems(ms5, DATAFILE, NoOfRecs);
                pause();
                break;
            
            case 5:
                addOrUpdateItem(ms5, &NoOfRecs);
                failSaveItems(ms5, DATAFILE, NoOfRecs);
                pause();
                break;
           
            case 0:
                printf("Exit the program? (Y)es/(N)o): ");
                found = yes();
        }                
    };       
};

/************************************************************/
/* ipc_ms3 prototype*/

double totalAfterTax(struct Item item){
    double total = 0;

    total = item.price * item.quantity;
    if(item.isTaxed){
        total = total * ( 1 + TAX);
    }
    return total;
};
int isLowQty(struct Item item){
    int found = 0;

    if(item.quantity < item.minQuantity){
        found = 1;
    }
    return found;
};
struct Item itemEntry(int sku){
    struct Item new;

    new.sku = sku;
    printf("        SKU: %d\n", new.sku);
    printf("       Name: ");
    scanf("%20[^\n]", new.name);
    clrKyb();
    printf("      Price: ");
        new.price = getDblLimited(0.01, 1000.00);
    printf("   Quantity: ");
        new.quantity = getIntLimited(1, MAX_QTY);
    printf("Minimum Qty: ");
        new.minQuantity = getIntLimited(0, 100);
    printf("   Is Taxed: ");
        new.isTaxed = yes();
    
    return new;
};
void dspItem(struct Item item, int linear){
    int i;
    if (linear){
        printf("|%3d|", item.sku);
        for(i = 0; item.name[i] != '\0'; i++){
            printf("%c", item.name[i]); 
        }
        while(i < 20){
            printf(" ");
            i++;
        }
        printf("|%8.2lf|  ", item.price);
        if (item.isTaxed){
            printf("Yes| ");
        }else{
            printf(" No| ");
        }
        printf("%3d | %3d |", item.quantity, item.minQuantity);
        if (item.isTaxed){
            printf("%12.2lf|", (item.price * item.quantity * (1 + TAX)));
        }else{
            printf("%12.2lf|", (item.price * item.quantity));
        }
        if (item.quantity <= 5){
            printf("***");
        }
        printf("\n");

    }else{
        printf("        SKU: %d\n", item.sku);
        printf("       Name: ");

        for (i = 0; item.name[i] != '\0'; i++){
            printf("%c", item.name[i]);
        }
        printf("\n      Price: %.2lf\n", item.price);
        printf("   Quantity: %d\n", item.quantity);
        printf("Minimum Qty: %d\n", item.minQuantity);

        if(item.isTaxed){
            printf("   Is Taxed: Yes\n");
        }else{
            printf("   Is Taxed: No\n");
        }

        if(item.quantity <= item.minQuantity){
            printf("WARNING: Quantity low, please order ASAP!!!\n");
        }
    }
};  
void listItems(const struct Item item[], int NoOfItems){
    int i;
    double grand_total = 0;
    prnTitle();

    for(i = 0; i < NoOfItems; i++){
        printf("%-4d", i+1 );
        dspItem(item[i], LINEAR);

        if (item[i].isTaxed){ 
            grand_total = grand_total + (item[i].price * item[i].quantity * (1 + TAX));
        }else{ 
            grand_total = grand_total + (item[i].price * item[i].quantity);
        }
    }
        prnFooter(grand_total);
};
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index){
    int i, true_false = 0;

    for(i = 0; i < NoOfRecs; i++){
        if(item[i].sku == sku){
            true_false = 1;
            *index = i;
            break;
        }
    }
    return true_false;
};

/************************************************************/
/* ipc_ms4 prototype*/

void search(const struct Item item[], int NoOfRecs) {
    int findSKU, index;
    printf("Please enter the SKU: ");
    findSKU = getIntLimited(SKU_MIN, SKU_MAX);

    if(locateItem(item, NoOfRecs, findSKU, &index)){
        dspItem(item[index], FORM);
    }else{
        printf("Item not found!\n");
    }
    
}

void updateItem(struct Item* itemptr) {
    struct Item update;

    printf("Enter new data:\n");
    update = itemEntry((*itemptr).sku);
    printf("Overwrite old data? (Y)es/(N)o: ");

    if(yes()){
        *itemptr = update;
        printf("--== Updated! ==--\n");
    }else{
        printf("--== Aborted! ==--\n");
    }
}

void addItem(struct Item item[], int *NoOfRecs, int sku) {
    struct Item add;

    if(*NoOfRecs == MAX_ITEM_NO){
        printf("Can not add new item; Storage Full!\n");
    }else{
        add = itemEntry(sku);
        printf("Add Item? (Y)es/(N)o: ");

        if(yes()){
            (item[*NoOfRecs]) = add;
            *NoOfRecs = *NoOfRecs + 1;

            printf("--== Added! ==--\n");
        }else{
            printf("--== Aborted! ==--\n");
        }
    }
}

void addOrUpdateItem(struct Item item[], int* NoOfRecs) {
    int findSKU, index;

    printf("Please enter the SKU: ");
    findSKU = getIntLimited(SKU_MIN, SKU_MAX);

    if(locateItem(item, *NoOfRecs, findSKU, &index)){
        dspItem(item[index], FORM);
        printf("Item already exists, Update? (Y)es/(N)o: ");

        if(yes()){
            updateItem(&item[index]);
        }else{
            printf("--== Aborted! ==--\n");
        }
    }else{
        addItem(item, NoOfRecs, findSKU);
    }
}

void adjustQty(struct Item item[], int NoOfRecs, int stock) {
    int findSKU, index;
    int update, max;
    char *stockCondition;

    printf("Please enter the SKU: ");
    findSKU = getIntLimited(SKU_MIN, SKU_MAX);

    if(locateItem(item, NoOfRecs, findSKU, &index)){
        dspItem(item[index], FORM);

        if(stock){
            stockCondition = "to stock";
            max = MAX_QTY - item[index].quantity;
        }else{
            stockCondition = "to checkout";
            max = item[index].quantity;
        }

        printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", 
                stockCondition, max);
        update = getIntLimited(0, max);

        if(update == 0){
            printf("--== Aborted! ==--\n");
        }else if(stock){
            item[index].quantity = item[index].quantity + update;
            printf("--== Stocked! ==--\n");
        }else{
            item[index].quantity = item[index].quantity - update;
            printf("--== Checked out! ==--\n");

            if(item[index].quantity <= item[index].minQuantity){
                printf("WARNING: Quantity is low, please reorder ASAP!!!\n");
            }
        }
    }
    else{
        printf("SKU not found in storage!\n");
    }
}

/*End of milestone 1 to 4 functions
*********************************************************************/








/* ms5 Tester output

***********Testing saveItem:
Your saveItem saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItem!


Press <ENTER> to continue...
***********Testing loadItem:
Your loadItem loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItem!


Press <ENTER> to continue...
***********Testing saveItems:
Your saveItems saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItems!


Press <ENTER> to continue...
***********Testing loadItems:
Your loadItems loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItems!


Press <ENTER> to continue...
Done!


*/
