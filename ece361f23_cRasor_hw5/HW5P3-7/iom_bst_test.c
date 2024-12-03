/** iom_bst_test.c - test program to get temperature readings and store into BST
 *
 * 
 * @author: Casey Rasor (crasor@pdx.edu)
 * @date:   12/3/2024
 *
 * @brief
 * Uses IOM361 and BST ADT to get 30 days worth of temperature values and store 
 * them into a binary search tree. Allows the user to search for specific dates
 * in the tree and then runs an in order traversal to print all data in 
 * ascending date order.
 *
 * @note this program is essentially a mashup of the bst_adt test and the iom361
 * temperature and humidity program from HW4.
 * 
*/
 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "bst_adt.h"
#include "iom361_r2.h"

//date length definition mm/dd/yy +\n + \0
#define DATE_STR_LEN 10
#define MAX_DATA_ITEMS 10
#define NUM_LEDS 16
#define NUM_SWITCHES 16
#define MAXINPUT 50
#define TEMP_RANGE_LOW	42.0
#define TEMP_RANGE_HI	52.0
#define HUMID_RANGE_LOW	72.6
#define HUMID_RANGE_HI	87.3

// global variables
uint32_t* io_base;	// base address of iom361


//function prototypes
/** populateBST() - Generates random temp and humidity values
  * 	using iom361 API, then inserts them into a binary search tree
  *
  * @param	int numDays: number of days in the month
  *
  *	@return pointer to root of the BST
  */
bst_node_ptr populateBST(int numDays);

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
	//local variables
	int rtn_code;
	char searchDate[DATE_STR_LEN];
	
	// greet the user and display the working directory for the application
    printf("Welcome iom BST test program!(crasor@pdx.edu)\n");
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
	
	// initialize IO module
    printf("Initalizing iom361 with 16 switches and 16 LEDs\n");
    sleep(1);
    io_base = iom361_initialize(NUM_SWITCHES, NUM_LEDS, &rtn_code);
    if (rtn_code != 0) {
    // initialization failed
    printf("FATAL(main): Could not initialize I/O module\n");
    return 1;
    }
    printf("iom361_r2 initialized\n");
    printf("\n");

 
	printf("Generating data for 30 days of temperature and humidity values"
	" and inserting into BST...\n");
	bst_node_ptr root = populateBST(30);
	
    
    
    
do {
    printf("Enter a date to search for in the format mm/dd/yy (e.g. 11/1/24):\n");
    getaLine(searchDate, DATE_STR_LEN);
	//pointer to hold search result
    search_tree(root, searchDate);
    
} while (strlen(searchDate) > 0);
   
   printf("\nPerforming in-order traversal of the tree:\n");
   inOrder(root);
 

  return 0;
}

//Helper functions

bst_node_ptr populateBST(int numDays) {
	//optimized order for storing up to 31 days of data in BST
	int order[] = {16,8,24,4,12,20,28,2,6,10,14,18,22,26,1,3,5,7,9,11,13,15,
                                               17,19,21,23,25,27,29,30,31};

	// Set the start date to the 1st of november 2024
	struct tm timestamp;
	timestamp.tm_year = 2024 - 1900; // Years since 1900
	timestamp.tm_mon = 11 - 1; // Months since January (0-indexed)
	timestamp.tm_mday = 1;
	timestamp.tm_hour = 10;
	timestamp.tm_min = 30;
	timestamp.tm_sec = 0;
	timestamp.tm_isdst = -1; // Let mktime() determine if DST is in effect
	
	//data struct array to hold all data
	temp_humid_data data[numDays];
	
	//create 30 days worth of data, store in data struct array
	printf("Starting date: 11/1/24...\n...Ending date: 11/30/24\n\n");
	for (int i = 0; i < numDays; ++i) {
		data[i].timestamp = mktime(&timestamp);
		_iom361_setSensor1_rndm(TEMP_RANGE_LOW, TEMP_RANGE_HI, HUMID_RANGE_LOW,
		HUMID_RANGE_HI);
		data[i].temp = iom361_readReg(io_base, TEMP_REG, NULL);//reads raw temp data
	    data[i].temp = (data[i].temp / powf(2,20)) * 200.0 - 50; //corrects temp data;
		data[i].humid = iom361_readReg(io_base, HUMID_REG, NULL);//reads raw humitity data
		data[i].humid = (data[i].humid/ pow(2, 20)) * 100;//corrects humidity data
		++timestamp.tm_mday;
	}
	// create root node
	bst_node_ptr root = create_tree(data[order[0]-1]);
	//store data in BST using insert_node function and optimized order
	for (int i = 1; i < numDays; ++i) {
		insert_node(root, data[order[i] - 1]); 
	}
	return root;	
}

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
