//
//  detection.cpp
//  lifegame_orchestra
//
//  Created by ogawa on 2014/07/15.
//
//

#include "patternDetect.h"

void patternDetect::detection(cell **grid) {
    cout <<  this->mPattern.pattern[0] << endl;
    
    /* これからc++に移植する
    index_ = 0;
    for ( dRow_ = 0; dRow_ <= dataRow_ - patternRow_; dRow_++ ) {  // オフセットを気にしている
        for ( dCol_ = 0; dCol_ <= dataCol_ - patternCol_; dCol_++ ) {  // オフセットを気にしつつ二次配列をぶん回す
            matchFlag_ = 1; // マッチフラッグは最初は1
            
            for ( pRow_ = 0; pRow_ < patternRow_; pRow_++ ) {  // パターン分の二次配列をぶん回す
                for ( pCol_ = 0; pCol_ < patternCol_; pCol_++ ) {  // パターン分の二次配列をぶん回す
                    
                    // オフセット分ふくめたデータとパターンが一致しなければフラグを0にしてbreakする
                    // パターンについては一次配列で渡されてきた、ので後半の演算はこのようになっていると
                    if ( dMatrix_[ dRow_ + pRow_ ][ dCol_ + pCol_ ] != pattern_[ patternCol_ * pRow_ + pCol_ ] )
                    {
                        matchFlag_ = 0;
                        break;
                    }
                }
                
                // もしすべてのパターンが揃っていれば、マッチフラグは1のままである。そうでなければ0でbreakする
                if ( matchFlag_ == 0 ) { break; }
            }
            
            // もしパターンが揃っていれば、そのパターンの座標をセットする。
            if ( matchFlag_ == 1 ) {
                retRow_[ index_ ] = dRow_;
                retCol_[ index_ ] = dCol_;
                
                // 返り血のインデックスを足してやる。これは配列追加メソッドとかでいいんじゃないかな。
                index_++;
            }
        }
    }
     */
     
}


