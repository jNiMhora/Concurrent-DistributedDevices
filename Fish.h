#pragma once
//Author: Lee Owens
//Class: Fish, used to create and maintain Fish objects 

class Fish
{
public:
	int breedTimer = 0;
	int Row = 0;
	int Col = 0;

	//Constructor
	Fish(int FishBreed, int row, int col)
	{
		setBreedTimer(FishBreed);
		setRow(row);
		setCol(col);
	}

	//Setter Methods
	void setBreedTimer(int FishBreed)
	{
		breedTimer = FishBreed;
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
	int getBreedTime()
	{
		return breedTimer;
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
