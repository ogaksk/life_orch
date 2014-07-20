//
//  detection.cpp
//  lifegame_orchestra
//
//  Created by ogawa on 2014/07/15.
//
//

#include "patternDetect.h"

resPattern patternDetect::detection(cell **grid, int rows, int cols) {
//    cout <<  this->mPattern.pattern[0] << endl;
    int index_ = 0;
    vector<resPattern> res;
    
    /* これからc++に移植する */
    int patternRow_ = this->mPattern.patternGrid[1];
    int patternCol_ = this->mPattern.patternGrid[0];

    for ( int i = 0; i <= rows - patternRow_; i++ ) {  // オフセットを気にしている
        for ( int j = 0; j <= cols - patternCol_; j++ ) {  // オフセットを気にしつつ二次配列をぶん回す
            int matchFlag_ = 1; // マッチフラッグは最初は1
            cell *thisCell = &grid[i][j];
            
            cout << "patCell----" << &grid[i][j] << endl;
//            if (thisCell->currState == true) {
//                cout << "patDec----true!!!" << endl;
//                cout << "i=" << i << ", j=" << j<< endl;
//            }
      
            for ( int k = 0; k < patternRow_; k++ ) {  // パターン分の二次配列をぶん回す
                for ( int l = 0; l < patternCol_; l++ ) {  // パターン分の二次配列をぶん回す

                  
//                    cout << grid[i][j].currState << endl;
//                    if (grid[i][j].currState == true) {
//                        cout << "true" << endl;
//                    }

                    // オフセット分ふくめたデータとパターンが一致しなければフラグを0にしてbreakする
                    // パターンについては一次配列で渡されてきた、ので後半の演算はこのようになっていると
                    if ( grid[i + k][j + l].currState != this->mPattern.pattern[patternCol_ * k + l ] ) {
                        matchFlag_ = 0;
                        break;
                    }
                 }
               
                // もしすべてのパターンが揃っていれば、マッチフラグは1のままである。そうでなければ0でbreakする
                if ( matchFlag_ == 0 ) { break; }
            }
            
            // もしパターンが揃っていれば、そのパターンの座標をセットする。
            if ( matchFlag_ == 1 ) {
//                cout << "detect" << endl;
//                res[index_].exist[1] = i;
//                res[index_].exist[0] = j;
//                retRow_[ index_ ] = dRow_;
//                retCol_[ index_ ] = dCol_;
//                
//                // 返り血のインデックスを足してやる。これは配列追加メソッドとかでいいんじゃないかな。
                index_++;
            }
        }
    }
}


void patternDetect::testMethod(cell **grid, int rows, int cols) {
    for ( int i = 0; i < cols; i++ ) {  // オフセットを気にしている
        for ( int j = 0; j < rows; j++ ) {  // オフセットを気にしつつ二次配列をぶん回す
            cout << grid[i][j].currState << endl;
        }
    }
}

