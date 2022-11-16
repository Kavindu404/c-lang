#include<stdio.h>
#include<stdlib.h>

struct point{

    int x; 
    int y;
    struct point *next;

};
void printList(struct point *ptr);
struct point* append(struct point *p1, struct point *p2);
struct point* createPoints(int x, int y);
void freePoints(struct point *start);

int main(void){

    struct point *start, *end, *newpt;
    int num, i, x, y;

    printf("How many points will there be? ");
    scanf("%d", &num);

    for(i=0;i<num;i++){

        printf("Point %d:\n", i+1);
        printf("x- coordinate: ");
        scanf("%d",&x);
        printf("y- coordinate: ");
        scanf("%d",&y);
        newpt=createPoints(x,y);
        if(i==0){
            start=end=newpt;
        }else{
            end=append(end, newpt);
        }
        printf("\n");
    }

    printList(start);
    freePoints(start);


    return 0;
}

struct point* append(struct point *p1, struct point *p2){

    p1->next=p2;
    
    return (p1->next);
}

void printList(struct point *ptr){

    while(ptr!=NULL){

        printf("(%d, %d)\n", ptr->x, ptr->y);
        ptr=ptr->next;
    }

}

struct point* createPoints(int x, int y){

    struct point *ptr;
    
    ptr=(struct point *)malloc(sizeof(struct point));

    ptr->x =x;
    ptr->y =y;
    ptr->next =NULL;
    return(ptr);
}
void freePoints(struct point *start){

    struct point *ptr= start;
    ptr=ptr->next;
    freePoints(ptr);

}





