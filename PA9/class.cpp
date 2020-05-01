/*
***********************************************************************************************************************
Programmer: Charles Ewing, Joseph Kattakayam, Jeff Li                                                                 *
Class: CptS 122; Lab Section 14                                                                                       *  
Programming Assignment: PA 9                                                                                          *
Date: 4/30/2020                                                                                                       *
Description: Checkers game in c++ using sfml                 `                                                        *
***********************************************************************************************************************
*/
#include "class.h"

checkers_piece::checkers_piece()
{
    row = -1;
    col = -1;
    is_killed = false;
    is_king = false;
}

void checkers_piece::setRow(int newRow)
{
    row = newRow;
}

void checkers_piece::setCol(int newCol)
{
    col = newCol;
}

void checkers_piece::setKilled(bool new_is_killed)
{
    is_killed = new_is_killed;
}

void checkers_piece::setKing(bool new_is_king)
{
    is_king = new_is_king;
}

int checkers_piece::getRow()
{
    return row;
}

int checkers_piece::getCol()
{
    return col;
}

bool checkers_piece::getKilled()
{
    return is_killed;
}
bool checkers_piece::getKing()
{
    return is_king;
}

game::game()
{
    //placing blue checkers on the board
    Blue_Side[0].setRow(0);
    Blue_Side[0].setCol(1);

    Blue_Side[1].setRow(0);
    Blue_Side[1].setCol(3);

    Blue_Side[2].setRow(0);
    Blue_Side[2].setCol(5);

    Blue_Side[3].setRow(0);
    Blue_Side[3].setCol(7);

    Blue_Side[4].setRow(1);
    Blue_Side[4].setCol(0);

    Blue_Side[5].setRow(1);
    Blue_Side[5].setCol(2);

    Blue_Side[6].setRow(1);
    Blue_Side[6].setCol(4);

    Blue_Side[7].setRow(1);
    Blue_Side[7].setCol(6);

    Blue_Side[8].setRow(2);
    Blue_Side[8].setCol(1);

    Blue_Side[9].setRow(2);
    Blue_Side[9].setCol(3);

    Blue_Side[10].setRow(2);
    Blue_Side[10].setCol(5);

    Blue_Side[11].setRow(2);
    Blue_Side[11].setCol(7);

    //placing red checkers on the board
    Red_Side[0].setRow(7);
    Red_Side[0].setCol(0);

    Red_Side[1].setRow(7);
    Red_Side[1].setCol(2);

    Red_Side[2].setRow(7);
    Red_Side[2].setCol(4);

    Red_Side[3].setRow(7);
    Red_Side[3].setCol(6);

    Red_Side[4].setRow(6);
    Red_Side[4].setCol(1);

    Red_Side[5].setRow(6);
    Red_Side[5].setCol(3);

    Red_Side[6].setRow(6);
    Red_Side[6].setCol(5);

    Red_Side[7].setRow(6);
    Red_Side[7].setCol(7);

    Red_Side[8].setRow(5);
    Red_Side[8].setCol(0);

    Red_Side[9].setRow(5);
    Red_Side[9].setCol(2);

    Red_Side[10].setRow(5);
    Red_Side[10].setCol(4);

    Red_Side[11].setRow(5);
    Red_Side[11].setCol(6);

    //start of game properties
    for (int index = 0; index < 12; index++)
    {
        Blue_Side[index].setKilled(false);
        Red_Side[index].setKilled(false);
        Blue_Side[index].setKing(false);
        Red_Side[index].setKing(false);
        Blue_Side_Kings[index].setKilled(false);
        Red_Side_Kings[index].setKilled(false);
        Blue_Side_Kings[index].setKing(true);
        Red_Side_Kings[index].setKing(true);
        Blue_Side_Kings[index].setRow(Blue_Side[index].getRow());
        Blue_Side_Kings[index].setCol(Blue_Side[index].getCol());
        Red_Side_Kings[index].setRow(Red_Side[index].getRow());
        Red_Side_Kings[index].setCol(Red_Side[index].getCol());
    }
}



