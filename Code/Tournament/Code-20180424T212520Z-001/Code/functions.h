///////////////
// FUNCTIONS///
///////////////

//Position Functions
void resetEncoders() {SensorValue(left)=0; SensorValue(right)=0; SensorValue(liftE)=0; target[0]=target[1]=0;}

void resetError() {totalError[0]=totalError[1]=0;}

void Intake(string *dir){
	if(*dir == "In"){motor[intake]=-127;}
	if(*dir == "Out"){motor[intake]=127;}
	if(*dir == "Stop"){motor[intake]=-25;}
	if(*dir == "StopForReal"){motor[intake]=0;}  delay(2); }


void Cone_Bar(int pos){ target[4]=pos; }


void Lift(int pwr){PIDon[5]=0; motor[liftL]=motor[liftR]=pwr;}


void LiftPos (int pos){PIDon[5]=1; target[5]=pos; delay(2);}

void LiftGo (int pos, int timeout=2000) { int s = SensorValue(liftE);
	Lift(127*sgn(s-pos));
	for(int i=0;i<timeout/10;i++){
		if(sgn(motor[liftL])==1){ if(SensorValue(liftE)<pos||vexRT[Btn5U]||vexRT[Btn5D]){break;} } //up
		if(sgn(motor[liftL])==-1){ if(SensorValue(liftE)>pos||vexRT[Btn5U]||vexRT[Btn5D]){break;} } //down
	delay(10);
}
Lift(0);
	}


void Goal(int pos){PIDon[3]=1; target[3]=pos; delay(2);}


void Forward(float rot) {PIDon[0]=PIDon[1]=1;
	kP[0]=kP[1]=0.30; kI[0]=kI[1]=0.0; kD[0]=kD[1]=0.06;
	resetError(); target[0]+=rot*360; target[1]+=rot*360; delay(5);}


void Turn(float rot) {PIDon[0]=PIDon[1]=1; SensorValue(left)=0; SensorValue(right)=0; resetError();
		kP[0]=kP[1]=0.85; kI[0]=kI[1]=0.02; kD[0]=kD[1]=0.05;
											target[0]=rot*360*turnSign; target[1]=-rot*360*turnSign; delay(5);}


void Wait(int pidchannel, int range, int timeout=3000) { int time=0;
	int Ldir = sgn(target[0]-SensorValue(left)); int Rdir = sgn(target[1]-SensorValue(right));

	if(pidchannel==0) {//Drive
		for(int i=0; i<timeout/10; i++){
			if(fabs(SensorValue(left)-target[0])*0.4+fabs(SensorValue(right)-target[1])*0.4<range){break;}
		delay(10); }
		//Brake
		PIDon[0]=PIDon[1]=0; resetError();
		motor[BL]=motor[FL]=-45*Ldir; motor[BR]=motor[FR]=-45*Rdir;
		delay(130);
		 motor[BL]=motor[FL]=motor[BR]=motor[FR]=0;  PIDon[0]=PIDon[1]=0;  }
//Goal
	if(pidchannel==3){while(fabs(SensorValue(goalpot)-target[3])>range&&time*10<timeout){delay(10); time++;
			if(vexRT[Btn5U]||vexRT[Btn5D]){break;}  }}//end of loop
//4 Bar
	if(pidchannel==4){while(fabs(SensorValue(conepot)-target[4])>range&&time*10<timeout){delay(10); time++;
			if(vexRT[Btn5U]||vexRT[Btn5D]){break;}  }}//end of loop
//Lift
	if(pidchannel==5){while(fabs(nMotorEncoder(liftR)-target[5])>range&&time*10<timeout){delay(10); time++;
			if(vexRT[Btn5U]||vexRT[Btn5D]){break;}  }}//end of loop
}//end of function


void GenericWait(int timeout){
	for(int i = 0; i*10 < timeout; i++){
		delay(10);
		if(vexRT[Btn5U]||vexRT[Btn5D]){
			break;
		}
	}
}//end of function


/////////////////////////////
///PRELOAD STACK FUNCTIONS///
/////////////////////////////


