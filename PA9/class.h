/*
***********************************************************************************************************************
Programmer: Charles Ewing, Joseph Kattakayam, Jeff Li                                                                 *
Class: CptS 122; Lab Section 14                                                                                       *  
Programming Assignment: PA 9                                                                                          *
Date: 4/30/2020                                                                                                       *
Description: Checkers game in c++ using sfml                 `                                                        *
***********************************************************************************************************************
*/

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// class for checkers piece
class checkers_piece
{
public:
	//constructor
	checkers_piece();

	//setters
	void setRow(int newRow);
	void setCol(int newCol);
	void setKilled(bool new_is_killed);
	void setKing(bool new_is_king);

	//getters
	int getRow();
	int getCol();
	bool getKilled();
	bool getKing();

private:
	//positional data
	int row;
	int col;

	//attributes
	bool is_killed;
	bool is_king;	
};

// class for king that inherites from checkers piece
class king: public checkers_piece
{
	bool getKing();
};

//class for game
class game
{
public:
	//game pieces
	checkers_piece Red_Side[12];
	checkers_piece Blue_Side[12];
	king Red_Side_Kings[12];
	king Blue_Side_Kings[12];

	//contructor
	game();

	//game modifiers
	void jump(int selection_index, int path_index, bool blueNotred);
	void be_king();
	bool valid_jump(int selection_index, int path_index, bool blueNotred);
	void move(int selection_index, int path_index, bool blueNotred);
	bool valid_move(int selection_index, int path_index, bool blueNotred);
	void kingCopy();
	bool win();
	bool bluewinsNotred();
};

