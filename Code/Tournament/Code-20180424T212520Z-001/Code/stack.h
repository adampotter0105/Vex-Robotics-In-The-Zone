task stack() //stacks cone with 5U and 5D being overrides
{
	while(true){



		//PRELOADS//
		while(vexRT[Btn7L]==1){
			//Bring to Top
			PIDon[5]=0;
			stackon=true;

			switch (cones){
			case 0:
				Cone1(); break;
			case 1:
				Cone2(); break;
			case 2:
				Cone3(); break;
			case 3:
				Cone4(); break;
			default:
				ConeRest(); break;
		}
			stackon = false;
			delay(50);
		}//end of preload loop




		//FIELDING//
		while(vexRT[Btn8R]==1){
		//Bring to Top
			stackon=true;

			//Lift Up
			Intake("Stop");
			Cone_Bar(CONEBAROUT);
			Lift(127);// up to top of stack
			waitUntil(SensorValue(liftE)<-fheight[cones]+40-fieldOffset||vexRT[Btn5U]||(vexRT[Btn5D]&&SensorValue(liftE)<LIFTPRELOAD)/*prevents glitch*/);
			//Pull Bar In
			Cone_Bar(CONEBARIN);
			LiftGo(-fheight[cones]-fieldOffset);//reaches target

			//Wait for Bar and Place
			Wait(4,350,800);
			GenericWait(140);
			Lift(-100);
			GenericWait(100);
			Intake("Out");
			GenericWait(70);

			//Off stack
			Lift(127) ;
			GenericWait(70);
			Cone_Bar(CONEBAROUT);
			LiftGo(-fheight[cones]-3);//get back over the cone placed
			GenericWait(230);

			//Back Down
			Intake("In");
			LiftGo(LIFTIDLE);
			Intake("Stop");
			Lift(0);

			//Ending
			if(cones<18){cones++;}
			GenericWait(100);
			stackon = false;


				}// end of infinite loop
}//end of task

	}//end of fielding
