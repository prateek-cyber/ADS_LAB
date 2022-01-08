#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int key;
    Node *left;
    Node *right;
    int height; 
};

int max(int a,int b);

int height(Node *N){
    if(N==NULL)
    return 0;
    return N->height;
}

int max(int a,int b){
    return(a>b)? a:b;
}

Node* newNode(int key){
    Node *node=new Node();
    node->key= key;
    node->left= NULL;
    node->right=NULL;
    node->height=1;
    return (node);
}

Node* rightRotate(Node* y){
    Node *x = y->left;
    Node *T2 = x->right;

    //after rotating right
    x->right = y;
    y->left = T2;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1; 
    return x;
}

Node* leftRotate(Node* x){
    Node *y = x->right;
    Node *T2 = y->left;

    //after rotating left
    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node *N){
    if(N==NULL)
    return 0;

    return height(N->left) - height(N->right);
}

Node* four_cases(Node* node, int balance, int key){
    if(balance>1 && key<node->left->key)
    return rightRotate(node);

    if(balance<-1 && key>node->right->key)
    return leftRotate(node);

    if(balance>1 && key>node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if(balance>-1 && key<node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* insert(Node* node, int key){
    if(node==NULL)
    return (newNode(key));

    if(key < node->key)
        node->left = insert (node->left,key);

        else if (key > node->key)
            node->right = insert (node->right,key);
        
        else

        return node;

    node->height = max(height(node->right), height(node->left)) + 1;

    int balance = getBalance(node);

    if(balance>1 || balance<-1)
    return four_cases(node,balance,key);
    return node;
}

Node* minValue(Node* node){
    Node *curr = node;
    while(curr->left!=NULL)
    curr= curr->left;
    return curr;
}

Node* deleteNode(Node* node,int key){
 if (node==NULL)
 return node;

 if(key<node->key){
     node->left = deleteNode(node->left,key);
 }

 else if(key>node->key){
     node->right = deleteNode(node->right,key);
 }
 else{
     if(node->left==NULL || node->right==NULL){
         Node* temp =node->left ? node->left : node->right;
         if(temp==NULL){
             temp=node;
             node=NULL;
         }
         else{
             *node=*temp;
         }
         free(temp);
     }
     else{
         Node* temp= minValue(node->right);
         node->key = temp->key;
         node->right = deleteNode(node->right, temp->key);
     }
 }
 if(node==NULL)
 return node;
     
     node->height = 1 + max(height(node->left),height(node->right));
     int balance = getBalance(node);

     if(balance>1 || balance<-1){
         return four_cases(node,balance,key);
     }
     return node;
}

void display(Node* node){
    if(node!=NULL){
        cout<<node->key<< "\t";
        display(node->left);
        display(node->right);
    }
}

int main(){
    Node* root = NULL;
 int n,ch=0;
 while(ch!=-1){
 cout<<"1.insert\t2.delete\t3.display"<<endl;
 cin>>ch;
 if(ch==1){
     cout<<"enter the nodes to be inserted:"<<endl;
     cin>>n;
     root=insert(root,n);
 }
 else if(ch==2){
     cout<<"enter the node to be deleted:"<<endl;
     cin>>n;
     root=deleteNode(root,n);
 }
 else if(ch==3){
    cout<<"Balanced AVL Tree:"<<endl;
      display(root);
      cout<<endl;
 }
}
return 0;
}
