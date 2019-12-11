
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//struct for node
struct node {
   int data;
   int key;
	
   struct node *next;
   struct node *prev;
};

//this link always point to first Link
struct node *head = NULL;

//this link always point to last Link 
struct node *last = NULL;

struct node *current = NULL;


//prototypes of all the functions
bool isEmpty(void);
void displayForward(void);
void displayBackward(void);
void insertFirst(int key, int data);
void insertLast(int key, int data);
bool insertAfter(int key, int newKey, int data);

int main(int argc, char** argv)
{
	
	//declaring the variables
	int key;
	int data;
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	struct node* curr = (struct node*)malloc(sizeof(struct node));
	
	//prompt user to enter the values
	printf("Enter the values of key and data. Enter 0 for key to stop");
	printf("\nKey: ");
	scanf("%d", &key);
	
	while(key!=0){
	
		printf("\nData: ");
		scanf("%d", &data);
		
		temp->data = data;
		temp->key = key;
		
		if(isEmpty()){
			insertFirst(temp->key, temp->data);				
		}
		
		else{
			curr = head;
			
			if(temp->key == curr->key){
				insertAfter(curr->key, temp->key, temp->data);
			}
			
			else if(temp->key < curr->key){
				insertFirst(temp->key, temp->data);
			}
			else if(temp->key > curr->key){
				while(curr!= NULL && (temp->key > curr->key)){
					curr = curr->next;
				}
				if(curr == NULL){
					insertLast(temp->key, temp->data);
				}
				else{
					curr = curr->prev;
					insertAfter(curr->key, temp->key, temp->data);
				}
								
			}
				
		}
				
		printf("\nKey: ");
		scanf("%d", &key);
		
	}

//display the list forward and then backward
	displayForward();
	displayBackward();
	
}

//......................................................functions...........................................

//is list empty
bool isEmpty() {
   return head == NULL;
}

//display the list in from first to last
void displayForward() {

   //start from the beginning
   struct node *ptr = head;
	
   //navigate till the end of the list
   printf("\n[ ");
	
   while(ptr != NULL) {        
      printf("(%d,%d) ",ptr->key,ptr->data);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

//display the list from last to first
void displayBackward() {

   //start from the last
   struct node *ptr = last;
	
   //navigate till the start of the list
   printf("\n[ ");
	
   while(ptr != NULL) {    
	
      //print data
      printf("(%d,%d) ",ptr->key,ptr->data);
		
      //move to next item
      ptr = ptr ->prev;
      
   }
	
}

//insert link at the first location
void insertFirst(int key, int data) {

   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
   link->key = key;
   link->data = data;
	
   if(isEmpty()) {
      //make it the last link
      last = link;
   } else {
      //update first prev link
      head->prev = link;
   }

   //point it to old first link
   link->next = head;
	
   //point first to new first link
   head = link;
}

//insert link at the last location
void insertLast(int key, int data) {

   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
   link->key = key;
   link->data = data;
	
   if(isEmpty()) {
      //make it the last link
      last = link;
   } else {
      //make link a new last link
      last->next = link;     
      
      //mark old last node as prev of new link
      link->prev = last;
   }

   //point last to new last node
   last = link;
   last->next = NULL;
}


//insert after a certain key
bool insertAfter(int key, int newKey, int data) {
   //start from the first link
   struct node *current = head; 
	
   //if list is empty
   if(head == NULL) {
      return false;
   }

   //navigate through list
   while(current->key != key) {
	
      //if it is last node
      if(current->next == NULL) {
         return false;
      } else {           
         //move to next link
         current = current->next;
      }
   }
	
   //create a link
   struct node *newLink = (struct node*) malloc(sizeof(struct node));
   newLink->key = newKey;
   newLink->data = data;

   if(current == last) {
      newLink->next = NULL; 
      last = newLink; 
   } else {
      newLink->next = current->next;         
      current->next->prev = newLink;
   }
	
   newLink->prev = current; 
   current->next = newLink; 
   return true; 
}


