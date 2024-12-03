/**
 * @file bst_adt.c
 *
 * @version 1.0
 * @author Casey Rasor (crasor@pdx.edu)
 * @date   30-Nov-2024
 *
 * @brief 
 * This is the source code file for a binary search tree ADT
 * This implementation is designed to be used with a months worth
 * of daily temperature and humidity readings 
 *
 * @details
 * Revision History
 * ----------------
 *	1.0.0	(07-Nov-2022)	Initial version
 *
 * @note Code is based on binaryTree.c from Narasimha Karumanchi
 * Data Structures and Algorithms Made Easy, Career Monk Publishers, 2016
 *
 * @note The data in this implementation needs to contain a timestamp
 * in epoch time, a temperature value and a humidity value.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "bst_adt.h"

//date length definition mm/dd/yy +\n + \0
#define DATE_STR_LEN 10

/***** API functions *****/

//creates a new node in the tree
//taken from karumanchi and modified to use data struct
//hidden from user and not included in .h file, only used to 
//implement create_tree and insert_node functions
bst_node_ptr createNewNode(temp_humid_data data){
    bst_node_ptr node = malloc(sizeof(bst_node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

//create a new tree
/*this function is kind of redundant as it just calls createNewNode
but i wanted to have a specific function for "creating a tree".
createNewNode function is not called during normal use
in my implementation but is just used for creating a tree and
inserting nodes*/
bst_node_ptr create_tree(temp_humid_data data) {
    bst_node_ptr root = createNewNode(data);
     return root;
}

// Insert a new node in the tree
void insert_node(bst_node_ptr root, temp_humid_data data){
     if (data.timestamp < root->data.timestamp) {
          if (root->left == NULL) {//check if left child is empty
               root->left = createNewNode(data);//if empty, create new node there
          }
          else {//if left child is not empty, move down tree
               insert_node(root->left, data);//call insert_node again
          }
     }
     else {//repeat for right side
          if (root->right == NULL) {
               root->right = createNewNode(data);
          }
          else {
               insert_node(root->right, data);
          }
     }
}


//search for a date in the tree
bst_node_ptr search_tree(bst_node_ptr root, char searchDate[]) {
     int sDate[3];
     int nDate[3];
     sscanf(searchDate, "%d/%d/%d", &sDate[1], &sDate[2], &sDate[0]);
     if (strlen(searchDate) == 0) {
          return NULL;
     }

     do {
          char nodeDate[DATE_STR_LEN];
          strftime(nodeDate, DATE_STR_LEN, "%m/%d/%y", localtime(&root->data.timestamp));
          sscanf(nodeDate, "%d/%d/%d", &nDate[1], &nDate[2], &nDate[0]);
          
          if (sDate[0] != nDate[0]) {
               printf("Wrong year, this tree contains 1 month of data from"
                    " year '%d'\n", nDate[0]);
               return NULL;
          }
          else if (sDate[1] != nDate[1]) {
               printf("Wrong month, this tree contains 1 month of data from"
                    " month '%d'\n", nDate[1]);
               return NULL;
          }
          else if (sDate[2] == nDate[2]) {
               printf("Data found!\n");
               printNodeData(root);
               return root;
          }
          else if (sDate[2] < nDate[2]) {
               root = root->left;
               continue;
          }
          else if (sDate[2] > nDate[2]) {
               root = root->right;
               continue;
          }
     } while (root != NULL);
     printf("Date not found in tree\n");
     return NULL;          
}

//print contents of data struct in node
void printNodeData(bst_node_ptr node) {
    char date[10];
    strftime(date, 10, "%m/%d/%y", localtime(&node->data.timestamp));
    printf("Date: %s, temp: %d, humid: %d\n", date, node->data.temp, node->data.humid);
}

// Traverse the tree - in order (left-root-right))
void inOrder(bst_node_ptr root){
     if (root == NULL) {// or if (!root)
          return;
     }
     
     inOrder(root->left); 
     printNodeData(root);
     inOrder(root->right);
}

// Traverse the tree - pre order (root-left-right))
void preOrder(bst_node_ptr root){
     if (root == NULL) {// or if (!root)
          return;
     }
     printNodeData(root);
     //printf("%d ", root->data);  
     preOrder(root->left);  
     preOrder(root->right);
}

// Traverse the tree - post order (left-right-root))
void postOrder(bst_node_ptr root){
     if (root == NULL) // or if (!root)
          return;

     postOrder(root->left);  
     postOrder(root->right);
     printNodeData(root);
     //printf("%d ", root->data);
}