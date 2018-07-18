/////////////////////////
///Statinary and Field///
/////////////////////////
///////////////////////
//Stationary Defensive//
///////////////////////

//Pin release
Intake("In");
Lift(-60);
GenericWait(160);

//Lift and forward
Forward(0.73);
Lift(127);
LiftGo(-320);
Cone_Bar(CONEBAROUT);
Wait(0,30,500);

//Place
GenericWait(140);
Lift(-60);
GenericWait(90);
Intake("Out");
GenericWait(120);
LiftGo(-350);
Intake("Stop");

//sneaky goal
Turn(-0.98);
Wait(0,30,2000);
LiftPos(-150);
Forward(2.1);
Wait(0,30,2000);
Turn(0.45);
GenericWait(200);
Goal(GOALMAX+140);
Wait(0,30,2000);



//Get Goal
Forward(2.9);
Wait(0,30,1500);
	PIDon[0]=PIDon[1]=0; motor[BL]=motor[BR]=motor[FL]=motor[FR]=60;
	GenericWait(100);
	motor[BL]=motor[BR]=motor[FL]=motor[FR]=-30;
	target[0]=SensorValue(left); target[1]=SensorValue(right);
Goal(GOALMIN);
	GenericWait(250);
Forward(0.65);
Wait(0,30,1000);

	//Grab 2nd cone
	Intake("In");
	Lift(-127);
	GenericWait(650);

	//Place 2nd Cone
	Lift(127);
	GenericWait(200);
	Intake("Stop");
	Lift(0);
	Cone_Bar(CONEBARIN);
	Forward(0.97);//move to 3rd cone
	GenericWait(320);
	Wait(0,30,1000);
	Lift(-60);
	GenericWait(170);
	Intake("Out");

	//Pick up 3rd cone
	GenericWait(180);
	Lift(90);
	Cone_Bar(CONEBAROUT);
	GenericWait(200);
	Intake("In");
	GenericWait(200);
	Lift(-127);
	GenericWait(730);

	LiftGo(-87);
	Intake("Stop");
	Lift(0);
	Cone_Bar(CONEBARIN);
	GenericWait(420);
	Forward(-4.46);//moving back
	Lift(-60);
	GenericWait(160);
	Intake("Out");
	GenericWait(360);
	Lift(0);

	//Lift off cone
	Lift(70);
	GenericWait(250);
	Lift(0);
	Intake("Stop");

	//Place
	Wait(0, 30, 2000);
	Turn(-2.45);
	Wait(0, 50, 1000);
		Goal(GOALMAX);
GenericWait(1300);
	Forward(-2.15);//back up
	Wait(0, 30, 1300);

//*/

//*/
