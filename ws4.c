#include <stdio.h>
 
int main(void) {
    int students = 0;
    long studentNumbers[40];
    int marks[40];
    int i = 0;
 
    float total;
 
    printf("       ---=== IPC mark Analyser V2.0 ===---\n");
    printf("Please enter the number of students(between 3 and 40): ");
    scanf("%d", &students);
 
    if (students < 3 || students > 40) {
    do
    {
      printf("Invalid number, enter a number between 3 and 40 inclusive: ");
      scanf("%d", &students);  
    } while (students < 3 || students > 40);
    } 
    
    printf("Row   Std No  Mrk\n");
    printf("--- --------- ---\n");
    
    for (i = 0; i < students; i++) {
        printf("    _________ ___\r");
        printf("%3d ", i+1);
        scanf("%9ld %3d", &studentNumbers[i], &marks[i]);
        total = total + marks[i];
    } 

    printf("=================\n");
    printf("Marks Entered, printing results:\n");
    printf("Row   Std No  Mrk\n");
    printf("--- --------- ---\n");
    
    for (i = 0; i < students; i++) {
        printf("%03d %09ld %3d\n", i+1, studentNumbers[i], marks[i]);
    }
    
    printf("=================\n");
    printf("The average of all marks in this group is %.1f.\n", total / students);
    printf("Program Ended.\n");
    return 0;
}  
