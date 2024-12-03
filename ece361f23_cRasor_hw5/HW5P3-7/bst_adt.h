/**
 * @file bst_adt.h
 *
 * @version 1.0
 * @author Casey Rasor (crasor@pdx.edu)
 * @date   30-Nov-2024
 * 
 * @brief
 * This is the header file for a binary search tree ADT 
 * that stores temperature and humidity data along with a timestamp
 *
 * @details
 * Revision History
 * ----------------
 *	1.0.0	(30-Nov-2022)	Initial version
 *
 * @note Code is based on binaryTree.c from Narasimha Karumanchi
 * Data Structures and Algorithms Made Easy, Career Monk Publishers, 2016
 *
 * @note The data in this implementation needs to contain a timestamp
 * in epoch time, a temperature value and a humidity value.
 *
 */

#ifndef _BST_ADT_H_
#define _BST_ADT_H_

// include required header files
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

//date length definition mm/dd/yy +\n + \0
#define DATE_STR_LEN 10

//typedefs and structs

// define the struct that contains temp,humidity, and timestamp
/**
 * @struct temp_humd_data
 * @brief Struct for the data in the binary search tree
 */
typedef struct temp_humid_data {
    time_t timestamp;
    uint32_t temp;
    uint32_t humid;
} temp_humid_data;

/**
 * @struct BinaryTreeNode
 * @brief Struct for a node on the binary tree
 */
typedef struct BinaryTreeNode{
    struct temp_humid_data data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
}bst_node, *bst_node_ptr;

// function prototypes

/**
 * @brief creates a ne binary search tree
 * @param data the data to be stored in the root node
 *
 * @returns	binary tree root pointer
 */
bst_node_ptr create_tree(temp_humid_data data);

/**
 * @brief Inserts a new node into binary tree
 * @param root is the pointer to root node of the binary tree
 * @param data is the data item to put into the new node
 *
 * @returns	void
 */
void insert_node(bst_node_ptr root, temp_humid_data data);

/**
 * @brief searches the tree for a specific date, if found, prints the data
 * @param root is a pointer to the root node of the binary tree
 * @param date is the date to search for
 *
 * @returns	node pointer containing data
 */
bst_node_ptr search_tree(bst_node_ptr root, char searchDate[]);

/**
 * @brief converts node timestamp into mm/dd/yy format
 *     then prints the date and data contained in node
 * @param node is a pointer to the node in the binary tree
 *
 * @returns	void
 */
void printNodeData(bst_node_ptr node);

/**
 * @brief traverses tree in order, prints data in each node
 * @param root is the pointer to root node of the binary tree
 *
 * @returns	void
 */
void inOrder(bst_node_ptr root);

/**
 * @brief traverses tree pre order, prints data in each node
 * @param root is the pointer to root node of the binary tree
 *
 * @returns	void
 */
void preOrder(bst_node_ptr root);

/**
 * @brief traverses tree post order, prints data in each node
 * @param root is the pointer to root node of the binary tree
 *
 * @returns	void
 */
void postOrder(bst_node_ptr root);


#endif