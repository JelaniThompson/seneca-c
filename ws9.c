// Workshop 9 - Files
// Name:
// Student #:
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND   -1


struct Box{
   int id;        // the box ID
   double size[3];   // dimensions of the box (Length, Width, Height)
   double weight; // weight of the box
};

void listBoxes(const char filename[]){ // lists all boxes in the file
    FILE *fpointer = NULL;
    fpointer = fopen(filename, "r");
    struct Box boxes;

    if(fpointer != NULL){
        printf("List of boxes\n");
        printf("=============\n\n");
        printf("ID Length Width Height Weight\n");
        printf("-----------------------------\n");

        while(fscanf(fpointer, "%d %lf %lf %lf %lf",
                                &boxes.id, 
                                &boxes.size[0], 
                                &boxes.size[1], 
                                &boxes.size[2], 
                                &boxes.weight) == 5)
        {
            printf("%2d %6.2lf %5.2lf %6.2lf %6.2lf\n", 
                    boxes.id, 
                    boxes.size[0], 
                    boxes.size[1], 
                    boxes.size[2], 
                    boxes.weight);   
        }
    }else{
       printf("Error!\n");
    }
    printf("\n");
    fclose(fpointer); 

}

void printBox(struct Box b);       // print one box- already implemented for you
// returns the record number of a box with specified ID, if found
int searchBox( FILE *fp, int id2Find){
    int found = -1;
    int i = 0;
    struct Box boxes;

    if(fp != NULL){
        while(
               fscanf(fp, "%d %lf %lf %lf %lf", 
                        &boxes.id, 
                        &boxes.size[0], 
                        &boxes.size[1], 
                        &boxes.size[2], 
                        &boxes.weight) != EOF){
        
           if(boxes.id == id2Find){
              found = i;
           }
              i++;
           
        }
    }
    return found;
}

void displayBox(const char filename[], int id2Find){     // display a box, given ID
    FILE *fp = NULL;
    struct Box boxes;
    int found,i = 0;
    fp = fopen(filename, "r");

    if(fp == NULL){
        printf("Error!\n");
    }else{
        found = searchBox(fp,id2Find);
    
         if(found != -1){
            rewind(fp);
            do{
                 fscanf(fp, "%d %lf %lf %lf %lf",
                            &boxes.id, 
                            &boxes.size[0], 
                            &boxes.size[1], 
                            &boxes.size[2], 
                            &boxes.weight);
               i++;
            }while(i <= found);
           
            printf("Found box %d as record #%d:\n", boxes.id, i);
            printBox(boxes);
        }else{
            printf("This box is not recorded.\n\n");
        }
        fclose(fp);
    }
}

int addBox(const char filename[], const struct Box * b2Add){  // add a box to file
    FILE *fp = NULL;
    int found;
    fp = fopen(filename, "a+");

    if(fp == NULL){
        printf("Error!\n");
    }else{
        found = searchBox(fp, b2Add->id);

        if(found != NOT_FOUND){ //found
            printf("A box with this ID is already recorded.\n");
            printf("0 box added to storage!\n\n");
        }else{ //not found
            //write box to file

            fprintf(fp, "%2d %6.2lf %5.2lf %6.2lf %6.2lf\n", 
                        b2Add->id,
                        b2Add->size[0],  
                        b2Add->size[1],  
                        b2Add->size[2],
                        b2Add->weight  
                   );
            printf("1 box added to storage!\n\n");
        }

        fclose(fp);
    }

    return 0;
}

int numberBoxes(const char filename[]){      // find the number of boxes in a file
    FILE *fp = NULL;
    int count, rec;
    fp = fopen(filename, "r");

    if(fp == NULL){
        printf("Error\n");
    }else{
        rec = -1;
        do{
            count = fgetc(fp);
            if(count != EOF){
                if((char)count == '\n'){
                    rec++;
                }
            }
        }while(feof(fp) == 0);
    fclose(fp); 
    }
    return rec;
}

