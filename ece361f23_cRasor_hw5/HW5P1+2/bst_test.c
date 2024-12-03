/**
 * @file bst_test.c
 *
 * @version 1.0
 * @author Casey Rasor (crasor@pdx.edu)
 * @date   30-Nov-2024
 * 
 * @brief
 * This is a tester file that creates a binary search tree, 
 * stores 30 days of data, then traverses the tree in order
 *
 * @details
 * Revision History
 * ----------------
 *	1.0.0	(30-Nov-2022)	Initial version
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include "bst_adt.h"



#define NUM_DAYS 30
//date length definition mm/dd/yy +\n + \0
#define DATE_STR_LEN 10

//Function prototypes
/** getaLine() - Gets a line from stdin, taken from lineHelper API
  * 	and modified to be used in this program
  *
  * @param	int lim: max length of input
  * @param	char s[]: char array to hold string
  *
  *	@return length of string
  */
int getaLine(char s[],int lim);

int main() {
	
	// greet the user and display the working directory for the application
    printf("Welcome BST test program!(crasor@pdx.edu)\n");
    errno = 0;
    char *buf = getcwd(NULL, 0);    // allocates a buffer to hold the path   
    if (buf == NULL) {
        perror("getcwd");
        printf("Could not display the path\n");
    }
    else {
        printf("Current working directory: %s\n", buf);
        free(buf);
    }
    printf("\n");

     char searchDate[DATE_STR_LEN];
  //create test data
  struct tm timestamp;

  // Set the start date to the 1st of november 2024
  timestamp.tm_year = 2024 - 1900; // Years since 1900
  timestamp.tm_mon = 11 - 1; // Months since January (0-indexed)
  timestamp.tm_mday = 1;
  timestamp.tm_hour = 10;
  timestamp.tm_min = 30;
  timestamp.tm_sec = 0;
  timestamp.tm_isdst = -1; // Let mktime() determine if DST is in effect
  
  temp_humid_data data[NUM_DAYS];

     //create 30 days worth of data, store in data struct array
	 printf("Creating 30 days of data for 11/1/24-11/30/24...\n");
  for (int i = 0; i < NUM_DAYS; ++i) {
      data[i].timestamp = mktime(&timestamp);
      data[i].temp = i;
      data[i].humid = i + 10;
      ++timestamp.tm_mday;
  }

     //optimized order for storing up to 31 days of data in BST
  int order[] = {16,8,24,4,12,20,28,2,6,10,14,18,22,26,1,3,5,7,9,11,13,15,
                                               17,19,21,23,25,27,29,30,31};
	printf("Creating Binary Search Tree and inserting data...\n");
  // create root node
  bst_node_ptr root = create_tree(data[order[0]-1]);
     //store data in BST using insert_node function and optimized order
  for (int i = 1; i < NUM_DAYS; ++i) {
      insert_node(root, data[order[i] - 1]); 
  }
    //pointer to hold search result
    bst_node_ptr searchNode;
    
do {
     printf("Enter a date to search for in the format mm/dd/yy (e.g. 11/1/24):\n");
     getaLine(searchDate, DATE_STR_LEN);
     searchNode = search_tree(root, searchDate);
    
} while (strlen(searchDate) > 0);
   
   printf("\nPerforming in-order traversal of the tree:\n");
   inOrder(root);
 

  return 0;
}

//helper functions
int getaLine(char s[],int lim){ 
    int c, i;

    // read the input line and store in s until we get a new line or
    // exceed the maximum number of characters to read
    for (i = 0; i < lim - 1 && (c = getchar())!=EOF && c!='\n'; ++i) 
        s[i] = c; 

    // append '\0' to terminate the string.  Include '\n' in the string
    if (c == '\n') { 
        s[i] = c; 
    } 
    s[i] = '\0'; 
    return i; 
}