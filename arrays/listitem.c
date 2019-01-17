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

int main() {
    LISTITEM *temp, head;

    head.next = (LISTITEM*)&head;
    head.prev = (LISTITEM*)&head;
    head.data = -1;
    
    

    // populate the list

    for (int i =0; i<3; i++) {
        temp = malloc(sizeof(LISTITEM));
        temp->data = i;
        temp->next = head.next;
        head.next = temp;
        temp->prev =&head;
        temp->next->prev = temp;
        
    }

    //temp = head;
    while (temp !=NULL) {
        printf("list item: current is %p; next is %p; data is %d\n", temp, temp->next, temp->data);
        temp = temp->next;
    }
    return 0;
}