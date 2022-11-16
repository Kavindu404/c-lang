#include<stdio.h>

struct point{

    int x; 
    int y;
    struct point *next;

};
void printList(struct point *ptr);
int main(void){

    struct point pt1={1,2,NULL};
    struct point pt2={3,4,NULL};
    struct point pt3={5,6,NULL};

    struct point *start;

    start=&pt1;
    pt1.next=&pt2;
    pt2.next=&pt3;

    printList(start);


    return 0;
}
void printList(struct point *ptr){

    while(ptr!=NULL){

        printf("(%d, %d)\n", ptr->x, ptr->y);
        ptr=ptr->next;
    }

}
