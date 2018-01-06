#pragma once
//Author: Lee Owens
//Class: Shark, used to create and maintain Shark objects 

class Shark
{
public:
	int starveCount = 0; //keep track of starve time
	int breedTimer = 0; //keep track of breed time
	int Row, Col = 0; //Sharks position in grid
	int lastEatTime = 4;

					  //Constructor
	Shark(int starve, int sharkBreed,int sharkLastEatTime, int row, int col)
	{
		setStarveTimer(starve);
		setBreedTimer(sharkBreed);
		setLastEatTime(sharkLastEatTime);
		setRow(row);
		setCol(col);
	}

	//Setter Methods
	void setStarveTimer(int starve)
	{
		starveCount = starve;
	}
	void setBreedTimer(int sharkBreed)
	{
		breedTimer = sharkBreed;
	}
	void setLastEatTime(int sharkLastEatTime)
	{
		lastEatTime = sharkLastEatTime;
	}
	void setRow(int row)
	{
		Row = row;
	}
	void setCol(int col)
	{
		Col = col;
	}

	//Getter Methods 
	int getStarveCount()
	{
		return starveCount;
	}
	int getBreedTimer()
	{
		return breedTimer;
	}
	int getLastEatTime()
	{
		return 
		lastEatTime;
	}
	int getRow()
	{
		return Row;
	}
	int getCol()
	{
		return Col;
	}
};
