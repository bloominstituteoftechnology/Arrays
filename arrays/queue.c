#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>

typedef struct listitem {
    struct listitem *next; //pointer to next item
    struct listitem *prev;  //pointer to previous item
    int data;                //some data
} LISTITEM;

//this is the queue header
typedef struct {
    struct listitem *first;   //pointer to next item
    struct listitem *last;   // pointer to previous

} LISTHDR;                      // the queue

void enqueue(LISTHDR *queue, LISTITEM *tem) {
    LISTITEM *temp;

    temp = queue->last;         //get the last item in the queue and keep hold of it
    queue->last = item;         //put the item in the queue at the end
    item->prev = temp;          //link back to old 'last ' item
    item->next = (LISTITEM*)queue; //set the forward link of the new item
    temp->next = item;              // set the forward link of the old 'last' item to the new one

}
//this removes an item from the front of a queue - returns the item or NULL if there are no items

LISTITEM* dequeue(LISTHDR *queue){
    LISTITEM *temp;

    temp = queue->first;             //get the first item
    if (temp == (LISTITEM*)queue){     //if the head of the queue header points to itself
        temp=NULL;                      //then the queue is empty
    }
    else {
        queue->first = temp->next;      // and set the queue header to point to the second item
        queue->first->prev = (LISTITEM*)queue;
    }
    return temp;
}

//returns the number of items in a queue

int queue_length(LISTHDR* queue){
    LISTITEM *temp;
    int length;
    temp = queue->first;   // get the first item
    length = 0;            //initialize the length
    do{
        //check for an empty queue 
        if (temp ==(LISTITEM*)queue){
            temp=NULL;   //this will break out of the do ...while loop
            break;
        }
        temp = temp->next;  //get the next item in the queue
        length = length + 1;
    } while (temp  !=NULL);
    return length;

}

int main(){
    LISTITEM *temp;

    //first, make an empty queue
    //...which is a queue where the header points to itself and there are no items in it
    head.first=(LISTITEM*)&head;
    head.last= (LISTITEM*)&head;
}

    }
}













printf("the length of the queu is %d\n", queue_length(&head));
//remove the entered index o

printf("enter the index of the queue entry...");
requested_index = atoi(gets(input));