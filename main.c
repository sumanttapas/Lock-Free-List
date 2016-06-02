#include <stdio.h>
#include <stdlib.h>

struct Node{
    int key;
    int element;
    int mark;
    int flag;
    struct Node* right;
    struct Node* backlink;
};

struct Search{
    struct Node* returnnode1;
    struct Node* returnnode2;
};

struct Node head;

/*int Search(int k)
{
    struct Search nod;
    nod =(Search*)SearchFrom(k,head);
    if(nod.returnnode1.key == k)
        return nod.returnnode1;
    else
        return FALSE;
}*/

int SearchFrom(int k,struct Node* curr_node)
{

    struct Node* next_node;
    struct Search* nod1;        //why malloc?
    //nod1 = malloc()
    next_node = curr_node->right;
    while(next_node->key <= k)
    {
        while((next_node->mark == 1)&&(curr_node->mark == 0 || curr_node->right != next_node))
              {
                  if(curr_node->right == next_node)
                   {
                       //HelpMarked(curr_node,next_node);
                   }
                  next_node = curr_node->right;
              }
        if(next_node->key <= k)
         {
            curr_node = next_node;
            next_node = curr_node->right;
            nod1->returnnode1 = curr_node;
            nod1->returnnode2 = next_node;
         }
    }
    return(nod1);
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
