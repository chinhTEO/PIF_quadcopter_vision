#include "vector_2Dmaster.h"

vector_2D::vector_2D(){
    
}

vector_2D::vector_2D(double X_R, double Y_A, baseCoordinates type){
    if(type == RECTANGULAR){
        this->X = X_R;
        this->Y = Y_A;
        convertToPolar();
    }
    else{
        this->R = X_R;
        this->A = Y_A;
        convertToReg();
    }
}

vector_2D::~vector_2D(){
}

vector_2D vector_2D::invertVector(){
    vector_2D buffer(-X, -Y, vector_2D::RECTANGULAR);
    return buffer;
}
vector_2D vector_2D::add(vector_2D vector){
    vector_2D buffer(X+vector.X, Y+vector.Y, vector_2D::RECTANGULAR);
    return buffer;
}
vector_2D vector_2D::subtract(vector_2D vector){
    vector_2D buffer(X-vector.X, Y-vector.Y, vector_2D::RECTANGULAR);
    return buffer;
}

double vector_2D::dot(vector_2D vector){
    return X*vector.X + Y*vector.Y; 
}
vector_2D vector_2D::rotate(double angle){
    vector_2D buffer(this->R, this->A + angle, vector_2D::POLAR);
    return buffer;
}

double vector_2D::angleWith(vector_2D vector){
        if( this->A < vector.A ){return vector.A - this->A;}
        else{ return 2*M_PI - this->A + vector.A;}
}

double vector_2D::angleDir(vector_2D vector){
        double normalAngle = this->angleWith(vector);
        double angle;
        if(normalAngle < M_PI) angle = normalAngle;
        else angle = -(2*M_PI - normalAngle);
        return  angle;
}

double vector_2D::getX(){ return X; }
double vector_2D::getY(){ return Y; }
double vector_2D::getRadius(){ return R; }
double vector_2D::getAngle(){ return A; }

void vector_2D::convertToReg(){
    X = R*cos(A);
    Y = R*sin(A);
}

void vector_2D::convertToPolar(){
    R = sqrt(X*X + Y*Y);
    if( Y > 0 ) A = acos(X/R);
    if( Y < 0 ) A = -acos(X/R);
    if( X >= 0 && Y == 0) A = 0;
    if( X < 0 && Y == 0) A = M_PI;
}


const vector_2D VECTOR_ROOT(0,0,vector_2D::RECTANGULAR); 