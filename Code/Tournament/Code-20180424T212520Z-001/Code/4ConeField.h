/////////////////
//4 Cone Field//
/////////////////

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
	GenericWait(650);
	Lift(-127);
	GenericWait(200);
	Forward(0.67);
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
	GenericWait(750);

	//Place 2nd Cone
	Intake("Stop");
	LiftGo(-55);
	Cone_Bar(CONEBARIN);
	GenericWait(200);
	Lift(-68);
Forward(0.97);//move to 3rd cone
	GenericWait(400);
	Intake("Out");
	Lift(0);
	GenericWait(250);
	Intake("Stop");
	Wait(0,40,1000);


	//Pick up 3rd cone
	GenericWait(180);
	Lift(90);
	Cone_Bar(CONEBAROUT);
	Intake("In");
	GenericWait(400);
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
	LiftGo(-87);
	Intake("Stop");
	Lift(0);
	Cone_Bar(CONEBARIN);
	GenericWait(420);
	Forward(-4.6);//moving back
	Lift(-60);
	GenericWait(160);
	Intake("Out");
	GenericWait(360);
	Lift(0);

	//Lift off cone
	Lift(70);
	Intake("Stop");
	GenericWait(250);
	Lift(0);

	//Place
	Wait(0, 30, 3000);
	Turn(-0.5);
	Wait(0, 30, 700);

	Forward(-2.2);//back up
	Wait(0, 30, 1300);

	Turn(-1.1);//turn to bar
	Wait(0, 30, 1100);

	//Place Goal
	Forward(2.35);//to corner
	GenericWait(750);
	Goal(GOALMAX+140);//move into corner
	GenericWait(1100);
	Forward(-2);
	GenericWait(100);
	Goal(GOALMIN);

//*/
