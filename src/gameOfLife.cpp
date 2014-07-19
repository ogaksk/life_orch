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
        detect1->detection(grid);
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
    int g1[] = {1, 3};
    int p1[] = {2, 1, 1};
    string n1 = "aaa";
    detect1 = new patternDetect(n1, g1, p1);
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
