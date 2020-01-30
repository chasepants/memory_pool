// Project:  Pool
// Name: Chase Parks
// Submitted: 02/05/2019
// I declare that the following source code was written by me, or provided
// by the instructor for this project. I understand that copying source
// code from any other source, providing source code to another student, 
// or leaving my code on a public web site constitutes cheating.
// I acknowledge that  If I am found in violation of this policy this may result
// in a zero grade, a permanent record on file and possibly immediate failure of the class.

/* Reflection (1-2 paragraphs): 
	
	This project felt a lot harder than the last for sure. What was challenging was understaning
    the use of pointers and the logically linked list. Also access the pointer through reinterpret 
    cast and the use of placement new was a learning point on this assignment. 

*/


#ifndef __POOL__
#define __POOL__

// include statements
#include <iostream>

class Pool {
    char** pool; //points to open row
    char* free_list; //points open cell
    size_t elem_size; //size of objects being allocate
    size_t block_size; //number of objects in a row
    size_t live_cells; // number of objects allocated
    size_t free_cells; //number of free cells available 
    size_t block_counter; 
    

    
    public:
        //private constructor
        Pool(size_t _elem_size, size_t _block_size=5);

        ~Pool();

        // Disables copy
        Pool(const Pool&) = delete;		

        // Disables assignment
        Pool& operator=(const Pool&) = delete;		// Disables assignment


        //return free_list and update the free_list
        void* allocate();

        void deallocate(void* toDelete);
             
        void link(char* row);


        void expand();

        void profile();
};

#endif