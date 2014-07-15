//
//  patterns.cpp
//  conway
//
//  Created by Chris Roby on 6/2/12.
//  Copyright (c) 2012 Chris Roby, 70bpm, LLC. All rights reserved.
//

#include "patterns.h"

void patterns::gliderGun(cell **grid, int startPosX, int startPosY) {
  // left box
  grid[startPosX+1][startPosY+5].currState = true;
  grid[startPosX+1][startPosY+6].currState = true;
  grid[startPosX+2][startPosY+5].currState = true;
  grid[startPosX+2][startPosY+6].currState = true;
  
  // left middle of gun
  grid[startPosX+11][startPosY+5].currState = true;
  grid[startPosX+11][startPosY+6].currState = true;
  grid[startPosX+11][startPosY+7].currState = true;
  grid[startPosX+12][startPosY+4].currState = true;  
  grid[startPosX+12][startPosY+8].currState = true;
  grid[startPosX+13][startPosY+3].currState = true;
  grid[startPosX+13][startPosY+9].currState = true;
  grid[startPosX+14][startPosY+3].currState = true;
  grid[startPosX+14][startPosY+9].currState = true;
  grid[startPosX+15][startPosY+6].currState = true;
  grid[startPosX+16][startPosY+4].currState = true;
  grid[startPosX+16][startPosY+8].currState = true;
  grid[startPosX+17][startPosY+5].currState = true;
  grid[startPosX+17][startPosY+6].currState = true;
  grid[startPosX+17][startPosY+7].currState = true;
  grid[startPosX+18][startPosY+6].currState = true;
  
  // right middle of gun
  grid[startPosX+21][startPosY+3].currState = true;
  grid[startPosX+21][startPosY+4].currState = true;
  grid[startPosX+21][startPosY+5].currState = true;
  grid[startPosX+22][startPosY+3].currState = true;
  grid[startPosX+22][startPosY+4].currState = true;
  grid[startPosX+22][startPosY+5].currState = true;
  grid[startPosX+23][startPosY+2].currState = true;
  grid[startPosX+23][startPosY+6].currState = true; 
  grid[startPosX+25][startPosY+1].currState = true;
  grid[startPosX+25][startPosY+2].currState = true;
  grid[startPosX+25][startPosY+6].currState = true;
  grid[startPosX+25][startPosY+7].currState = true;    
  
  // right block
  grid[startPosX+35][startPosY+3].currState = true;
  grid[startPosX+35][startPosY+4].currState = true;
  grid[startPosX+36][startPosY+3].currState = true;
  grid[startPosX+36][startPosY+4].currState = true;
}

void patterns::pufferTrain(cell **grid, int startPosX, int startPosY) {
  grid[startPosX+1][startPosY+2].currState = true;
  grid[startPosX+2][startPosY+1].currState = true;
  grid[startPosX+3][startPosY+1].currState = true;
  grid[startPosX+3][startPosY+5].currState = true;
  grid[startPosX+4][startPosY+1].currState = true;
  grid[startPosX+4][startPosY+2].currState = true;
  grid[startPosX+4][startPosY+3].currState = true;
  grid[startPosX+4][startPosY+4].currState = true;
  
  grid[startPosX+8][startPosY+5].currState = true;
  grid[startPosX+9][startPosY+3].currState = true;
  grid[startPosX+9][startPosY+4].currState = true;
  grid[startPosX+10][startPosY+3].currState = true;
  grid[startPosX+11][startPosY+3].currState = true;
  grid[startPosX+12][startPosY+4].currState = true;
  
  grid[startPosX+15][startPosY+2].currState = true;
  grid[startPosX+16][startPosY+1].currState = true;
  grid[startPosX+17][startPosY+1].currState = true;
  grid[startPosX+17][startPosY+5].currState = true;
  grid[startPosX+18][startPosY+1].currState = true;
  grid[startPosX+18][startPosY+2].currState = true;
  grid[startPosX+18][startPosY+3].currState = true;
  grid[startPosX+18][startPosY+4].currState = true;
}
