#include "point_2Dmaster.h"
point_2D::point_2D(){

}
point_2D::point_2D(vector_2D root,  vector_2D point){
	this->root = root;
	this->point = point;
}
point_2D::point_2D(double X, double Y, point_2D root){
	vector_2D point(X, Y, vector_2D::RECTANGULAR);
	this->root = root.root.add(root.point);
	this->point = point;
}
point_2D::point_2D(double X, double Y, vector_2D root){
	vector_2D point(X, Y, vector_2D::RECTANGULAR);
	this->root = root;
	this->point = point;
}
point_2D::~point_2D(){
}

point_2D point_2D::changeCoordinateTo(vector_2D root){
	point_2D buffer(root, this->root.add(this->point).subtract(root));
	return buffer;
}

point_2D point_2D::changeCoordinateTo(point_2D root){
	vector_2D buffer_root = root.root.add(root.point);
	point_2D buffer(buffer_root, this->root.add(this->point).subtract(buffer_root));
	return buffer;
}

double point_2D::distanceTo(point_2D point){ return this->root.add(this->point).subtract(point.root).subtract(point.point).getRadius(); }

double point_2D::angleWith(point_2D point, point_2D view){
	vector_2D commonRoot = view.root.add(view.point);
	point_2D A = this->changeCoordinateTo(commonRoot);
	point_2D B = point.changeCoordinateTo(commonRoot);
	double angle = A.point.angleWith(B.point);
	return angle;
}

double point_2D::angleDir(point_2D point, point_2D view){
	vector_2D commonRoot = view.root.add(view.point);
	point_2D A = this->changeCoordinateTo(commonRoot);
	point_2D B = point.changeCoordinateTo(commonRoot);
	double angle = A.point.angleDir(B.point);
	return angle;
}

point_2D point_2D::moveWithVector(vector_2D vector){
	 point_2D buffer(this->root, this->point.add(vector));
	 return buffer;
}

point_2D point_2D::rotateByPoint(point_2D point, double angle){
	 point_2D buffer = this->changeCoordinateTo(point.root.add(point.point));
	 vector_2D buffer_rotatedVector = buffer.point.rotate(angle);
	 point_2D newTarget(buffer.root, buffer_rotatedVector);
	 return newTarget;
}

double point_2D::getX(){ return this->point.X; }
double point_2D::getY(){ return this->point.Y; }
double point_2D::getRadius(){return this->point.R; }
double point_2D::getAngle(){return this->point.A; }

const point_2D POINT_ROOT(VECTOR_ROOT,VECTOR_ROOT);