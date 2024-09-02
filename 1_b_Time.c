//Program to perform operations on time
#include<stdio.h>
#include<stdlib.h>

struct Time{
    int hours;
    int min;
    int sec;
};

void read(struct Time *t){
    printf("Enter the time in hours:minutes:seconds format:\n");
    scanf("%d%d%d", &(t->hours), &(t->min), &(t->sec));
}

void display(struct Time *t){
    printf("Time in hours:minutes:seconds format: ");
    printf("%02d:%02d:%02d", t->hours, t->min, t->sec);
    printf("\n");
}

void update(struct Time *t){
    t->sec = t->sec+1;
    if(t->sec >= 60){
        t->sec = 0;
        t->min = t->min +1;
    }
    if(t->min>=60){
        t->min = 0;
        t->hours = t->hours+1;
    }
    if(t->hours>=24){
        t->sec = 0;
        t->min = 0;
        t->hours = 0;
    }
}

void add(struct Time *t1, struct Time *t2, struct Time *rest){
    rest->sec = t1->sec + t2->sec;
    rest->min = t1->min + t2->min;    
    rest->hours = t1->hours + t2->hours;
     if(rest->sec >= 60){
        rest->min = rest->min +(rest->sec/60);
        rest->sec = (rest->sec%60);
        
    }
    if(rest->min>=60){
        rest->hours = rest->hours+ (rest->min/60);
        rest->min = (rest->min%60);
    }
    if(rest->hours>=24){
        rest->hours = (rest->hours%24);
    }
    
}

int main(){
    
    struct Time *t1 = (struct Time *)malloc(sizeof( struct Time));
    struct Time *t2 = (struct Time *)malloc(sizeof( struct Time));
    struct Time *rest = (struct Time *)malloc(sizeof( struct Time));
    if (t1 == NULL || t2==NULL || rest==NULL) {
        printf("Memory allocation failed. Exiting program.\n");
        return 1;
    }
    int choice;
    do{
        printf("Menu\n");
        printf("1. Read time\n");
        printf("2. Display time\n");
        printf("3. Update time\n");
        printf("4. Add time\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: read(t1);
                    break;
            case 2: display(t1);
                    break;
            case 3: update(t1);
                    display(t1);
                    break;
            case 4: read(t1);
                    read(t2);
                    add(t1,t2,rest);
                    display(rest);
                    break;
            case 5: printf("Exiting Program\n");
                    break;
            default: printf("Enter a valid choice:\n");
                    break;
        }
    }while(choice!=5);

    free(t1);
    free(t2);
    free(rest);
    return 0;
}