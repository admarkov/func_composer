//
// Created by admarkov on 22.04.17.
//

#ifndef FUNC_COMPOSER_FRAME_H
#define FUNC_COMPOSER_FRAME_H

#include <string>
using namespace std;

typedef unsigned int index;

void crash(string info="No information.") {
    puts("Fatal error: "+info);
    exit(0);
}

#endif //FUNC_COMPOSER_FRAME_H
