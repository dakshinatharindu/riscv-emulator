//
// Created by Dakshina Tharindu on 3/11/24.
//

#include "Core.h"
#include <iostream>

int main() {
    Core core;
    core.run(0xebbff36f);
    core.run(0xebbff36f);

    core.print_state();
    return 0;
}
