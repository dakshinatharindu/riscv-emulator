//
// Created by Dakshina Tharindu on 3/10/24.
//

#ifndef CORE_H
#define CORE_H

#include <cstdint>

class Core {
public:
    Core();

    ~Core();

    void run(int instrt);

    void print_state();

private:
    uint32_t pc;
    uint32_t reg[32];
    uint8_t *mem;


};


#endif //CORE_H
