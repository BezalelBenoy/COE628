#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Bezalel Benoy
 */
void PQ_insert(int priority, char * data) {   
    Node_t*hold = (Node_t*)malloc(sizeof(struct node));
    
    hold -> priority = priority;
    hold->data = data;
    hold->next =NULL;
    
    if(head==NULL){
        head = hold;
    }
    else{
        Node_t*counter = (Node_t*)malloc(sizeof(struct node));
        counter = head;
        
        while(counter->next !=NULL){
            counter = counter->next;
        }
        counter->next=hold;
        }
    }


Node_ptr_t PQ_delete() {
    int highestPriority = 0;
    
    Node_t*counter =(Node_t*)malloc(sizeof(struct node));
    
    counter = head;
    
    do{
        if(counter->priority>highestPriority){
            highestPriority = counter->priority;
        }
         counter= counter->next;
    }
    while(counter!=NULL);
    counter=head;
    do{
        if(counter->priority==highestPriority){
            if(counter==head){
                head=counter->next;
                return counter;
            }
        }
        else
            if(counter->next->priority==highestPriority){
                Node_t*hold= (Node_t*)malloc(sizeof(struct node));
                hold=counter->next;
                counter->next = counter->next->next;
                return hold;
            }
            else{
                counter= counter->next;
            }
    }
    while(counter!=NULL);
   

    
 //   
    return NULL;
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}
void test(){
    printf("\n%d", PQ_get_size());
}


