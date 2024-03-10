//
// Created by Dakshina Tharindu on 3/10/24.
//

#ifndef CORE_H
#define CORE_H


class Core {
public:
    Core();

    ~Core();

    void run();

private:
    int pc;
    int reg[32];
};


#endif //CORE_H
