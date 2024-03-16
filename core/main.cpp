//
// Created by Dakshina Tharindu on 3/11/24.
//

#include "Core.h"
#include <iostream>

int main() {
    Core core;
    core.run(0x0ea00267);
//    core.run(0x0ea00267);
    core.run(0x00402023);
    core.run(0x00005283);

    core.print_state();
    return 0;
}
