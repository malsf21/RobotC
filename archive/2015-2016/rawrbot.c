
task main()
{
while(true){
	motor[port2] = vexRT[Ch2];
	motor[port3] = -vexRT[Ch2];
	if(vexRT[Btn8U]){
		motor[port4] = 127;
  }
  else if(vexRT[Btn8D]){
  	motor[port4] = -127;
	}
	else{
		motor[port4] = 0;
	}
}


}
