#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image happy;
  happy.readFromFile("./happy.png");
  Image sad;
  sad.readFromFile("./sad.png");
  Image mistake;
  mistake.readFromFile("./mistake.png");

  Image passed;
  passed.readFromFile("./passed.png");
  Image output;
  sad.scale(10);
  mistake.scale(0.5);
  happy.scale(3.5);

  StickerSheet x = StickerSheet(sad,3);
  x.addSticker(mistake,4500,2500);
  x.addSticker(happy,300,2000);
  x.addSticker(passed,100,3000);
  output = x.render();

  output.writeToFile("myImage.png");




  return 0;
}
