#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRLeft,         sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     Compass,        sensorI2CHiTechnicCompass)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     Right,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Left,          tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     Intake,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     Hood,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_1,     Conveyor,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     Lift,          tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    Gripper,              tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    lock,                 tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#define TRUE 1
#define FALSE 0
#define MIN (X, Y) (((X)<(Y) ?(X) : (Y)
#define MAX (A, B) (((A)>(B) ?(X) : (Y)
#define MotorSpecRPM 200
#define MotorSpecPPR	1120
#define ToleranceRPM 2
void Drive(int TargetRPM);
task main()
{
    Drive(90);
}
//find frquency in 0.25s/pulse count (1/4 HZ)
//rpm= pulsefrequency*4*60/motor spec ppr




void Drive(int TargetRPM)
{
    int curTValue, LastRPM, TimePassed, RPow, lastTValue=0;
    clearTimer(T1);
    if(TargetRPM<MotorSpecRPM*0.75)//make sure we are within the limitations of the motor
    {
        while(true)
        {
            //find pulse frequency of encoder in HZ
            //how much time accumulativly has passed?
            int	Time=time10[T1];// time in 10 msec ticks, 100 per second
            curTValue =Time;
            motor[Right]=;
            TimePassed=lastTValue=curTValue;//counts every 1/100 of a second
            //how many times has the encoder pulsed in that time?
            int PulseFreqeuncy=nMotorEncoder[Right]/TimePassed*100; /*pulses/seconds in HZ*/
            //get wheel rpm
            int RPM=(PulseFreqeuncy*60)/MotorSpecPPR;//(pulse/sec*60sec/min)/PPR = R/M
            writeDebugStream("\n RPM:%i, TIME:%i, PulseFreqeuncy:%i",RPM, TimePassed/100, PulseFreqeuncy);
            wait10Msec(50);
            clearDebugStream();
            ////set motor speeds
            //if(abs(TargetRPM-RPM)<Tolerance)//if (setpoint-processvalue<tolerance)
            //{
            //	//do nothing we will later integrate distance tracking in here
            //}
            //else if(TargetRPM<RPM)
            //{
            //Rpow++;
            ////increase motor power
            ////add exception for nochangeStall @return error "STALL"
            //}
            //else if(CurRate>RPM)
            //{
            //	Rpow--;
            //	//decrease motor power
            //	//add exception for innertia(downhill movement)
            //}
            ////motor[Left]=Lpow;//not
        }//while loop
    }
    else
    {
        //@return error "OUT OF RANGE"
        return;
    }
}
