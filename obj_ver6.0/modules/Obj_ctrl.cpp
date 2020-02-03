#include "Obj_ctrl.h"

Obj_ctrl::Obj_ctrl(){}
Obj_ctrl::~Obj_ctrl(){}

void Obj_ctrl::add(String name,int Id, HSV_range range){
    Object_img newObj(name, Id);
    newObj.setHSVRange(range);
    Obj_list.push_back(newObj);
}
void Obj_ctrl::del(int Id){
    for(int i = 0; i < Obj_list.size(); i++){
        if(Obj_list.at(i).id == Id){
            Obj_list.erase(Obj_list.begin() + i);
            return;
        }
    }
}

void Obj_ctrl::updateImg(Mat img){
    this->RGB_img = img;
    Mat OBJ_buffer_img;
    cvtColor(this->RGB_img, OBJ_buffer_img, CV_BGR2HSV);
    this->HSV_img = OBJ_buffer_img;
}

void Obj_ctrl::updateObjHSV(int Id, HSV_range range){
    for(int i = 0; i < Obj_list.size(); i++){
        if(Obj_list.at(i).id == Id){
            Obj_list.at(i).color = range;
            return;  
        }      
    }
}

void Obj_ctrl::processing(){
    for(int i = 0; i < Obj_list.size(); i++){
       Obj_list.at(i).updateImg(RGB_img);
       Obj_list.at(i).processing();
    }
}

void Obj_ctrl::fastProcessing(){
    for(int i = 0; i < Obj_list.size(); i++){
        Obj_list.at(i).fastprocessing(HSV_img);
    }
}

Mat Obj_ctrl::getImg(int Id){
    for(int i = 0; i < Obj_list.size(); i++){
        if(Obj_list.at(i).id == Id)
            return Obj_list.at(i).Obj_img;
    }
    Mat buffer;
    return buffer;
}
point_2D Obj_ctrl::getPosition(int Id, point_2D root){
    for(int i = 0; i < Obj_list.size(); i++){
        if(Obj_list.at(i).id == Id)
            return Obj_list.at(i).getPosition(root);
    }
    point_2D buffer;
    return buffer;
}

point_2D Obj_ctrl::getPosition(int Id, vector_2D root){
    for(int i = 0; i < Obj_list.size(); i++){
        if(Obj_list.at(i).id == Id){
            return Obj_list.at(i).getPosition(root);
        }
    }
    point_2D buffer;
    return buffer;
}