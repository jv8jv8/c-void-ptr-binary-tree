/*
BUILD:
gcc -DJV_BINTREE_INT_DEBUG jv_bintree.h jv_bintree.c bintreetest.c -o test

RUN:
./test
*/

//JV_BINTREE_INT_DEBUG must be defined for test program
//Definition is done in build command line

#include <stdio.h>
#include <stdlib.h>
#include "jv_bintree.h"

#define SIZE 4ULL
#define START 0x80UL
#define LLMASK 0x8000000000000000

void printMenu();
void printBinary(void* variable, unsigned int bits);

int main()
{
    printf("Creating initial root...\n");
    jv_bintree_node* test_root = jv_createTemplateTreeNode(SIZE);
    test_root->data = malloc(sizeof(int));
    *(int*)(test_root->data) = 0;
    printf("Created initial root\n");

    printf("Creating tree struct...\n");
    jv_bintree test_tree = jv_createTemplateTree();
    printf("Created tree struct\n");

    printf("Setting tree struct...\n");
    jv_bintree* test = &test_tree;
    printf("Set tree struct\n");

    printf("Initializing tree...\n");
    jv_initializeTree(test, test_root, true);
    printf("Initialized tree\n\n");

    printf("Binary tree test program using int type\n");
    printf("Build your own tree of integers\n\n");    

    uint8_t path = 0;
    uint8_t path_mask = START;
    uint8_t path_length = 0;
    jv_bintree_node* traveler = test->root; //GI players?
    int op = -1, n = 0;
    while(op != 12)
    {
        printMenu();
        scanf("%d", &op);

        switch (op)
        {
            case 0:
                if(traveler->left == NULL)
                {
                    printf("There is no node connected to the left\n\n");
                    break;
                }

                if(path_length >= 8)
                {
                    printf("Tree's too deep\n\n");
                    break;
                }
                traveler = traveler->left;
                path &= !path_mask;
                path_mask >>= 1;
                path_length++;
                printf("Moved left\n\n");
                break;
            case 1:
                if(traveler->right == NULL)
                {
                    printf("There is no node connected to the right\n\n");
                    break;
                }

                if(path_length >= 8)
                {
                    printf("Tree's too deep\n\n");
                    break;
                }
                traveler = traveler->right;
                path |= path_mask;
                path_mask >>= 1;
                path_length++;
                printf("Moved right\n\n");
                break;
            case 2:
            {
                if(path_length >= 8)
                {
                    printf("Tree's too deep\n\n");
                    break;
                }
                
                if(traveler->left != NULL)
                {
                    printf("There is already a node to the left\n\n");
                    break;
                }

                int* new_int = (int*)malloc(sizeof(int));
                printf("Enter value for the new node: ");
                scanf("%d", new_int);

                traveler->left = jv_createLeafTreeNode(SIZE, new_int);
                printf("\n\nInserted %d to the left\n\n", op);
                op = -1;
                break;
            }
            case 3:
                if(path_length >= 8)
                {
                    printf("Tree's too deep\n\n");
                    break;
                }
                
                if(traveler->right != NULL)
                {
                    printf("There is already a node to the right\n\n");
                    break;
                }

                int* new_int = (int*)malloc(sizeof(int));
                printf("Enter value for the new node: ");
                scanf("%d", new_int);

                traveler->right = jv_createLeafTreeNode(SIZE, new_int);
                printf("\n\nInserted %d to the right\n\n", op);
                op = -1;
                break;
            case 4:
                printf("Current node's value: %d\n\n", *(int*)(traveler->data));
                break;
            case 5:
                printf("Enter new value for node: ");
                scanf("%d", &op);
                *(int*)(traveler->data) = op;
                printf("\n\nChanged current node's value to %d\n\n", op);
                op = -1;
                break;
            case 6:
                traveler = test->root;
                path = 0;
                path_mask = START;
                printf("Back at root\n\n");
                break;
            case 7:
                printf("Preorder traversal:\n");
                jv_treePreOrder(test, stdout);
                printf("\n\n");
                break;
            case 8:
                printf("Inorder traversal:\n");
                jv_treeInOrder(test, stdout);
                printf("\n\n");
                break;
            case 9:
                printf("Postorder traversal:\n");
                jv_treePostOrder(test, stdout);
                printf("\n\n");
                break;
            case 10:
                if(traveler == NULL)
                {
                    printf("You're at NULL!\n");
                    printf("Let's put you back the the root\n\n");
                    traveler = test->root;
                    break;
                }

                if(traveler->left == NULL)
                {
                    printf("There is no node to the left\n\n");
                    break;
                }

                printf("Freeing left sub tree\n");
                jv_freeTreeNode(traveler->left, true);
                traveler->left = NULL;
                break;
            case 11:
                if(traveler == NULL)
                {
                    printf("You're at NULL!\n");
                    printf("Let's put you back the the root\n\n");
                    traveler = test->root;
                    break;
                }

                if(traveler->right == NULL)
                {
                    printf("There is no node to the right\n\n");
                    break;
                }

                printf("Freeing right sub tree\n");
                jv_freeTreeNode(traveler->right, true);
                traveler->right = NULL;
                break;
            case 12:
                jv_deconstructTree(test);
                printf("Exiting program\n");
                break;
            default:
                printf("Enter valid operation\n\n");
                break;
        }
    }

    system("pause");
    return 0;
}

void printMenu()
{
    //Bothers me that 0 isn't for exiting test programs like I usually do but
    //it'd bother me more if 0 wasnt to go left and 1 to go right
    printf("(0)  Traverse left\n");
    printf("(1)  Traverse right\n");
    printf("(2)  Insert node left\n");
    printf("(3)  Insert node right\n");
    printf("(4)  Display current value\n");
    printf("(5)  Change current value\n");
    printf("(6)  Go back to root\n");
    printf("(7)  Show preorder traversal\n");
    printf("(8)  Show inorder traversal\n");
    printf("(9)  Show postorder traversal\n");
    printf("(10) Free left subtree\n");
    printf("(11) Free right subtree\n");
    printf("(12) Exit program\n\n");
    printf("Select operation: ");
}
