#pragma config(Motor, port3, 	leftMotor, 	tmotorNormal, openLoop)
#pragma config(Motor, port4, 	rightMotor, tmotorNormal, openLoop)
#pragma config(Motor, port5, 	liftMotor, 	tmotorNormal, openLoop)
#pragma config(Motor, port6, 	clawMotor, 	tmotorNormal, openLoop)

task main (){
	while (1==1){
		motor[leftMotor]  = -vexRT[Ch3];
		motor[rightMotor] = vexRT[Ch3];

		if(vexRT[Btn8U] == true){
			motor[liftMotor] = 127;
		}
		else if(vexRT[Btn8D] == true){
			motor[liftMotor] = -127;
		}
		if(vexRT[Btn8R] == true){
			motor[clawMotor] = 127;
		}
		else if(vexRT[Btn8L] == true){
			motor[clawMotor] = -127;
		}
	}
}