/******************************************************************************/
//MIT License
//
//Copyright (c) 2024 jv8jv8
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
/******************************************************************************/

/******************************************************************************/
//Implementation of binary tree node and binary tree using void pointers for
//data to allow for greater flexibility at cost of greater memory overhead.
//Attribute type_size is used as in indicator for how many bytes the associated
//data type uses. For example, if the node points to a standard int type, then
//type_size = 4. A uint64_t is used so that the node struct is a round 32 bytes
//in size. Since data is referenced by a pointer, and the node struct is
//intended to be dynamically allocated, the function deconstructing the node
//takes a parameter that specifies whether or not to also free the data pointer
//because the referenced data may not be dynamically allocated. The tree struct
//has an attribute that indicates if the data of its nodes is dynamically
//allocated or not.
//
//Notes:
//(1) The user should still (/is expected to) cast the data they are accessing.
//(2) The tree struct is handled through pointers when passing to functions.
//(3) This library does not contain any method for memory pools and is up to the
//    user to implement
/******************************************************************************/

#ifndef JV_BINTREE_H
#define JV_BINTREE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct node;

typedef struct node
{
    uint64_t type_size;
    void* data;
    struct node* left;
    struct node* right;
} jv_bintree_node;

typedef struct
{
    uint64_t type_size;
    bool dynamic;
    jv_bintree_node* root;
} jv_bintree;

jv_bintree_node* jv_createTemplateTreeNode(uint64_t bytes);
jv_bintree_node* jv_createLeafTreeNode(uint64_t bytes, void* init_data);
jv_bintree_node* jv_createInnerTreeNode(uint64_t bytes, void* init_data,
                 jv_bintree_node* init_left, jv_bintree_node* init_right);
void jv_freeTreeNode(jv_bintree_node* root_node, bool free_data);

jv_bintree jv_createTemplateTree();
void jv_initializeTree(jv_bintree* tree, jv_bintree_node* new_root,
     bool is_dynamic);
void jv_deconstructTree(jv_bintree* tree);

#ifdef JV_BINTREE_INT_DEBUG //Used for testing functionality
//And definitely not because I realized too late the complexity of using void*s

void jv_nodePreOrder(jv_bintree_node* root, FILE* out);
void jv_nodeInOrder(jv_bintree_node* root, FILE* out);
void jv_nodePostOrder(jv_bintree_node* root, FILE* out);

void jv_treePreOrder(jv_bintree* tree, FILE* out);
void jv_treeInOrder(jv_bintree* tree, FILE* out);
void jv_treePostOrder(jv_bintree* tree, FILE* out);

#endif //JV_BINTREE_INT_DEBUG
#endif //JV_BINTREE_H
