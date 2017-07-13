//This program is a user interface for the user to create a Binary Search Tree and write its content on a file 
//Author: Gerardo Muela
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"

//Main function where the user uses the interface to create a Binary Search Tree
int main(){
  BSTNode *root = root = NULL;
  char command = 'c';
  char *name;
  //Loop to keep asking the user for a command to add, delete, list, read or write to and from a file, to Binary Search Tree or exit the program
  while(command != 'e'){
    printf("Please enter command 'a' to enter an employee name\n"
	   "Please enter command 'd' to delete an employee name\n"
	   "Please enter command 'l' to list all employee names\n"
	   "Please enter command 'r' to read employee names from a file\n"
	   "Please enter command 'w' to write employee names to a file\n"
	   "Please enter command 'e' to exit the program\n");
    scanf("%c",&command);
    //If the user wants to add a name to a Binary Search Tree
    if(command == 'a'){
      printf("Enter the employee name you wish to add: \n");
      scanf("%s",name);
      root = addNode(root,name);
    }
    //If the user wants to delete a name from a Binary Search Tree
    else if(command == 'd'){
      printf("Enter the employee name you wish to delete: \n");
      scanf("%s",name);
      root = removeNode(root,name);
    }
    //If the user wants to list the content of a Binary Search Tree
    else if(command == 'l'){
      displayTree(root);
    }
    //If the user wants to store content from a file into a Binary Search Tree
    else if(command == 'r'){
      printf("Enter the name of the file you want to use to read "
	     "employee names: \n");
      scanf("%s",name);
      root = readFromFile(root,name);
    }
    //If the user wants to write the content of a Binary Search Tree into a file
    else if(command == 'w'){
      printf("Enter the name of the file you want to write the employee "
	     "names to: \n");
      scanf("%s",name);
      FILE *file;
      file = fopen(name,"w");
      writeToFile(root,file);
      fclose(file);
    }
    getchar();
  }
  printf("Thank you for using this program!\n");
  //Free the allocated memory used in a Binary Search Tree
  root = freeMemory(root);
}

//newBSTNode function to create a new BSTNode
BSTNode* newBSTNode(char* employeeName){
  //Allocate memory for the BSTNode to be store
  BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
  //Allocate memory for the value of the char* to be store in a BSTNode
  node->name = malloc(strlen(employeeName)+1);
  strcpy(node->name,employeeName);
  node->left = NULL;
  node->right = NULL;
  return node;
}

//addNode function to add a new BSTNode to a Binary Search Tree
BSTNode* addNode(BSTNode *root, char *employeeName){
  //Create a root withe BSTNode if the Binary Search Tree is empty
  if(root == NULL)
    root = newBSTNode(employeeName);
  int temp = strcmp(root->name,employeeName);
  //Add BSTNode to the left side of the Binary Search Tree
  if(temp > 0)
    root->left = addNode(root->left,employeeName);
  //Add BSTNode to the right side of the Binary Search Tree
  else if(temp < 0)
    root->right = addNode(root->right,employeeName);
  return root;
}

//removeNode function to remove a BSTNode from a Binary Search Tree
BSTNode* removeNode(BSTNode *root, char *employeeName){
  if(root == NULL)
    return root;
  //Search for BSTNode in the Binary Search Tree
  int temp = strcmp(root->name,employeeName);
  //Search for BSTNode on the left side of the Binary Search Tree
  if(temp > 0)
    root->left = removeNode(root->left,employeeName);
  //Search for BSTNode on the right side of the Binary Search Tree
  else if(temp < 0)
    root->right = removeNode(root->right,employeeName);
  else{
    BSTNode *temp1 = (BSTNode*)malloc(sizeof(BSTNode));
    BSTNode *temp2 = (BSTNode*)malloc(sizeof(BSTNode));
    BSTNode *temp3 = (BSTNode*)malloc(sizeof(BSTNode));
    //If the BSTNode to be remove has a right child or none
    if(root->left == NULL){
      temp1 = root->right;
      //Free the memory allocated used to store the char*
      free(root->name);
      //Free the memory allocated used to store the BSTNode*
      free(root);
      return temp1;
    }
    //If the BSTNode to be remove has a left child
    else if(root->right == NULL){
      temp1 = root->left;
      //Free the memory allocated used to store the char*
      free(root->name);
      //Free the memory allocated used to store the BSTNode*
      free(root);
      return temp1;
    }
    //If the BSTNode to be remove has two children
    else{
      temp1 = root->right;
      temp2 = root->left;
      //Free the memory allocated used to store the char*
      free(root->name);
      //Free the memory allocated used to store the BSTNode*
      free(root);
      //Allocate memory for the value of the char*
      temp3->name = malloc(strlen(temp1->name)+1);
      //Get the smallest BSTNode from the right side to become the new root
      strcpy(temp3->name,min(temp1)->name);
      temp3->left = temp2;
      temp3->right = removeNode(temp1,temp3->name);
      return temp3;
    }
  }
}

//min function to find the smallest value from a Binary Search Tree
BSTNode* min(BSTNode *root){
  //Move to the left BSTNode until it access the smallest Binary Search Tree
  if(root->left == NULL)
    return root;
  return min(root->left);
}

//displayTree function to print the Binary Search Tree in order
void displayTree(BSTNode *root){
  if(root != NULL){
    displayTree(root->left);
    printf("%s\n",root->name);
    displayTree(root->right);
  }
}

//freeMemory function to free the memory allocated for the Binary Search Tree
BSTNode* freeMemory(BSTNode *root){
  while(root != NULL){
    //Call remove function since when it deletes a BSTNode it frees the memory allocated for that BSTNode
    root = removeNode(root,root->name);
  }
  return NULL;
}

//readFromFile function to read content from a file and store in a Binary Search Tree
BSTNode* readFromFile(BSTNode *root, char *filename){
  FILE *file;
  //Open file to read
  file = fopen(filename,"r");
  //Condition to handle if the file doesn't exist
  if(file == NULL){
    printf("File doesn't exist!\n");
    return root;
  }
  //Temporary variable to store each line of the file
  char *name = (char*)malloc(sizeof(char*));
  //Loop to read the content of the file
  while(!feof(file)){
    fscanf(file,"%s",name);
    root = addNode(root,name);
  }
  //Close file
  fclose(file);
  //Free the allocate memory used for the temporary variable used to store the string extracted from the file
  free(name);
  return root;
}

//writeToFile function to write the content of a Binary Search Tree in a file the user specified 
void writeToFile(BSTNode *root, FILE *file){
  if(root != NULL){
    writeToFile(root->left,file);
    fprintf(file,"%s\n",root->name);
    writeToFile(root->right,file);
  }
}
