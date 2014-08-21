　/*
 *  gameOfLife.cpp
 *  conway
 *
 *  Created by Chris Roby on 3/26/10.
 *  Copyright (c) 2012 Chris Roby. All rights reserved.
 *
 */

#include "gameOfLife.h"
#include "patterns.h"
#include "patternDetect.h"

const int WIDTH = 800;
const int HEIGHT = 500;
const int CELLSIZE = 6;
const int FULLSCREEN_CELLSIZE = 8;
const int TICK_INTERVAL = 6;
const int FRAMERATE = 60;

/*//////////////////////////////////*/
    // いくつかのグローバル変数//

patternDetect *blink1;
patternDetect *blink2;
patternDetect *glider1;
patternDetect *glider2;
patternDetect *glider3;
patternDetect *glider4;
patternDetect *line5;

vector<resPattern> datas;
vector<resPattern>::iterator resData;

/*//////////////////////////////////*/

ofImage myImage;

void gameOfLife::setup() {
  fullScreen = false;
  highlight = false;
  active = false;
  
  ofSetFullscreen(false);
  ofSetWindowShape(WIDTH, HEIGHT);
  
  init(WIDTH, HEIGHT, CELLSIZE);
  
	ofBackground(ofColor::white);
	ofSetBackgroundAuto(true);
	ofSetWindowTitle("Conway's Game of Life");
	ofSetFrameRate(FRAMERATE);
  
  myImage.loadImage("circleAlpha.tif");
  
  sender.setup(HOST, PORT);
  audioSetup();
  
}

void gameOfLife::init(int width, int height, int cellSize) {
	cols = width/cellSize;
	rows = height/cellSize;
	
	if (width % cellSize != 0 || (height & cellSize) != 0) {
		float ratio = width/height;
		cellWidth = cellSize * ratio;
		cellHeight = cellSize;
	} else {
		cellWidth = cellSize;
		cellHeight = cellSize;
	}
  
	// set up grid
	clear();
    patternMapping();
}

void gameOfLife::update() {
    if (ofGetFrameNum() % TICK_INTERVAL == 0 && active) {
      tick();
      datas.push_back(blink1->detection(grid, rows, cols));
      datas.push_back(blink2->detection(grid, rows, cols));
      
      datas.push_back(glider1->detection(grid, rows, cols));
      datas.push_back(glider2->detection(grid, rows, cols));
      datas.push_back(glider3->detection(grid, rows, cols));
      datas.push_back(glider4->detection(grid, rows, cols));
      
      datas.push_back(line5->detection(grid, rows, cols));
      audioTick = true;
//      oscSending(datas);
    }
}

/*今は参照渡し風に書いている　複数のインスタンスを渡してバグが生まれたら対応*/
//void gameOfLife::oscSending(vector<resPattern> &datas) {
//  for(resData = datas.begin(); resData != datas.end(); ++resData) {
//    std::stringstream result_x, result_y;
//    std::copy(&*resData->x.begin(), &*resData->x.end(), std::ostream_iterator<int>(result_x, ","));
//    std::copy(&*resData->y.begin(), &*resData->y.end(), std::ostream_iterator<int>(result_y, ","));
//    
//    ofxOscMessage mx, my;
//    string textName = "/";
//    textName += resData->mPattern.name;
//    textName += "/";
//    string textX = textName + "x";
//    string textY = textName + "y";
//    
//    mx.setAddress(textX);
//    mx.addStringArg( result_x.str() );
//    
//    my.setAddress( textY );
//    my.addStringArg( result_y.str() );
//    
//    //メッセージを送信
//    sender.sendMessage( mx );
//    sender.sendMessage( my );
//  }
//}


void gameOfLife::tick() {
	// get active neighbors for each cell
    
	for (int i=0; i<cols; i++) {
        for (int j=0; j<rows; j++) {
            cell *thisCell = &grid[i][j];
            thisCell->activeNeighbors = getNumActiveNeighbors(i, j);
            bool currState = thisCell->currState;
            int activeNeighbors = thisCell->activeNeighbors;
            if (currState == true && activeNeighbors < 2) {
                thisCell->nextState = false;
            } else if (currState == true && activeNeighbors > 3) {
                thisCell->nextState = false;
            } else if (currState == true && activeNeighbors > 1 && activeNeighbors < 4) {
                thisCell->nextState = true;
                thisCell->color = ofColor::white;
            } else if (currState == false && activeNeighbors == 3) {
                thisCell->nextState = true;
                thisCell->color = highlight ? ofColor::green : ofColor::white;
            }
        }
	}
	makeNextStateCurrent();
}

void gameOfLife::makeNextStateCurrent() {
	for (int i=0; i<cols; i++) {
		for (int j=0; j<rows; j++) {
			grid[i][j].currState = grid[i][j].nextState;		
		}
	}
}

