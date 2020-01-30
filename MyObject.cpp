#include "MyObject.h"

MyObject* MyObject::create(int id, const std::string& name){
    return new MyObject(id, name);
}

void MyObject::profile(){
    // std::cout << myPool.getLiveCells() << std::endl;
    myPool.profile();
}

Pool MyObject::myPool(sizeof(MyObject));