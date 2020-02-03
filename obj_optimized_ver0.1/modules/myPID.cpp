#include "Arduino.h"
#include "myPID.h"

PID::PID(double kp, double ki, double kd, unsigned long samplingTime)
{
	this -> kp = kp;
	this -> ki = ki;
	this -> kd = kd;
	this -> samplingTime = samplingTime;
	lastTime = micros() - samplingTime;
}

PID::PID(double kp, double ki, double kd)
{
  this -> kp = kp;
  this -> ki = ki;
  this -> kd = kd;
}
PID::~PID()
{
  
}
void PID::setRange(double min, double max)
{
	this -> minOutput = min;
	this -> maxOutput = max;
	rangeOutput = max - min;
}

void PID::setPID(double kp, double ki, double kd)
{
	this -> kp = kp;
	this -> ki = ki;
	this -> kp = kp;
}

void PID::setSampleTime(unsigned long samplingTime)
{
	this -> samplingTime = samplingTime;
}

void PID::computeFixTime(double baseValue, double inputValue){
	double error = baseValue - inputValue;
	double kpValue = kp*error;
	integral +=  ki*error*((double)samplingTime/1000000);
	if(integral > rangeOutput) integral = rangeOutput;
  	if(integral < -rangeOutput) integral = -rangeOutput;
	double kiValue = integral;
	double kdValue = kd*(inputValue - lastInput)/((double)samplingTime/1000000);
    //Serial.print(kpValue);
    //Serial.print(" ");
    //Serial.print(kiValue);
    //Serial.print(" ");
    //Serial.println(kdValue);
	PIDvalue = kpValue + kiValue - kdValue;
    lastInput = inputValue;
}

bool PID::computeFixTime(double baseValue, double inputValue, unsigned long timeNow)
{
	if((timeNow - lastTime) >= samplingTime)
	{
		double error = baseValue - inputValue;
		double kpValue = kp*error;
	 	integral +=  ki*error*((double)samplingTime/1000000);
	 	if(integral > rangeOutput) integral = rangeOutput;
  		if(integral < -rangeOutput) integral = -rangeOutput;
		double kiValue = integral;
		double kdValue = kd*(inputValue - lastInput)/((double)samplingTime/1000000);
    //Serial.print(kpValue);
    //Serial.print(" ");
    //Serial.print(kiValue);
    //Serial.print(" ");
    //Serial.println(kdValue);
	PIDvalue = kpValue + kiValue - kdValue;
    lastInput = inputValue;
		return true;
	}
    return false;
}

void PID::computeDynamic(double baseValue, double inputValue, unsigned long timeNow)
{
	double Dtime = (double)(timeNow - lastTime)/1000000;
	
	double error = baseValue - inputValue;
	double kpValue = kp*error;
  	integral +=  ki*error*Dtime;
  	if(integral > rangeOutput) integral = rangeOutput;
  	if(integral < -rangeOutput) integral = -rangeOutput;
	double kiValue = integral;
	double kdValue = kd*(inputValue - lastInput)/Dtime;

  //Serial.print(kpValue);
  //Serial.print(" ");
  //Serial.print(kiValue);
  //Serial.print(" ");
  //Serial.println(kdValue);
   
  PIDvalue = kpValue + kiValue - kdValue;
  lastTime = timeNow;
  lastInput = inputValue;
}

double PID::forwardDecrease(double baseControl)
{
	double value = baseControl + PIDvalue;
	if ( value > maxOutput)
		value = maxOutput;
	else if (value < minOutput)
		value = minOutput;
	return value;
}

double PID::backwradIncrease(double baseControl)
{
	double value = baseControl - PIDvalue;
	if ( value > maxOutput)
		value = maxOutput;
	else if (value < minOutput)
		value = minOutput;
	return value;
}

