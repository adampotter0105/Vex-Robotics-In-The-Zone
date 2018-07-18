#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    goalpot,        sensorPotentiometer)
#pragma config(Sensor, in2,    conepot,        sensorPotentiometer)
#pragma config(Sensor, in3,    intakepot,      sensorPotentiometer)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           BL,            tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port2,           FL,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           barL,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           goalL,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           goalR,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           barR,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           FR,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          BR,            tmotorVex393_HBridge, openLoop, reversed, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
// Two Controller: ex. "vexRt[Btn5DXmtr2]"
// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

// SENSOR DEFINITIONS
#define GOALMIN 800  // mobile goal 4-bar
#define GOALMAX 2550

#define INTAKEOPEN 1600
#define INTAKETHRESH1 1250  //start open, open, grab goal, thresh1, grab cone, thresh 2, close
#define INTAKETHRESH2 1600
//BAR Sections   [target, low, high]
#define BARMIN 1400
#define BARMAX 3500
int barLOW[3] = {960, 1000, 1500};
int barMID[3] = {2150, 1500, 2300};
int barHI[3] = {2850, 2300, 4001};
//////////////////////
// GLOBAL VARIABLES///
//////////////////////
int driveMin  = 25; //defining joystick dead space

int PIDon[6] = {0,0,0,0,0,0}; // 0:driveL 1:drive 2:turn 3:mobilegoal 4:cone-bar 5:lift
float target[6] = {0,0,0,0,0,0};
int motorMin[6] = {20,20,20,20,20,30};  //defining dead space for motors
float kP[6] = {0.2,0.2,0.1,0.05,0.09,0.9};
float kI[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
float kD[6] = {0.0,0.0,0.0,0.0,0.0,0.0};

int dT = 50;  // ms delay
int dTplayback = 20; //max motor output

float motorOut[6] = {0,0,0,0,0,0};
//Record/Playback
int L[1200];
int R[1200];
int T[200];
int B[200];
int In[150];
int posL = 0;
int posR = 0;
int posT = 0;
int posB = 0;
int posI = 0;

// 0:driveL 1:driveR 2:turn 3:mobilegoal 4:cone-bar 5:lift
//encoder: 392 for turbo, 627.2 for torque
///////////
// TASKS///
///////////

task PID()  // 0:driveL 1:drive 2:turn 3:mobilegoal 4:cone-bar 5:lift
// 0:integrated 1:integrated 2:gyro 3:pot 4:pot 5:integrated
{ int sensor[6] = {0,0,0,0,0,0};
    int totalError[6] = {0,0,0,0,0,0};
    float lastError[6] = {0,0,0,0,0,0};
    float dError[6] = {0,0,0,0,0,0};
    float error[6] = {0,0,0,0,0,0};
    while(true)
    { //Sensors
        if(PIDon[3]){sensor[3]=SensorValue(goalpot);}
        if(PIDon[4]){sensor[4]=SensorValue(conepot);}
        //P
        for(int i=0;i<6;i++)
        {error[i]=target[i]-sensor[i];}
        //I
        for(int i=0;i<6;i++)
        {totalError[i]+=error[i];}
        //D
        for(int i=0;i<6;i++)
        {dError[i]=lastError[i]-error[i];}
        //Motor Output
        motorOut[4]=kP[4]*error[4]+kI[4]*totalError[4]+kD[4]*dError[4];
        if(fabs(motorOut[4])>100)  {motorOut[4]=sgn(motorOut[4])*90;}//round down to 90
        if(PIDon[4]&&fabs(motorOut[4])>motorMin[4])motor[barL]=motor[barR]=motorOut[4];  //Cone Bar
        else if(PIDon[4]) motor[barL]=motor[barR]=0;
        //Last Error
        for(int i=0;i<6;i++)
        {lastError[i]=error[i];}
        delay(dT);
    }//end of infinite loop
}//end of PID task


////INTAKE TOGGLE////
task intaketoggle()
{    motor[intake]=-100; delay(550); motor[intake]=-12; //initial closing
	int intakeon = 0;

	while(true){
		if(vexRT[Btn7D]==1 || vexRT[Btn7U]==1 || (vexRT[Ch4]<-90 && vexRT[Ch1]>90)){ //if button pressed

		if(intakeon) {intakeon=0; motor[intake]=-100;//close
				delay(500);
			if(SensorValue(intakepot)>INTAKETHRESH2)
					{motor[intake]=-40;}	//closes on goal
			if(SensorValue(intakepot)<INTAKETHRESH1)
				{motor[intake]=0;} //closes on nothing
			else {motor[intake]=-30;} //closes on cone

				}

		else {intakeon=1;
				motor[intake]=127; delay(400);
				//for(int i=0; i<350; i+=50){motor[intake]=0.13*(INTAKEOPEN-SensorValue(intakepot)); delay(50);}//prop moves to open position
				motor[intake]=0;}//opening
		}

	}//end of infinite loop
}//end of task

///RECORD///

task record()
{  while(true){if(vexRT[Btn8D]==1){
		posL=0; posR=0; posT=0; posB=0; posI=0; //posDPID=0;

		for(int j=0;j<699;j++){L[j]=0;}	//Clear arrays
		for(int j=0;j<699;j++){R[j]=0;}
		for(int j=0;j<199;j++){T[j]=0;}
		for(int j=0;j<199;j++){B[j]=0;}
		for(int j=0;j<149;j++){In[j]=0;}
		int t=0;
  while(true) {

      if(fabs(motor[BL]-L[posL])>=10){L[posL+2]=motor[BL]; L[posL+3]=t; posL+=2;}//if difference in motor out is big
      if(fabs(motor[BR]-R[posR])>=10){R[posR+2]=motor[BR]; R[posR+3]=t; posR+=2;}//enough, make new entry for pwr and time and move pos var
      if(fabs(motor[goalL]-B[posB])>10){B[posB+2]=motor[goalL]; B[posB+3]=t; posB+=2;}//forward two, evens pwr, odds time

      //First entry for top bar
      if(posT==0){T[0]=2850; T[1]=0;}
      //Necessary to Keep Loop Running
      t+=dTplayback;
      if(vexRT[Btn8U]==1){break;}//break out of loop
			delay(dTplayback);

			if(fabs(motor[intake]-In[posI])>10){In[posI+2]=motor[intake]; In[posI+3]=t; posI+=2;}

      if(PIDon[4]) { //saving values for bar
      if(fabs(target[4]-T[posT])>10)	{T[posT+2]=target[4]; T[posT+3]=t; posT+=2;}	}//if pid is on
      else {	if(motor[barL]!=T[posT])	{T[posT+2]=motor[barL]; T[posT+3]=t; posT+=2;}	}//if pid is off

      //if(fabs(L[posL])<15&&fabs(R[posR])<15){DPID[posDPID]=nMotorEncoder[BL]; DPID[posDPID+1]=nMotorEncoder[BR];}
      //if the motor output for both drive motors is low enough, save encoder position

  } //end of for loop

  }delay(10);}//end of while and if
}//end of task

/////////////
//PRE-AUTON//
/////////////
void pre_auton(){
//PASTE ARRAYS//


}

////////////
///AUTON////
////////////
task autonomous()
{ stopTask(intaketoggle);
	posL=posR=posT=posB=posL=posI=0;//reset position
	startTask(PID);
	PIDon[3]=PIDon[4]=0;//turning off pid
	//PIDon[0]=PIDon[1]=1;
    ///Main//
//PLAYBACK
	int t=0; //time marker

while(true)
{
    if(L[posL+1]==t){motor[BL]=motor[FL]=L[posL]; posL+=2;}//playing back arrays
    if(R[posR+1]==t){motor[BR]=motor[FR]=R[posR]; posR+=2;}
    if(B[posB+1]==t){motor[goalL]=motor[goalR]=B[posB]; posB+=2;}
    if(In[posI+1]==t){motor[intake]=In[posI]; posI+=2;}
    //Additions
		if(T[posT+1]==t){//if time is right
			if(fabs(T[posT])==127) {PIDon[4]=0; motor[barL]=motor[barR]=T[posT]; posT+=2;}//if power is 127/-127
			else{PIDon[4]=1; target[4]=T[posT]; posT+=2;}
		}

		//if(SensorValue(conepot)<1400&&motor[barL]<-110){motor[barL]=motor[barR]=0;}//limit on bottom to prevent clicking

		//Necessary to Loop
		t+=dTplayback;
    delay(dTplayback);
    if(t>59800){break;}

    //End of additions
} //end of for
//End with all motors 0
motor[FL]=motor[FR]=motor[BL]=motor[BR]=0;
motor[intake]=motor[barL]=motor[barR]=0;
motor[goalL]=motor[goalR]=0;
    //End
}

///////////////////
////USER CONTROL///
///////////////////

task usercontrol()
{ // 0:driveL 1:drive 2:turn 3:mobilegoal 4:cone-bar 5:lift
    //Variables
    PIDon[0]=PIDon[1]=PIDon[3]=PIDon[4]=0;  // Turn drive PID off
    float goaldir = 0;
    //Tasks
    startTask(PID);
    startTask(record);
    startTask(intaketoggle);
    //LOFL
    while (true)
    {		//DELAY
    		delay(dTplayback);

        //Drive
        /*if(fabs(vexRT[Ch2]+vexRT[Ch1])>driveMin) {motor[BL]=motor[FL]=10*ceil((vexRT[Ch2]+vexRT[Ch1])/10);}
        else {motor[BL]=motor[FL]=0;}
        if(fabs(vexRT[Ch2]-vexRT[Ch1])>driveMin) {motor[BR]=motor[FR]=10*ceil((vexRT[Ch2]-vexRT[Ch1])/10);}
        else {motor[BR]=motor[FR]=0;}*/
    		if(fabs(vexRT[Ch3])>driveMin) {motor[BL]=motor[FL]=10*ceil(vexRT[Ch3]/10);}
        else {motor[BL]=motor[FL]=0;}
        if(fabs(vexRT[Ch2])>driveMin) {motor[BR]=motor[FR]=10*ceil(vexRT[Ch2]/10);}
        else {motor[BR]=motor[FR]=0;}
        //Mobile Goal
        if(SensorValue(goalpot)>GOALMIN&&vexRT[Btn6U]) {PIDon[3]=0; motor[goalL]=motor[goalR]=127; goaldir=1.2;}  //unaffected by stack
        else if(SensorValue(goalpot)<GOALMAX&&vexRT[Btn6D]) {PIDon[3]=0; motor[goalL]=motor[goalR]=-127; goaldir=-1;}
        else if(PIDon[3]==0) {motor[goalL]=motor[goalR]=0; /*PIDon[3]=1; target[3]=SensorValue(goalpot)-220*goaldir; goaldir=0;*/}
        //Manual ConeBar
        if(SensorValue(conepot)>BARMIN&&vexRT[Btn5D]) {PIDon[4]=0; motor[barL]=motor[barR]=-127;}  //button press
        else if(SensorValue(conepot)<BARMAX&&vexRT[Btn5U]) {PIDon[4]=0; motor[barL]=motor[barR]=127;}
        else if(PIDon[4]==0){motor[barL]=motor[barR]=0; PIDon[4]=1;
        	if(SensorValue(conepot)>barLOW[1]&&SensorValue(conepot)<barLOW[2])	{target[4]=barLOW[0];}//interval 1
        	if(SensorValue(conepot)>barMID[1]&&SensorValue(conepot)<barMID[2])	{target[4]=barMID[0];}//interval 2
        	if(SensorValue(conepot)>barHI[1]&&SensorValue(conepot)<barHI[2])	{target[4]=barHI[0];}//interval 3
        	}

        ///////////////////////
        //Return Array values//
        //////////////////////
        if(vexRT[Btn7R]==1){string foo;
        clearDebugStream();
        	//L
        	writeDebugStreamLine("L[700]={");
        	for(int i=0;i<700;i++){foo=L[i]; if(i%15==0){writeDebugStreamLine(foo);}else{writeDebugStream(foo);} writeDebugStream(", ");}
        	writeDebugStreamLine("};");
        }//end of array value out
        if(vexRT[Btn8L]==1){string foo;
        clearDebugStream();
        	//R
        	writeDebugStreamLine("R[700]={");
        	for(int i=0;i<700;i++){foo=R[i]; if(i%15==0){writeDebugStreamLine(foo);}else{writeDebugStream(foo);} writeDebugStream(", ");}
        	writeDebugStreamLine("};");
        }//end of array value out
        if(vexRT[Btn8R]==1){string foo;
        	clearDebugStream();
        	//T
        	writeDebugStreamLine("T[200]={");
        	for(int i=0;i<200;i++){foo=T[i]; if(i%15==0){writeDebugStreamLine(foo);}else{writeDebugStream(foo);} writeDebugStream(", ");}
        	writeDebugStreamLine("};");
        	//B
        	writeDebugStreamLine("B[200]={");
        	for(int i=0;i<200;i++){foo=B[i]; if(i%15==0){writeDebugStreamLine(foo);}else{writeDebugStream(foo);} writeDebugStream(", ");}
        	writeDebugStreamLine("};");
        	//I
        	writeDebugStreamLine("In[150]={");
        	for(int i=0;i<150;i++){foo=In[i]; if(i%15==0){writeDebugStreamLine(foo);}else{writeDebugStream(foo);} writeDebugStream(", ");}
        	writeDebugStreamLine("};");
        }//end of array value conditional

    }//end of infinite loop

}//end of
