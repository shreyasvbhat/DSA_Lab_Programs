//Program to do operations on student details (Menu driven program)
#include<stdio.h>
#include<stdlib.h>

struct Student
{
    char name[25];
    char regNo[25];
    int marks[3];
    float avg_marks;
};

void read(struct Student *students, int n){
    int i,j;
    for(i=0;i<n;i++){
        printf("Enter the students name:\n");
        scanf("%s", (students+i)->name);
        printf("Enter the students register number:\n");
        scanf("%s",(students+i)->regNo);
        printf("Enter the three subjects marks:\n");
        for(j=0;j<3;j++){
            scanf("%d", &(students+i)->marks[j]);
        }
    }
}

void display(struct Student *students, int n){
    int i,j;
    printf("Name\tRegister_Number\t\tMark1\tMark2\tMark3\tAverageMarks\n");
    for(i=0;i<n;i++){
        printf("%s\t", (students+i)->name);
        printf("%s\t", (students+i)->regNo);
        printf("\t");
        for(j=0;j<3;j++){
         printf("%d\t", (students+i)->marks[j]);
        }
        printf("%f\t",((students + i)->avg_marks));
        printf("\n");
    }
}

void calculate(struct Student *students, int n){
    int i;
    for(i=0;i<n;i++){
        int min = (students+i)->marks[0];
        min = (students+i)->marks[1]<min ? (students+i)->marks[1] : min;
        min = (students+i)->marks[2]<min ? (students+i)->marks[2] : min;
        
        (students+i)->avg_marks = (( (students+i)->marks[1] + (students+i)->marks[2] + (students+i)->marks[0] - min )/2);
    }
}

int main(){
    int n;
    printf("Enter the number of students:\n");
    scanf("%d",&n);
    struct Student *students = (struct Student *)malloc(n*sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed. Exiting program.\n");
        return 1;
    }
    int choice;
    do{
        printf("Menu\n");
        printf("1. Read student information\n");
        printf("2. Display student information\n");
        printf("3. Calculate average of best two test marks\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            read(students,n);
            break;
        case 2:
            display(students,n);
            break;
        case 3:
            calculate(students,n);
            break;
        case 4:
            printf("Exiting Program\n");
            break;
        default:
            printf("Enter a valid choice:\n");
            break;
        }

    }while(choice!=4);

    free(students);
    return 0;
}
