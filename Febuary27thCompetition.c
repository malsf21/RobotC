#pragma config(Motor,  port2,           frontRightMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           backRightMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port4,           frontLeftMotor, tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port5,           backLeftMotor, tmotorNormal, openLoop)
#pragma platform(VEX)

//Competition Control and Duration Settings
//MOST IMPORTANT! DO NOT FORGET WHEN WRITING NEW CODE
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
//					INITALIZE FUNCTIONS FOR AUTONOMOUS CODE HERE
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
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

	//VERY TANK CONTROLS BASIC USER CONTROL CODE

    //Right side of the robot is controlled by the right joystick, Y-axis
    motor[frontRightMotor] = vexRT[Ch2];
    motor[backRightMotor]  = vexRT[Ch2];
    //Left side of the robot is controlled by the left joystick, Y-axis
    motor[frontLeftMotor] = vexRT[Ch3];
    motor[backLeftMotor]  = vexRT[Ch3];

	}
}
