///////////////////////
////Kick Ass Auton! ///
///////////////////////

//Goal 1
Forward(1);
/*Wait(0.5);
Goal("Out");
Wait();
Claw("Out");
GyTurn(90);*/
//Goal 2

//Goal 3

//Goal 4

//Goal 5

//Goal 6

//Goal 7

//Goal 8

//Park

//Done!

/*Documentation for Tasks and Functions
Task: PID()
	controls bar and goal intake, controlled by "target" and "targetgoal"
Task: Autobar()
	changes between 4 states(including starting) during auton
Task: Move()
	if "go" or "turn" are set not zero, pid pulls drive to target
	untile reaches deadzone, then brakes
Function: Forward()
	moves forward or backwards with float argument in feet
Function: GyTurn()
	turns with argument int degrees clockwise positive
Function: Goal()
	moves goal intake with argument "In" or "Out"
Function: Claw()
	moves bar and claw between states with arguments "Out", "Grab", "Place"
Function: Wait()
	by default, it waits untile movement is complete ("go" or "turn" = 0)
	with argument in feet progress, it breaks when forward() is "progress" into movement
*/
