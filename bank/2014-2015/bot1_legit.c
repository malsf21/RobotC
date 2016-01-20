#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,     rightIEM,             sensorQuadEncoderOnI2CPort,        , AutoAssign)
#pragma config(Sensor, I2C_2,     leftIEM,                 sensorQuadEncoderOnI2CPort,        , AutoAssign)
#pragma config(Motor,     port1,                        rightMotor,         tmotorVex269, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,     port10,                    leftMotor,         tmotorVex269, openLoop, encoder, encoderPort, I2C_2, 1000)
#pragma config(Sensor, dgtl9,  left_encoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl11,  right_encoder,  sensorQuadEncoder)
#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

//#include <Vex_Competition_Includes.c>

void pre_auton() {
	//bStopTasksBetweenModes = true;
}
//QUAD ENCODERS FOR SCISSOR LIFT

signed int constrain(signed int input, signed int minimum, signed int maximum) {
	if(minimum>maximum) {
		signed int temp = minimum;
		minimum = maximum;
		maximum = temp;
	}
	if(input<minimum) {
		return minimum;
	}
	if(input>maximum) {
		return maximum;
	}
	return input;
}

void ereset() {
	nMotorEncoder[rightMotor] = 0; nMotorEncoder[leftMotor] = 0;
}

void drive(signed int fl, signed int bl, signed int fr, signed int br) {
	//too bad integers can't be null, or else I would do this way less sketchily
	//pass a value <-127 or >127 to ignore those ports. e.g. drive(127, 127, -128, -128) will set fl and bl to 127, but leave fr and br alone
	if(fl>-128 && fl<128) {
		motor[port4] = -fl;
	}
	if(bl>-128 && bl<128) {
		motor[port2] = bl;
	}
	if(fr>-128 && fr<128) {
		motor[port5] = fr;
	}
	if(br>-128 && br<128) {
		motor[port3] = br;
	}
}
void intake(bool forward) {
	motor[port8] = 127*(forward?1:-1);
	motor[port9] = 127*(forward?1:-1);
}
void scissor(unsigned int target) {
    //left_encoder and right_encoder become more negative as it lifts
    //for port3, positive values raise, for port2, negative values raise
	clearTimer(T1);
	signed int absle = (sensorValue[left_encoder])*-1; signed int absre = (sensorValue[right_encoder])*-1;
	//makes the encoder values more intuitive: orgiinally was abs() hence the name, but realized that was stupid

	signed char sign[2] = { absle>target?-1:1, absre>target?-1:1 };
	while(absle*sign[0]<target*sign[0] && absre*sign[1]<target*sign[1] && time10[T1]<400) { //needs some work
		if(absle*sign[0]<target*sign[0]) {
			motor[port7] = constrain(target-absle, 50*sign[0], 127*sign[0]); //left encoder motor ports
			//target-absle<0 iff absle>target: lower if current state > target
			//motor[port3] = constrain(sensorValue[left_encoder]-target, 50*sign[0], 127*sign[0]); //try if not working!!!!
		}
		else {
			motor[port7] = 30*sign[0]; //continue slightly to avoid SHM
		}


		if(sensorValue[right_encoder]*sign[1]<target*sign[1]) {
			motor[port6] = -constrain(target-absre, 50*sign[1], 127*sign[1]); //right encoder motor ports

			//motor[port2] = constrain(sensorValue[right_encoder]-target, 50*sign[0], 127*sign[0]); //try if not working!!!!
		}
		else {
			motor[port6] = -30*sign[1]; //slightly higher than hold power so it doesn't drop and waste time
		}
		absle = sensorValue[left_encoder]*-1;
		absre = sensorValue[right_encoder]*-1;
	}
	motor[port6] = -15; //hold power
	motor[port7] = 15;
}

