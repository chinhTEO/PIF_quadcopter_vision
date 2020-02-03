#ifndef POINT_2DMASTER_H_
#define POINT_2DMASTER_H_ 1

#include "vector_2Dmaster.h"
class point_2D{
public:
	vector_2D root;
    vector_2D point;

	point_2D();
	point_2D(vector_2D root,  vector_2D point);
	point_2D(double X, double Y, point_2D root);
	point_2D(double X, double Y, vector_2D root);
	~point_2D();

	point_2D changeCoordinateTo(vector_2D root);
	point_2D changeCoordinateTo(point_2D root);

	double distanceTo(point_2D point);

	double angleWith(point_2D point, point_2D view);
	double angleDir(point_2D point, point_2D view);
	point_2D moveWithVector(vector_2D vector);
	point_2D rotateByPoint(point_2D point, double angle);

	double getX();
	double getY();
	double getRadius();
	double getAngle();
};

extern const point_2D POINT_ROOT;

#endif