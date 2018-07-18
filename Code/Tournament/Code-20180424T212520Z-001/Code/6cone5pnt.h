////////////////////
//5 pnt Preloads//
///////////////////

	//Initiate
	Intake("In");
  Lift(-100);//pin release
	Goal(GOALMAX+50);
	GenericWait(250);
	Lift(0);
	Forward(3.8); // move to mobile goal
	Cone_Bar(CONEBARIN);
	Wait(0, 30, 3000);

	//Pick up goal
	GenericWait(100);
	Lift(35);
	Goal(GOALMIN);
	GenericWait(425);
	Forward(-1.03);
	//Place preload
	GenericWait(200);
	Lift(-67);
	GenericWait(120);
	Intake("Out");
	GenericWait(200);
	Intake("Stop");
	Wait(0,30, 3000);




	//Raise for Preloads
	Turn(-1.0);
	LiftGo(-175);
	Cone_Bar(CONEBAROUT);
	Wait(0,30, 3000);
	Forward(-0.23);
	Wait(0,30, 3000);
	Intake("In");//to grab cone
	LiftGo(LIFTPRELOAD+10);


	//STACK

	//Cone 2
			Intake("Stop");
			Cone_Bar(CONEBARIN);
			Wait(4,240, 600);
			//Place
			GenericWait(110);
			Lift(-80);
			GenericWait(160);
			Intake("Out");
			GenericWait(140);
			//Up
			Lift(127);
			GenericWait(120);
			Cone_Bar(CONEBAROUT);
			GenericWait(230);
			//Back Down
			Intake("In");
			Lift(-60);
			GenericWait(140);
			Lift(0);
			cones++;


	//Cone 3
			Intake("Stop");
			Cone_Bar(CONEBARIN);
			Wait(4,240, 600);
			//Place
			GenericWait(80);
			Lift(-65);
			GenericWait(180);
			Intake("Out");
			GenericWait(120);
			//Up
			Lift(127);
			GenericWait(180);
			Cone_Bar(CONEBAROUT);
			GenericWait(370);
			//Back Down
			Intake("In");
			Lift(-120);
			GenericWait(110);
			cones++;

	//Cone 4
			Intake("Stop");
			Lift(100);
			GenericWait(50);
			Cone_Bar(CONEBARIN);
			Wait(4,300, 500);
			//Place
			Lift(-65);
			GenericWait(100);
			Intake("Out");
			GenericWait(130);
			//Up
			Lift(120);
			GenericWait(100);
			Cone_Bar(CONEBAROUT);
			GenericWait(170);
			//Back Down
			Intake("In");
			Lift(-127);
			GenericWait(190);


	//Cone 5
			Intake("Stop");
			Cone_Bar(CONEBAROUT);// bar out
			LiftGo(-200);

			Cone_Bar(CONEBARIN);//start bringing in
			//Down
			GenericWait(160);
			Lift(-65);
			GenericWait(250);
			Intake("Out");

			GenericWait(130);
			//Back up
			Cone_Bar(CONEBAROUT);
			Lift(110);
			GenericWait(250);
			Intake("In");
			Lift(-127);
			GenericWait(220);

			//cone 6
			Intake("stop");
			LiftGo(-240);

			Forward(-0.23);
				Cone_Bar(CONEBARIN);//start bringing in
			//Down
			GenericWait(160);
			Lift(-65);
			GenericWait(250);
			Intake("Out");
	Turn(-9.);//turn towards corner

	Intake("StopForReal");
	Wait(0,30,3000);

	Wait(0, 30, 3000);
	Forward(3.6);//to corner
	Wait(0, 50,3000);
	Turn(0.92);//turn straight with bar
	Wait(0, 50, 3000);

	//Place goal
	Forward(1.7);
	GenericWait(960);
	Goal(GOALMAX);//move into corner
	GenericWait(1500);
	Goal(GOALMIN);
	GenericWait(100);
	Forward(-2);
	//*/