task autonomous() {
  motor[port2] = -127;
	motor[port3] = 127;
	motor[port4] = 127;
	motor[port5] = 127;
	Sleep(4000);
  motor[port2] = 127;
	motor[port3] = -127;
	motor[port4] = -127;
	motor[port5] = -127;
	Sleep(1000);
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	//627.2 counts per revolution in high-torque configuration, 4.000" diameter mecanum wheels = 49.91 counts per inch (assuming no slippage). Assuming 90% traction, at ~45 counts per inch.
	//At 100% traction, with 4.000" mecanum wheels, we're looking at 4p/13.348 rev/90º, or 6.5608249 counts per degree.
	/*ereset();
	drive(127, 127, 127, 127);
	while(nMotorEncoder[rightMotor]<473 && nMotorEncoder[leftMotor]<473) { //10.5" forward
	}
	ereset();
	drive(30, 30, 30, 30);
	intake(1);
	while(nMotorEncoder[rightMotor]<90 && nMotorEncoder[leftMotor]<90) { //2" forward
	}
	ereset();
	drive(127, -127, -127, 127);
	//we'll have to estimate on this one
	while(abs(nMotorEncoder[rightMotor])<80 && abs(nMotorEncoder[leftMotor])<80) { //??" strafe
	}
	ereset();
	drive(127, 127, 127, 127);
	while(abs(nMotorEncoder[rightMotor])<620 && abs(nMotorEncoder[leftMotor])<620) { //13.7"
	}

	ereset();
	drive(-127, -127, 127, 127);
	while(abs(nMotorEncoder[rightMotor])<640 && abs(nMotorEncoder[leftMotor])<640) { //~90º left turn, assuming 50 counts of slippage (should be 590 for 90º turn)
	}

	ereset();
	drive(127, 127, 127, 127);

	scissor(340); //311 = 70º of scissor lift turning, first stage

	/*
	//----------- USE IF DESPERATE, AXE SCISSOR(340); -----------
	motor[port2] = -127;
	motor[port3] = 127;
	while(SensorValue[rightMotor]<340 || SensorValue[leftMotor]<340) {
	}
	motor[port2] = -30;
	motor[port3] = 30;
	*/

	/*intake(0);
	Sleep(3000);

	drive(-30, -30, -30, -30);

	scissor(0);*/
}

task main() {
    while(true) {
        /*if(vexRT[Btn8U]) {
            sensorValue[right_encoder] = 0; sensorValue[left_encoder] = 0;
        }*/
		//displayLCDNumber(0,0,sensorValue[right_encoder],6);
		//displayLCDNumber(1,0,sensorValue[left_encoder],6);
		/*if(vexRT[Btn6U]==1) { //please do not touch: magic
			motor[port6] = constrain(127-(sensorValue[right_encoder]-sensorValue[left_encoder]), 0, 127);
			motor[port7] = -constrain(127-(sensorValue[left_encoder]-sensorValue[right_encoder]), 0, 127);
    	}
		else if(vexRT[Btn6D]==1) {
			motor[port6] = constrain(-127-(sensorValue[right_encoder]-sensorValue[left_encoder]), -127, 0);
			motor[port7] = -constrain(-127-(sensorValue[left_encoder]-sensorValue[right_encoder]), -127, 0);
		}
		else {
			motor[port6] = -10;
			motor[port7] = 10;
		}*/
		motor[port6] = -(vexRT[Btn5U]?127:(vexRT[Btn5D]?-127:15));
		motor[port7] = (vexRT[Btn6U]?127:(vexRT[Btn6D]?-127:15));
		if(vexRT[Btn7U]) {
			motor[port8] = 90;
			motor[port9] = 90;
        }
        else if(vexRT[Btn7D]) {
			motor[port8] = -90; motor[port9] = -90;
	    }
		else {
		    //if(vexRT[Btn5D]) {
		        motor[port8] = 10; motor[port9] = 10; //for finesse cube drops, setting like this by default. Means that the intake will be running all the time.
		    /*}
		    else {
		        motor[port8] = 0; motor[port9] = 0;
		    }*/
		}
		motor[port2] = (-vexRT[Ch2]-vexRT[Ch1]+vexRT[Ch4]);
		motor[port3] = -(-vexRT[Ch2]+vexRT[Ch1]+vexRT[Ch4]);
		motor[port4] = -(-vexRT[Ch2]-vexRT[Ch1]-vexRT[Ch4]);
		motor[port5] = -(-vexRT[Ch2]+vexRT[Ch1]-vexRt[Ch4]);
	}
}
