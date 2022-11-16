#include<stdio.h>

struct point{

    int x; 
    int y;
    struct point *next;

};
void printList(struct point *ptr);
struct point* append(struct point *p1, struct point *p2);
int main(void){

    struct point pt1={1,2,NULL};
    struct point pt2={3,4,NULL};
    struct point pt3={5,6,NULL};

    struct point *start, *end;

    start=end=&pt1;
    end=append(end, &pt2);
    end=append(end, &pt3);

    printList(start);


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
