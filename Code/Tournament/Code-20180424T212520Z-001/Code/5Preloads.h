///////////////////
//5 pnt Preloads//
//////////////////


	//Initiate
	Intake("In");
	Cone_Bar(CONEBARIN);
  Lift(-100);//pin release
	Goal(GOALMAX+140);
	GenericWait(250);
	Lift(0);
	Forward(3.98); // move to mobile goal
	Wait(0, 30, 3000);

	PIDon[0]=PIDon[1]=0; motor[BL]=motor[BR]=motor[FL]=motor[FR]=60;
	GenericWait(100);
	motor[BL]=motor[BR]=motor[FL]=motor[FR]=-30;
	target[0]=SensorValue(left); target[1]=SensorValue(right);

	Goal(GOALMIN);


	//Pick up goal
	Lift(30);
	GenericWait(630);
	Forward(-0.64);
	//Place preload
	GenericWait(350);
	Lift(-75);
	GenericWait(120);
	Intake("Out");
	GenericWait(150);
	Wait(0,30, 540);
	Intake("Stop");




	//Raise for Preloads
	Turn(-1.0);
	LiftGo(-175);
	Cone_Bar(CONEBAROUT);
	Wait(0,40, 900);
	Forward(-0.5);
	Intake("In");//to grab cone
	Wait(0,40, 1050);
	LiftGo(LIFTPRELOAD);


	//STACK

	//Cones
	Cone2a();
	GenericWait(100);
	Cone3a();
	GenericWait(100);
	Cone4();
	Lift(-127);
	GenericWait(100);

	//Cone 5
	Intake("Stop");
			Cone_Bar(CONEBAROUT);// bar out
			LiftGo(-190);
Forward(-0.25);
			Cone_Bar(CONEBARIN);//start bringing in
			//Place
			Wait(4,350,800);
			Lift(-100);
			GenericWait(120);
			Intake("Out");
			GenericWait(70);
			Turn(-0.80);//turn towards corner
			LiftGo(-200);//get off last cone

			//5 Cones!

	//END STACK
	Intake("StopForReal");
	Wait(0, 50, 1000);
	Forward(1.2);//to corner
	GenericWait(550);
	//Place in 5
	Goal(GOALMAX);
	GenericWait(950);
	Forward(-2);


	//*/
