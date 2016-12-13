#include <stdio.h>
#define MAX 100

struct studentMarks {
   int   id;
   float marks;
};

void welcome(void){
    printf("####### Marks Analyzer V3.0 #######\n");
};

int get_data( struct studentMarks * ptr ){
    int size = 0;
    int id = 0;
    float marks = 0;

    do{
        printf("Enter student id and marks (e.g. 12345 89.5): ");
        scanf("%d %f", &id,&marks);

        if((size < MAX) && (id != -1) && (marks != -1)){
            ptr[size].id = id;
            ptr[size].marks = marks;
            size++;
        }
    }while((size < MAX) && (id != -1) && (marks != -1));
    
    return size;
};

void show( struct studentMarks list[], int num ){
    int i;

    for(i=0; i<num; i++){
        printf("%d. %d, %.2f\n", i+1, list[i].id, list[i].marks);
    }
};

float analyze( struct studentMarks list[], int num, float* ptr_highest, float* ptr_lowest){
    int i;
    float total = 0;
    float avg = 0;

    * ptr_highest = list[0].marks;
    * ptr_lowest  = list[0].marks;

    for(i=0; i<num; i++){
        total = total + list[i].marks;

        if(list[i].marks > * ptr_highest){
            * ptr_highest = list[i].marks;
        }else if(list[i].marks < * ptr_lowest){
            * ptr_lowest = list[i].marks;
        }
    }
    avg = total / num;
    return avg;
};

void print_summary( float avg, float high, float low){

    printf("### result of marks analysis ###\n");
    printf("average: %.2f, ",avg);
    printf("highest marks: %.2f, ",high);
    printf("lowest marks: %.2f\n",low);
};

int main(void){
    // declarations of a constant, an array and variables
    struct studentMarks stdMark[MAX]; 
    int size;
    float avg = 0, high = 0, low = 0;

    // call a function to display a welcome message
    welcome();

   // 1. use a do-while loop to get student ids and student marks
    size = get_data(stdMark);

   // 2. print out all the student marks
    show(stdMark,size);

   // 3. data analysis
    //analyze(stdMark,size,&high,&low);
    avg = analyze(stdMark,size,&high,&low);

   // 4. print the result of data anaalysis
    print_summary(avg, high, low); 
   
    return 0;
}