//this takes a checkers piece and moves it using data from main
void game::move(int selection_index, int path_index, bool blueNotred)
{
            //checks if blue, assigns piece to appropirate path based on index
            if (path_index == 0 && blueNotred)
            {
                Blue_Side[selection_index].setCol(Blue_Side[selection_index].getCol() - 1);
                Blue_Side[selection_index].setRow(Blue_Side[selection_index].getRow() + 1);
            }
            else if (path_index == 1 && blueNotred)
            {
                Blue_Side[selection_index].setCol(Blue_Side[selection_index].getCol() + 1);
                Blue_Side[selection_index].setRow(Blue_Side[selection_index].getRow() + 1);
            }

            //for kings
            else if (path_index == 2 && blueNotred)
            {
                Blue_Side[selection_index].setCol(Blue_Side[selection_index].getCol() + 1);
                Blue_Side[selection_index].setRow(Blue_Side[selection_index].getRow() - 1);
            }
            else if (path_index == -1 && blueNotred)
            {
                Blue_Side[selection_index].setCol(Blue_Side[selection_index].getCol() - 1);
                Blue_Side[selection_index].setRow(Blue_Side[selection_index].getRow() - 1);
            }

            //slready checked for red piece, just look for path
            else if (path_index == 1)
            {
                Red_Side[selection_index].setCol(Red_Side[selection_index].getCol() + 1);
                Red_Side[selection_index].setRow(Red_Side[selection_index].getRow() - 1);
            }
            else if (path_index == 0)
            {
                Red_Side[selection_index].setCol(Red_Side[selection_index].getCol() - 1);
                Red_Side[selection_index].setRow(Red_Side[selection_index].getRow() - 1);
            }

            //for kings
            else if (path_index == -1)
            {
                Red_Side[selection_index].setCol(Red_Side[selection_index].getCol() - 1);
                Red_Side[selection_index].setRow(Red_Side[selection_index].getRow() + 1);
            }
            else if (path_index == 2)
            {
                Red_Side[selection_index].setCol(Red_Side[selection_index].getCol() + 1);
                Red_Side[selection_index].setRow(Red_Side[selection_index].getRow() + 1);
            }
}

//copies checkerspiece positional data and death data
void game::kingCopy()
{
    //copy pieces
    for (int i = 0; i < 12; i++)
    {
        Blue_Side_Kings[i].setRow(Blue_Side[i].getRow());
        Blue_Side_Kings[i].setCol(Blue_Side[i].getCol());
        Blue_Side_Kings[i].setKing(Blue_Side[i].getKing());
        Blue_Side_Kings[i].setKilled(Blue_Side[i].getKilled());
        Red_Side_Kings[i].setRow(Red_Side[i].getRow());
        Red_Side_Kings[i].setCol(Red_Side[i].getCol());
        Red_Side_Kings[i].setKing(Red_Side[i].getKing());
        Red_Side_Kings[i].setKilled(Red_Side[i].getKilled());
    }
}

// check if the move is valid
bool game::valid_move(int selection_index, int path_index, bool blueNotred)
{
    //move valid until it's proven not to be
    bool valid = true;
    bool in_bounds = false;

    //checks if blue, assigns piece to appropirate path based on index
    if (path_index == 0 && blueNotred)
    {
        if (((Blue_Side[selection_index].getCol() - 1) >= 0) && (Blue_Side[selection_index].getRow() + 1) < 8)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Blue_Side[selection_index].getCol() - 1)) && (Blue_Side[i].getRow() == (Blue_Side[selection_index].getRow() + 1)))
                || ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() - 1)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() + 1))))
            {
                valid = false;
            }
        }
    }
    else if (path_index == 1 && blueNotred)
    {
        if (((Blue_Side[selection_index].getCol() + 1) < 8) && (Blue_Side[selection_index].getRow() + 1) < 8)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Blue_Side[selection_index].getCol() + 1)) && (Blue_Side[i].getRow() == (Blue_Side[selection_index].getRow() + 1)))
                || ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() + 1)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() + 1))))
            {
                valid = false;
            }
        }
    }

    //for kings
    else if (path_index == 2 && blueNotred)
    {
		if (((Blue_Side[selection_index].getCol() + 1) < 8) && (Blue_Side[selection_index].getRow() - 1) >= 0)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Blue_Side[selection_index].getCol() + 1)) && (Blue_Side[i].getRow() == (Blue_Side[selection_index].getRow() - 1)))
                || ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() + 1)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() - 1))))
            {
                valid = false;
            }
        }
    }
    else if (path_index == -1 && blueNotred)
    {
		if (((Blue_Side[selection_index].getCol() - 1) >= 0) && (Blue_Side[selection_index].getRow() - 1) >= 0)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Blue_Side[selection_index].getCol() - 1)) && (Blue_Side[i].getRow() == (Blue_Side[selection_index].getRow() - 1)))
                || ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() - 1)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() - 1))))
            {
                valid = false;
            }
        }
    }

    //slready checked for red piece, just look for path
    else if (path_index == 0)
    {
		if (((Red_Side[selection_index].getCol() - 1) >= 0) && (Red_Side[selection_index].getRow() - 1) >= 0)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() - 1)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() - 1)))
                || ((Red_Side[i].getCol() == (Red_Side[selection_index].getCol() - 1)) && (Red_Side[i].getRow() == (Red_Side[selection_index].getRow() - 1))))
            {
                valid = false;
            }
        }
    }
    else if (path_index == 1)
    {
        if (((Red_Side[selection_index].getCol() + 1) < 8) && (Red_Side[selection_index].getRow() - 1) >= 0)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() + 1)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() - 1)))
                || ((Red_Side[i].getCol() == (Red_Side[selection_index].getCol() + 1)) && (Red_Side[i].getRow() == (Red_Side[selection_index].getRow() - 1))))
            {
                valid = false;
            }
        }
    }

    //for kings
    else if (path_index == -1)
    {
        if (((Red_Side[selection_index].getCol() - 1) >= 0) && (Red_Side[selection_index].getRow() + 1) < 8)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() - 1)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() + 1)))
                || ((Red_Side[i].getCol() == (Red_Side[selection_index].getCol() - 1)) && (Red_Side[i].getRow() == (Red_Side[selection_index].getRow() + 1))))
            {
                valid = false;
            }
        }
    }
    else if (path_index == 2)
    {
     if (((Red_Side[selection_index].getCol() + 1) < 8) && (Red_Side[selection_index].getRow() + 1) < 8)
     {
         in_bounds = true;
     }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() + 1)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() + 1)))
                || ((Red_Side[i].getCol() == (Red_Side[selection_index].getCol() + 1)) && (Red_Side[i].getRow() == (Red_Side[selection_index].getRow() + 1))))
            {
                valid = false;
            }
        }
    }

    if (!in_bounds)
    {
        valid = false;
    }

    return valid;
}


