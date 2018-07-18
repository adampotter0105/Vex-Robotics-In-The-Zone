////////////////////
//20 pnt Preloads//
///////////////////

	//Initiate
	Intake("In");
	Cone_Bar(CONEBARIN);
  Lift(-100);//pin release
	Goal(GOALMAX+140);
	GenericWait(250);
	Lift(0);
	Forward(4.2); // move to mobile goal
	GenericWait(1620);
	Goal(GOALMIN);
	Wait(0, 30, 3000);

	//Pick up goal
	Lift(30);
	GenericWait(570);
	Forward(-1.32);
	//Place preload
	GenericWait(350);
	Lift(-75);
	GenericWait(120);
	Intake("Out");
	GenericWait(150);
	Wait(0,30, 1000);
	Intake("Stop");




	//Raise for Preloads
	Turn(-1.03);
	LiftGo(-175);
	Cone_Bar(CONEBAROUT);
	Wait(0,40, 650);
	Forward(-0.4);
	Wait(0,30, 600);
	Intake("In");//to grab cone
	LiftGo(LIFTPRELOAD+18);


	//

	//Cones
	Cone2a();
	GenericWait(70);
	Cone3a();
	GenericWait(70);
	Cone4a();
	Lift(-127);
	GenericWait(70);
	/*cones=5;
	ConeRest();*/

	//Cone 6
	Intake("Stop");
			Cone_Bar(CONEBAROUT);// bar out
			LiftGo(-190);//LiftGo(-205);
Forward(-0.15);
			Cone_Bar(CONEBARIN);//start bringing in
			//Place
			Wait(4,350,700);
			Lift(-100);
			GenericWait(110);
Turn(-0.9);//turn towards corner
			Intake("Out");
			GenericWait(70);
			LiftGo(-210);//get off last cone

			//5 Cones!


	Intake("StopForReal");
	Wait(0, 55, 850);
	Forward(1.6);//to corner
	GenericWait(380);
	//Place in 5
	Goal(GOALMAX);
	GenericWait(730);
	Forward(-1.5);

	//END STACK
/*	Intake("StopForReal");
	Wait(0, 30, 1000);
	Forward(3.7);//to corner
	Wait(0, 50,3000);
	Turn(0.9);//turn straight with bar
	Wait(0, 50, 3000);

	//Place goal
	Forward(3);
	GenericWait(900);
	Goal(GOALMAX);//move into corner
	GenericWait(1000);
	Forward(-2);
	GenericWait(150);
	Goal(GOALMIN);


	//*/
