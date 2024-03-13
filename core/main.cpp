//
// Created by Dakshina Tharindu on 3/11/24.
//

#include "Core.h"
#include <iostream>

int main() {
    Core core;
    core.run(0x00000037);
    core.run(0x00000017);

    core.print_state();
    return 0;
}
