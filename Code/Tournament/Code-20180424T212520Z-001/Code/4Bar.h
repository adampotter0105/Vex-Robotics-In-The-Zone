
task fourBarNORforbar()
{	while(true){
	//Infinite Loop
if(PIDon[4]) {
	int move=0; //currently going full power

switch (target[4]){

case CONEBARIN:
	while(PIDon[4]&&SensorValue(conepot)>CONEBARIN+300){motor[conebar]=127; move=1;}//full power until
		if(move==1){
			for(int i=0; i<25; i++){delay(10);
				if(target[4]!=CONEBARIN||PIDon[4]==0){break;}
			}
				move=0;}
	if(PIDon[4]){motor[conebar]=-kP[4]*(target[4]-SensorValue(conepot));}//PID
	else { motor[conebar]=0;}
	break;

case CONEBAROUT:
	while(PIDon[4]&&SensorValue(conepot)<CONEBAROUT-300&&target[4]==CONEBAROUT){motor[conebar]=-127;}//full power until
	if(PIDon[4]){motor[conebar]=-kP[4]*(target[4]-SensorValue(conepot));}//PID
	else {motor[conebar]=0;}
	break;

default:
	motor[conebar]=-kP[4]*(target[4]-SensorValue(conepot));
	break;
}

delay(10);

		}  //end of if
	} //end of while
} //end of task
