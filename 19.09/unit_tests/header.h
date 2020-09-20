#pragma once

#include <iostream>

class Dummy {
public:
    void doSmth() {
        if (true) {
            std::cout << "It's alive!" << std::endl;
        } else {
            std::cout << "Forever alone" << std::endl;
        }
    }
};