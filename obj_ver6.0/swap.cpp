#include <iostream>
#include "opencv2/opencv.hpp"
#include "./modules/Obj_img.h"
#include <stdio.h>

using namespace std;
using namespace cv;

/*****************************************************************
* ROUTINES
******************************************************************/
Object_img redUSB("USB",0001);

int var1=1;
Point pos;
int radius = 20;
int range = 30;
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if( event == EVENT_LBUTTONDOWN )
    {
        pos.x=x;
        pos.y=y;
        var1=0;


    Mat selec = redUSB.HSV_img;
    int countPixel = 0;
    int h_var = 0, s_var=0, v_var=0;
    for(int var2=pos.y-radius;var2<=pos.y+radius;var2++)
    for(int var3=pos.x-radius;var3<=pos.x+radius;var3++)
    {
        Vec3b intensity = selec.at<Vec3b>(var2,var3);   
        h_var += intensity.val[0];
        s_var += intensity.val[1];
        v_var += intensity.val[2];
        countPixel++;
    } 
    h_var = h_var/countPixel;
    s_var = s_var/countPixel;
    v_var = v_var/countPixel;

    redUSB.setHueRange((h_var - range) < 0? 0:(h_var - range) ,(h_var + range) > 255? 255:(h_var + range));
    redUSB.setSatRange((s_var - range) < 0? 0:(s_var - range) ,(s_var + range) > 255? 255:(s_var + range));
    redUSB.setValRange((v_var - 4*range) < 0? 0:(v_var - 4*range) ,(v_var + 4*range) > 255? 255:(v_var + 3*range));
    redUSB.setMorphology(1,4);

    }
    else if(event == CV_EVENT_MOUSEMOVE)
    {
        pos.x=x;
        pos.y=y;
    }
}

/*****************************************************************
 * MAIN
 *****************************************************************/
//Main program
int main (void)
{
  // Create a VideoCapture object to capture image from camera
  // Change the initial parameter to select the right camera
  VideoCapture cap(0);

  // Check if camera is opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video device" << endl;
    return -1;
  }


  Mat frame; 

  namedWindow("Live view", WINDOW_AUTOSIZE);
  namedWindow("Result", WINDOW_AUTOSIZE);
  namedWindow("hao",WINDOW_AUTOSIZE);
  createTrackbar("erode", "Result", &redUSB.erodeLevel, 10, NULL);
  createTrackbar("dilate", "Result", &redUSB.dilateLevel, 10, NULL);
  
  /*
  while(var1==1)
  {
      //set the callback function for any mouse event
      

      cap >> frame;
      
      // If the frame object is empty, there is a problem with stream
      if (frame.empty())
            break;
      
      // Display the current frame
          
      redUSB.updateImg(frame);
      redUSB.processing();
      //redUSB.fastprocessing(redUSB.HSV_img);
      //show the image
      
      imshow("Live view", redUSB.RGB_img);
      imshow("Result", redUSB.Obj_img);
      // Wait until user press some key
      waitKey(10);    
  }

 
*/
      

  //createTrackbar("Min H", "Result", &redUSB.H_min, 255, NULL);
  //createTrackbar("Max H", "Result", &redUSB.H_max, 255, NULL);
  //createTrackbar("Min S", "Result", &redUSB.S_min, 255, NULL);
  //createTrackbar("Max S", "Result", &redUSB.S_max, 255, NULL);
  //createTrackbar("Min V", "Result", &redUSB.V_min, 255, NULL);
  //createTrackbar("Max V", "Result", &redUSB.V_max, 255, NULL);
 

  
  while(1){
    // Create object to handle image
    // Get camera frame
    setMouseCallback("Live view", CallBackFunc, NULL);

    cap >> frame;

    // If the frame object is empty, there is a problem with stream
    if (frame.empty())
      break;

    // Display the current frame
    
    redUSB.updateImg(frame);
    redUSB.processing();
    //redUSB.fastprocessing(redUSB.HSV_img);
    point_2D position;
    if(redUSB.isObjExist() == true){
        position = redUSB.getPosition(POINT_ROOT);
        printf("(%lf, %lf)\n", position.getX(), position.getY());
    }
    else 
      printf("error \n");

    // Display the result
    circle(redUSB.RGB_img, Point(pos.x, pos.y), radius, Scalar( 0, 255, 0 ), 2, 8);
    circle(redUSB.RGB_img, Point( position.getX(), -position.getY()), 50, Scalar( 0, 255, 0 ), 2, 8);
    imshow("Live view", redUSB.RGB_img);
    imshow("Result", redUSB.Obj_img);
    imshow("hao",redUSB.HSV_selected_img);

    // Get the input from keyboard
    char c = (char)waitKey(25);
    
    // If the ESC key is pressed, terminate program
    if(c==27)
      break;
    waitKey(10); 
  }

  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();

  return 0;
}