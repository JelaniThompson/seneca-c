#include < stdio.h >

#define MAX_ITEMS 10

struct Item {
  int sku;
  float price;
  int quantity;
};

int main() {
  struct Item items[MAX_ITEMS];
  int size = 0, choice = 0, i = 0;
  const int low = -1;
  const int high = 5;

  for (i = 0; i < 20; i++) {
    printf("\n");
  }

  printf("Welcome to the Shop\n");
  printf("===================\n");

  do {
    choice = validate(low, high);
    
    // Replace with switch statement
    if (choice == 1) {
      displayInventory(items, size);
    }

    if (choice == 2) {

      addItem(items, & size);

    }
    if (choice == 3) {

      checkPrice();
    }
    if (choice == 4) {
      clear();

    }
  } while (choice != 0);

  printf("Goodbye!\n");
  return 0;
}

void menu() {

  printf("Please select from the following options:\n");
  printf("1) Display the inventory.\n2) Add to the inventory.\n3) Check price.\n4) Clear Screen.\n0) Exit.\n");

}

int validate(const int low,
  const int high) {

  int choice;

  menu();
  printf("Select: ");
  scanf("%d", & choice);
  do {
    if (choice < 0 || choice > 4) {

      printf("Invalid input, try again: ");
      scanf("%d", & choice);
    }
  } while (choice < 0 || choice > 4);
  return choice;
}

void clear() {
  int i;
  for (i = 0; i < 40; i++) {
    printf("\n");
  }

}

void displayInventory(const struct Item items[],
  const int size) {

  int i = 0;
  printf("Inventory\n");
  printf("======================\n");
  printf("Sku      Price     Quantity\n");
  while (i < size) {

    printf("%d     %0.2f     %d\n", items[i].sku, items[i].price, items[i].quantity);
    i++;

  }

  printf("=======================\n");

}

int searchInventory(const struct Item items[],
  const int sku_item,
    const int size) {

  int i = 0;
  while (i < size) {
    if (sku_item == items[i].sku) {
      return i;

    }
    i++;

  }
  return -1;
}
void addItem(struct Item items[], int * size) {
  int sku_item, searchres, additem;
  printf("Please input a SKU number: ");
  scanf("%d", & sku_item);
  searchres = searchInventory(items, sku_item, * size);
  if (searchres == -1) {
    items[ * size].sku = sku_item;
    printf("Quantity: ");
    scanf("%d", & items[ * size].quantity);
    printf("Price: ");
    scanf("%f", & items[ * size].price);
    printf("The item is successfully added to the inventory.\n"); * size = * size + 1;
  } else {
    printf("Quantity: ");
    scanf("%d", & additem);
    printf("The item exists in the repository, quantity is updated.\n");

    items[searchres].quantity = items[searchres].quantity + additem;
  }
}

void checkPrice() {

  printf("Not Implemented\n");

}
