#include <iostream>
#include <time.h>
#include "opencv2/opencv.hpp"
#include "./modules/Obj_img.h"
#include <stdio.h>

using namespace std;
using namespace cv;

/*****************************************************************
* ROUTINES
******************************************************************/
Mat frame;
int main (void)
{
    VideoCapture cap;

    cap.open("./Video1.wmv");
    if(!cap.isOpened()){
    cout << "Error opening video device" << endl;
    while(1);
    }

    Object_img newObject("this",23);

    struct HSV_range color;
        color.H_min = 35;
        color.H_max = 75;
        color.S_min = 141;
        color.S_max = 181;
        color.V_min = 77;
        color.V_max = 217;


        newObject.setHSVRange(color);
        newObject.setMorphology(0,0);
    

    point_2D center_img(320, -240, VECTOR_ROOT);
    point_2D Y_axis(0,1,center_img);
    point_2D position;

    clock_t t1,t2;
    long count = 0;
    t1=clock();

        while(1){
        count++;
        cap >> frame;
        if (frame.empty())
            break;
        newObject.updateImg(frame);
        newObject.processing();
        if(newObject.isObjExist() == true){
            position = newObject.getPosition(center_img);
            printf("(roll: %lf, pitch: %lf, yaw: %lf ) | \n ", position.getX(), position.getY(), position.angleDir(Y_axis, center_img));
        }
    else{
                printf("error \n");
        }
    }
    t2=clock();
    float diff = ((float)t2-(float)t1);
    double fps = (double)count / ((double)diff / CLOCKS_PER_SEC);
    cout << fps <<endl;
}

