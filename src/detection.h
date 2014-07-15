//
//  detection.h
//  lifegame_orchestra
//
//  Created by ogawa on 2014/07/15.
//
//

#pragma once

#include "gameOfLife.h"

struct matchPattern {
    string name;
    int patternSize; // ポインタ指定するとこけなかった
	int* pattern = new int[patternSize];
};


struct response {
    string patternNname;
	int exist[2];
};

class detection {
public:
    matchPattern mPattern;
    response res;
    static void doit(cell **grid);
};