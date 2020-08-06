/* Your code here! */
#include <iostream>
#include "dsets.h"
#include "maze.h"
#include <vector>
#include "cs225/PNG.h"
#include <vector>
#include <queue>
using namespace std;
using namespace cs225;


SquareMaze::SquareMaze(){
}

void SquareMaze::makeMaze(int width, int height){
  width_ = width;
  height_ = height;
  int mazeSize = width * height;
  mazeSets.addelements(mazeSize);
  for(int i = 0; i < mazeSize; i++){
    rightWalls.push_back(true);
    downWalls.push_back(true);
  }
  int x, y, cur;
  while(mazeSets.size(0) < mazeSize){
    x = rand() % width_;
    y = rand() % height_;
    cur = y * width_ + x;
    if(rand() % 2 == 0){
      if(x < width_ - 1){
        if(mazeSets.find(cur) != mazeSets.find(cur + 1)){
          setWall(x, y, 0, false);  //or use setWall
          mazeSets.setunion(cur, cur + 1);
        }
      }
    }
    else{
      if(y < height_ - 1){
        if(mazeSets.find(cur) != mazeSets.find(cur + width_)){
          setWall(x, y, 1, false);
          mazeSets.setunion(cur, cur + width_);
        }
      }
    }
  }

}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  int cur = y * width_ + x;
  if(dir == 0){//Either 0 (right) or 1 (down)
    rightWalls[cur] = exists;
  }
  else if(dir == 1){
    downWalls[cur] = exists;
  }
}


bool SquareMaze::canTravel(int x, int y, int dir) const {
  /**
  dir = 0 represents a rightward step (+1 to the x coordinate)
  dir = 1 represents a downward step (+1 to the y coordinate)
  dir = 2 represents a leftward step (-1 to the x coordinate)
  dir = 3 represents an upward step (-1 to the y coordinate)
  */
  int cur = y * width_ + x;
	if (dir == 0) {
		if (x >= width_ - 1) {
      return false;
    }
		return !rightWalls[cur];
	}
  if (dir == 1) {
		if (y >= height_ - 1) {
      return false;
    }
		return !downWalls[cur];
	}
	// check left
  if (dir == 2) {
		if (x <= 0) {return false;
    }
		return  !rightWalls[cur - 1];
	}
	// check up
  if (dir == 3) {
		if (y <= 0) {
      return false;
    }
		return !downWalls[cur - width_];
	}
  return false;
}


vector<int> SquareMaze::solveMaze(){
    int x;
    int y;
    int cur;
    int totalsize = width_ * height_;
    queue<int> bfsqueue;
    vector<pair<int, int>> prev_distance;
    prev_distance.push_back(pair<int, int>(0,0));
    for(int i = 1; i < totalsize; i++){
      prev_distance.push_back(pair<int, int>(-1,0));
    }
    bfsqueue.push(0);
    while(!bfsqueue.empty()){
      cur = bfsqueue.front();
      x = cur % width_;
      y = cur / width_;
      if(canTravel(x, y, 0) && (prev_distance[cur + 1].first == -1)){
          bfsqueue.push(cur + 1);
          prev_distance[cur + 1].first = cur;
          prev_distance[cur + 1].second = prev_distance[cur].second + 1;
      }
      if(canTravel(x, y, 1) && prev_distance[cur + width_].first == -1){
          bfsqueue.push(cur + width_);
          prev_distance[cur + width_].first = cur;
          prev_distance[cur + width_].second = prev_distance[cur].second + 1;
      }
      if(canTravel(x, y, 2) && prev_distance[cur - 1].first == -1){
          bfsqueue.push(cur - 1);
          prev_distance[cur - 1].first = cur;
          prev_distance[cur - 1].second = prev_distance[cur].second + 1;

      }
      if(canTravel(x, y, 3)&& prev_distance[cur - width_].first == -1){
          bfsqueue.push(cur - width_);
          prev_distance[cur - width_].first = cur;
          prev_distance[cur - width_].second = prev_distance[cur].second + 1;

      }
      bfsqueue.pop();
    }
    int longest_path = totalsize - width_;
    for(int k = 0; k < width_; k++){
      if(prev_distance[totalsize - width_ + k].second > prev_distance[longest_path].second){
        longest_path = totalsize - width_ + k;
      }
    }
    destination = longest_path;
    vector<int> toreturn;
    cur = destination;
    while(cur != 0){
      if(prev_distance[cur].first == cur - 1){
        toreturn.push_back(0);
      }
      if(prev_distance[cur].first == cur - width_){
        toreturn.push_back(1);
      }
      if(prev_distance[cur].first == cur + 1){
        toreturn.push_back(2);
      }
      if(prev_distance[cur].first == cur + width_){
        toreturn.push_back(3);
      }
      cur = prev_distance[cur].first;
    }
    reverse(toreturn.begin(), toreturn.end());

  return toreturn;

}