int getRandomInt(int lower, int higher){  // get a random number
    int num;
    
    srand(time(NULL)); // here is the seed for the random number
    num = lower + rand() % (higher - lower +1);

    return num; 
}

void displayBoxN(char filename[], int n){ // display a box given its record number
    FILE *fp = NULL;
    int record,i = 0;
    struct Box boxes;
    fp = fopen(filename, "r");

    if(fp == NULL){
        printf("Error!\n");
    }else{
        record = getRandomInt(1,n);
     if(record != -1){
            rewind(fp);
            do{
                 fscanf(fp, "%d %lf %lf %lf %lf",
                            &boxes.id, 
                            &boxes.size[0], 
                            &boxes.size[1], 
                            &boxes.size[2], 
                            &boxes.weight);
               i++;
            }while(i <= record);

        printBox(boxes);
    }
    fclose(fp);
    }
}

void printBox(struct Box b){
   printf("\nID:     %6d\n"
      "Length: %6.2lf\n"
      "Width:  %6.2lf\n"
      "Height: %6.2lf\n"
      "Weight: %6.2lf\n\n", b.id, b.size[0], b.size[1], b.size[2], b.weight);
}

int menu(void){
   int choice = -1;

   printf("1- List all boxes\n");
   printf("2- Find a box\n");
   printf("3- Add a box\n");
   printf("4- Randomly pick a lucky box!\n");
   printf("0- Exit program\n");

   printf("Select an option: ");
   do{
      scanf("%d", &choice);
      if (choice < 0 || choice > 4)
         printf("Please enter a number between 0 and 4: ");
   } while (choice < 0 || choice > 4);
   return choice;
}


int main(void){

   int choice;
   int id2Find;
   int r; // , boxID, r;
   char filename[] = "storage.txt";
   struct Box b;


   printf("Welcome to My Storage Room\n");
   printf("==========================\n");
   do {
      // get user's choice
      choice = menu();
      r = numberBoxes(filename);

      switch (choice){
      case 1:
         // IN_LAB: list items
         listBoxes(filename);
         break;

      case 2:
         // IN_LAB: find a box given its ID
         // ask for ID
         printf("Enter box ID: ");
         scanf("%d", &id2Find);
         displayBox(filename,id2Find);


         // call displayBox



         break;

      case 3:
         // AT_HOME: add a box
         // get user input for box's ID, size and weight
         printf("Please enter the box's ID, length, width, height and weight: ");
         scanf("%d %lf %lf %lf %lf", 
                 &b.id,
                 &b.size[0],
                 &b.size[1],
                 &b.size[2],
                 &b.weight
              );

         // call addBox, print message to show number of boxes added
         addBox(filename, &b);




         break;

      case 4:
         // AT_HOME: randomly pick a lucky box
         r = numberBoxes(filename);
         getRandomInt(1,r);
         printf("\nLucky box picked:\n");
         displayBoxN(filename,r);
         // choose a random number between 1 and the number of boxes in storage


         // display the lucky box!



         break;


      };

   } while (choice > 0);

   return 0;
}

/*
Welcome to My Storage Room
==========================
1- List all boxes
2- Find a box
3- Add a box
4- Randomly pick a lucky box!
0- Exit program
Select an option: 1
List of boxes
=============

ID Length Width Height Weight
-----------------------------
10  50.34 61.00  30.00  50.50
11  25.60 12.34   9.23  12.89
55  10.00 20.00  30.00  40.50
56  30.00 40.00  50.00  60.00
57   5.20  6.30   7.40   8.50

1- List all boxes
2- Find a box
3- Add a box
4- Randomly pick a lucky box!
0- Exit program
Select an option: 2
Enter box ID: 55
Found box 55 as record #3:

ID:         55
Length:  10.00
Width:   20.00
Height:  30.00
Weight:  40.50

1- List all boxes
2- Find a box
3- Add a box
4- Randomly pick a lucky box!
0- Exit program
Select an option: 2
Enter box ID: 15
This box is not recorded.

1- List all boxes
2- Find a box
3- Add a box
4- Randomly pick a lucky box!
0- Exit program
Select an option: 0
*/
