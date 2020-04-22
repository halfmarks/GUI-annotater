#include "linkedlist.h"
#include <iostream>
using namespace std;


/* List releated */
/* Initialize all of them to NULL */
linkedList::linkedList(){
    head = NULL;
    curr = NULL;
    temp = NULL;
}
/* Define addNode function */
void linkedList::addNode(int addData){
    nodePtr n = new node;   /* Node pointer n point to a newly created node*/
    n->next = NULL;         /* Finding the node n is poiting to and setting its pointer to NULL */
    n->data = addData;

    if(head != NULL){                   /* This part requires at least 1 element alreay in the node */
        curr = head;
        while(curr->next != NULL){      /* While the current node is not poitning to NULL, point to the next node */
            curr = curr->next;          /* If current is NULL, exit out of while loop */
        }
        curr->next = n;                 /* After pointing to the last node, process restarts*/
    }
    else
    {
        head = n;
    }
}

/* Define deleteNode function */
void linkedList::deleteNode(int delData){
    nodePtr delPtr = NULL;
    temp = head;
    curr = head;
    while (curr != NULL && curr->data != delData)    /* if we went throught the list and did not find the data to be deleted, we need to exit the loop */
    {                                                /* also we need to make sure the data is not the data we need to delete, otherwise exit the loop */
        temp = curr;                                   /* temp is 1 step behinde curr*/
        curr = curr->next;                            /* curr one step ahead of temp, since it points to next node in list */
        /* when the while loop exit one of the 2 conditions failed, either no data found or data found to be deleted */
    }
    if(curr == NULL)                                 /* If it is equal to NULL we did not find the data to be deleted */
    {
        cout << delData << "Value was not in the list\n";    /* Display if the data was not found to be deleted */
        delete delPtr;                               /* delPtr needs to be deleted, otherwise it will folat in memory */
    }
    else                                             /* Node was found with matching data */
    {
        delPtr = curr;                               /* delPtr becamoes equal to the current node */
        curr = curr->next;                           /* advance current to the next node, it does not have to get involed with delete */
        temp->next = curr;                           /* since temp is one step behind compared to current, we can patch the list together again by patching temp and jumping over node to be deleted and adding patching it to actual curr*/
        delete delPtr;                               /* delete whatever is delPtr is pointing to */
        cout <<" The deleted data was "<< delData<< " and got deleted\n";
    }
}

/* print out the values placed in the list for testing, as long as it is not equal to NULL */
void linkedList::printList(){
    curr = head;
    while(curr != NULL){
        cout<< curr->data << endl;
        curr = curr->next;
    }
}


