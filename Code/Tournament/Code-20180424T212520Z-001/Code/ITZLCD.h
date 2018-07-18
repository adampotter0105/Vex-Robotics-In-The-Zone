//LCD
void waitUntilButtonRelease(){
	while(nLCDButtons!=0){
		wait1Msec(50);
	}
}
bool autonSide = true;// true=right
int selectedAuton = 0;//0-6:  4 Cone Field, 20 Preloads, 5 Preloads, Stat Defensive, Stat Fielding, 6c5pnt, 4c5pnt

task LCD(){

	bLCDBacklight = true;
	string str;

	int delayAmount = 100;
	int screen = 3;
	/*
	0 = home screen
	1 = autonomous selection
	2 = battery voltage
	3 = match display
	4 = lift
	*/
	const int AUTONS = 7;
	string names[AUTONS];
	names[0]="4 Cone Field";
	names[1]="20 Preloads";
	names[2]="5 Preloads";
	names[3]="Stat Defensive";
	names[4]="Stat Fielding";
	names[5]="6 Cone 5 Point";
	names[6]="4 Cone 5 Point";


	int selected = 0;

	const int SCREENS = 5;//number of screens not including home screen
	string options[SCREENS];//for selections in home screen
	options[0] = "Autono"; options[1] = "Battry"; options[2] = "Disply"; options[3] = "Lift H"; options[4]="DREAD";

	while(true){

		while (screen == 0){//home screen

			clearLCDLine(0);
			clearLCDLine(1);

			string output = "";
			output+=options[(selected+(SCREENS-1))%SCREENS];
			output+="<  >";
			output+=options[(selected+1)%SCREENS];
			displayLCDString(0,0,output);

			output=">";
			output+=options[selected];
			output+="<";
			displayLCDCenteredString(1,output);

			if(nLCDButtons==1){//left button
				selected=(selected+(SCREENS-1))%SCREENS;//select previous option
				wait1Msec(delayAmount);}
			if(nLCDButtons==2){//center button
				screen = selected+1;//go to selected screen
				wait1Msec(delayAmount);
				waitUntilButtonRelease();
				break;}
			if(nLCDButtons==4){//right button
				selected=(selected+1)%SCREENS;//select next option
				wait1Msec(delayAmount);}

			wait1Msec(delayAmount);
		}//end screen 0

		while (screen == 1){//autonomous selection


			clearLCDLine(0);
			clearLCDLine(1);


			//printing:
			string output = "";
			output+=names[selectedAuton];
			displayLCDString(0,0,output);

			output = "Side: ";
			if(autonSide) output+="Right";
				else output+="Left";
			displayLCDString(1,0, output);

			//button handling:
			if(nLCDButtons==1){//left button
				selected = 0;
				screen = 0;
				waitUntilButtonRelease();
				break;}//exit to home screen

			if(nLCDButtons==2){//center button
				autonSide = autonSide!=true;//toggle selected auton element
				waitUntilButtonRelease();}
			if(nLCDButtons==4){//right button
				selectedAuton = (selectedAuton+1)%AUTONS;//cycle selected element
				waitUntilButtonRelease();}



			wait1Msec(delayAmount);

		}//end of screen 1


		while(screen == 2){//battery
			clearLCDLine(0);
			clearLCDLine(1);

			//Display the Primary Robot battery voltage
			displayLCDString(0, 0, "M:");
			sprintf(str, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V');//main battery
			displayNextLCDString(str);
			displayNextLCDString(" E:");
			sprintf(str, "%1.2f%c", SensorValue[expander]/275.0,'V');//expander battery
			displayNextLCDString(str);

			//Display the Backup battery voltage
			displayLCDString(1, 0, "Backup: ");
			sprintf(str, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');//backup battery
			displayNextLCDString(str);

			//Short delay for the LCD refresh rate
			wait1Msec(delayAmount);

			//handling buttons:
			if(nLCDButtons==1){//left button
				screen = 0;
				waitUntilButtonRelease();
				break;
			}

			wait1Msec(delayAmount);
		}//end of screen 2

		while(screen == 3){//match display
			clearLCDLine(0);
			clearLCDLine(1);

			string output = "A:----";
			output+=" Bat:";
			sprintf(str, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V');//builds main battery voltage
			output+=str;
			displayLCDString(0,0,output);
			output = "Cones: ";
			sprintf(str, "%d", cones);
			output+=str;
			displayLCDString(1,0,output);

			//handling buttons:
			if(nLCDButtons==1){//left button
				screen = 0;
				waitUntilButtonRelease();
				break;}//back to home screen
			if(nLCDButtons==2){//center button
				if(cones>0) cones--;//decrement cone counter if its not zero
				waitUntilButtonRelease();}
			if(nLCDButtons==4){//right button
				cones++;//increment cone counter
				waitUntilButtonRelease();}
			if(nLCDButtons==6){//center and right buttons
				cones=0;
				waitUntilButtonRelease();}



			wait1Msec(delayAmount);
		}//end of screen 3

		while(screen==4){//lift

			clearLCDLine(0);
			clearLCDLine(1);

			displayLCDString(0,0,"Lift: ");

			sprintf(str, "%d", nMotorEncoder(liftL));
			displayNextLCDString(str);
			//displayLCDString(1,0,"Center to Reset");

			//handling buttons:
			if(nLCDButtons==1){
				screen = 0;
				waitUntilButtonRelease();
				break;//back to main screen
			}

			/*if(nLCDButtons==2){
				waitUntilButtonRelease();
				clearLCDLine(0);
				clearLCDLine(1);
				displayLCDCenteredString(0,"Resetting Gyro");
				displayLCDCenteredString(1,"lul");
				wait1Msec(500);
				wait1Msec(500);
			}*/

			wait1Msec(delayAmount);

		}//end of screen 4

		while(screen==5){
			clearLCDLine(0);
			clearLCDLine(1);

			GenericWait(500);
			displayLCDCenteredString(0,"DREADNOUGHT");
			GenericWait(500);
			displayLCDCenteredString(1,"Now Loading:");
			GenericWait(1000);
			clearLCDLine(1);
			GenericWait(400);
			displayLCDCenteredString(1,"EpicReveal.mp4");
			GenericWait(1300);
			clearLCDLine(1);
			GenericWait(400);
			displayLCDCenteredString(1,"[--------------]");
			GenericWait(500);
			for(int i = 1; i < 15; i++){
				displayLCDChar(1,i,'X');
				GenericWait(400-28*i);
			}
			GenericWait(100);
			clearLCDLine(1);
			GenericWait(400);
			displayLCDCenteredString(1,"[XXXXXXXXXXXXXX]");
			GenericWait(400);
			clearLCDLine(1);
			GenericWait(400);
			displayLCDCenteredString(1,"[XXXXXXXXXXXXXX]");
			GenericWait(400);
			displayLCDCenteredString(1,"ENGAGE");
			GenericWait(2000);
			clearLCDLine(0);
			clearLCDLine(1);
			GenericWait(750);
			screen=0;
			break;

		}//end of screen 5


		wait1Msec(delayAmount);

	}//end of while(true)





}//end of LCD task