// Cheks if the checker peice can make a valid jump over an enemy piece
bool game::valid_jump(int selection_index, int path_index, bool blueNotred)
{
    //assuming open space but check for it in if statement
    bool open_space = true;

    //false untill proven true
    bool opponent = false;
    bool valid = false;
    bool in_bounds = false;

    //checks if blue, assigns piece to appropirate path based on index
    if (path_index == 0 && blueNotred)
    {
        if (((Blue_Side[selection_index].getCol() - 2) >= 0) && (Blue_Side[selection_index].getRow() + 2) < 8)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Blue_Side[selection_index].getCol() - 2)) && (Blue_Side[i].getRow() == (Blue_Side[selection_index].getRow() + 2))) 
                || ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() - 2)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() + 2))))
            {
                open_space = false;
            }
            if ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() - 1)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() + 1)))
            {
                opponent = true;
            }
        }
    }
    else if (path_index == 1 && blueNotred)
    {
        if (((Blue_Side[selection_index].getCol() + 2) < 8) && (Blue_Side[selection_index].getRow() + 2) < 8)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Blue_Side[selection_index].getCol() + 2)) && (Blue_Side[i].getRow() == (Blue_Side[selection_index].getRow() + 2)))
                || ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() + 2)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() + 2))))
            {
                open_space = false;
            }
            if ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() + 1)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() + 1)))
            {
                opponent = true;
            }
        }
    }

    //for kings
    else if (path_index == 2 && blueNotred)
    {
        if (((Blue_Side[selection_index].getCol() + 2) < 8) && (Blue_Side[selection_index].getRow() - 2) >= 0)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Blue_Side[selection_index].getCol() + 2)) && (Blue_Side[i].getRow() == (Blue_Side[selection_index].getRow() - 2)))
                || ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() + 2)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() - 2))))
            {
                open_space = false;
            }
            if ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() + 1)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() - 1)))
            {
                opponent = true;
            }
        }
    }
    else if (path_index == -1 && blueNotred)
    {
        if (((Blue_Side[selection_index].getCol() - 2) >= 0) && (Blue_Side[selection_index].getRow() - 2) >= 0)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Blue_Side[selection_index].getCol() - 2)) && (Blue_Side[i].getRow() == (Blue_Side[selection_index].getRow() - 2)))
                || ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() - 2)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() - 2))))
            {
                open_space = false;
            }
            if ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() - 1)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() - 1)))
            {
                opponent = true;
            }
        }
    }

    //already checked for red piece, just look for path
    else if (path_index == 0)
    {
        if (((Red_Side[selection_index].getCol() - 2) >= 0) && (Red_Side[selection_index].getRow() - 2) >= 0)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() - 2)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() - 2)))
                || ((Red_Side[i].getCol() == (Red_Side[selection_index].getCol() - 2)) && (Red_Side[i].getRow() == (Red_Side[selection_index].getRow() - 2))))
            {
                open_space = false;
            }
            if ((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() - 1)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() - 1)))
            {
                opponent = true;
            }
        }
    }
    else if (path_index == 1)
    {
        if (((Red_Side[selection_index].getCol() + 2) < 8) && (Red_Side[selection_index].getRow() - 2) >= 0)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() + 2)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() - 2)))
                || ((Red_Side[i].getCol() == (Red_Side[selection_index].getCol() + 2)) && (Red_Side[i].getRow() == (Red_Side[selection_index].getRow() - 2))))
            {
                open_space = false;
            }
            if ((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() + 1)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() - 1)))
            {
                opponent = true;
            }
        }
    }

    //for kings
    else if (path_index == -1)
    {
        if (((Red_Side[selection_index].getCol() - 2) >= 0) && (Red_Side[selection_index].getRow() + 2) < 8)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() - 2)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() + 2)))
                || ((Red_Side[i].getCol() == (Red_Side[selection_index].getCol() - 2)) && (Red_Side[i].getRow() == (Red_Side[selection_index].getRow() + 2))))
            {
                open_space = false;
            }
            if ((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() - 1)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() + 1)))
            {
                opponent = true;
            }
        }
    }
    else if (path_index == 2)
    {
        if (((Red_Side[selection_index].getCol() + 2) < 8) && (Red_Side[selection_index].getRow() + 2) < 8)
        {
            in_bounds = true;
        }
        for (int i = 0; i < 12; i++)
        {
            if (((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() + 2)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() + 2)))
                || ((Red_Side[i].getCol() == (Red_Side[selection_index].getCol() + 2)) && (Red_Side[i].getRow() == (Red_Side[selection_index].getRow() + 2))))
            {
                open_space = false;
            }
            if ((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() + 1)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() + 1)))
            {
                opponent = true;
            }
        }
    }

    if (open_space && opponent && in_bounds)
    {
        valid = true;
    }

    return valid;
}

