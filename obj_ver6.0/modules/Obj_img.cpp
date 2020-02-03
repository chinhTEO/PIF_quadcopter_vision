#include "Obj_img.h"

Object_img::Object_img(String name, int id){
    this->name = name;
    this->id = id;
}
Object_img::~Object_img(){}

void Object_img::setHueRange(int min, int max){
    this->color.H_max = max;
    this->color.H_min = min;
}
void Object_img::setValRange(int min, int max){
    this->color.V_max = max;
    this->color.V_min = min;
}
void Object_img::setSatRange(int min, int max){
    this->color.S_max = max;
    this->color.S_min = min;
}

void Object_img::setHSVRange(HSV_range range){
    this->color = range;
}

void Object_img::setMorphology(int erodeLevel, int dilateLevel){
    this->erodeLevel = erodeLevel;
    this->dilateLevel = dilateLevel;
}

void Object_img::processing(){
    Mat OBJ_buffer_img;
    inRange(this->HSV_img,  Scalar(this->color.H_min, this->color.S_min, this->color.V_min),
                      Scalar(this->color.H_max, this->color.S_max, this->color.V_max), OBJ_buffer_img);
    this->HSV_selected_img = cancelNoise(OBJ_buffer_img);
    this->Obj_img = pickObject(this->HSV_selected_img);
    updatePosition();
}

void Object_img::fastprocessing(Mat HSV_img){
    Mat OBJ_buffer_img;
    inRange(HSV_img,  Scalar(this->color.H_min, this->color.S_min, this->color.V_min),
                      Scalar(this->color.H_max, this->color.S_max, this->color.V_max), OBJ_buffer_img);
    this->Obj_img = pickObject(OBJ_buffer_img);
    updatePosition();
}

Mat Object_img::getArea(){

}
Mat Object_img::getBorder(){

}
void Object_img::updatePosition(){
    int sumAllWhitePixRow = 0, sumAllWhitePixCol = 0, avrRow=0, avrCol=0;
    int countWhitePix = 0;

    for(int i = 0; i < Obj_img.rows; i++)
        for(int j = 0; j < Obj_img.cols; j++)
            if(Obj_img.at<char>(i,j) != 0){
                sumAllWhitePixRow += i;
                sumAllWhitePixCol += j;
                countWhitePix++;
            }
    if(countWhitePix != 0){
        avrRow = (double)sumAllWhitePixRow / countWhitePix;
        avrCol = (double)sumAllWhitePixCol / countWhitePix;
        vector_2D vectorToPoint(avrCol, -avrRow, vector_2D::RECTANGULAR);
        point_2D posisionAtRoot(VECTOR_ROOT, vectorToPoint);
        Obj_position = posisionAtRoot;
        ObjExistance = true;
    }
    else
        ObjExistance = false;
}

point_2D Object_img::getPosition(vector_2D root){
    point_2D buffer = Obj_position.changeCoordinateTo(root);
    return buffer;
}

point_2D Object_img::getPosition(point_2D root){
    point_2D buffer = Obj_position.changeCoordinateTo(root);
    return buffer;
}

bool Object_img::isObjExist(){ return ObjExistance;}

void Object_img::updateImg(Mat img){
    this->RGB_img = img;
    Mat OBJ_buffer_img;
    cvtColor(this->RGB_img, OBJ_buffer_img, CV_BGR2HSV);
    this->HSV_img = OBJ_buffer_img;
}

Mat Object_img::cancelNoise(Mat img){
    if(this->erodeLevel != 0){
        //create structuring element that will be used to "dilate" and "erode" image.
        //the element chosen here is a 3px by 3px rectangle
        Mat erodeElement = getStructuringElement( MORPH_RECT,Size(this->erodeLevel,this->erodeLevel));
        erode(img,img,erodeElement);
        erode(img,img,erodeElement);
    }
        //dilate with larger element so make sure object is nicely visible
    if(this->dilateLevel != 0){
        Mat dilateElement = getStructuringElement( MORPH_RECT,Size(this->erodeLevel,this->erodeLevel));
	    dilate(img,img,dilateElement);
        dilate(img,img,dilateElement);
    }
    return img;
}

Mat Object_img::pickObject(Mat img){
    int largest_area = 0;
    int largest_contour_index = 0;

    Mat dst(img.rows,img.cols,CV_8UC1,Scalar::all(0));

    vector< vector<Point> > contours; // Vector for storing contour
    vector<Vec4i> hierarchy;
    
    findContours( img, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

    for( int i = 0; i< contours.size(); i++ ) // iterate through each contour. 
    {
      double a = contourArea( contours[i],false);  //  Find the area of contour
      if(a>largest_area){
            largest_area=a;
            largest_contour_index=i;                //Store the index of largest contour
      }
    }
    Scalar color( 255,255,255);
    drawContours( dst, contours,largest_contour_index, color, CV_FILLED, 8, hierarchy );
    return dst;
}