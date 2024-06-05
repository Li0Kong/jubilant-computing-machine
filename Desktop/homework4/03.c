#include<stdio.h>
#include<stdlib.h>
typedef struct list_item{
    int data;
    struct list_item*next;
}list_item;

void erase_list(list_item*head){
    list_item*current = head;
    list_item*next;
    while (current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}

int main(){
    list_item*head = malloc(sizeof(list_item));
    head->data = 1;
    
    list_item*second = malloc(sizeof(list_item));
    second->data = 2;
    
    list_item*third = malloc(sizeof(list_item));
    third->data = 3;
    
    head->next = second;
    second->next = third;
    third->next = NULL;
    
    erase_list(head);
    
    return 0;
}
