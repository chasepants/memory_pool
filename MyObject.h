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


#ifndef __MYOBJECT__
#define __MYOBJECT__

// include statements
#include <iostream>
#include "Pool.h"

class MyObject {
    std::size_t elem_size = 20;
    // Add you data members here...
    int id;
    std::string name; 
   
    //private constructor
    MyObject(int i, const std::string& nm): name(nm){ 
        id = i;
    }

    public:
        //static pool member
        static Pool myPool; 
        //factory method
        static MyObject* create(int id, const std::string& name);

        // Disables copy
        MyObject(const MyObject&) = delete;		

        // Disables assignment
        MyObject& operator=(const MyObject&) = delete;		

        //get memory from pool;
        void* operator new(std::size_t size){
            return myPool.allocate();
        }

        void operator delete(void* ptr){
            myPool.deallocate(ptr);
        }        

            //OVERLOAD << operator for debuggin purposes
	    friend std::ostream& operator<<(std::ostream &output, const MyObject &M) {
            output << "{ " << M.id << ", " << M.name << " }\n";
		    return output;
	    }

        static void profile();
        //print out the amount of live cells, the amount of free cells, and address of free list
};


#endif