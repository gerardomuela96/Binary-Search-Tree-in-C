#ifndef BST_INCLUDE
#define BST_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definition of the structure BSTNode which has three fields two BSTNode* and a char* */
typedef struct BSTNode{
  char *name;
  struct BSTNode *left;
  struct BSTNode *right;
}BSTNode;

/* Definition of the function newBSTNode which creates a new BSTNode assigning to it a char* and two BSTNode* */
BSTNode* newBSTNode(char*);

/* Definition of the function addNode which adds a new BSTNode to the tree. It takes the root of the BST to store the char* in the BST */
BSTNode* addNode(BSTNode*,char*);

/* Definition of the function removeNode which removes a BSTNode from a BST. It takes the root of the BST and the char* value from the BSTNode to be removed */
BSTNode* removeNode(BSTNode*,char*);

/* Definition of the function min which returns the smaller BSTNode value from a BST */
BSTNode* min(BSTNode*);

/* Definition of the function displayTree which prints all the values of a BST in order from least to greatest */
void displayTree(BSTNode*);

/* Definition of the function freeMemory which frees all the memory allocated used for a BST by removing all of the BSTNodes from the BST */
BSTNode* freeMemory(BSTNode*);

/* Definition of the function readFromFile which takes a char* which represent the name of the file to read from and store its content in a BST */
BSTNode* readFromFile(BSTNode*,char*);

/* Definition of the function writeToFile which writes all of the content of a BST into a file which the user specifies its name by passing a char* */
void writeToFile(BSTNode*,FILE*);

#endif
