#include "windownView.h"

windownActionAndView::windownActionAndView(){}
windownActionAndView::~windownActionAndView(){}

bool windownActionAndView::init(){
  Obj_idcount = 0;
  radius = 20;
  range = 20;

  cap.open(0);
  // Check if camera is opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video device" << endl;
    return false;
  }

  cap.set(CV_CAP_PROP_FRAME_WIDTH,1280);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT,720);
  namedWindow("Live view", WINDOW_AUTOSIZE);
  createTrackbar("radius", "Live view", &radius,100, NULL);
  createTrackbar("range", "Live view",  &range, 50, NULL);

  return true;
}

void windownActionAndView::mouse_callback(int event, int x, int y, int flags, void* userdata){
	if( event == EVENT_LBUTTONDOWN ){
      // del the Obj
      point_2D clickedPoint(x, -y, VECTOR_ROOT);
      for(int i = 0; i < Obj_controller.Obj_list.size(); i++){
        clickedPoint = clickedPoint.changeCoordinateTo(Obj_controller.Obj_list.at(i).getPosition(VECTOR_ROOT));
        if(clickedPoint.getRadius() < 50){
            destroyWindow(Obj_controller.Obj_list.at(i).name);
            Obj_controller.Obj_list.erase(Obj_controller.Obj_list.begin() + i);
            return;
        }
      }

      // create object;
    	Obj_idcount++;
    	Object_img newObject(to_string(Obj_idcount),Obj_idcount);
   
      pos.x=x;
      pos.y=y;

	    Mat selec = Obj_controller.HSV_img;
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

	    struct HSV_range color;
	    color.H_min = (h_var - range) < 0? 0:(h_var - range);
	    color.H_max = (h_var + range) > 255? 255:(h_var + range);
	    color.S_min = (s_var - range) < 0? 0:(s_var - range);
	    color.S_max = (s_var + range) > 255? 255:(s_var + range);
	    color.V_min = (v_var - 4*range) < 0? 0:(v_var - 4*range);
	    color.V_max = (v_var + 4*range) > 255? 255:(v_var + 3*range);


	    newObject.setHSVRange(color);
	    newObject.setMorphology(1,4);

	    Obj_controller.Obj_list.push_back(newObject);
	    namedWindow(to_string(Obj_idcount), WINDOW_AUTOSIZE);

	    for(int i = 0; i < Obj_controller.Obj_list.size(); i++){
        	if(Obj_controller.Obj_list.at(i).id == Obj_idcount){
            createTrackbar("erode", to_string(Obj_idcount), &Obj_controller.Obj_list.at(i).erodeLevel, 10, NULL);
            createTrackbar("dilate",to_string(Obj_idcount), &Obj_controller.Obj_list.at(i).dilateLevel, 10, NULL);
  			    createTrackbar("Min H", to_string(Obj_idcount), &Obj_controller.Obj_list.at(i).color.H_min, 255, NULL);
  		  		createTrackbar("Max H", to_string(Obj_idcount), &Obj_controller.Obj_list.at(i).color.H_max, 255, NULL);
  		  		createTrackbar("Min S", to_string(Obj_idcount), &Obj_controller.Obj_list.at(i).color.S_min, 255, NULL);
  		  		createTrackbar("Max S", to_string(Obj_idcount), &Obj_controller.Obj_list.at(i).color.S_max, 255, NULL);
  		  		createTrackbar("Min V", to_string(Obj_idcount), &Obj_controller.Obj_list.at(i).color.V_min, 255, NULL);
  		  		createTrackbar("Max V", to_string(Obj_idcount), &Obj_controller.Obj_list.at(i).color.V_max, 255, NULL);
	  		}
      }
    }
    else if(event == CV_EVENT_MOUSEMOVE){
      pos.x=x;
      pos.y=y;
    }
    else if(event == EVENT_RBUTTONDOWN){
    }
}

bool windownActionAndView::run(){
	//setMouseCallback("Live view", this->mouse_callback, NULL);
  cap >> frame;

	if (frame.empty())
      return false;


    Obj_controller.updateImg(frame);
  	Obj_controller.processing();

  	for(int i = 0; i < Obj_controller.Obj_list.size(); i++){
  		point_2D position;
    	if(Obj_controller.Obj_list.at(i).isObjExist() == true){
        	position = Obj_controller.Obj_list.at(i).getPosition(POINT_ROOT);
          circle(frame, Point( position.getX(), -position.getY()), 50, Scalar( 0, 255, 0 ), 2, 8);
        	printf("(%lf, %lf) | ", position.getX(), position.getY());
   		 }
    	else 
      		printf("error \n");
  		imshow(Obj_controller.Obj_list.at(i).name, Obj_controller.Obj_list.at(i).HSV_selected_img);
  	}

  	printf("\n");
  	circle(frame, Point(pos.x, pos.y), radius, Scalar( 0, 255, 0 ), 2, 8);
  	imshow("Live view", frame);
  	waitKey(10); 
  	return true;
}