/*
 * pid.c
 *
 *  Created on: Jan 12, 2021
 *      Author: David    Original work by Jose Barros (PTDreamer), 2017
 */

#include "pid.h"
#include "tempsensors.h"
#include "settings.h"

PIDController_t pid;


void setupPID(pid_values_t* p) {
  pid.Kp =        (float)p->Kp/1000000;
  pid.Ki =        (float)p->Ki/1000000;
  pid.Kd =        (float)p->Kd/1000000;
  pid.limMinInt = (float)p->minI/100;
  pid.limMaxInt = (float)p->maxI/100;
  pid.limMin =    (float)0;                 // Min 0% (Also prevents negative PID output to the PWM)
  pid.limMax =    (float)1;                 // Max 100%
}

int32_t calculatePID(int32_t setpoint, int32_t measurement, int32_t base) {
  float dt = (float)(HAL_GetTick() - pid.lastTime)/1000;
  float error = setpoint - measurement;

  pid.proportional = pid.Kp * error;                                            // Proportional term
                                                                 // Else, normal PID calculation
  pid.integrator = pid.integrator + (pid.Ki*(error*dt));                      // Integral

  if (pid.integrator > pid.limMaxInt) {                                       // Integrator clamping
    pid.integrator = pid.limMaxInt;
  }
  else if (pid.integrator < pid.limMinInt) {
    pid.integrator = pid.limMinInt;
  }
  pid.derivative = pid.Kd*((error-pid.prevError)/dt);

  pid.out = pid.proportional + pid.integrator + pid.derivative;               // Compute output

  if(pid.out > pid.limMax){                                                     // Apply limits
      pid.out = pid.limMax;
  } else if (pid.out < pid.limMin) {
      pid.out = pid.limMin;
  }

  pid.prevMeasurement = measurement;                                            // Store data for later use
  pid.lastTime = HAL_GetTick();
  pid.prevError = error;
  return (pid.out*base);
}


float getPID_D() {
  return pid.derivative;
}
float getPID_P() {
  return pid.proportional;
}
float getPID_I() {
  return pid.integrator;
}
float getPID_Error() {
  return pid.prevError;
}
float getPID_Output() {
  return pid.out;
}
int32_t getPID_SetPoint() {
  return pid.lastSetpoint;
}
int32_t getPID_PresentValue() {
  return pid.lastMeasurement;
}
