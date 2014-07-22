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
patternDetect *detect1;

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
  
  myImage.loadImage("test.jpg");
  
  sender.setup(HOST, PORT);
  
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
    }
}

/*今は参照渡し風に書いている　複数のインスタンスを渡してバグが生まれたら対応*/
void gameOfLife::oscSending(resPattern &datas) {
  std::stringstream result_x, result_y;
  std::copy(datas.x.begin(), datas.x.end(), std::ostream_iterator<int>(result_x, ","));
  std::copy(datas.y.begin(), datas.y.end(), std::ostream_iterator<int>(result_y, ","));
  
  ofxOscMessage mx, my;
  string textName = "/";
  textName += datas.patternName;
  textName += "/";
  string textX = textName + "x";
  string textY = textName + "y";
  
  mx.setAddress(textX);
  mx.addStringArg( result_x.str() );
  
  my.setAddress( textY );
  my.addStringArg( result_y.str() );
  
  //メッセージを送信
  sender.sendMessage( mx );
  sender.sendMessage( my );
}

void gameOfLife::drawingResPatterns(resPattern &datas, matchPattern &mPattern) {
//  glEnable(GL_BLEND);
  
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  if (datas.x.size() != 0) {
    /* datas.xの配列をイテレートする必要がある */
    /* 今はx[0]だけでためしにやる */
    /*なんか配列操作がおかしいので見直す*/
    for (int h=0; h < datas.x.size(); h++) {
      for (int i=0; i< mPattern.patternGrid[0]; i++) {
        for (int j=0; j < mPattern.patternGrid[1]; j++) {
//          ofSetColor(200, 200, 200);
          ofNoFill();
          if (mPattern.pattern[mPattern.patternGrid[0] * i + j ] == 1) {
            ofSetColor(250, 100, 30, 40);
            ofFill();
            ofRect( (i + datas.x[h]) * cellWidth, (j + datas.y[h]) * cellHeight, cellWidth, cellHeight);
          }
        }
      }
    }
  }
}
  

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
                thisCell->color = ofColor::black;
            } else if (currState == false && activeNeighbors == 3) {
                thisCell->nextState = true;
                thisCell->color = highlight ? ofColor::green : ofColor::black;
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
	for (int i=0; i<cols; i++) {
		for (int j=0; j<rows; j++) {
      cell thisCell = grid[i][j];
			ofSetColor(200, 200, 200);
			ofNoFill();
			ofRect(i*cellWidth, j*cellHeight, cellWidth, cellHeight);
      if (thisCell.currState == true) {
				ofSetColor(thisCell.color.r, thisCell.color.g, thisCell.color.b, 100);
				ofFill();				
  			ofRect(i*cellWidth, j*cellHeight, cellWidth, cellHeight);
				ofNoFill();
			}
		}
	}
  
  /*パターン検出インスタンスの実行メソッド*/
  resPattern datas = detect1->detection(grid, rows, cols);
  oscSending(datas);
  ofEnableBlendMode(OF_BLENDMODE_SCREEN);
  drawingResPatterns(datas, detect1->mPattern);
  ofEnableBlendMode(OF_BLENDMODE_DISABLED);
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

/**
 * 検出パターンを初期化するメソッド
*/
 
void gameOfLife::patternMapping() {
    int grid1[] = {1, 3};
    int pat1[] = {1, 1, 1};
    string name1 = "aaa";
    detect1 = new patternDetect(name1, grid1, pat1);
//    cout << detect1->mPattern.name << endl;
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
