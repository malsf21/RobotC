#pragma config(Motor,  port2,           A_Motor,     tmotorNormal, openLoop)
#pragma config(Motor,  port3,           B_Motor,     tmotorNormal, openLoop)
#pragma config(Motor,  port4,           C_Motor,     tmotorNormal, openLoop)
#pragma config(Motor,  port5,           D_Motor,     tmotorNormal, openLoop)
#pragma config(Motor,  port6,           L_armMotor,  tmotorNormal, openLoop)
#pragma config(Motor,  port7,           R_armMotor,  tmotorNormal, openLoop)


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++

task main()
{
  while(1 == 1){
    //Driving Motor Control
    motor[A_Motor] = vexRT[Ch2];
    motor[B_Motor] = vexRT[Ch2];
    motor[C_Motor] = vexRT[Ch3];
    motor[D_Motor] = vexRT[Ch3];

    //Arm Control
    if(vexRT[Btn5U] == 1)
    {
      motor[L_armMotor] = 40;
    }
    else if(vexRT[Btn6U] == 1)
    {
      motor[R_armMotor] = 40;
    }
    else if(vexRT[Btn5D] == 1)
    {
      motor[L_armMotor] = -40;
    }
    else if(vexRT[Btn6D] == 1)
    {
      motor[R_armMotor] = -40;
    }
    else
    {
      motor[L_armMotor] = 0;
      motor[R_armMotor] = 0;
    }
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
