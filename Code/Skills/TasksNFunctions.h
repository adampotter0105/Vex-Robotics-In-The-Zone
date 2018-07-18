////PID Bar////
int target=GOALIN;
int targetgoal = 0;

float kbar = 0.04;
float kgoal = 0.11;

int max = 85;

bool pidon=true;
bool pidongoal=false;


task PID()

{ int motorout=0;
	int motorgoal=0;
	while(true)
	{ //Sensors

	 motorout = (int)(kbar*(target-SensorValue(pot)));
		motorgoal = (int)(kgoal*(targetgoal-SensorValue(goalpot)));
	 //Bar
	 if (pidon){
	 if(fabs(motorout)>max){motorout=max*sgn(motorout);}
	 if(fabs(motorout)<20){motorout=0;}
	else {motor[barL]=motor[barR]=motorout;}
				}
		//Goal
		if(pidongoal){motor[goalL]=motor[goalR]=motorgoal;}

	 delay(50);
	}//end of infinite loop
}//end of PID task


////AutoBar///
int barstate=0;//start

task autobar()
{ startTask(PID);

	while(true){ //0 start, 1 in, 2 mid, 3 out
	switch (barstate){
	//Start
	case 0:
	motor[intake]=100; target=MID;
	delay(200); motor[intake]=540;
	break;
	//In
	case 1:
	pidon=false; motor[barL]=motor[barR]=-80;
	motor[intake]=-120; delay(350); motor[barL]=motor[barR]=0; motor[intake]=-10;
	break;
	//Mid
	case 2:
	motor[intake]=120; delay(170);
	max = 100; target=MID; pidon=true; delay(200); motor[intake]=35;
	break;
	//Out
	case 3:
	max = 65; target=IN; pidon=true;
	delay(500); pidon=false; motor[barL]=motor[barR]=0; motor[intake]=-120; delay(150);
	pidon=true; target=MID; delay(200); motor[intake]=0;
	break;
}//end of switch
delay(50);
}}

//Function//
void resetEncoders() {resetMotorEncoder(BL); resetMotorEncoder(BR);}


//////////////////
///Auton Moving///
/////////////////
float go=0; //units in feet
float turn=0; //units in degrees
float progress=0;

//Task
task move()
{	int target;
	int targetT;
	int deadzone=5;
	int deadzoneT=10;//millidegrees

	static int integral = 0;
  static int prevErr = 0;
  int derivative; // derivative
  int error; //error, used for both
  int gv; int sv; //sensor values

  float kp = 0.2;//1.0;
  float kpT = 0.25;
  float ki = 0;//0.1;
  float kiT = 0.005;
  float kd = 0;//3;
  float kdT = 0.5;

	while(true){


	//FORWARD
if(go!=0)
{ resetEncoders();
	target=go;//c=ticks/foot
	integral = 0; prevErr = 0;
	//Loop
	do{
	//P
  sv = (-nMotorEncoder(BL) + nMotorEncoder(BR))/2;
  error = target - sv; // find error
  //I
  integral += error; // calculate integral
  if(abs(error) > 100){integral = 0;}
  progress=sv*374.5;
	//D
  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error
	//Motors
  motor[BL]=motor[BR]=motor[FR]=motor[FL] = (error*kp + integral*ki + derivative*kd); // add the values to get the motor speed

	delay(40); //delaying

}while(fabs(error)>deadzone);//end of while
	//Brake
	motor[BL]=motor[FL]=motor[BR]=motor[FR]=-15*sgn(go);
	delay(100);
	motor[BL]=motor[BR]=motor[FL]=motor[FR]=0;
go=0;
}//end of move



	//TURNING
if(turn!=0)
{	SensorValue[gyro]=0;
	targetT=turn;//c=ticks/degree
	integral = 0; prevErr = 0;
	//Loop
	do{
	//P
  gv = SensorValue(gyro);
  error = targetT - gv; // find error
  //I
  integral += error; // calculate integral
  if(abs(error) > 100){integral = 0;}
	//D
  derivative = error - prevErr; // calculate the derivative
  prevErr = error; // set current error to equal previous error
	//Motor
  motor[BL]=motor[FL]= error*kpT + integral*kiT + derivative*kdT; // add the values to get the motor speed
  motor[BR]=motor[FR]= -( error*kpT + integral*kiT + derivative*kdT);

	delay(40); //delaying

}while(fabs(error)>deadzoneT);//end of while
//Braking
	motor[BL]=motor[FL]=-15*sgn(turn);
	motor[BR]=motor[FR]=15*sgn(turn);
	delay(100);
	motor[BL]=motor[BR]=motor[FL]=motor[FR]=0;
	turn=0;
}//end of turn

}}



///Functions///
void Forward(float feet){go=feet*374.5;}
void GyTurn(int deg){turn=deg*10;}
void Goal(string *state) { pidongoal=true;
	if(*state == "In"){targetgoal=GOALIN;}
	if(*state == "Out"){targetgoal=GOALOUT;} }
void Claw(string *state){
	if(*state=="Out"){barstate=1;}
	if(*state=="Grab"){barstate=2;}
	if(*state=="Place"){barstate=3;}
}
void Wait(float prog=0) //default w/o progress, override breaks at progress point
{while(go!=0||turn!=0){
	delay(50);
	if(fabs(prog)>fabs(progress)){break;}
}
}
