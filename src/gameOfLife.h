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
#include "ofxOsc.h"
#include "ofxMaxim.h"


#define HOST "localhost" //送信先ホストのIPを設定
#define PORT 8000 //送信先のポート番号を設定

struct cell {
	bool currState;
	bool nextState;
	int activeNeighbors;
	ofColor color;
};


struct matchPattern {
  string name;
  ofColor color;
  int patternGrid[2]; // ポインタ指定するとこけなかった 謎
  int *pattern;
};

struct resPattern {
//  string patternName;
  matchPattern mPattern;
	vector<int> x;
  vector<int> y;
};

class gameOfLife : public ofBaseApp {
  
public:
  void setup();
  void init(int width, int height, int cellsize);
  
  void tick();
  void update();
  void draw();
  void clear();
  void patternMapping();
  void oscSending(vector<resPattern> &datas);
  void drawingResPatterns(vector<resPattern> &datas);
  void pause();
  
  void keyPressed(int key);
  void mousePressed(int x, int y, int button);
  int rows, cols;
  
  bool active;
  
  /************************/
  // ofxMaximまわり変数宣言 //
  /***********************/
  void audioOut(float * output, int bufferSize, int nChannels);
  void audioSetup();
  float patTofreq(string patName);
  int initialBufferSize;
  int sampleRate;
  int mode;
  double wave, sample, ADSRout, outputs[2];
  ofxMaxiMix mymix;
  ofxMaxiOsc osc;
  ofxMaxiEnvelope ADSR;
  double adsrEnv[6]={0, 3, 0.1, 10, 0, 40};
  vector <ofxMaxiOsc> oscbank;
  vector <float> lAudio;
  vector <float> rAudio;
  
  std::map<std::string, float> freqMap;
  bool audioTick = false;
  
private:
  cell **grid;
  float cellWidth, cellHeight;
  bool fullScreen, highlight;

  int getNumActiveNeighbors(int colIndex, int rowIndex);
  int currState(int colIndex, int rowIndex);
  

  void makeNextStateCurrent();
  void goFullScreen();
    
  ofxOscSender sender;
};
