#pragma config(Sensor, S1,     lightSensor,    sensorLightActive)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)

//Prototypes
void countingLines (void);
void displayNumberCentre(int num);
void blackSensor(void);


int r = 2230;


task main()
{


	nMotorEncoder[motorC]=0;
	nMotorEncoder[motorB]=0;

	while(nMotorEncoder[motorC] <r && nMotorEncoder[motorB] <r)
	{
		motor[motorC]=50;
		motor[motorB]=50;

		//Calling Function countingLines();
		countingLines ();
		//Call Function displayNumberCentre();
		displayNumberCentre(100);
	}
	while(nMotorRunState[motorC] != runStateIdle)
	{
		motor[motorC]=0;
		motor[motorB]=0;
	}

}

//Implementing countingLines
void countingLines ()
{
	int count=0;
	int count2=0;

	while (nMotorEncoder[motorC] <r && nMotorEncoder[motorB] <r)
	{
		if (SensorValue(lightSensor) < 45)
		{
			while (count2==0)
			{
				if (SensorValue(lightSensor) > 45)
				{
					count++;
					count2=1;
					wait1Msec(20);
				}//End inner if
			}//End inner while
		}//End outer if

		displayNumberCentre(count);
		count2=0;

	}//End  outer while
}//End countingLines

//Implementing displayNumberCentre
void displayNumberCentre(int num)
{
		nxtDisplayCenteredTextLine(3, "%d", num);
}//End displayNumberCentre

void blackSensor(void)
{
	while(SensorValue(lightSensor) < 40 )
	{
		nMotorEncoder[motorB] = 0;
		nMotorEncoder[motorC] = 0;
		nMotorEncoderTarget[motorB] = 60;
		nMotorEncoderTarget[motorC] = 60;
		motor[motorB] = 50;
		motor[motorC] = 50;
		wait1Msec(300);

		if(SensorValue(lightSensor) < 40 )
		{
			motor[motorB] = -50;
			motor[motorC] = -50;
			wait1Msec(300);

			motor[motorB] = -50;
			motor[motorC] = 50;
			wait1Msec(300);
		}
	}
}










