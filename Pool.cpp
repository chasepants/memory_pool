#include "Pool.h"

 Pool::Pool(size_t _elem_size, size_t _block_size){
    //grab the size of the object and how many blocks
    elem_size = _elem_size;
    block_size = _block_size;
    block_counter = 0;

    std::cout << "Initializing a pool with element size " 
    << elem_size << " and a block size of " << block_size << std::endl;
    
    //set live_cells and free_cells to 0
    live_cells = 0;
    free_cells = 0;
    block_counter = 0;
    pool = new char*[block_counter];

    

    //create first block
    char* block = new char[elem_size * block_size];
    //set free_list to the beginning of the block
    free_list = block; 
    //link the block_size number of cells in the new row together
    link(block);
    //point pool to the beginning of the row
    pool[0] = block;

}

Pool::~Pool(){
    //delete all new allocations
    delete free_list;
    delete pool;
}

//return free_list and update the free_list
void* Pool::allocate(){  
    //if full expand 
    if(free_cells == 0){
        expand();
    }   
    //iterate through entire list until free list is found
    //get the free cell and increment free_list to the next free cell
    void* alloc_mem = static_cast<void*>(free_list);
    free_list = *reinterpret_cast<char**>(free_list);    
    
    //increment live cells and decrement free cells
    free_cells--; 
    live_cells++; 
    std::cout << "Cell allocated at " << alloc_mem << std::endl;
    return alloc_mem; 
    
}
    
void Pool::deallocate(void* toDelete){
    std::cout << "Cell deallocated at " << toDelete << std:: endl;
    //save where free_list is pointing to
    char* temp = free_list;
    //point free list to what needs to be deleted
    free_list = static_cast<char*>(toDelete);
    //set the char where free list points to the next free space
    //check to see if temp was null
    new (free_list) char* (temp);
    free_cells++;
    live_cells--;
}
        


void Pool::link(char* row){
    //make a link list in the new row 
    //iterate to the next logical location of a block and put the address of 
    //the successor block.
    size_t  index_of_block;
    size_t curr_pos;
    size_t next_pos;
    for(index_of_block = 0; index_of_block < block_size; index_of_block++){ 
        curr_pos = index_of_block * elem_size;
        next_pos = curr_pos + elem_size;
        //*reinterpret_cast<char**>(row + curr_pos) = &row[next_pos];
        new (row + curr_pos) char* (row + next_pos); 
    }
    new (row + curr_pos) char* (nullptr);
    //update number of live cells
    free_cells += 5; 
}


void Pool::expand(){
    std::cout << "Expanding Pool..." << std::endl; 
    block_counter++;
    char* block = new char[elem_size * block_size];
    free_list = block;
    link(block);
    pool[block_counter];
}

void Pool::profile(){

    std::cout << "Live cells: " << live_cells << " Free cells: " 
    << free_cells << " Free list: \n"; 
    char* curr_address = free_list;
    //Iterate through the all the free cells
    for(int i = 0; i < free_cells; i++){                    
        std::cout << static_cast<void*> (curr_address) << std::endl;
        curr_address = *reinterpret_cast<char**>(curr_address);
    } 
} 