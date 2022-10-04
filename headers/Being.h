#ifndef BEING_H
#define BEING_H

#include "../headers/base_includes.h"

class Being {
    public:
        bool Is(string type) {
            if (type == "Being") {
                return true;    
            }
            return false;
        } 
};


#endif