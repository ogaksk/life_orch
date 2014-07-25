//
//  detection.cpp
//  lifegame_orchestra
//
//  Created by ogawa on 2014/07/15.
//
//

#include "patternDetect.h"

resPattern patternDetect::detection(cell **grid, int rows, int cols) {

    resPattern res;
    
    /* これからc++に移植する */
    int patternRow_ = this->mPattern.patternGrid[0];
    int patternCol_ = this->mPattern.patternGrid[1];

    for ( int i = 0; i <= cols - patternCol_; i++ ) {  // オフセットを気にしている
        for ( int j = 0; j <= rows - patternRow_; j++ ) {  // オフセットを気にしつつ二次配列をぶん回す
            int matchFlag_ = 1; // マッチフラッグは最初は1
            cell *thisCell = &grid[i][j];
            
            for ( int k = 0; k < patternCol_; k++ ) {  // パターン分の二次配列をぶん回す
                for ( int l = 0; l < patternRow_; l++ ) {  // パターン分の二次配列をぶん回す

                    // オフセット分ふくめたデータとパターンが一致しなければフラグを0にしてbreakする
                    // パターンについては一次配列で渡されてきた、ので後半の演算はこのようになっていると
                    if ( grid[i + k][j + l].currState != this->mPattern.pattern[patternCol_ * l + k ] ) {
                        matchFlag_ = 0;
                        break;
                    }
                 }
               
                // もしすべてのパターンが揃っていれば、マッチフラグは1のままである。そうでなければ0でbreakする
                if ( matchFlag_ == 0 ) { break; }
            }
            
            // もしパターンが揃っていれば、そのパターンの座標をセットする。
            if ( matchFlag_ == 1 ) {
                res.x.push_back(i);
                res.y.push_back(j);
            }
        }

    }
    res.mPattern =this->mPattern;
    return res;
}