void gameOfLife::draw() {
  ofBackground(0, 0, 0);
  ofEnableBlendMode(OF_BLENDMODE_ADD);
	for (int i=0; i<cols; i++) {
		for (int j=0; j<rows; j++) {
      cell thisCell = grid[i][j];
			ofSetColor(200, 200, 200);
			ofNoFill();
//			ofRect(i*cellWidth, j*cellHeight, cellWidth, cellHeight);
      if (thisCell.currState == true) {
				ofSetColor(thisCell.color.r, thisCell.color.g, thisCell.color.b, 60);
				ofFill();
        myImage.ofImage_::draw((float)(i*cellWidth), (float)(j*cellHeight), cellWidth*2.3, cellHeight*2.3);
//  			ofRect(i*cellWidth, j*cellHeight, cellWidth, cellHeight);
				ofNoFill();
			}
		}
	}


  if (ofGetFrameNum() % TICK_INTERVAL == 0 && active) {

    drawingResPatterns(datas);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    /*レスデータはここでクリアする*/
    datas.clear();
  }
}

/*::::::::::::::::::::::::
 // パターン発見時の描画まわり
::::::::::::::::::::::::*/

void gameOfLife::drawingResPatterns(vector<resPattern> &datas) {
  for(resData = datas.begin(); resData != datas.end(); ++resData) {
    resData->x.size();
    if (resData->x.size() != 0) {
      for (int h=0; h < resData->x.size(); h++) {
        for (int i=0; i< resData->mPattern.patternGrid[0]; i++) {
          for (int j=0; j < resData->mPattern.patternGrid[1]; j++) {
            if (resData->mPattern.pattern[resData->mPattern.patternGrid[0] * j + i ] == 1) {
              
              /*検出描画チェックログ よくつかう*/
//              cout << resData->mPattern.name << endl;
              
              ofSetColor(resData->mPattern.color.r, resData->mPattern.color.g, resData->mPattern.color.b, 200);
              ofFill();
              myImage.ofImage_::draw((float)((i + resData->x.at(h)) * cellWidth) - cellWidth / 2, (float)((j + resData->y.at(h)) * cellHeight) - cellHeight / 2, cellWidth*3.0, cellHeight*3.0);
//              ofRect( (i + resData->x.at(h)) * cellWidth, (j + resData->y.at(h)) * cellHeight, cellWidth, cellHeight);
//              ofNoFill();
            }
          }
        }
      }
    }
  }
}


void gameOfLife::clear() {
	grid = new cell *[cols];
	for (int i=0; i<cols; i++) {
		grid[i] = new cell[rows];
		for (int j=0; j<rows; j++) {
      cell *thisCell = &grid[i][j];
			thisCell->currState = false;
			thisCell->nextState = false;	
			thisCell->color = ofColor::black;
		}
	}
}

/*****************************
 * 検出パターンを初期化するメソッド
*****************************/
void gameOfLife::patternMapping() {
    
    int grid1[] = {1, 7};
    int grid2[] = {3, 3};
    int pat1[] = {0, 0, 0, 1, 1, 1, 0, 0, 0};
    int pat2[] = {0, 1, 0, 0, 1, 0, 0, 1, 0};
    int pat3[] = {0, 1, 1, 1, 1, 1, 0};
  
    int patGlider1[] = {0, 1, 0, 0, 0, 1, 1, 1, 1};
    int patGlider2[] = {0, 0, 1, 1, 0, 1, 0, 1, 1};
    int patGlider3[] = {1, 0, 0, 0, 1, 1, 1, 1, 0};
    int patGlider4[] = {0, 0, 1, 1, 1, 0, 0, 1, 1};
  
    blink1 = new patternDetect("blink1", grid2, pat1, ofColor::cyan);
    blink2 = new patternDetect("blink2", grid2, pat2, ofColor::cyan);
  
    glider1 = new patternDetect("glider1", grid2, patGlider1, ofColor::cyan);
    glider2 = new patternDetect("glider2", grid2, patGlider2, ofColor::cyan);
    glider3 = new patternDetect("glider3", grid2, patGlider3, ofColor::cyan);
    glider4 = new patternDetect("glider4", grid2, patGlider4, ofColor::cyan);
  
    line5 = new patternDetect("line5", grid2, pat3, ofColor::cyan);
}


/*****************************
 * オーディオ出力
 *****************************/

void gameOfLife::audioSetup() {
  
  sampleRate 			= 44100; /* Sampling Rate */
	initialBufferSize	= 512;	/* Buffer Size. you have to fill this buffer with sound*/
	
	ofSoundStreamSetup(2,0,this, sampleRate, initialBufferSize, 4);
  
  lAudio.assign(initialBufferSize, 0.0);
	rAudio.assign(initialBufferSize, 0.0);
  
  /*frequencyのマッピング*/
  freqMap["blink1"] = 493.883301;
  freqMap["blink2"] = 329.627563;
  
  freqMap["glider1"] = 277.182617;
  freqMap["glider2"] = 369.994415;
  freqMap["glider3"] = 415.304688;
  freqMap["glider4"] = 440.0;
  
  freqMap["line5"] = 554.365234;
  
  mode = 0;

}

