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
	int pattern[3] = {0, 0, 0};
};

struct response {
    string patternNname;
	int exist[2];
};

class patternDetect {
public:
    matchPattern mPattern;
    response res;
    static void detection(cell **grid);
    
    patternDetect(string paramsName, int paramsGrid[] ,int paramspattern[]) {
        cout << paramspattern << endl;
        this -> mPattern.name = paramsName;
        this -> mPattern.patternGrid[0] = paramsGrid[0];
        this -> mPattern.patternGrid[1] = paramsGrid[1];
//        this -> mPattern.pattern = paramspattern;
    }
};