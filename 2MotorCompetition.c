#pragma config(Motor,  port2,           leftMotor, tmotorNormal, openLoop,)
#pragma config(Motor,  port3,           rightMotor, tmotorNormal, openLoop, reversed)
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
//			INITALIZE FUNCTIONS FOR AUTONOMOUS pre_auton FUNCTION HERE
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
  	// Such as resetting motor encoder values, setting motors to specific positions
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................
  //AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}


task usercontrol()
{
	// User control code here, inside the loop

	while (true) //While 1 == 1 would also work here. Just saying. 
	{

	//Possibly more complex Tank Controls code

    motor[leftMotor] = (vexRT[Ch4] + vexRT[Ch3])/2;
    motor[rightMotor] = (vexRT[Ch2] - vexRT[Ch1])/2;

	}
}