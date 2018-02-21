//
//  main.cpp
//  B+Tree
//
//  Created by Henry on 20/02/18.
//  Copyright © 2018 A01019108. All rights reserved.
//

#include <iostream>

#include "b_plus_tree.hpp"
void printTree(int leave, int data){
    std::cout << "leave" << leave;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    mds::b_plus_tree<int, int> * arbol;
    
    arbol = new mds::b_plus_tree<int, int>(3,3,std::less<int>());
    
    arbol->insert(3, 32452);
    arbol->insert(6, 5634);
    arbol->insert(2, 5476);
    arbol->insert(8, 6789);
    arbol->insert(9, 3452);
    arbol->insert(4, 73686);
    std::less<int> *fun = new std::less<int>();
    arbol->walk(*fun);
    
    return 0;
}
