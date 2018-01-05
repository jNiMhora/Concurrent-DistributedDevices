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
			if (grid[sharkRow - 1][sharkCol] == 'f')
			{
				//found a fish above, nom nom!
				rowLoc = sharkRow - 1;
				colLoc = sharkCol;
				fishFound = 1;
			}
			else if (grid[sharkRow + 1][sharkCol] == 'f')
			{
				//found a fish, nom nom!
				rowLoc = sharkRow + 1;
				colLoc = sharkCol;
				fishFound = 1;
			}
			else if (grid[sharkRow][sharkCol - 1] == 'f')
			{
				//found a fish, nom nom!
				rowLoc = sharkRow;
				colLoc = sharkCol - 1;
				fishFound = 1;
			}
			else if (grid[sharkRow][sharkCol + 1] == 'f')
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
		//SEND BACK DOWN THE SHARK LOCATION AS WELL
		//put shark in first 

		fishLocation.push_back(rowLoc);
		fishLocation.push_back(colLoc);//pushing the two values for row and column into a vector so that can be returned to locate fish

	}
	//the first location we find to be occupied by a fish
	//we set the value to be 1 and send back the location eg: [0][1]
	//for the shark to  eat and kill fish 
	//fishLocation.push_back(rowLoc);
	//fishLocation.push_back(colLoc);//pushing the two values for row and column into a vector so that can be returned to locate fish

	return fishLocation;
}//end function 

int main()
{
	//variables 
	char grid[20][50];//Wa-Tor World 
	srand(time(NULL));
	int i = 0;
	int Timer = 500;
	int NumShark = 5; //start number of sharks 
	int NumFish = 10; //start number of fish 
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
	int sharkStarveTime = 4;
	int sharkLastEatTime = 0;
	bool sharkBesideFish = false;
	//shark breed variables
	int sharkBreedTime = 6; //constant
	int sharkTime = 0; //counter of time 
	//fish breed variables
	int fishBreedTime = 2; //constant
	int fishTime = 0; //counter of time
	//shark tracker variables
	int sTrackRow = 1;
	int sTrackCol = 1;
	//fish tracker variables
	int fishRow = 0;
	int fishCol = 0;

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
				Shark s(starve, SharkBreed, row, col); //Create shark object 
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
	for (i = 0; i < 10; i++)
	{
		
		//system("CLS");
		char(*ptGrids)[50] = Move(sharkTracker, fishTracker, shark, grid, 20);
		char(*ptGridf)[50] = Move(sharkTracker, fishTracker, fish, grid, 20);
		vector<int> sharkBesideFishResult = checkSharkBesideFish(grid, sharkTracker, 2);

		/*for (vector<int>::iterator it=sharkBesideFishResult.begin(); it != sharkBesideFishResult.end(); ++it)
		{
			cout << ' ' << *it;
		}
		*/
		//check sharkBesideFishResult to see if the shark can eat and RESET BOOL SHARKBESIDEFISH TO TRUE

			//this is to find the fish location so we can remove it from the grid in the 'else if' statement
		while (!sharkBesideFishResult.empty())//while theres still a value in the vector
		{
			fishCol = sharkBesideFishResult.back();
			sharkBesideFishResult.pop_back();
			fishRow = sharkBesideFishResult.back();
			sharkBesideFishResult.pop_back();
			//push back for fish location to use when eat() is called 
			
			cout << "fishRow[" << fishRow << "]";
			cout << "fishCol[" << fishCol << "]";
			
			//if the location is not "empty"
			if (fishCol != 100 && fishRow != 100)
			{
				sharkBesideFish = true;
				//pop off corresponding shark col and row
			}
			//find the corresponding shark in the vector at this location
			if (sharkLastEatTime == 0 && sharkBesideFish == false)
			{
				//remove shark from the vector and grid
				//remove this shark using the current location points
				cout << "shark dies" << endl;
				sharkLastEatTime = 0;
			}
			else if (sharkBesideFish == true)
			{
				//eat();
				//remove fish from the vector and grid using the current fishCol and fishRow 
				//change the shark at the current sharkRow and sharkCol 's last eat time
				sharkLastEatTime = 0;
				cout << "shark lives for another turn" << endl;
			}
			else
			{
				//use the current sharkRow and sharkCol to change this sharks lastEatTime
				sharkLastEatTime++;
				cout << "shark closer to starving" << endl;
			}
		}
		
		/*
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
		}*/
		//every iteration, shark will grow older to breed
		sharkTime++;
		//every iteration, fish will get older
		fishTime++;
		
		Print(grid);
	}
	/*	cout << "FISH:" << endl;
	for (i = 0; i < fishTracker.size(); i++)
	{
		row = fishTracker[i].getRow();
		col = fishTracker[i].getCol();
		cout << row << endl;
		cout << col << endl;
	}
	cout << "SHARK:" << endl;
	for (i = 0; i < sharkTracker.size(); i++)
	{
		row = sharkTracker[i].getRow();
		col = sharkTracker[i].getCol();
		cout << row << endl;
		cout << col << endl;
	}
*/
	cin.get();
	return 0;
}
