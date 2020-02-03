#include <stdio.h>
#include <string.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "point_2Dmaster.h"
using namespace cv;
using namespace std;
struct HSV_range{
    int H_max;
    int H_min;
    int V_max;
    int V_min;
    int S_max;
    int S_min;
};

class Object_img
{
public:
    String name;
    int id;

    Mat RGB_img;
    Mat HSV_img;
    Mat HSV_selected_img;
    Mat Obj_img;
    point_2D Obj_position;
    bool ObjExistance;

    Object_img(String name, int Id);
    ~Object_img();

    void setHueRange(int min, int max);
    void setValRange(int min, int max);
    void setSatRange(int min, int max);
    void setHSVRange(HSV_range range);
    void setMorphology(int erodeLevel, int dilate);

    void updateImg(Mat img);
    void processing();
    void fastprocessing(Mat HSV_img);
    
    Mat getArea();
    Mat getBorder();
    bool isObjExist();
    void updatePosition();
    point_2D getPosition(vector_2D root);
    point_2D getPosition(point_2D root);

    struct HSV_range color;
    
    int erodeLevel;
    int dilateLevel;
    int blurLevel;

    Mat cancelNoise(Mat img);
    Mat pickObject(Mat img);
private:
};