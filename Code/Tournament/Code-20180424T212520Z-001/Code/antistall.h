//Prevents stalling in auton

task antistall()
{	float velocityL;
	float velocityR;
	int prevL = SensorValue(left);
	int prevR = SensorValue(right);
	int streakL=0;
	int streakR=0;
	const int RpmCutoff = 15;
	const int MotorMin = 50;
	const float SecStreak = 1.2;

	while(true)
{		//Calculating velocity
		velocityL=fabs(SensorValue(left)-prevL);
		velocityR=fabs(SensorValue(right)-prevR);
		prevL=nMotorEncoder[BL];
		prevR=nMotorEncoder[BR];
		//Threshold for cuttoff is 15 rpm
		if(velocityL<1.5*RpmCutoff && motor[BL]>MotorMin){streakL++;}
		else{streakL=0;}

		if(velocityR<1.5*RpmCutoff && motor[BR]>MotorMin){streakR++;}
		else{streakR=0;}

		//3 sec stall cuts motors
		if(streakL>SecStreak/0.25){stall=0;}
		if(streakR>SecStreak/0.25){stall=0;}

		delay(250); //1/5 sec

}
}
