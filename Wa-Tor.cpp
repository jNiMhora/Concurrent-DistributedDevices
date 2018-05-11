//!
//!Authors: Lee Owens and Jessica Moore
//!Date: 8/01/2018
//!Purpose: Wator - simulation of sharks and fish
//!
// Wa-Tor.cpp : Defines the entry point for the console application.
//

#include "Shark.h"
#include "Fish.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
using namespace std;
//!
//!function to move the sharks and fishes accordng to their location and the empty spaces
//!
char(*Move(vector<Shark>& sTracker, vector<Fish>& fTracker, char type, char grid[][50], size_t sz))[50]
{//This changes objects positions in the grid & checks for collions between positions beofre moving
	int i;
char move;
int sRow;
int sCol;
int fRow;
int fCol;
int movePos; //!used to randomise the choice of movement //!
bool newPos = false; //!used to break out of while loop when a new position is found or shark or fish cant move //!
bool Down = true; //! if cant move D,U,L,R set to false so it doesnt check to move down in the next iteration //!
bool Up = true;
bool Left = true;
bool Right = true;
srand(time(NULL));

//! if the entity is a shark //!
if (type == 's')
{
	#pragma omp parallel
	for (i = 0; i < sTracker.size(); i++)
	{
		sRow = sTracker[i].getRow();
		sCol = sTracker[i].getCol();
		movePos = rand() % 3;// !randomly choose movement //! 

		while (newPos == false)//! keep trying to find a new position untill one is found //! 
		{
			//!*************** DOWN ****************** //!
			if (movePos == 0 && Down != false) //! check randomised number and if down has been checked already //!
			{
				if (sRow < 19)
				{
					if (grid[sRow + 1][sCol] == '_') //! check if shark can move down //!
					{
						move = 'D';//! move down //!
						newPos = true;//! break while loop //!
					}
				}
				else if (sRow == 19)
				{
					if (grid[0][sCol] == '_') //! check if shark can wrap back around //! 
					{
						grid[sRow][sCol] = '_';
						grid[0][sCol] = 'S';
						sTracker[i].setRow(0);
						move = '-';
						newPos = true;
					}
				}
				else { Down = false; } //! If it cant do either this movement cant be made and is set to false //! 
			}
			//! *************** UP ****************** //!
			if (movePos == 1 && Up != false)
			{
				if (sRow > 0)
				{
					if (grid[sRow - 1][sCol] == '_')
					{
						//cout << "move up" << endl;
						move = 'U';//!move up //!
						newPos = true;//! break while loop //!
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
			//!*************** LEFT ****************** //!
			if (movePos == 2 && Left != false)
			{
				if (sCol > 0)
				{
					if (grid[sRow][sCol - 1] == '_')
					{
						//cout << "move left" << endl;
						move = 'L';//! move left //!
						newPos = true;//! break while loop //!
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
			//! *************** RIGHT ****************** //!
			if (movePos == 3 && Right != false)
			{
				if (sCol < 49)
				{
					if (grid[sRow][sCol + 1] == '_')
					{
						//cout << "move right" << endl;
						move = 'R';//! move right //!
						newPos = true;//! break while loop //!
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
			//! *************** CANT MOVE ****************** //!
			else if (Down == false && Up == false && Left == false && Right == false)
			{
				move = 'C';
				newPos = true;
			}
			movePos = rand() % 3;//! randomly choose movement //! 
		}
		switch (move)
		{
		case 'D':
			//! switch move down //!
			//cout << " switch move down" << endl;
			grid[sRow][sCol] = '_';
			grid[sRow + 1][sCol] = 'S';
			sTracker[i].setRow(sRow + 1);
			break;
		case 'U':
			//! switch move up //!
			//cout << "switch move up" << endl;
			grid[sRow][sCol] = '_';
			grid[sRow - 1][sCol] = 'S';
			sTracker[i].setRow(sRow - 1);
			break;
		case 'L':
			//! switch move left //!
			//cout << "switch move left" << endl;
			grid[sRow][sCol] = '_';
			grid[sRow][sCol - 1] = 'S';
			sTracker[i].setCol(sCol - 1);
			break;
		case 'R':
			//!switch move right //!
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
//! ************FISH******************** //!
if (type == 'f')
{
	#pragma omp parallel
	for (i = 0; i < fTracker.size(); i++)
	{
		fRow = fTracker[i].getRow();
		fCol = fTracker[i].getCol();
		movePos = rand() % 3;//! randomly choose movement //!

		while (newPos == false)//! keep trying to find a new position untill one is found //! 
		{
			//! *************** DOWN ****************** //!
			if (movePos == 0 && Down != false) //! check randomised number and if down has been checked already //!
			{
				if (fRow < 19)
				{
					if (grid[fRow + 1][fCol] == '_') //! check if fish can move down //! 
					{
						move = 'D';//! move down //!
						newPos = true;//! break while loop //!
					}
				}
				else if (fRow == 19)
				{
					if (grid[0][fCol] == '_') //! check if fish can wrap back around //! 
					{
						grid[fRow][fCol] = '_';
						grid[0][fCol] = 'F';
						fTracker[i].setRow(0);
						move = '-';
						newPos = true;
					}
				}
				else { Down = false; } //! If it cant do either this movement cant be made and is set to false //! 
			}
			//! *************** UP ****************** //!
			if (movePos == 1 && Up != false)
			{
				if (fRow > 0)
				{
					if (grid[fRow - 1][fCol] == '_')
					{
						//cout << "move up" << endl;
						move = 'U';//! move up //!
						newPos = true;//! break while loop //!
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
			//! *************** LEFT ****************** //! 
			if (movePos == 2 && Left != false)
			{
				if (fCol > 0)
				{
					if (grid[fRow][fCol - 1] == '_')
					{
						move = 'L';//! move left //!
						newPos = true;//! break while loop //!
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
			//! *************** RIGHT ****************** //!
			if (movePos == 3 && Right != false)
			{
				if (fCol < 49)
				{
					if (grid[fRow][fCol + 1] == '_')
					{
						move = 'R';//! move right //!
						newPos = true;//! break while loop //!
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
			//! *************** CANT MOVE ****************** //!
			else if (Down == false && Up == false && Left == false && Right == false)
			{
				move = 'C';
				newPos = true;
			}
			movePos = rand() % 3;//! randomly choose movement //! 
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
//!
//!function to print the grid of fish and shark
//!
return grid;
}
void Print(char grid[20][50])
{
	#pragma omp parallel
	for (int r = 0; r < 20; r++)
	{
		for (int c = 0; c < 50; c++)
		{
			cout << grid[r][c];
		}
		cout << endl;
	}
}
//!
//!function to check sharks and the location of fish to see if there are any beside the sharks to be eaten 
//!
vector<int> checkSharkBesideFish(char grid[20][50], vector<Shark>& sTracker, int locationLength)//! is the shark near a fish to eat? //!
{
	int fishFound = 0;
	vector<int> fishLocation;
	int sharkRow = 0;
	int sharkCol = 0;
	int rowLoc = 0;
	int colLoc = 0;
	//! function to check if shark has any fish to eat //!

	//! get into the shark tracker to identify individual sharks //!
	#pragma omp parallel
	for (int i = 0; i < sTracker.size(); i++)
	{
		sharkRow = sTracker[i].getRow();
		sharkCol = sTracker[i].getCol();
		while (fishFound == 0)
		{
			//!shark is at grid[sharkRow][sharkCol] //!
			if (grid[sharkRow - 1][sharkCol] == 'F')
			{
				//! found a fish above //!
				rowLoc = sharkRow - 1;
				colLoc = sharkCol;
				fishFound = 1;
			}
			else if (grid[sharkRow + 1][sharkCol] == 'F')
			{
				//! found a fish below //!
				rowLoc = sharkRow + 1;
				colLoc = sharkCol;
				fishFound = 1;
			}
			else if (grid[sharkRow][sharkCol - 1] == 'F')
			{
				//! found a fish left //!
				rowLoc = sharkRow;
				colLoc = sharkCol - 1;
				fishFound = 1;
			}
			else if (grid[sharkRow][sharkCol + 1] == 'F')
			{
				//! found a fish right //!
				rowLoc = sharkRow;
				colLoc = sharkCol + 1;
				fishFound = 1;
			}
			else
			{
				//! no fish near shark //!
				rowLoc = 100;
				colLoc = 100;
				//!
				//!location being set to 100 shows that no fish was close to shark
				//!and will mean the shark lastEatTime increases
				//!
				fishFound = 1;
			}
		}
		fishFound = 0;

		fishLocation.push_back(sharkRow);
		fishLocation.push_back(sharkCol);

		fishLocation.push_back(rowLoc);
		fishLocation.push_back(colLoc);
		//!
		//!pushing the two values for row and column into a vector so that
		//!can be returned to locate fish and correspoding shark
		//!

	}

	return fishLocation;
}//! end function fishBesideShark //! 

int main()
{
  auto start = chrono::steady_clock::now();
  
	//! variables //!
	srand(time(NULL));
	char grid[20][50];//!Wa-Tor World //! 
	int i = 0;
	int Timer = 100;
	int NumShark = 10; //! start number of sharks //!
	int NumFish = 20; //! start number of fish //! 
	int sharkTime = 0; //! Number of iterations before shark can breed //! 
	int fishTime = 0; //! Number of iterations before fish can breed //!
	int SharkBreed = 15;
	int FishBreed = 5;
	int babyFishes = 0; //!Current number of fishes divided by 2
	int babySharks = 0;
	int starve = 10; //! Number of iterations before shark starves and is deleted from vector //! 
	char slot = ' '; //! Used for insertion into Grid //!
	char space = ' ';//! Used for insertion into Grid //!
	int col = 0;  //! Used for insertion into Grid //!
	int row = 0;  //! Used for insertion into Grid //!
	char shark = 's'; //! Used for sending to functions to execute function on either fish or sharks //! 
	char fish = 'f';
	vector<Shark>sharkTracker; //! Holds all current Shark objects and their details (e.g. position) //!
	vector<Fish>fishTracker;  //! Holds all current Fish objects and their details (e.g. position) //!
	vector<Shark>::iterator itS;  //! declare an iterator Shark vector //!
	vector<Fish>::iterator itF;  //! declare an iterator Shark vector //!
	int fishCount = 0;
	int sharkCount = 0;
	//! new variables //!
	int sharkStarveTime = 0;
	int sharkLastEatTime = 100;
	int lastEat = 0;
	bool sharkBesideFish = false;
	//! shark tracker variables //!
	int sTrackRow = 0;
	int sTrackCol = 0;
	int trackCol = 0;
	int trackRow = 0;
	//! fish tracker variables //!
	int fishRow = 0;
	int fishCol = 0;
	int fTrackRow = 0;
	int fTrackCol = 0;

	//! Intialize grid to be empty //! 
	for (row = 0; row < 20; row++)
	{
		for (col = 0; col < 50; col++)
		{
			grid[row][col] = '_';
		}
	}
	//! insert sharks //!
	#pragma omp parallel
	for (i = 0; i < NumShark; i++)
	{
		while (slot != 'E')//! find position in grid for new shark object //!
		{
			row = rand() % 19;
			col = rand() % 49;
			space = grid[row][col];
			if (space = '_')
			{
				grid[row][col] = 'S';
				Shark s(starve, SharkBreed, sharkLastEatTime, row, col); //! Create shark object //!
				sharkTracker.push_back(s); //! add to tracker //! 
				slot = 'E';
			}
		}
		slot = ' ';//! reset to get back into while loop //!
	}
	//! insert fish //!
	#pragma omp parallel
	for (i = 0; i < NumFish; i++)
	{
		while (slot != 'E')//! find position in grid for new fish object //!
		{
			row = rand() % 19;
			col = rand() % 49;
			space = grid[row][col];
			if (space = '_')
			{
				grid[row][col] = 'F';
				Fish f(FishBreed, row, col); //! Create shark object //! 
				fishTracker.push_back(f); //! add to tracker //!
				slot = 'E';
			}
		}
		slot = ' ';
	}

	//! Life Cycle //!
	#pragma omp parallel
	for (int j = 0; j < Timer; j++)//! changed to j as i was being used elsewhere //!
	{

		system("clear");
		char(*ptGrids)[50] = Move(sharkTracker, fishTracker, shark, grid, 20);
		char(*ptGridf)[50] = Move(sharkTracker, fishTracker, fish, grid, 20);
		vector<int> sharkBesideFishResult = checkSharkBesideFish(grid, sharkTracker, 2);
		//this is for checking
		/*for (vector<int>::iterator it=sharkBesideFishResult.begin(); it != sharkBesideFishResult.end(); ++it)
		{
		cout << ' ' << *it << endl;
		}
		*/
		//!check sharkBesideFishResult to see if the shark can eat and RESET BOOL SHARKBESIDEFISH TO TRUE //!


		while (!sharkBesideFishResult.empty())//! while theres still a value in the vector //!
		{
			//! pop off next fish //!
			fishCol = sharkBesideFishResult.back();
			sharkBesideFishResult.pop_back();
			fishRow = sharkBesideFishResult.back();
			sharkBesideFishResult.pop_back();
			//cout << "fish at: " << fishRow << "/" << fishCol << endl;

			//! pop off corresponding shark col and row //!
			sTrackCol = sharkBesideFishResult.back();
			sharkBesideFishResult.pop_back();
			sTrackRow = sharkBesideFishResult.back();
			sharkBesideFishResult.pop_back();
			//cout << "shark at: " << sTrackRow << "/" << sTrackCol << endl;

			//! if the location is not "empty",ie [100][100], there is a fish beside a shark //!
			if (fishRow != 100 && fishCol != 100)
			{
				sharkBesideFish = true;
			}
			else
			{
				sharkBesideFish == false;
			}

			if (sharkBesideFish == false)//! there was no fish //!
			{
				int sharkSize = sharkTracker.size();
				int fishSize = fishTracker.size();

				//! find current shark in vector and decrease its sharkLastEatTime by one //!
				for (i = 0; i < sharkTracker.size(); i++)
				{
					trackRow = sharkTracker[i].getRow();
					trackCol = sharkTracker[i].getCol();
					lastEat = sharkTracker[i].getLastEatTime();
					//! if the current shark has run out of time to eat //!
					if (lastEat == 0 && trackRow == sTrackRow && trackCol == sTrackCol)
					{
						//! remove shark from the vector //!
						sharkTracker.erase(sharkTracker.begin() + i);
						NumShark--;
						//! remove shark from grid //!
						grid[trackRow][trackCol] = '_';

						//cout << "shark dies" << endl;
					}
					//! current shark is still hungry //! 
					else if (trackRow == sTrackRow && trackCol == sTrackCol)
					{
						//cout << lastEat << endl;
						sharkLastEatTime = lastEat - 1;
						sharkTracker[i].setLastEatTime(sharkLastEatTime);
						// int check = sharkTracker[i].getLastEatTime();
						// cout << check << endl;
						//cout << "shark closer to starving" << endl;

					}


				}
			}
			else if (sharkBesideFish == true) //!there is a fish //!
			{
				//! remove fish from the vector using the current fishCol and fishRow //!
				for (i = 0; i < fishTracker.size(); i++)
				{
					fTrackRow = fishTracker[i].getRow();
					fTrackCol = fishTracker[i].getCol();

					//! find the current fish to take it out //!
					if (fishRow == fTrackRow && fishCol == fTrackCol)
					{
						//! remove fish from the vector //!
						fishTracker.erase(fishTracker.begin() + i);
						NumFish--;
						//! remove fish from grid //!
						grid[fTrackRow][fTrackCol] = '_';

						//cout << "fish eaten" << endl;
						//cout << "numFish" << NumFish << endl;
					}
				}
				//! reset the current shark's last eat time //!
				for (i = 0; i < sharkTracker.size(); i++)
				{
					trackRow = sharkTracker[i].getRow();
					trackCol = sharkTracker[i].getCol();
					//lastEat = sharkTracker[i].getLastEatTime();
					//cout << lastEat << endl;

					//! find current shark in the vector of sharks to update its value //!
					if (trackRow == sTrackRow && trackCol == sTrackCol)
					{
						sharkLastEatTime = 100;
						sharkTracker[i].setLastEatTime(sharkLastEatTime);
						//int doubleCheck = sharkTracker[i].getLastEatTime();
						//cout << "update last eat time" << doubleCheck << endl;

						//cout << "shark lives for another turn" << endl;

					}

				}
				sharkBesideFish = false;//! resets so the sharks dont become invincible //! 
			}
		}

		//! BREED METHODS //!
		//! every iteration, shark will grow older to breed //!
		sharkTime++;
		//! every iteration, fish will get older //!
		fishTime++;
		if (sharkTime == SharkBreed && NumShark != 0)
		{
			//babySharks = NumShark / 2;
			babySharks = 1;
			for (i = 0; i < babySharks; i++)
			{
				while (slot != 'E')//! find position in grid for new shark object //!
				{
					row = rand() % 19;
					col = rand() % 49;
					space = grid[row][col];
					if (space = '_')
					{
						grid[row][col] = 'S';
						Shark s(starve, SharkBreed, sharkLastEatTime, row, col); //! Create shark object //! 
						sharkTracker.push_back(s); //! add to tracker //! 
						NumShark++;
						slot = 'E';
					}
				}
				slot = ' ';
			}
			sharkTime = 0;
		}
		if (fishTime == FishBreed && NumFish != 0)
		{
			//babyFishes = NumFish / 2;
			babyFishes = 1;
			for (i = 0; i < babyFishes; i++)
			{
				while (slot != 'E')//! find position in grid for new fish object //!
				{
					row = rand() % 19;
					col = rand() % 49;
					space = grid[row][col];
					if (space = '_')
					{
						grid[row][col] = 'F';
						Fish f(FishBreed, row, col); //! Create shark object //! 
						fishTracker.push_back(f); //! add to tracker //! 
						NumFish++;
						slot = 'E';
					}
				}
				slot = ' ';
			}
			fishTime = 0;
		}

		Print(grid);
		cout << endl;
		cout << "Number of Fish: " << NumFish << ' ' << "Number of Sharks: " << NumShark << endl;
		usleep(150000);

	}

	cout << "simulation ended" << endl;
	auto end = chrono::steady_clock::now();
	double elapsed = chrono::duration_cast<chrono::duration<double> >(end - start).count();
	cout << elapsed << '\n';
	cin.get();
	return 0;
}
