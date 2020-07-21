#include <stdio.h>
#include <stdlib.h>
#define Max 10  //Max number of parking spots in each category

int parking[7][Max];  
// 2-D array representing parking lot
// This 2-d array is interpreted as row 1,2,3 represent wing A,B,C compact parking spots
// And row 4,5,6 represent wing A,B,C Large Parking spots 
//This helps in easier calculation because the wing Id is taken from user as 1 for A , 2 for B and 3 for C
//Thus helps in avoiding maintainence of different arrays and multiple if-else blocks 
void initialise_parking()
{
    for(int i=0;i<7;i++)
    {
        for(int j=0;j<Max;j++)
        {
            parking[i][j]=0;
        }
    }
}

//The values stored in parking lot have specific meaning as follows:
// 0 means the spot is free 
// 1 means the spot has been mapped to a certain vehicle
// Any other value reprents that vehicle has been parked with the value as vehicle number: 


void display_parking()
{

        printf("\nCompact Spots status for Wing A(1) : ");

        for(int j=0;j<Max;j++)
        {
            //parking[i][j]=0;
            
            printf("%d ",parking[1][j]);
        }

        printf("\n");

        printf("\nCompact Spots status for Wing B(2) : ");

        for(int j=0;j<Max;j++)
        {
            //parking[i][j]=0;
            
            printf("%d ",parking[2][j]);
        }

        printf("\n");

        printf("\nCompact Spots status for Wing C(3) : ");

        for(int j=0;j<Max;j++)
        {
            //parking[i][j]=0;
            
            printf("%d ",parking[3][j]);
        }

        printf("\n");

        printf("\nLarge Spots status for Wing A(1) : ");

        for(int j=0;j<Max;j++)
        {
            //parking[i][j]=0;
            
            printf("%d ",parking[4][j]);
        }

        printf("\n");


        printf("\nLarge Spots status for Wing B(2) : ");

        for(int j=0;j<Max;j++)
        {
            //parking[i][j]=0;
            
            printf("%d ",parking[5][j]);
        }

        printf("\n");

        printf("\nLarge Spots status for Wing C(3) : ");

        for(int j=0;j<Max;j++)
        {
            //parking[i][j]=0;
            
            printf("%d ",parking[3][j]);
        }

        printf("\n");
        
    

}



// Node to store all the flat details
//whenever required all the flat details can be obtained by traversing a linked list of flat details
typedef struct node{  
    int flat_id;
    int nt;
    int nf;
    int floor;
    int wing_id;
    int alloted_wing;
    int alloted_spot;
    int v;


    struct node *next;  
} flat_details;  

//Represent the head and tail of the singly linked list of flat details 
struct node *head, *tail = NULL;  

//function to map vehicle into a tree
void Map_Vehicle(flat_details* temp, int vt);
   
//addNode() will add a new node to the list  
flat_details* addNode(int v,int flat_id,int nt,int nf,int floor,int wing_id,int alloted_wing,int alloted_spot) {  
    //Create a new node  
    struct node *newNode = (struct node*)malloc(sizeof(struct node)); 
    newNode->v = v; 
    newNode->flat_id = flat_id;
    newNode->nt = nt;
    newNode->nf = nf;
    newNode->floor = floor;
    newNode->wing_id = wing_id; 
    newNode->alloted_wing = alloted_wing; 
    newNode->alloted_spot = alloted_spot; 

    newNode->next = NULL;  
      
    //Checks if the list is empty  
    if(head == NULL) {  
        //If list is empty, both head and tail will point to new node  
        head = newNode;  
        tail = newNode;  
    }  
    else {  
        //newNode will be added after tail such that tail's next will point to newNode  
        tail->next = newNode;  
        //newNode will become new tail of the list  
        tail = newNode;  
    } 


    return newNode; 
}  
   
//display() will display all the nodes present in the list of parking details 
void display() {  
    //Node current will point to head  
    struct node *current = head;  
      
    if(head == NULL) {  
        printf("List is empty\n");  
        return;  
    }  
    printf("Nodes of singly linked list: \n");  
    while(current != NULL) {  
        //Prints each node by incrementing pointer  
        printf("%d ", current->v);  
        current = current->next;  
    }  
    printf("\n");  
}  

// node for the avl tree containg address of flat details node of corresponding vehicle number stored as root
typedef struct Node {
  int key;
  flat_details* aptr;

  struct Node *left;
  struct Node *right;
  int height;
}tree_node;

