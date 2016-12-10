/* marks.c */
#include <stdio.h>

int main() {
   int currentVal = 0;

   int numOfMarks,
       total = 0,
       userMark;

   float average;

   printf("       ---=== IPC mark Analyser ===---\n");
   printf("Please enter the number of marks(between 3 and 40): ");
   scanf("%d", &numOfMarks);
   
   if (numOfMarks < 3 || numOfMarks > 40) {
   //If less than or greater than 3 or 40 inclusive, return error message
   do 
   {
     printf("Invalid number, enter a number between 3 and 40 inclusive: ");
     scanf("%d", &numOfMarks);	
   } while (numOfMarks < 3 || numOfMarks > 40);
   }


   do
{
	currentVal++;
	printf("%d>", currentVal);
	scanf("%d", &userMark);
	total += userMark;	
} while (currentVal < numOfMarks);

   average = total /(float) numOfMarks;

   printf("The average of all marks in this group is %.1f.\n", average);
   printf("Program Ended.\n");

   return 0;
}
