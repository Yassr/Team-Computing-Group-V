#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)

task main()
{
	int object1Dist; // Distance from start to first object
	int object2Dist; // Distance from first to second object
	int stopDist = 15; // Stopping distance before objects
	int turnDist = 180; // Encoder counts that wheels rotate during each 90-degree turn
	int fwdPower = 30; // Motor power when robot drives forward
	int turnPower = 10; // Motor power when robot turns

	// Searching for the first object
	nMotorEncoder[motorB] = 0; // Sets the motorD encoder to zero

	while (SensorValue[sonarSensor] > stopDist) // Moves forward until within 15 cm (stopDist) of first object
	{
		motor[motorB] = fwdPower;
		motor[motorC] = fwdPower;
	}
		motor[motorB] = 0; // Stop motors and make the robot wait for half a second
		motor[motorC] = 0;
		wait1Msec(500);

		object1Dist = nMotorEncoder[motorB]; // Sets distance from start to first object
		nMotorEncoder[motorB] = 0; // Resets the motor encoder of motor D to zero

	while (nMotorEncoder[motorB] < turnDist) // Must tweak the turnDist encoder count value so that robot turns 90 degrees
	{
		motor[motorB] = turnPower;
		motor[motorC] = -turnPower;
	}
		motor[motorB] = 0;
		motor[motorC] = 0;
		wait1Msec(500);

		// Searching for the second object
		nMotorEncoder[motorB] = 0;

		while (SensorValue[sonarSensor] > stopDist) // Moves forward until within 15 cm (stopDist) of second object
		{
			motor[motorB] = fwdPower;
			motor[motorC] = fwdPower;
		}
			motor[motorB] = 0;
			motor[motorC] = 0;
			wait1Msec(500);

			object2Dist = nMotorEncoder[motorB]; // Sets distance from first to second object
			nMotorEncoder[motorB] = 0;

		while (nMotorEncoder[motorB] < turnDist)
		{
			motor[motorB] = turnPower;
			motor[motorC] = -turnPower;
		}
			motor[motorB] = 0;
			motor[motorC] = 0;
			wait1Msec(500);

			// Begins to travel back to the start
			nMotorEncoder[motorB] = 0;
			while (nMotorEncoder[motorB] < object1Dist)
		{
			motor[motorB] = fwdPower;
			motor[motorC] = fwdPower;
		}

			motor[motorB] = 0;
			motor[motorC] = 0;
			wait1Msec(500);

			nMotorEncoder[motorB] = 0;

			while (nMotorEncoder[motorB] < turnDist)
		{
			motor[motorB] = turnPower;
			motor[motorC] = -turnPower;
		}
			motor[motorB] = 0;
			motor[motorC] = 0;
			wait1Msec(500);

		// Drives back to starting point
		nMotorEncoder[motorB] = 0;

		while (nMotorEncoder[motorB] < object2Dist)
		{
			motor[motorB] = fwdPower;
			motor[motorC] = fwdPower;
		}
			motor[motorB] = 0;
			motor[motorC] = 0;
}
