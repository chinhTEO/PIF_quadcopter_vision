#ifndef MYPID_H_
#define MYPID_H_ 1
#define LIBRARY_VERSION 0.0.1

class PID
{
public:
	 double kp = 0;
	 double ki = 0;
	 double kd = 0;

	 unsigned long lastTime = 0;
	 unsigned long samplingTime = 0;
	 
	 double minOutput = 0;
	 double maxOutput = 255;
	 double rangeOutput = 255;

	 double PIDvalue = 0;
	 double integral = 0;
	 double lastInput = 0;


	 PID(double kp, double ki, double kd, unsigned long samplingTime);
   	 PID(double kp, double ki, double kd);
   	 PID();
	 ~PID();
	 void setRange(double min, double max);
	 void setPID(double kp, double ki, double kd);
	 void setSampleTime(unsigned long samplingTime);

	 void computeFixTime(double baseValue, double inputValue);
	 bool computeFixTime(double baseValue, double inputValue, unsigned long timeNow);
	 void computeDynamic(double baseValue, double inputValue,  unsigned long timeNow);

	 double forwardDecrease(double baseControl);
	 double backwradIncrease(double baseControl);
};

#endif
