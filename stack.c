#include<stdio.h>
#include<stdlib.h>

struct point{
    int x;
    int y;
    struct point *next;
};

struct point* appendNodes(int,int);
struct point* createNodes(struct point *end, struct point *newpt);
struct point* pop(struct point *start);
void removeStack(struct point *start, struct point *node);
void printList(struct point *ptr);

int count=0;

int main(void){
    int j;
    while(1){
    printf("-----------------------------------\n");
    printf("To Continue: Enter 1, To Terminate: Enter 2\n");
    scanf("%d",&j);
    if(j==1){
            int a,x,y;
            struct point *start, *end, *newpt;
            printf("Push: Enter 1\nPop: Enter 2\n");
            scanf("%d",&a);
            if(a==1){
	        printf("Point %d:\n",(count+1)); 
       	        printf("Enter x-coordinate: ");
	        scanf("%d",&x);
                printf("Enter y-coordinate: ");
	        scanf("%d",&y);
	        newpt=appendNodes(x,y);
	        if(count==0){
	            start=end=newpt;
	        }else{
	            end=createNodes(end, newpt);
	        }
            count++;
	        
            }
            if(a==2){
                struct point *node;
                node=pop(start);
                removeStack(start, node);
		
            }
            printf("\n");
            printf("Linked list: \n");
            printList(start);
            printf("\n");
            printf("-----------------------------------\n");
        }else{
            printf("Program Terminated\n");
            printf("-----------------------------------\n");
            break;
        }
    }
}

struct point* appendNodes(int x, int y){
    struct point *ptr= (struct point *)malloc(sizeof(struct point *));
    ptr->x=x;
    ptr->y=y;
    return ptr;
}

struct point* createNodes(struct point *end, struct point *newpt){
    
    end->next=newpt;
    return(end->next);
}

struct point* pop(struct point *start){
    while(start->next != NULL){
        start=start->next;
    }
    return start;
}

void removeStack(struct point *start, struct point *node){
    if(start->next == node){
        start->next = NULL;
    }else{
        start=start->next;
        removeStack(start, node);
    }
    count--;
}

void printList(struct point *ptr){
    while(ptr!=NULL){
        printf("(%d, %d)\n", ptr->x, ptr->y);
        ptr=ptr->next;
    }
}




