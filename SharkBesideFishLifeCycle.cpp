#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

vector<int> checkSharkBesideFish(char grid[3][5], int sharkRow, int sharkCol, int locationLength)//is the shark near a fish to eat?
{
	int fishFound = 0;
	vector<int> fishLocation;
	int rowLoc = 0;
	int colLoc = 0;
	//function to check if shark has any fish to eat
	//NOT EATING FUNCTION, that will be called after
	//shark is at [1][1]
	//have to check for fish at;
	//[0][1] : row above, same column
	//[2][1] : row below, same column
	//[1][0] : same row, left column
	//[1][2] : same row, right column

	//1: Get into the grid
	while (fishFound == 0)
	{
		for (int r = 0; r < 20; r++)
		{
			for (int c = 0; c < 50; c++)
			{
				if (r = sharkRow && c == sharkCol)
				{
					//found where shark is in the grid
					if (grid[r - 1][c] == 'f')
					{
						//found a fish, nom nom!
						rowLoc = r - 1;
						colLoc = c;
						fishFound = 1;
					}
					else if (grid[r + 1][c] == 'f')
					{
						//found a fish, nom nom!
						rowLoc = r + 1;
						colLoc = c;
						fishFound = 1;
					}
					else if (grid[r][c - 1] == 'f')
					{
						//found a fish, nom nom!
						rowLoc = r;
						colLoc = c - 1;
						fishFound = 1;
					}
					else if (grid[r][c + 1] == 'f')
					{
						//found a fish, nom nom!
						rowLoc = r;
						colLoc = c + 1;
						fishFound = 1;
					}
				}
			}
		}
	}
	fishLocation.push_back(rowLoc);
	fishLocation.push_back(colLoc);//pushing the two values for row and column into a vector so that can be returned to locate fish


	//the first location we find to be occupied by a fish
	//we set the value to be 1 and send back the location eg: [0][1]
	//for the shark to  eat and kill fish 
	return fishLocation;
}//end function 

int main()
{
	//life cycle variables 
	int completeLifeCycle = 10; //really is 300 but for testing, less is more.
	int lifeCycleStep = 0;
	//shark eating and starving variables
	int sharkStarveTime = 4;
	int sharkLastEatTime = 0;
	bool sharkBesideFish = false;
	//shark breed variables
	int sharkBreedTime = 6; //constant
	int sharkTime = 0; //counter of time 
	//fish breed variables
	int fishBreedTime = 2; //constant
	int fishTime = 0; //counter of time


	char arr[3][5];
	for (int i = 0; i < 3; ++i)//initisalising empty grid
	{
		for (int j = 0; j < 5; ++j)
		{
			arr[i][j] = '_';
		}
	}
	arr[0][1] = 'f';//causing a collision up
	arr[1][1] = 's';//causing a collision down
	arr[1][2] = '_';//causing a collision to the right
	arr[1][0] = '_';//"" "" "" to the left
	
	while (lifeCycleStep < completeLifeCycle)//big loop for the simulation
	{
		int sTrackRow = 1;
		int sTrackCol = 1;
		int fishRow = 0;
		int fishCol = 0;
		//WILL NEED THE FOR LOOPS HERE TO STEP THROUGH THE 2D ARRAY
		//move function call here

		vector<int> sharkBesideFishResult = checkSharkBesideFish(arr, sTrackRow, sTrackCol, 2);
		//check sharkBesideFishResult to see if the shark can eat and RESET BOOL SHARKBESIDEFISH TO TRUE
		if (sharkBesideFishResult.empty() == false)//a fish location was sent back
		{
			sharkBesideFish = true;
			//this is to find the fish location so we can remove it from the grid in the 'else if' statement
			while (!sharkBesideFishResult.empty())//while theres still a value in the vector
			{
				fishCol = sharkBesideFishResult.back();
				fishRow = sharkBesideFishResult.back();
				//push back for fish location to use when eat() is called 
			}
		} 
		
		if (sharkLastEatTime == sharkStarveTime - 1 && sharkBesideFish == false)
		{
			//remove shark from the vector and grid
			cout << "shark dies" << endl;
			sharkLastEatTime = 0;
		}
		else if (sharkBesideFish == true)//not going in here yet
		{
			//eat();
			//remove fish from the vector and grid using the vector sharkBesideFishResult coordinates
			sharkLastEatTime = 0;
			cout << "shark lives for another turn" << endl;
		}
		else
		{
			sharkLastEatTime++;
			cout << "shark closer to starving" << endl;
		}

		if (sharkTime == sharkBreedTime)
		{
			//increase number of sharks
			//add shark vector to the array
			//call displayGrid() function to get the shark added
			cout << "new baby shark" << endl;
			sharkTime = 0;//reset the shark breed counter	
		}

		if (fishTime == fishBreedTime)
		{
			//increase number of fish
			//add fish vector to the array
			//call displayGrid() function to get the fish added
			cout << "new baby fish" << endl;
			fishTime = 0;//reset the fish breed counter
		}
		//every iteration, shark will grow older to breed
		sharkTime++;
		//every iteration, fish will get older
		fishTime++;
		
		//the last thing that happens in this loop
		cout << "life cycle iteration is: " << lifeCycleStep << endl;
		lifeCycleStep++;
	}

	cin.get();
	return 0;
}