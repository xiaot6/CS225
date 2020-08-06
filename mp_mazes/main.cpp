#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze maze;
    maze.makeMaze(120, 120);
    PNG* canvas = maze.drawCreativeMaze();
    canvas->writeToFile("creative.png");
    cout << "creative maze created" << endl;
    return 0;
}
