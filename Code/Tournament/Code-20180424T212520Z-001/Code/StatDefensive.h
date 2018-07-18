///////////////////////
//Stationary Defensive//
///////////////////////
/////////////////
//20 point goal Cone Field//
/////////////////

//
Intake("In");
Forward(0.75);
Wait(0,30,400);
Turn(-0.9);
Wait(0,30,2000);
Forward(1.85);
Wait(0,30,1200);
Turn(0.35);
Wait(0,30,1000);

	//Initiate
	Intake("In");
  Lift(-100);//pin release
	Goal(GOALMAX+140);
	GenericWait(250);
	Lift(0);
	Forward(3.4);
	Cone_Bar(CONEBARIN);
	Wait(0, 30, 1700);

	//Grab goal and place preload
	Lift(40);
	Goal(GOALMIN);
	GenericWait(650);
	Lift(-127);
	Intake("Out");//Place preload
	GenericWait(100);
	Forward(0.5);


	//Grab 2nd cone
	GenericWait(150);
	Lift(100);
	Cone_Bar(CONEBAROUT);
	Intake("In");
	GenericWait(240);
	Intake("In");
	GenericWait(170);
	Lift(-127);
	GenericWait(870);

//Place
	LiftGo(-72);
Forward(-4.17);//moving back
	Cone_Bar(CONEBARIN);
	GenericWait(300);
	Lift(-60);
	GenericWait(160);
	Intake("Out");
	GenericWait(320);
	Lift(0);

	//Lift off cone
	Lift(90);
	GenericWait(250);
	Lift(0);
	Intake("Stop");

	//Place
	Wait(0, 30, 3000);
	Turn(-0.5);
	Wait(0, 30, 700);

	Forward(-2.23);//back up
	Wait(0, 30, 1300);

	Turn(-1.1);//turn to bar
	Wait(0, 30, 1100);

	//Place Goal
Forward(2.34);//to corner
	GenericWait(750);
	Goal(GOALMAX+140);//move into corner
	GenericWait(1200);
	Forward(-3);
	GenericWait(100);
	Goal(GOALMIN);
	GenericWait(500);
	Goal(GOALMIN);

//*/

/*
//Pin release
Intake("In");
Lift(-60);
Cone_Bar(CONEBAROUT);
GenericWait(160);

//Lift and forward
Forward(0.7);
Lift(127);
LiftGo(-480);
Wait(0,30,2000);

//Place
Lift(-60);
GenericWait(150);
Intake("Out");
GenericWait(120);
LiftGo(-490);
Intake("Stop");

//sneaky goal
Forward(-0.6);
Wait(0,30,1000);
Turn(0.5);
LiftPos(LIFTIDLE);
Cone_Bar(CONEBARIN);
Wait(0,30,2000);
Forward(0.7);
Wait(0,30,2000);
Turn(-0.5);
Wait(0,30,2000);
Forward(2.5);//get em!
Turn(0.6);
Goal(GOALMAX);
Forward(2);
//*/
