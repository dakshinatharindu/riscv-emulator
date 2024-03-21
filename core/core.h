//
// Created by Dakshina Tharindu on 3/10/24.
//

#ifndef CORE_H
#define CORE_H

#include <stdint.h>
#include <stdio.h>

struct State {
  uint32_t reg[32];
  uint32_t pc;
};

#endif // CORE_H