PNG* SquareMaze::drawMaze() const{
  /**
  First, create a new PNG.
  Set the dimensions of the PNG to (width*10+1,height*10+1).
  where height and width were the arguments to makeMaze.
  Blacken the entire topmost row and leftmost column of pixels,
   except the entrance (1,0) through (9,0).
   For each square in the maze,
   call its maze coordinates (x,y).
   If the right wall exists,
   then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10.
   If the bottom wall exists,
   then blacken the pixels with coordinates (x*10+k,
   (y+1)*10) for k from 0 to 10.*/
  int canvas_width = width_ * 10 + 1;
  int canvas_height = height_ * 10 + 1;
  // int cur = y * width_ + x;
  PNG* canvas = new PNG(canvas_width, canvas_height);
  for(int x = 0; x < canvas_width; x++){
    for(int y = 0; y < canvas_height; y++){
      if((y == 0 && x >= 10) || (x == 0)) {
        HSLAPixel& p = canvas->getPixel(x, y);
        p.l = 0;
      }
    }
  }
  for(int x = 0; x < width_; x++){
    for(int y = 0; y < height_; y++){
      if(rightWalls[y * width_ + x] == true){
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel((x + 1) * 10, y * 10 + k);
          p.l = 0;
        }
      }
      if(downWalls[y * width_ + x] == true){
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel(x * 10 + k, (y + 1) * 10);
          p.l = 0;
        }
      }
    }
  }
  return canvas;
}


PNG* SquareMaze::drawMazeWithSolution(){
  PNG* canvas = drawMaze();
  vector<int> solution = solveMaze();
  int x = 5;
  int y = 5;
  for(int k = 1; k < 10; k++){
    HSLAPixel& p = canvas->getPixel(destination % width_ * 10 + k, (destination / height_ + 1) * 10);
    p.l = 1;
  }
  for(size_t i = 0; i < solution.size(); i++){
      if(solution[i] == 0) {
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel(x + k, y);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        x += 10;
      }
      else if(solution[i] == 1) {
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel(x, y + k);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        y += 10;
      }
      else if(solution[i] == 2) {
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel(x - k, y);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        x -= 10;
      }
      else if(solution[i] == 3) {
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel(x, y - k);
          p.h = 0;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
        y -= 10;
      }
    }
  return canvas;
}

PNG* SquareMaze::drawCreativeMaze(){
  int canvas_width = width_ * 10 + 1;
  int canvas_height = height_ * 10 + 1;
  PNG* canvas = new PNG(canvas_width, canvas_height);
  for(int y = 0; y < int(canvas_height); y++){
    HSLAPixel& p = canvas->getPixel(0, y);
    p.l = 0;  //Blacken
  }
  for(int y = 3 * int(canvas_height); y < canvas_height; y++){
    HSLAPixel& p = canvas->getPixel(0, y);
    p.l = 0;  //Blacken
  }
  for(int x = 10; x < canvas_width; x++){
    HSLAPixel& p = canvas->getPixel(x, 0);
    p.l = 0;  //Blacken
  }


  for(int x = 0; x < width_; x++){
    for(int y = 0; y < int(height_ / 4); y++){
          if(rightWalls[y * width_ + x]){
            //blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10
            for(int k = 0; k <= 10; k++){
              HSLAPixel& p = canvas->getPixel((x + 1) * 10, y * 10 + k);
              p.h = 50;
              p.s = 1;
              p.l = 0.5;
              p.a = 1;
            }
          }
          if(downWalls[y * width_ + x]){
            //blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10
            for(int k = 0; k <= 10; k++){
              HSLAPixel& p = canvas->getPixel(x * 10 + k, (y + 1) * 10);
              p.h = 5;
              p.s = 1;
              p.l = 0.5;
              p.a = 1;
            }
          }
    }
    for(int y = 3 * int(height_ / 4); y < height_; y++){
          if(rightWalls[y * width_ + x]){
            //blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10
            for(int k = 0; k <= 10; k++){
              HSLAPixel& p = canvas->getPixel((x + 1) * 10, y * 10 + k);
              p.h = 150;
              p.s = 1;
              p.l = 0.5;
              p.a = 1;
            }
          }
          if(downWalls[y * width_ + x]){
            for(int k = 0; k <= 10; k++){
              HSLAPixel& p = canvas->getPixel(x * 10 + k, (y + 1) * 10);
              p.h = 22;
              p.s = 1;
              p.l = 0.5;
              p.a = 1;
            }
          }
    }
  }





  for(int x = 0; x < int(width_ / 3); x++){
    for(int y = int(height_ / 4); y < 3 * int(height_ / 4); y++){
      if(rightWalls[y * width_ + x]){
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel((x + 1) * 10, y * 10 + k);
          p.h = 127;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
      }
      if(downWalls[y * width_ + x]){
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel(x * 10 + k, (y + 1) * 10);
          p.h = 235;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
      }
    }
  }
  for(int x = int(width_)*2 /3 ; x < int(width_); x++){
    for(int y = int(height_ / 4); y < 3 * int(height_ / 4); y++){
      if(rightWalls[y * width_ + x]){
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel((x + 1) * 10, y * 10 + k);
          p.h = 190;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
      }
      if(downWalls[y * width_ + x]){
        for(int k = 0; k <= 10; k++){
          HSLAPixel& p = canvas->getPixel(x * 10 + k, (y + 1) * 10);
          p.h = 40;
          p.s = 1;
          p.l = 0.5;
          p.a = 1;
        }
      }
    }
  }


  return canvas;
}
