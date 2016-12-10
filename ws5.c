#include <stdio.h>

#define MAX_ITEMS 10

     struct Item{
     int sku;
     float price;
     int quantity;
 };

 int main(){
     // Declare values
     struct Item item[MAX_ITEMS];
     int size = 0;
     int input_num = 0,quantity_input;
     float price_input;
     int input_sku;

     printf("Welcome to the Shop\n");
     printf("===================\n");

     do {
     printf("Please select from the following options:\n");
     printf("1) Display the inventory.\n");
     printf("2) Add to shop.\n");
	//printf("3) Price check.\n");
     printf("0) Exit.\n");
     printf("Select:");


     scanf("%d", &input_num);
   // Loop to check input numbers
   while(input_num < 0 || input_num > 3){
	 printf("Invalid input, try again: Please select from the following options:\n");
	 printf("1) Display the inventory.\n");
	 printf("2) Add to shop.\n");
	    //printf("3) Price check.\n");
printf("0) Exit.\n");
	 printf("Select:");
	 scanf("%d", &input_num);
     }

     switch(input_num)
     {
	 case 1:
	 printf("\n");
	 printf("\n");
	 printf("Inventory\n");
	 printf("=========================================\n");
	 printf("Sku         Price       Quanity\n");
	 int k;
	 for(k = 0; k < size; k++){
	     printf("%4d        %.2f       %d         \n", item[k].sku, item[k].price, item[k].quantity);
	  }
	 printf("=========================================\n");
	 break;


	 case 2:

	 printf("Please input a SKU number:");
	 scanf("%d", &input_sku);
	 int i,found =-1;

	 for(i = 0; i < size;i++){
	     if(input_sku == item[i].sku){
	     found = i;
	     i = size;
	    }
	 }

	 if(found >= 0){
printf("Quantity:");
	     scanf("%d", &quantity_input);
	     item[found].quantity += quantity_input;
	     printf("The item exists in the repository, quanity is updated.\n");
	 }
	 else
	 {
	     
	     printf("Quantity:");
	     scanf("%d", &quantity_input);
	     printf("Price:");
	     scanf("%f", &price_input);
	     printf("The item is successfully added to the inventory.\n");
	     item[i].sku = input_sku;
	     item[i].quantity = quantity_input;
	     item[i].price = price_input;

	     size++;
	 }

	 break;
// Break 3 for WS5 at home portion
/*
     case 3:
	 printf("Please input the sku number of the item:\n");
	 scanf("%d", &input_sku);

	 for(i = 0; i < size;i++){
	 if(inputsku == item[i].sku){
	     found = i;
	     i = size;
	 }
	 if(found >= 0){
		printf("Item %d costs $%.2f\n", item[found].sku, item[found].price);
	 }else
	     printf("Item does not exist in the shop! Please try again.\n");

      break;
*/
	     }
	 }
     while(input_num != 0); {
	 printf("Good bye!\n");
     }
 return 0;
 }
