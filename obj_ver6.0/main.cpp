#include <iostream>
#include "opencv2/opencv.hpp"
#include "./modules/windownView.h"
#include <stdio.h>

using namespace std;
using namespace cv;

/*****************************************************************
* ROUTINES
******************************************************************/
windownActionAndView myView;
void mouse_callback(int event, int x, int y, int flags, void* userdata){
    myView.mouse_callback(event,x,y,flags, userdata);
}


int main (void)
{
  if(myView.init() == false){
    cout << "Error opening video device" << endl;
    return -1;
  }
  while(1){
    setMouseCallback("Live view", mouse_callback, NULL);
    if(myView.run() == false){
      cout << "Error opening video device" << endl;
      return -1;
    }
  }

  // When everything done, release the video capture object
  myView.cap.release();

  // Closes all the frames
  destroyAllWindows();

  return 0;
}