int max(int a, int b);

int height(struct Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// Create a node
struct Node *newNode(int key , flat_details* aptr ) {
  struct Node *node = (struct Node *)
    malloc(sizeof(struct Node));
  node->key = key;
  node->aptr = aptr;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Right rotate
struct Node *rightRotate(struct Node *y) {
  struct Node *x = y->left;
  struct Node *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

// Left Rotate
struct Node *leftRotate(struct Node *x) {
  struct Node *y = x->right;
  struct Node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

// Get the balance factor
int getBalanceFactor(struct Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// Insert node
struct Node *insertNode(struct Node *node, int key ,flat_details* aptr) {
  // Find the correct position to insert the node and insert it
  if (node == NULL)
    return (newNode(key,aptr));
  if (key < node->key)
    node->left = insertNode(node->left, key , aptr);
  else if (key > node->key)
    node->right = insertNode(node->right, key , aptr);
  else
    return node;

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (key < node->left->key) {
      return rightRotate(node);
    } else if (key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (key > node->right->key) {
      return leftRotate(node);
    } else if (key < node->right->key) {
      node->left = rightRotate(node->left);
      return leftRotate(node);
    }
  }
  return node;
}

struct Node *minValueNode(struct Node *node) {
  struct Node *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

// Delete a node
struct Node *deleteNode(struct Node *root, int key) {
  // Find the node and delete it
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;

      free(temp);
    } else {
      struct Node *temp = minValueNode(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right, temp->key);
    }
  }
  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1) {
    if (getBalanceFactor(root->left) >= 0) {
      return rightRotate(root);
    } else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(root->right) <= 0) {
      return leftRotate(root);
    } else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}

// Print the tree
void printPreOrder(struct Node *root) {
  if (root != NULL) {
    printf("Vehicle no: %d ", root->key);
    printf("Floor : %d ", root->aptr->floor);

    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

//To search in the vehicle mapping tree
struct Node* search(struct Node* root, int key) 
{ 
    // Base Cases: root is null or key is present at root 
    if (root == NULL || root->key == key) 
       return root; 
     
    // Key is greater than root's key 
    if (root->key < key) 
       return search(root->right, key); 
  
    // Key is smaller than root's key 
    return search(root->left, key); 
}

struct History_Node{ 
    int vn; 
    int date;
    int time;  
    struct History_Node *next;  
};      
   
//Represent the head_History and tail_History of the singly linked list  
struct History_Node *head_History, *tail_History = NULL;  
   
//addHistory_Node() will add a new History_Node to the list  
void addHistory_Node(int date,int time ,int vn) {  
    //Create a new History_Node  
    struct History_Node *newHistory_Node = (struct History_Node*)malloc(sizeof(struct History_Node));  
    newHistory_Node->date = date;  
     newHistory_Node->time = time;  
     newHistory_Node->vn = vn;
    newHistory_Node->next = NULL;  
      
    //Checks if the list is empty  
    if(head_History == NULL) {  
        //If list is empty, both head_History and tail_History will point to new History_Node  
        head_History = newHistory_Node;  
        tail_History = newHistory_Node;  
    }  
    else {  
        //newHistory_Node will be added after tail_History such that tail_History's next will point to newHistory_Node  
        tail_History->next = newHistory_Node;  
        //newHistory_Node will become new tail_History of the list  
        tail_History = newHistory_Node;  
    }  
}  
   
//display() will display all the History_Nodes present in the list  
void Display_History(int date) {  
    //History_Node current will point to head_History  
    struct History_Node *current = head_History;  
      
    if(head_History == NULL) {  
        printf("List is empty\n");  
        return;  
    }  
    printf("Vehicles parked on this date are: \n");  
    while(current != NULL) {  
        //Prints each History_Node by incrementing pointer
        if(current->date==date)
        {
                printf("%d ", current->vn);  
                
        }  

        current = current->next; 
         
    }  
    printf("\n");  
} 




int main() {
  struct Node *root = NULL;
  int op;
  int inp_vn;
  int inp_vt;
  int inp_flat_id;
  int inp_floor;
  int inp_wing_id;
  int inp_time;
  int inp_date;
  flat_details* temp;
  struct Node* ptr;
  initialise_parking();
  //Lets Hardcode some values:
  temp = addNode(1234,1,0,0,1,1,-1,-1);
  root = insertNode(root,1234,temp);
  Map_Vehicle(temp,1);
  temp = addNode(4982,2,0,0,1,1,-1,-1);
  root = insertNode(root,4982,temp);
  Map_Vehicle(temp,1);
  temp = addNode(7879,3,0,0,1,1,-1,-1);
  root = insertNode(root,7879,temp);
  Map_Vehicle(temp,2);
  temp = addNode(8634,5,0,0,3,2,-1,-1);
  root = insertNode(root,8634,temp);
  Map_Vehicle(temp,1);
  temp = addNode(5634,6,0,0,2,3,-1,-1);
  root = insertNode(root,5634,temp);
  Map_Vehicle(temp,2);
  temp = addNode(9596,4,0,0,2,2,-1,-1);
  root = insertNode(root,9596,temp);
  Map_Vehicle(temp,2);


    do
    {
        printf("\n1)Add/Map A vehicle:");
        printf("\n2)Park Vehicle:");
        printf("\n3)Remove Already Mapped Vehicle:");
        printf("\n4) Check history:");
        printf("\n5) See parking Status:");
        printf("\n6)Dispaly Vehicle Mapping tree:");
        printf("\n7)Quit:");
        printf("\n\nEnter Your Choice:");
        scanf("%d",&op);

        switch(op)
        {
            case 1:
                    
                    printf("\n Enter Vehicle number: ");
                    scanf("%d",&inp_vn);
                    printf("\n Enter Vehicle Type: (1 for two wheeler and 2 for four wheeler) ");    //1 for two wheeler   //  2 for 4 wheeler
                    scanf("%d",&inp_vt);
                    printf("\n Enter Flat Id:");
                    scanf("%d",&inp_flat_id);
                    printf("\n Enter Floor:");
                    scanf("%d",&inp_floor);
                    printf("\n Enter Wing Id (1 for A)  (2 for B)  (3 for C) :");
                    scanf("%d",&inp_wing_id);
                    temp = addNode(inp_vn,inp_flat_id,0,0,inp_floor,inp_wing_id,-1,-1);
                    root = insertNode(root,inp_vn,temp);
                    Map_Vehicle(temp,inp_vt);

                   

                    break;

            case 2:

                
                   printf("\nEnter vehicle number to be parked");
                   scanf("%d",&inp_vn);
                   printf("\nEnter date");
                   scanf("%d",&inp_date);
                   printf("\nEnter time");
                   scanf("%d",&inp_time);

                   ptr = search(root,inp_vn);
                   if(ptr!=NULL)
                   {
                       parking[ptr->aptr->alloted_wing][ptr->aptr->alloted_spot]=inp_vn;
                       addHistory_Node(inp_date,inp_time,inp_vn); 
                    
                   }


                   else
                   {
                       printf("\nGuest Vehicle\n");
                       printf("\nEnter vehicle type: (1 for two wheeler and 2 for four wheeler): ");
                       scanf("%d",&inp_vt);
                       int allot=0;
                       
                        if(inp_vt==1)
                        {
                            for(int i=1;i<7 && allot==0;i++)
                            {
                                for(int j=0;j<7 && allot==0;j++)
                                {
                                    if(parking[i][j]==0)
                                    {
                                        parking[i][j]=inp_vn;
                                        addHistory_Node(inp_date,inp_time,inp_vn);

                                        allot++;
                                    }
                                }
                            }


                            if(allot==0)
                            {
                                printf("\nNo parking Spot available");
                            }
                        }

                        else
                        {
                            for(int i=1;i<=3 && allot==0;i++)
                            {
                                for(int j=0;j<Max-1 && allot==0;j++)
                                {
                                    if(parking[i][j]==0 && parking[i][j+1]==0)
                                    {
                                        parking[i][j]=inp_vn;
                                        parking[i][j+1]=inp_vn;
                                        addHistory_Node(inp_date,inp_time,inp_vn);
                                        allot++;
                                    }
                                }
                            }

                            if(allot==0)
                            {
                                for(int i=4;i<=6 && allot==0;i++)
                                {
                                    for(int j=0;j<Max && allot==0;j++)
                                    {
                                         if(parking[i][j]==0)
                                         {
                                             parking[i][j]=inp_vn;
                                             addHistory_Node(inp_date,inp_time,inp_vn);
                                         }   
                                    }
                                }
                            }

                            if(allot==0)
                            {
                                printf("\nNo available parking Spot");
                            }
                        }
                        
                       
                   }
                   


                   



                    break;

            case 3:

                    

                  printf("\nEnter vehicle number to be unmapped");
                  scanf("%d",&inp_vn);
                  ptr = search(root,inp_vn);

                  if(ptr==NULL)
                  {
                      printf("\nVehicle already not mapped");
                  }

                  else
                  {

                      parking[ptr->aptr->alloted_wing][ptr->aptr->alloted_spot]=0;
                      root = deleteNode(root,inp_vn);
                      printf("\nUnmapped");

                      
                  }
                  

                  






                    break;

            case 4:
                    

                     printf("\nEnter date for which history is to be checked ");
                     scanf("%d",&inp_date);
                     Display_History(inp_date);




                    break;




            case 5:
                   
                    display_parking();

                    break;



            case 6:

                    printPreOrder(root);

                            


        }
    }while(op!=7);







}



void Map_Vehicle(flat_details* temp, int vt)
{
    int w_id = temp->wing_id;

    int status=0;
    if(vt==1 && w_id==1)
    {
        for(int i=0;i<Max;i++)
        {
            if(status==0)
            {

                if(parking[1][i]==0)
                {
                    parking[1][i]=1;
                    temp->alloted_wing=1;
                    temp->alloted_spot=i;

                    status++;
                }

            }
            
        }

        if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[2][i]==0)
                    {
                        parking[2][i]=1;
                        temp->alloted_wing=2;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }

        if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[3][i]==0)
                    {
                        parking[3][i]=1;
                        temp->alloted_wing=3;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }


    }



    else if(vt==1 && w_id==2)
    {
        for(int i=0;i<Max;i++)
        {
            if(status==0)
            {

                if(parking[2][i]==0)
                {
                    parking[2][i]=1;
                    temp->alloted_wing=2;
                    temp->alloted_spot=i;
                    status++;
                }

            }
            
        }

        if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[1][i]==0)
                    {
                        parking[1][i]=1;
                        temp->alloted_wing=1;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }

        if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[3][i]==0)
                    {
                        parking[3][i]=1;
                        temp->alloted_wing=3;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }


    }


    else if(vt==1 && w_id==3)
    {
        for(int i=0;i<Max;i++)
        {
            if(status==0)
            {

                if(parking[3][i]==0)
                {
                    parking[3][i]=1;
                    temp->alloted_wing=3;
                    temp->alloted_spot=i;
                    status++;
                }

            }
            
        }

        if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[1][i]==0)
                    {
                        parking[1][i]=1;
                        temp->alloted_wing=1;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }

        if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[2][i]==0)
                    {
                        parking[2][i]=1;
                        temp->alloted_wing=2;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }


    }


    else if(vt==2 && w_id==1)
    {

        if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[4][i]==0)
                    {
                        parking[4][i]=1;
                        temp->alloted_wing=4;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }

        if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[5][i]==0)
                    {
                        parking[5][i]=1;
                        temp->alloted_wing=5;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }

         if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[6][i]==0)
                    {
                        parking[6][i]=1;
                        temp->alloted_wing=6;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }

        
    }


    else if(vt==2 && w_id==2)
    {

        if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[5][i]==0)
                    {
                        parking[5][i]=1;
                        temp->alloted_wing=5;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }

        if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[4][i]==0)
                    {
                        parking[4][i]=1;
                        temp->alloted_wing=4;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }

         if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[6][i]==0)
                    {
                        parking[6][i]=1;
                        temp->alloted_wing=6;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }

        
    }


    else if(vt==2 && w_id==3)
    {

        if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[6][i]==0)
                    {
                        parking[6][i]=1;
                        temp->alloted_wing=6;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }

        if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[4][i]==0)
                    {
                        parking[4][i]=1;
                        temp->alloted_wing=4;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }

         if(status==0)
        {

             for(int i=0;i<Max;i++)
            {
                if(status==0)
                {

                    if(parking[5][i]==0)
                    {
                        parking[5][i]=1;
                        temp->alloted_wing=5;
                        temp->alloted_spot=i;
                        status++;
                    }

                }
                
            }

        }

        
    }


    if(status==0)
    {
        printf("parking spot not available Sorry!!!");
    }

    else
    {
    
        printf("\nmapped at wing %d and spot %d",temp->alloted_wing,temp->alloted_spot);
    }
    


    return;

}