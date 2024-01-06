#include <stdlib.h>
#include "jv_bintree.h"

jv_bintree_node* jv_createTemplateTreeNode(uint64_t bytes)
{
    jv_bintree_node* node = (jv_bintree_node*)malloc(sizeof(jv_bintree_node));
    node->type_size = bytes;
    node->data = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

jv_bintree_node* jv_createLeafTreeNode(uint64_t bytes, void* init_data)
{
    jv_bintree_node* node = (jv_bintree_node*)malloc(sizeof(jv_bintree_node));
    node->type_size = bytes;
    node->data = init_data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

jv_bintree_node* jv_createInnerTreeNode(uint64_t bytes, void* init_data,
                 jv_bintree_node* init_left, jv_bintree_node* init_right)
{
    jv_bintree_node* node = (jv_bintree_node*)malloc(sizeof(jv_bintree_node));
    node->type_size = bytes;
    node->data = init_data;
    node->left = init_left;
    node->right = init_right;
    return node;
}

void jv_freeTreeNode(jv_bintree_node* root_node, bool free_data)
{
    if(root_node == NULL)
        return;

    jv_freeTreeNode(root_node->left, free_data);
    jv_freeTreeNode(root_node->right, free_data);
    if(free_data)
    {
        free(root_node->data);
        root_node->data = NULL;
    }
    root_node->left = NULL;
    root_node->right = NULL;
    root_node->type_size = 0;
    free(root_node);
}

jv_bintree jv_createTemplateTree()
{
    jv_bintree new_tree;
    new_tree.root = NULL;
    new_tree.dynamic = false;
    new_tree.type_size = 0;
    return new_tree;
}

void jv_initializeTree(jv_bintree* tree, jv_bintree_node* new_root,
     bool is_dynamic)
{
    if(tree != NULL)
        if(tree->root != NULL)
            jv_freeTreeNode(tree->root, tree->dynamic);

    tree->root = new_root;
    tree->dynamic = is_dynamic;
    tree->type_size = new_root->type_size;
}

void jv_deconstructTree(jv_bintree* tree)
{
    if(tree == NULL)
        return;
    
    tree->type_size = 0;
    if(tree->root != NULL)
        jv_freeTreeNode(tree->root, tree->dynamic);
}

#ifdef JV_BINTREE_INT_DEBUG

void jv_nodePreOrder(jv_bintree_node* root, FILE* out)
{
    if(root == NULL)
        return;

    fprintf(out, "%d ", *(int*)(root->data));
    jv_nodePreOrder(root->left, out);
    jv_nodePreOrder(root->right, out);
}

void jv_nodeInOrder(jv_bintree_node* root, FILE* out)
{
    if(root == NULL)
        return;

    jv_nodeInOrder(root->left, out);
    fprintf(out, "%d ", *(int*)(root->data));
    jv_nodeInOrder(root->right, out);
}

void jv_nodePostOrder(jv_bintree_node* root, FILE* out)
{
    if(root == NULL)
        return;

    jv_nodePostOrder(root->left, out);
    jv_nodePostOrder(root->right, out);
    fprintf(out, "%d ", *(int*)(root->data));
}

void jv_treePreOrder(jv_bintree* tree, FILE* out)
{
    if(tree == NULL)
        return;
    
    if(tree->root == NULL)
        return;
    
    jv_nodePreOrder(tree->root, out);
}

void jv_treeInOrder(jv_bintree* tree, FILE* out)
{
    if(tree == NULL)
        return;
    
    if(tree->root == NULL)
        return;
    
    jv_nodeInOrder(tree->root, out);
}

void jv_treePostOrder(jv_bintree* tree, FILE* out)
{
    if(tree == NULL)
        return;
    
    if(tree->root == NULL)
        return;
    
    jv_nodePostOrder(tree->root, out);
}

#endif //JV_BINTREE_INT_DEBUG
