//
// Created by Dakshina Tharindu on 3/10/24.
//

#include "Core.h"
#include <iostream>

// Constructor
Core::Core() {
    pc = 0;
    for (int i = 0; i < 32; i++) {
        reg[i] = 0;
    }
}

// Destructor
Core::~Core() {
    // Nothing to do here
}

// Run the core
void Core::run() {
    std::cout << "Running the core" << std::endl;
}

