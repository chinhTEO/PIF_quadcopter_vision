#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "Obj_ctrl.h"

using namespace cv;
using namespace std;

class windownActionAndView{
public:
	Obj_ctrl Obj_controller;
	int Obj_idcount;

	VideoCapture cap;
	Mat frame;

	Point pos;
	int radius;
	int range;

	windownActionAndView();
	~windownActionAndView();
	
	void mouse_callback(int event, int x, int y, int flags, void* userdata);
	
	bool init();

	bool run();

};