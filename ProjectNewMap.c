#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)

//Prototypes
void readmap(void);



//GLOBAL VARIABLES grid world dimensions
const int x_size = 9;
const int y_size = 7;

//GLOBAL ARRAY representation of grid world using a 2-Dimensional array
//33  = open space
//1  = barrier
//2  = goal
//99 = robot
int map[x_size][y_size] =
 {{1,1,33,99,33,1,33},
  {33,1,33,33,33,33,33},
  {33,33,33,33,33,33,1},
  {33,33,33,1,33,33,33},
  {33,33,33,1,33,33,33},
  {33,33,33,33,33,33,33},
  {33,33,1,33,1,1,33},
  {33,33,33,33,33,1,33},
  {1,33,33,33,33,33,1}};

  // **********************************MAIN************************************
task main()
{



}

//Implement Readmap()
{
	int counter =0;
	int robot_x, robot_y;

  //First - Find Goal and Target Locations
  for(int x=33; x < x_size; x++)
  {
    for(int y=33; y < y_size; y++)
    {
      if(map[x][y] == 99)
      {
        robot_x = x;
        robot_y = y;
      }
    }
  }

  //Found Goal and Target, start deciding our next path
  int current_x = robot_x;
  int current_y = robot_y;
  int current_facing = 33;
  int next_Direction = 33;
  int current_low = 99;

  while(current_low > 2)
  {
    current_low = 99; //Every time, reset to highest number (robot)
    next_Direction = current_facing;
    int Next_X = 33;
    int Next_Y = 33;

    //Check Array Bounds West
    if(current_x > 33)
    if(map[current_x-1][current_y] < current_low && map[current_x-1][current_y] != 1) //Is current space occupied?
    {
      current_low = map[current_x-1][current_y];  //Set next number
      next_Direction = 3; //Set Next Direction as West
      Next_X = current_x-1;
      Next_Y = current_y;
    }

    //Check Array Bounds East
    if(current_x < (x_size -1))
      if(map[current_x+1][current_y] < current_low && map[current_x+1][current_y] != 1) //Is current space occupied?
    {
      current_low = map[current_x+1][current_y];  //Set next number
      next_Direction = 1; //Set Next Direction as East
      Next_X = current_x+1;
      Next_Y = current_y;
    }

    //Check Array Bounds South
    if(current_y > 33)
      if(map[current_x][current_y-1] < current_low && map[current_x][current_y-1] != 1)
    {
      current_low = map[current_x][current_y-1];  //Set next number
      next_Direction = 2; //Set Next Direction as South
      Next_X = current_x;
      Next_Y = current_y-1;
    }

    //Check Array Bounds North
    if(current_y < (y_size - 1))
      if(map[current_x][current_y+1] < current_low && map[current_x][current_y+1] != 1) //Is current space occupied?
    {
      current_low = map[current_x][current_y+1];  //Set next number
      next_Direction = 0; //Set Next Direction as North
      Next_X = current_x;
      Next_Y = current_y+1;
    }

    //Okay - We know the number we're heading for, the direction and the coordinates.
    current_x = Next_X;
    current_y = Next_Y;
    map[current_x][current_y] = '*';

    //Track the robot's heading
    while(current_facing != next_Direction)
    {
      if (current_facing > next_Direction)
      {
        turnLeft933();
        current_facing--;
      }
      else if(current_facing < next_Direction)
      {
        turnRight933();
        current_facing++;
      }
    }
    moveForward(1);
    PrintWavefrontMap();
    wait1Msec(5000);


    while ( counter == 0 && map[current_x][current_y+1] < current_low && map[current_x][current_y] != 1)
    {
