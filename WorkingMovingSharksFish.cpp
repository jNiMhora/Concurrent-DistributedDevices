// Wa-Tor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Shark.h"
#include "Fish.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

char(*Move(vector<Shark>& sTracker, vector<Fish>& fTracker, char type, char grid[][50], size_t sz))[50]
{//This changes objects positions in the grid & checks for collions between positions beofre moving
	int i;
char move;
int sRow;
int sCol;
int fRow;
int fCol;
int movePos; //used to randomise the choice of movement 
bool newPos = false; //used to break out of while loop when a new position is found or shark or fish cant move 
bool Down = true; //if cant move D,U,L,R set to false so it doesnt check to move down in the next iteration 
bool Up = true;
bool Left = true;
bool Right = true;
srand(time(NULL));

if (type == 's')
{
	for (i = 0; i < sTracker.size(); i++)
	{
		sRow = sTracker[i].getRow();
		sCol = sTracker[i].getCol();
		movePos = rand() % 3;//randomly choose movement 

		while (newPos == false)//keep trying to find a new position untill one is found 
		{
			//*************** DOWN ******************
			if (movePos == 0 && Down != false) //check randomised number and if down has been checked already
			{
				if (sRow < 19)
				{
					if (grid[sRow + 1][sCol] == '_') //check if shark can move down 
					{
						move = 'D';//move down
						newPos = true;//break while loop
					}
				}
				else if (sRow == 19)
				{
					if (grid[0][sCol] == '_') //check if shark can wrap back around 
					{
						grid[sRow][sCol] = '_';
						grid[0][sCol] = 'S';
						sTracker[i].setRow(0);
						move = '-';
						newPos = true;
					}
				}
				else { Down = false; } //If it cant do either this movement cant be made and is set to false 
			}
			//*************** UP ******************
			if (movePos == 1 && Up != false)
			{
				if (sRow > 0)
				{
					if (grid[sRow - 1][sCol] == '_')
					{
						//cout << "move up" << endl;
						move = 'U';//move up
						newPos = true;//break while loop
					}
				}
				else if (sRow == 0)
				{
					if (grid[19][sCol] == '_')
					{
						grid[sRow][sCol] = '_';
						grid[19][sCol] = 'S';
						sTracker[i].setRow(19);
						move = '-';
						newPos = true;
					}
				}
				else { Up = false; }
			}
			//*************** LEFT ******************
			if (movePos == 2 && Left != false)
			{
				if (sCol > 0)
				{
					if (grid[sRow][sCol - 1] == '_')
					{
						//cout << "move left" << endl;
						move = 'L';//move left
						newPos = true;//break while loop
					}
				}
				else if (sCol == 0)
				{
					if (grid[sRow][49] == '_')
					{
						grid[sRow][sCol] = '_';
						grid[sRow][49] = 'S';
						sTracker[i].setCol(49);
						move = '-';
						newPos = true;
					}
				}
				else { Left = false; }
			}
			//*************** RIGHT ******************
			if (movePos == 3 && Right != false)
			{
				if (sCol < 49)
				{
					if (grid[sRow][sCol + 1] == '_')
					{
						//cout << "move right" << endl;
						move = 'R';//move right
						newPos = true;//break while loop
					}
				}
				else if (sCol == 49)
				{
					if (grid[sRow][0] == '_')
					{
						grid[sRow][sCol] = '_';
						grid[sRow][0] = 'S';
						sTracker[i].setCol(0);
						move = '-';
						newPos = true;
					}
				}
				else { Right = false; }
			}
			//*************** CANT MOVE ******************
			else if (Down == false && Up == false && Left == false && Right == false)
			{
				move = 'C';
				newPos = true;
			}
			movePos = rand() % 3;//randomly choose movement 
		}
		switch (move)
		{
		case 'D':
			//cout << " switch move down" << endl;
			grid[sRow][sCol] = '_';
			grid[sRow + 1][sCol] = 'S';
			sTracker[i].setRow(sRow + 1);
			break;
		case 'U':
			//cout << "switch move up" << endl;
			grid[sRow][sCol] = '_';
			grid[sRow - 1][sCol] = 'S';
			sTracker[i].setRow(sRow - 1);
			break;
		case 'L':
			//cout << "switch move left" << endl;
			grid[sRow][sCol] = '_';
			grid[sRow][sCol - 1] = 'S';
			sTracker[i].setCol(sCol - 1);
			break;
		case 'R':
			//cout << "switch move right" << endl;
			grid[sRow][sCol] = '_';
			grid[sRow][sCol + 1] = 'S';
			sTracker[i].setRow(sCol + 1);
			break;
		case 'C':
			break;
		}
		Down = true;
		Up = true;
		Left = true;
		Right = true;
		newPos = false;
	}
}
//************FISH********************
if (type == 'f')
{
	for (i = 0; i < fTracker.size(); i++)
	{
		fRow = fTracker[i].getRow();
		fCol = fTracker[i].getCol();
		movePos = rand() % 3;//randomly choose movement 

		while (newPos == false)//keep trying to find a new position untill one is found 
		{
			//*************** DOWN ******************
			if (movePos == 0 && Down != false) //check randomised number and if down has been checked already
			{
				if (fRow < 19)
				{
					if (grid[fRow + 1][fCol] == '_') //check if fish can move down 
					{
						move = 'D';//move down
						newPos = true;//break while loop
					}
				}
				else if (fRow == 19)
				{
					if (grid[0][fCol] == '_') //check if fish can wrap back around 
					{
						grid[fRow][fCol] = '_';
						grid[0][fCol] = 'F';
						fTracker[i].setRow(0);
						move = '-';
						newPos = true;
					}
				}
				else { Down = false; } //If it cant do either this movement cant be made and is set to false 
			}
			//*************** UP ******************
			if (movePos == 1 && Up != false)
			{
				if (fRow > 0)
				{
					if (grid[fRow - 1][fCol] == '_')
					{
						//cout << "move up" << endl;
						move = 'U';//move up
						newPos = true;//break while loop
					}
				}
				else if (fRow == 0)
				{
					if (grid[19][fCol] == '_')
					{
						grid[fRow][fCol] = '_';
						grid[19][fCol] = 'F';
						fTracker[i].setRow(19);
						move = '-';
						newPos = true;
					}
				}
				else { Up = false; }
			}
			//*************** LEFT ******************
			if (movePos == 2 && Left != false)
			{
				if (fCol > 0)
				{
					if (grid[fRow][fCol - 1] == '_')
					{
						move = 'L';//move left
						newPos = true;//break while loop
					}
				}
				else if (fCol == 0)
				{
					if (grid[fRow][49] == '_')
					{
						grid[fRow][fCol] = '_';
						grid[fRow][49] = 'F';
						fTracker[i].setCol(49);
						move = '-';
						newPos = true;
					}
				}
				else { Left = false; }
			}
			//*************** RIGHT ******************
			if (movePos == 3 && Right != false)
			{
				if (fCol < 49)
				{
					if (grid[fRow][fCol + 1] == '_')
					{
						move = 'R';//move right
						newPos = true;//break while loop
					}
				}
				else if (fCol == 49)
				{
					if (grid[fRow][0] == '_')
					{
						grid[fRow][fCol] = '_';
						grid[fRow][0] = 'F';
						fTracker[i].setCol(0);
						move = '-';
						newPos = true;
					}
				}
				else { Right = false; }
			}
			//*************** CANT MOVE ******************
			else if (Down == false && Up == false && Left == false && Right == false)
			{
				move = 'C';
				newPos = true;
			}
			movePos = rand() % 3;//randomly choose movement 
		}
		switch (move)
		{
		case 'D':
			grid[fRow][fCol] = '_';
			grid[fRow + 1][fCol] = 'F';
			fTracker[i].setRow(fRow + 1);
			break;
		case 'U':
			grid[fRow][fCol] = '_';
			grid[fRow - 1][fCol] = 'F';
			fTracker[i].setRow(fRow - 1);
			break;
		case 'L':
			grid[fRow][fCol] = '_';
			grid[fRow][fCol - 1] = 'F';
			fTracker[i].setCol(fCol - 1);
			break;
		case 'R':
			grid[fRow][fCol] = '_';
			grid[fRow][fCol + 1] = 'F';
			fTracker[i].setRow(fCol + 1);
			break;
		case 'C':
			break;
		}
		Down = true;
		Up = true;
		Left = true;
		Right = true;
		newPos = false;
	}
}
//********************
return grid;
}
void Print(char grid[20][50])
{
	for (int r = 0; r < 20; r++)
	{
		for (int c = 0; c < 50; c++)
		{
			cout << grid[r][c];
		}
		cout << endl;
	}
}
//**************************
vector<int> checkSharkBesideFish(char grid[20][50], vector<Shark>& sTracker, int locationLength)//is the shark near a fish to eat?
{
	int fishFound = 0;
	vector<int> fishLocation;
	int sharkRow = 0;
	int sharkCol = 0;
	int rowLoc = 0;
	int colLoc = 0;
	//function to check if shark has any fish to eat
	
	//1: Get into the shark tracker with for loop
	for (int i = 0; i < sTracker.size(); i++)
	{
		sharkRow = sTracker[i].getRow();
		sharkCol = sTracker[i].getCol();
		while (fishFound == 0)
		{
			//shark is at grid[sharkRow][sharkCol]
			//found where shark is in the grid
			if (grid[sharkRow - 1][sharkCol] == 'F')
			{
				//found a fish above, nom nom!
				rowLoc = sharkRow - 1;
				colLoc = sharkCol;
				fishFound = 1;
			}
			else if (grid[sharkRow + 1][sharkCol] == 'F')
			{
				//found a fish, nom nom!
				rowLoc = sharkRow + 1;
				colLoc = sharkCol;
				fishFound = 1;
			}
			else if (grid[sharkRow][sharkCol - 1] == 'F')
			{
				//found a fish, nom nom!
				rowLoc = sharkRow;
				colLoc = sharkCol - 1;
				fishFound = 1;
			}
			else if (grid[sharkRow][sharkCol + 1] == 'F')
			{
				//found a fish, nom nom!
				rowLoc = sharkRow;
				colLoc = sharkCol + 1;
				fishFound = 1;
			}
			else
			{
				//no fish near shark
				rowLoc = 100;
				colLoc = 100;
				//location being set to 100 shows that no fish was close to shark and will mean the shark lastEatTime increases
				fishFound = 1;
			}
		}
		fishFound = 0;
		
		fishLocation.push_back(sharkRow);
		fishLocation.push_back(sharkCol);

		fishLocation.push_back(rowLoc);
		fishLocation.push_back(colLoc);//pushing the two values for row and column into a vector so that can be returned to locate fish and correspoding shark
	

	}
	
	return fishLocation;
}//end function 

