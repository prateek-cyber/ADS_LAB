#include<bits/stdc++.h>
#include<inttypes.h>

using namespace std;

class Node{
    public:
    int data;
    Node  *next;
};

Node* XOR(Node* a, Node* b){
    return (Node* ) ((uintptr_t)(a)^(uintptr_t)(b));
}

Node* insert_front(Node** head_ref,int data){
    Node* new_node= new Node();
    new_node->data=data;
    new_node->next=*head_ref;
    if(*head_ref!=NULL){
        (*head_ref)->next=XOR(new_node,(*head_ref)->next);    
    }
    *head_ref=new_node;
    return *head_ref;

}

Node* insert_end (Node** head,int data){
    Node* new_node=new Node();
    new_node->data=data;
    if(!(*head)){
        *head=new_node;
        new_node->next=NULL;
        return *head;
    }
    if(!((*head)->next)){
        (*head)->next=XOR(new_node,(*head)->next);
        new_node->next=*head;
        return *head;
    }
    Node* prev=*head;
    Node* nextp=(*head)->next;
    while(prev!=nextp->next){
        Node* q=XOR(nextp->next,prev);
        prev=nextp;
        nextp=q;
    }
    nextp->next=XOR(nextp->next,new_node);
    new_node->next= nextp;
    return *head;
}
void printList(Node* head) {
    Node* curr = head;
    Node* prev = NULL;
    Node* nextp;
    if (head == NULL) {
        cout << "Empty XOR Linked List" << endl;
        return;
    }
    cout << "Following are the nodes of XOR Linked List: " << endl;

    while (curr != NULL) {
        cout << curr->data << " ";
        nextp = XOR(prev, curr->next);
        prev = curr;
        curr = nextp;
    }
    cout << endl;
}
Node* delete_front(Node** head){
    if(*head==NULL){
        cout<<"List is empty"<<endl;
    }
    if((*head)->next==NULL){
        return NULL;
    }
    Node* p= *head;
    *head=(*head)->next;
    (*head)->next=XOR((*head)->next,p);
    cout<<"Deleted element is "<<(p->data)<<endl;
    return *head;
}
int main(){
    Node* head=NULL;
    cout<<"1. Insert at beginning\n2. Insert at end\n3. Display\n4. Delete from front\n5. Exit " << endl;
    int choice;
    while(true){
        cout<<"Enter your choice"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                int el;
                cout<<"Enter the element"<<endl;
                cin>>el;
                head=insert_front(&head,el);
                break;
            case 2:
                int ele;
                cout<<"Enter the element"<<endl;
                cin>>ele;
                head=insert_end(&head,ele);
                break;
            case 3:
                printList(head);
                break;
            case 4:
                head=delete_front(&head);
                break;
            case 5:
                return 0;
        }

    }
    return 0;
    //head=insert_front(&head,9);
    //head=insert_front(&head,10);
    //head=insert_front(&head,11);
    //head=insert_end(&head,12);
    //head=delete_front(&head);
    //printList(head);

}