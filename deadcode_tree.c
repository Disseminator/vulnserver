// Dead Code - Binary Tree Class
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* root;
    int count;
} BinaryTree;

BinaryTree* binary_tree_create() {
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    if (tree) {
        tree->root = NULL;
        tree->count = 0;
    }
    return tree;
}

static TreeNode* tree_node_create(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node) {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

static void tree_insert_recursive(TreeNode** node, int data) {
    if (*node == NULL) {
        *node = tree_node_create(data);
    } else if (data < (*node)->data) {
        tree_insert_recursive(&((*node)->left), data);
    } else {
        tree_insert_recursive(&((*node)->right), data);
    }
}

void binary_tree_insert(BinaryTree* tree, int data) {
    if (tree) {
        tree_insert_recursive(&(tree->root), data);
        tree->count++;
    }
}

static int tree_search_recursive(TreeNode* node, int data) {
    if (node == NULL) {
        return 0;
    }
    if (node->data == data) {
        return 1;
    }
    if (data < node->data) {
        return tree_search_recursive(node->left, data);
    }
    return tree_search_recursive(node->right, data);
}

int binary_tree_search(BinaryTree* tree, int data) {
    if (tree) {
        return tree_search_recursive(tree->root, data);
    }
    return 0;
}

static void tree_destroy_recursive(TreeNode* node) {
    if (node) {
        tree_destroy_recursive(node->left);
        tree_destroy_recursive(node->right);
        free(node);
    }
}

void binary_tree_destroy(BinaryTree* tree) {
    if (tree) {
        tree_destroy_recursive(tree->root);
        free(tree);
    }
}

int binary_tree_size(BinaryTree* tree) {
    if (tree) {
        return tree->count;
    }
    return 0;
}

