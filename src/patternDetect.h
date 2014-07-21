//
//  detection.h
//  lifegame_orchestra
//
//  Created by ogawa on 2014/07/15.
//
//

#pragma once

#include "gameOfLife.h"

// この配列は静的だから参照受けのほうがよいか
struct matchPattern {
    string name;
    int patternGrid[2]; // ポインタ指定するとこけなかった 謎
    int *pattern;
};

struct resPattern {
    string patternName;
	vector<int> x;
    vector<int> y;
};

class patternDetect {
public:
    matchPattern mPattern;
    resPattern detection(cell **grid, int rows, int cols);
    void testMethod(cell **grid, int rows, int cols);
    
    patternDetect(string paramsName, int paramsGrid[] ,int paramsPattern[]) {
        this -> mPattern.name = paramsName;
        this -> mPattern.patternGrid[0] = paramsGrid[0];
        this -> mPattern.patternGrid[1] = paramsGrid[1];
        this -> mPattern.pattern = new int[(paramsGrid[0] * paramsGrid[1])];
        for(int i = 0; i < (paramsGrid[0] * paramsGrid[1]); i++) {
            this -> mPattern.pattern[i] = paramsPattern[i];
        }
    }
};