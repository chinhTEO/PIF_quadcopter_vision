#ifndef VECTOR_2DMASTER_H_
#define VECTOR_2DMASTER_H_ 1

#include <stdio.h>
#include <math.h>

class vector_2D{
public:
	enum baseCoordinates{
		RECTANGULAR,
		POLAR
	};

	double X;
	double Y;
	double R;
	double A;
	
	vector_2D();
	vector_2D(double X_R, double Y_A, baseCoordinates type);
	~vector_2D();
	
	vector_2D invertVector();
	vector_2D add(vector_2D vector);
	vector_2D subtract(vector_2D vector);
	double dot(vector_2D vector);
	vector_2D rotate(double angle);

	double angleWith(vector_2D vector);
	double angleDir(vector_2D vector);
	double getX();
	double getY();
	double getRadius();
	double getAngle();

	void convertToReg();
	void convertToPolar();
};

extern const vector_2D VECTOR_ROOT;

#endif