//Stack stuff
void Cone1()
{			//Down
			Intake("Stop");
			Cone_Bar(CONEBARIN);
			Lift(-65);
			Wait(4,240, 500);
			GenericWait(130);
			//Place
			Intake("Out");
			GenericWait(170);
			Lift(127);
			//Up
			Cone_Bar(CONEBAROUT);
			GenericWait(250);
			//Back Down
			Intake("In");
			Lift(-127);
			GenericWait(210);
			cones++;
}
void Cone2()
{				Intake("Stop");
			Cone_Bar(CONEBARIN);
			Wait(4,240, 600);
			//Place
			GenericWait(110);
			Lift(-70);
			GenericWait(140);
			Intake("Out");
			GenericWait(140);\
			//Up
			Lift(127);
			GenericWait(100);
			Cone_Bar(CONEBAROUT);
			GenericWait(270);
			//Back Down
			Intake("In");
			Lift(-127);
			GenericWait(280);
			Lift(0);
			cones++;
}
void Cone3()
{			//Down
			Intake("Stop");
			Cone_Bar(CONEBARIN);
			Lift(50);
			GenericWait(250);
			//Place
			Lift(-65);
			GenericWait(120);
			Intake("Out");
			GenericWait(120);
			//Up
			Lift(127);
			GenericWait(200);
			Cone_Bar(CONEBAROUT);
			GenericWait(250);
			//Back Down
			Intake("In");
			Lift(-120);
			GenericWait(300);
			cones++;
}

void Cone4(){
			Intake("Stop");
			Lift(127);
			Cone_Bar(CONEBARIN);
			Wait(4,300, 250);
			//Place
			Lift(-65);
			GenericWait(100);
			Intake("Out");
			GenericWait(130);
			//Up
			Lift(127);
			GenericWait(130);
			Cone_Bar(CONEBAROUT);
			GenericWait(260);
			//Back Down
			Intake("In");
			Lift(-127);
			GenericWait(350);
			cones++;
}
void Cone2a()
{				Intake("Stop");
			Cone_Bar(CONEBARIN);
			Lift(20);
			Wait(4,240, 600);
			//Place
			Lift(-127);
			GenericWait(120);
			Intake("Out");
			GenericWait(140);
			//Up
			Lift(127);
			GenericWait(100);
			Cone_Bar(CONEBAROUT);
			GenericWait(260);
			//Back Down
			Intake("In");
			Lift(-127);
			GenericWait(280);
			Lift(0);
			cones++;
}

void Cone3a()
{			//Down
			Intake("Stop");
			Lift(40);
			Cone_Bar(CONEBARIN);


			Wait(4,240, 600);
			//Place
			Lift(-60);
			GenericWait(140);
			Intake("Out");
			GenericWait(120);
			//Up
			Lift(127);
			GenericWait(190);
			Cone_Bar(CONEBAROUT);
			GenericWait(250);
			//Back Down
			Intake("In");
			Lift(-120);
			GenericWait(300);
			cones++;
}

void Cone4a(){
			Intake("Stop");
			LiftGo(-200);
			GenericWait(80);
			Cone_Bar(CONEBARIN);
			Wait(4,300, 800);
			//Place
			Lift(-127);
			GenericWait(280);
			Intake("Out");
			GenericWait(100);
			//Up
			Lift(127);
			GenericWait(100);
			Cone_Bar(CONEBAROUT);
			GenericWait(230);
			//Back Down
			Intake("In");
			Lift(-127);
			GenericWait(350);
			cones++;
}
void ConeRest()
{			//Up
			Intake("Stop");
			Cone_Bar(CONEBAROUT);// bar out
			Lift(127);//up
			LiftGo(-cheight[cones]+30);
			Cone_Bar(CONEBARIN);//start bringing in
			LiftGo(-cheight[cones]);
			//Place
			Wait(4,350,800);
			Lift(-100);
			GenericWait(120);
			Intake("Out");
			GenericWait(70);

			//Off stack
			Cone_Bar(CONEBAROUT);
			Lift(127);
			GenericWait(210);

			LiftGo(-fheight[cones]-11);//get back over the cone placed
			GenericWait(200);

			//Back Down
			Intake("In");
			LiftGo(LIFTPRELOAD-25);
			if(cones<19){cones++;}
}
