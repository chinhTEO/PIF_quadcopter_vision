#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "Obj_img.h"

using namespace cv;
using namespace std;

class Obj_ctrl{
public:
    vector<Object_img> Obj_list;
    Mat RGB_img;
    Mat HSV_img;

    Obj_ctrl();
    ~Obj_ctrl();
    
    void add(String name,int Id, HSV_range range);
    void del(int Id);

    void updateImg(Mat img);
    void updateObjHSV(int Id, HSV_range range);

    void processing();
    void fastProcessing();

    Mat getImg(int Id);
    point_2D getPosition(int Id, point_2D root);
    point_2D getPosition(int Id, vector_2D root);
};