void game::jump(int selection_index, int path_index, bool blueNotred)
{
    int kill_index = -1;

	        //checks if blue, assigns piece to appropirate path based on index
            if (path_index == 0 && blueNotred)
            {   
                //kill the jumped piece
                for (int i = 0; i < 12; i++)
                {
                    //I will find you and I will kill you
                    if ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() - 1)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() + 1)))
                    {
                        kill_index = i;
                    }
                }

                //FINISH THEM
                Red_Side[kill_index].setKilled(true);

                //DISPOSE OF THE BODY
                Red_Side[kill_index].setCol(-1);
                Red_Side[kill_index].setRow(-1);

				//moves piece
                Blue_Side[selection_index].setCol(Blue_Side[selection_index].getCol() - 2);
                Blue_Side[selection_index].setRow(Blue_Side[selection_index].getRow() + 2);
            }

            else if (path_index == 1 && blueNotred)
            {
				//kill the jumped piece
                for (int i = 0; i < 12; i++)
                {
                    //I will find you and I will kill you
                    if ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() + 1)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() + 1)))
                    {
                        kill_index = i;
                    }
                }

                //FINISH THEM
                Red_Side[kill_index].setKilled(true);

                //DISPOSE OF THE BODY
                Red_Side[kill_index].setCol(-1);
                Red_Side[kill_index].setRow(-1);

				//moves piece
                Blue_Side[selection_index].setCol(Blue_Side[selection_index].getCol() + 2);
                Blue_Side[selection_index].setRow(Blue_Side[selection_index].getRow() + 2);
            }

            //for kings
            else if (path_index == 2 && blueNotred)
            {
				//kill the jumped piece
                for (int i = 0; i < 12; i++)
                {
                    //I will find you and I will kill you
                    if ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() + 1)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() - 1)))
                    {
                        kill_index = i;
                    }
                }

                //FINISH THEM
                Red_Side[kill_index].setKilled(true);

                //DISPOSE OF THE BODY
                Red_Side[kill_index].setCol(-1);
                Red_Side[kill_index].setRow(-1);

				//moves piece
                Blue_Side[selection_index].setCol(Blue_Side[selection_index].getCol() + 2);
                Blue_Side[selection_index].setRow(Blue_Side[selection_index].getRow() - 2);
            }
            else if (path_index == -1 && blueNotred)
            {
				//kill the jumped piece
                for (int i = 0; i < 12; i++)
                {
                    //I will find you and I will kill you
                    if ((Red_Side[i].getCol() == (Blue_Side[selection_index].getCol() - 1)) && (Red_Side[i].getRow() == (Blue_Side[selection_index].getRow() - 1)))
                    {
                        kill_index = i;
                    }
                }

                //FINISH THEM
                Red_Side[kill_index].setKilled(true);

                //DISPOSE OF THE BODY
                Red_Side[kill_index].setCol(-1);
                Red_Side[kill_index].setRow(-1);

				//moves piece
                Blue_Side[selection_index].setCol(Blue_Side[selection_index].getCol() - 2);
                Blue_Side[selection_index].setRow(Blue_Side[selection_index].getRow() - 2);
            }

            //already checked for red piece, just look for path
            else if (path_index == 1)
            {
				//kill the jumped piece
                for (int i = 0; i < 12; i++)
                {
                    //I will find you and I will kill you
                    if ((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() + 1)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() - 1)))
                    {
                        kill_index = i;
                    }
                }

                //FINISH THEM
                Blue_Side[kill_index].setKilled(true);

                //DISPOSE OF THE BODY
                Blue_Side[kill_index].setCol(-1);
                Blue_Side[kill_index].setRow(-1);

				//moves piece
                Red_Side[selection_index].setCol(Red_Side[selection_index].getCol() + 2);
                Red_Side[selection_index].setRow(Red_Side[selection_index].getRow() - 2);
            }

            else if (path_index == 0)
            {
				//kill the jumped piece
                for (int i = 0; i < 12; i++)
                {
                    //I will find you and I will kill you
                    if ((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() - 1)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() - 1)))
                    {
                        kill_index = i;
                    }
                }

                //FINISH THEM
                Blue_Side[kill_index].setKilled(true);

                //DISPOSE OF THE BODY
                Blue_Side[kill_index].setCol(-1);
                Blue_Side[kill_index].setRow(-1);

				Red_Side[selection_index].setCol(Red_Side[selection_index].getCol() - 2);
                Red_Side[selection_index].setRow(Red_Side[selection_index].getRow() - 2);
            }

            //for kings
            else if (path_index == -1)
            {
                //kill the jumped piece
                for (int i = 0; i < 12; i++)
                {
                    //I will find you and I will kill you
                    if ((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() - 1)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() + 1)))
                    {
                        kill_index = i;
                    }
                }

                //FINISH THEM
                Blue_Side[kill_index].setKilled(true);

                //DISPOSE OF THE BODY
                Blue_Side[kill_index].setCol(-1);
                Blue_Side[kill_index].setRow(-1);

				Red_Side[selection_index].setCol(Red_Side[selection_index].getCol() - 2);
                Red_Side[selection_index].setRow(Red_Side[selection_index].getRow() + 2);
            }
            else if (path_index == 2)
            {
                //kill the jumped piece
                for (int i = 0; i < 12; i++)
                {
                    //I will find you and I will kill you
                    if ((Blue_Side[i].getCol() == (Red_Side[selection_index].getCol() + 1)) && (Blue_Side[i].getRow() == (Red_Side[selection_index].getRow() + 1)))
                    {
                        kill_index = i;
                    }
                }

                //FINISH THEM
                Blue_Side[kill_index].setKilled(true);

                //dispose of the piece
                Blue_Side[kill_index].setCol(-1);
                Blue_Side[kill_index].setRow(-1);

                //move
                Red_Side[selection_index].setCol(Red_Side[selection_index].getCol() + 2);
                Red_Side[selection_index].setRow(Red_Side[selection_index].getRow() + 2);
            }
}

void game::be_king()
{
    for (int i = 0; i < 12; i++)
    {
        if (Blue_Side[i].getRow() == 7)
        {
            Blue_Side[i].setKing(true);
        }
		else if (Red_Side[i].getRow() == 0)
		{
			Red_Side[i].setKing(true);
		}
    }
}

bool king::getKing()
{
    return true;
}

bool game::win()
{
    bool win = true;
    for (int i = 0; i < 12; i++)
    {
        if (Blue_Side[i].getKilled() == false)
        {
            win = false;
        }
        if (Red_Side[i].getKilled() == false)
        {
            win = false;
        }
    }

    return win;
}

bool game::bluewinsNotred()
{
    bool bluewinsNotred = true;
    for (int i = 0; i < 12; i++)
    {
        if (Red_Side[i].getKilled() == false)
        {
            bluewinsNotred = false;
        }
    }

    return bluewinsNotred;
}