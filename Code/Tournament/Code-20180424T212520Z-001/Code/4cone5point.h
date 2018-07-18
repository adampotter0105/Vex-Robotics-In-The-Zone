/////////////////////////////
///4 Cone Field in 5 Point///
////////////////////////////

//TORQUE AUTON

	//Initiate
	Intake("In");
  Lift(-100);//pin release
	Goal(GOALMAX+140);
	GenericWait(250);
	Lift(0);
	Forward(3.7); // move to mobile goal
	Cone_Bar(CONEBARIN);
	Wait(0, 30, 3000);
	PIDon[0]=PIDon[1]=0; motor[BL]=motor[BR]=motor[FL]=motor[FR]=60;
	GenericWait(100);
	motor[BL]=motor[BR]=motor[FL]=motor[FR]=-30;
	target[0]=SensorValue(left); target[1]=SensorValue(right);

	//Grab goal and place preload
	Lift(50);
	Goal(GOALMIN);
	GenericWait(600);
	Lift(-127);
	GenericWait(180);
	Forward(0.65);
	Intake("Out");//Place preload

	//Grab 2nd cone
	GenericWait(150);
	Lift(0);
	Lift(100);
	Cone_Bar(CONEBAROUT);
	GenericWait(270);
	Intake("In");
	GenericWait(200);
	Lift(-127);
	GenericWait(650);

	//Place 2nd Cone
	Lift(127);
	GenericWait(200);
	Intake("Stop");
	Lift(0);
	Cone_Bar(CONEBARIN);
	Forward(0.95);//move to 3rd cone
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

	/*Place 3rd Cone
	Lift(120);
	Intake("Stop");
	GenericWait(270);
	Lift(0);
	Cone_Bar(CONEBARIN);
	Forward(0.72);//move to 4th
	GenericWait(390);
	Lift(-60);
	GenericWait(150);
	Intake("Out");
	GenericWait(200);

	// Pick up 4th cone
	Lift(50);
	Cone_Bar(CONEBAROUT);
	GenericWait(300);
	Intake("In");
	GenericWait(300);
	Turn(-0.1);
	Lift(-127);
	GenericWait(690); */

	//Place 4th Cone
	//LiftGo(-95);
	LiftGo(-90);
	Intake("Stop");
	Lift(0);
	Cone_Bar(CONEBARIN);
	GenericWait(400);
	Forward(-4.4);//moving back
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
	Wait(0, 30, 3000);
	Turn(-2);
	Wait(0, 30, 1500);

	Goal(GOALMAX);//move into corner
	GenericWait(1200);
	Forward(-2);

//*/
