
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG image;  image.readFromFile("myPNG.png");
  FloodFilledImage pic(image);
  //use both traversals to fill image
  DFS d(image, Point(150, 150), .3);
  BFS b(image, Point(70, 60), .3);
  MyColorPicker c1(7);
  //two different colorpickers to fill image
  MyColorPicker c2(5);
  //fill image using both traversals
  pic.addFloodFill(d, c2);
  pic.addFloodFill(b, c1);

  Animation animation = pic.animate(1100);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");



  return 0;
}
