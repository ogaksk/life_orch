/*
 *  gameOfLife.h
 *  conway
 *
 *  Created by Chris Roby on 3/26/10.
 *  Copyright (c) 2012 Chris Roby, 70bpm, LLC. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

struct cell {
	bool currState;
	bool nextState;
	int activeNeighbors;
	ofColor color;
};

class gameOfLife : public ofBaseApp {
  
public:
  void setup();
  void init(int width, int height, int cellsize);
  
  void tick();
  void update();
  void draw();
  void clear();
  void pause();
  
  void keyPressed(int key);
  void mousePressed(int x, int y, int button);
  
  bool active;
  
private:
  cell **grid;
  int rows, cols;
  float cellWidth, cellHeight;
  bool fullScreen, highlight;

  int getNumActiveNeighbors(int colIndex, int rowIndex);
  int currState(int colIndex, int rowIndex);

  void makeNextStateCurrent();
  void goFullScreen();
};