int main()
{
	//variables 
	char grid[20][50];//Wa-Tor World 
	srand(time(NULL));
	int i = 0;
	int Timer = 10;
	int NumShark = 5; //start number of sharks 
	int NumFish = 20; //start number of fish 
	int SharkBreed = 25; //Number of iterations before shark can breed 
	int FishBreed = 10; //Number of iterations before fish can breed 
	int starve = 4; //Number of iterations before shark starves and is deleted from vector 
	char slot = ' '; //Used for insertion into Grid
	char space = ' ';//Used for insertion into Grid
	int col = 0;  //Used for insertion into Grid
	int row = 0;  //Used for insertion into Grid
	char shark = 's'; //Used for sending to functions to ecxexute function on either fish or sharks 
	char fish = 'f';  //Used for sending to functions to ecxexute function on either fish or sharks 
	vector<Shark>sharkTracker; //Holds all current Shark objects and their details (e.g. position)
	vector<Fish>fishTracker;  //Holds all current Shark objects and their details (e.g. position)
	vector<Shark>::iterator itS;  // declare an iterator Shark vector
	vector<Fish>::iterator itF;  // declare an iterator Shark vector
	int fishCount = 0;
	int sharkCount = 0;
	//new variables
	int sharkStarveTime = 0;
	int sharkLastEatTime = 4;
	int lastEat = 0;
	bool sharkBesideFish = false;
	//shark breed variables
	int sharkBreedTime = 6; //constant
	int sharkTime = 0; //counter of time 
	//fish breed variables
	int fishBreedTime = 2; //constant
	int fishTime = 0; //counter of time
	//shark tracker variables
	int sTrackRow = 0;
	int sTrackCol = 0;
	int trackCol = 0;
	int trackRow = 0;
	//fish tracker variables
	int fishRow = 0;
	int fishCol = 0;
	int fTrackRow = 0;
	int fTrackCol = 0;

	//Intialize grid to be empty 
	for (row = 0; row < 20; row++)
	{
		for (col = 0; col < 50; col++)
		{
			grid[row][col] = '_';
		}
	}
	//insert sharks
	for (i = 0; i < NumShark; i++)
	{
		while (slot != 'E')//find position in grid for new shark object
		{
			row = rand() % 19;
			col = rand() % 49;
			space = grid[row][col];
			if (space = '_')
			{
				grid[row][col] = 'S';
				Shark s(starve, SharkBreed, sharkLastEatTime, row, col); //Create shark object 
				sharkTracker.push_back(s); //add to tracker 
				slot = 'E';
			}
		}
		slot = ' ';//reset to get back into while loop
	}
	//insert fish
	for (i = 0; i < NumFish; i++)
	{
		while (slot != 'E')//find position in grid for new fish object
		{
			row = rand() % 19;
			col = rand() % 49;
			space = grid[row][col];
			if (space = '_')
			{
				grid[row][col] = 'F';
				Fish f(FishBreed, row, col); //Create shark object 
				fishTracker.push_back(f); //add to tracker 
				slot = 'E';
			}
		}
		slot = ' ';
	}

	//Life Cycle 
	for (int j = 0; j < Timer; j++)//changed to j as i was being used elsewhere
	{
		
		//system("CLS");
		char(*ptGrids)[50] = Move(sharkTracker, fishTracker, shark, grid, 20);
		char(*ptGridf)[50] = Move(sharkTracker, fishTracker, fish, grid, 20);
		vector<int> sharkBesideFishResult = checkSharkBesideFish(grid, sharkTracker, 2);
		//this is for checking
		/*for (vector<int>::iterator it=sharkBesideFishResult.begin(); it != sharkBesideFishResult.end(); ++it)
		{
			cout << ' ' << *it << endl;
		}
		*/
		//check sharkBesideFishResult to see if the shark can eat and RESET BOOL SHARKBESIDEFISH TO TRUE

		
		while (!sharkBesideFishResult.empty())//while theres still a value in the vector
		{
			//pop off next fish
			fishCol = sharkBesideFishResult.back();
			sharkBesideFishResult.pop_back();
			fishRow = sharkBesideFishResult.back();
			sharkBesideFishResult.pop_back();
			cout << "fish at: " << fishRow << "/" << fishCol << endl;

			//pop off corresponding shark col and row
			sTrackCol = sharkBesideFishResult.back();
			sharkBesideFishResult.pop_back();
			sTrackRow = sharkBesideFishResult.back();
			sharkBesideFishResult.pop_back();
			cout << "shark at: " << sTrackRow << "/" << sTrackCol << endl;
			
			//if the location is not "empty", if there is a fish beside a shark
			if (fishRow != 100 && fishCol != 100)
			{
				sharkBesideFish = true;
			}
			else
			{
				sharkBesideFish == false;
			}
			
			if(sharkBesideFish == false)//there was no fish
			{
				int sharkSize = sharkTracker.size();
				int fishSize = fishTracker.size();

				//find current shark in vector and decrease its sharkLastEatTime by one
				for (i = 0; i < sharkTracker.size(); i++)
				{
					 trackRow = sharkTracker[i].getRow();
					 trackCol = sharkTracker[i].getCol();
					 lastEat = sharkTracker[i].getLastEatTime();
					 //if the current shark has run out of time to eat
					 if (lastEat == 0 && trackRow == sTrackRow && trackCol == sTrackCol)
					 {
						 //remove shark from the vector
						 sharkTracker.erase(sharkTracker.begin() + i);
						 NumShark--;
						 //remove shark from grid
						 grid[trackRow][trackCol] = '_';							//IS THIS ALRIGHT TO REMOVE THE SHARK FROM GRID?

						 //remove this shark using the current location points
						 cout << "shark dies" << endl;
					 } 
					 //current shark is still hungry
					 else if (trackRow == sTrackRow && trackCol == sTrackCol)
					 {
						 //cout << lastEat << endl;
						 sharkLastEatTime = lastEat - 1;
						 sharkTracker[i].setLastEatTime(sharkLastEatTime);
						// int check = sharkTracker[i].getLastEatTime();
						// cout << check << endl;
						cout << "shark closer to starving" << endl;
						
					 }
					
					 
				}
			}
			else if (sharkBesideFish == true)
			{
				//remove fish from the vector using the current fishCol and fishRow 
				for (i = 0; i < fishTracker.size(); i++)
				{
					fTrackRow = fishTracker[i].getRow();
					fTrackCol = fishTracker[i].getCol();

					//find the current fish to take it out
					if (fishRow == fTrackRow && fishCol == fTrackCol)
					{
						//remove fish from the vector 
						fishTracker.erase(fishTracker.begin() + i);
						NumFish--;
						//remove fish from grid
						grid[fTrackRow][fTrackCol] = '_';						//IS THIS ALRIGHT TO REMOVE THE FISH FROM GRID?

						//cout << "fish eaten" << endl;
						//cout << "numFish" << NumFish << endl;
					}
				}
				//reset the current shark's last eat time
				for (i = 0; i < sharkTracker.size(); i++)
				{
					trackRow = sharkTracker[i].getRow();
					trackCol = sharkTracker[i].getCol();
					//lastEat = sharkTracker[i].getLastEatTime();
					//cout << lastEat << endl;

					//find current shark in the vector of sharks to update its value
					if (trackRow == sTrackRow && trackCol == sTrackCol)
					{
						sharkLastEatTime = 4;
						sharkTracker[i].setLastEatTime(sharkLastEatTime);
						//int doubleCheck = sharkTracker[i].getLastEatTime();
						//cout << "update last eat time" << doubleCheck << endl;

						cout << "shark lives for another turn" << endl;
						
					}

				}  
				sharkBesideFish = false;//resets so the sharks dont become invincible 
			}
		}
		
		///BREED METHODS
		//every iteration, shark will grow older to breed
		sharkTime++;
		//every iteration, fish will get older
		fishTime++;
		if (sharkTime == SharkBreed)
		{
			while (slot != 'E')//find position in grid for new shark object
			{
				row = rand() % 19;
				col = rand() % 49;
				space = grid[row][col];
				if (space = '_')
				{
					grid[row][col] = 'S';
					Shark s(starve, SharkBreed, sharkLastEatTime, row, col); //Create shark object 
					sharkTracker.push_back(s); //add to tracker 
					NumShark++;
					sharkTime = 0;
					slot = 'E';
				}
			}
			slot = ' ';
		}
		if (fishTime == FishBreed)
		{
			while (slot != 'E')//find position in grid for new fish object
			{
				row = rand() % 19;
				col = rand() % 49;
				space = grid[row][col];
				if (space = '_')
				{
					grid[row][col] = 'F';
					Fish f(FishBreed, row, col); //Create shark object 
					fishTracker.push_back(f); //add to tracker 
					NumFish++;
					fishTime = 0;
					slot = 'E';
				}
			}
			slot = ' ';
		}
			
		Print(grid);
		cout << endl;
		cout << "Number of Fish: " << NumFish << ' ' << "Number of Sharks: " << NumShark << endl;

	}
	
	cin.get();
	return 0;
}
