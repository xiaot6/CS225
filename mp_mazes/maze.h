/* Your code here! */
#pragma once
#include "dsets.h"
#include <vector>
#include "cs225/PNG.h"
#include <iostream>
using namespace std;
using namespace cs225;


class SquareMaze{
public:
  SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  vector<int> solveMaze();
  void setWall(int x, int y, int dir, bool exists);
  PNG* drawMaze() const;
  PNG* drawMazeWithSolution();


  PNG* drawCreativeMaze();

  int width_;
  int height_;
  int destination;
  DisjointSets mazeSets;
  vector<bool> rightWalls;
  vector<bool> downWalls;

};