void gameOfLife::audioOut(float *output, int bufferSize, int nChannels) {
  float currentTone[polyNum];
  float currentAdditiveTone[polyNum];
  int currentX[polyNum]; // 発音数に応じて得れる要素数を制限する
  int currentY[polyNum]; // 発音数に応じて得れる要素数を制限する
  
  for (int i = 0; i < bufferSize; i++) {
//    for(resData = datas.begin(); resData != datas.end(); ++resData) {
//      float career = patTofreq(resData->mPattern.name);
//      for(int i = 0; i < resData->x.size(); i++) {
//        wave = osc.sinewave(career) * resData->y[i] * 0.01;
//        float pan = 1 / resData->x[i];
//        mymix.stereo(wave, outputs, pan);
//      }

//
//      lAudio[i] = output[i * nChannels] = outputs[0];
//      rAudio[i] = output[i * nChannels + 1] = outputs[1];
//    }

    if (audioTick == true) {
      wave = 0;
      
      for(int j = 0; j < polyNum; j ++ ) {
        ADSR[j].trigger(0, adsrEnv[0]);
        currentTone[j] = 0;
      }
      
      for (int k = 0; k < 7; k ++ ) {
        for(int l = 0; l < datas[k].x.size(); l ++ ) {
          float career = patTofreq(datas[k].mPattern.name);
          
          /*決めウチのオシレーター数を超えないようのif文*/
          if ((k * l) + l < polyNum) {
            
            currentTone[(k * l) + l] = career;
            // ちょっと後で原因究明したいが、いったん変な値を汚く間引く
            currentX[(k * l) + l] = datas[k].x[l] > 0 && datas[k].x[l] < 2000 ? datas[k].x[l] : 0;
            currentY[(k * l) + l] = datas[k].y[l] > 0 && datas[k].y[l] < 2000 ? datas[k].y[l] : 0;
          }
        }
      }
      
//    float career = patTofreq(resData->mPattern.name);
      addOscCOunter ++;
      audioTick = false;
    }
    
    if (addOscCOunter % 43 == 42) {
      for (int i = 0; i < polyNum; i ++ ) {
        currentAdditiveTone[i] = currentTone[i] + (rand() % 10) ;
      }
      addOscCOunter = 0;
    }
    
    for(int m = 0; m < polyNum; m ++ ) {
      ADSRout = ADSR[m].line(6, adsrEnv);
      if (currentTone[m] != 0) {
        wave += oscbank[m].square(currentTone[m]);
        mymix.stereo(wave * ADSRout, outputs, (1.0 / (float)(currentX[m]) ) );
      }
      
      if (currentAdditiveTone[m] != 0) {
        wave2 += addOsc[m].sinewave(currentAdditiveTone[m]) * 0.001;
      }
      
    }
    
//    mymix.stereo(wave2, outputs, 0.5);
    lAudio[i] = output[i * nChannels] = outputs[0] + wave2;
    rAudio[i] = output[i * nChannels + 1] = outputs[1] + wave2;
  }
}

float gameOfLife::patTofreq(string patName) {
  if (freqMap.find(patName) == freqMap.end()) {
    // not found

    return 0.0;
  } else {
    // found

    return freqMap[patName];
  }
}

/**
 * Ensure it is a valid col/row combo (on grid) and
 * that this cell's currState is true
 */
int gameOfLife::currState(int col, int row) {
  return (col >= 0 && row >= 0 &&
          col < cols && row < rows &&
          grid[col][row].currState == true) ? 1 : 0;
}

/**
 * Checks for the number of neighbors that are in an active state
 */
int gameOfLife::getNumActiveNeighbors(int colIndex, int rowIndex) {
  int ret = 0;
  
  int prevCol = colIndex-1;
  int nextCol = colIndex+1;
  int prevRow = rowIndex-1;
  int nextRow = rowIndex+1;
  
  ret += currState(prevCol, prevRow);
  ret += currState(prevCol, rowIndex);
  ret += currState(prevCol, nextRow);
  
  ret += currState(colIndex, prevRow);
  ret += currState(colIndex, nextRow);
  
  ret += currState(nextCol, prevRow);
  ret += currState(nextCol, rowIndex);
  ret += currState(nextCol, nextRow);
  
  return ret;
}

void gameOfLife::goFullScreen() {
  active = false;
  ofToggleFullscreen();
  fullScreen = !fullScreen;
  if (fullScreen) {
    init(ofGetScreenWidth(), ofGetScreenHeight(), FULLSCREEN_CELLSIZE);
  } else {
    init(WIDTH, HEIGHT, CELLSIZE);
  }
}

void gameOfLife::pause() {
  active = false;
  clear();
}

void gameOfLife::mousePressed(int x, int y, int button) {
  int xcell = x/cellWidth;
	int ycell = y/cellHeight;
	grid[xcell][ycell].currState = !grid[xcell][ycell].currState;
}

void gameOfLife::keyPressed(int key) {
  switch (key) {
    case ' ':
      active = !active;
      break;
    case 'c':
      clear();
      break;
    case 'f':
      goFullScreen();
      break;
    case 'h':
      highlight = !highlight;
      break;
    case 'g':
      pause();
      patterns::gliderGun(grid, 2, 2);
      break;
    case 'p':
      pause();
      patterns::pufferTrain(grid, cols/2 - 10, rows - 30);
    default:
      break;
  }
}
