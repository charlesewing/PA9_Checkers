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

int main()
{
	//a beautifully constrained made board size
    int N = 8, M = 8;
    int size = 128;
    int w = size * N;
    int h = size * M;
    int selection_index = 0;
    int path_index = 0;
    bool alternate = true;
    bool start = false;
    bool done_selecting_checker = false;
    bool done_selecting_path = false;
    bool game_over = false;
    bool blueNotred = true;
    bool start_of_turn = true;

	//some quality made pngs
    Texture White_Square, Black_Square, Blue_Checker, Red_Checker, Blue_Checker_King, Red_Checker_King, Checkers_Splashscreen, YellowHighlight, PurpleHighlight, bluewins, redwins;
    White_Square.loadFromFile("White.png");
    Black_Square.loadFromFile("Black.png");
    Blue_Checker.loadFromFile("BlueChecker.png");
    Red_Checker.loadFromFile("RedChecker.png");
    Blue_Checker_King.loadFromFile("BlueCheckerKing.png");
    Red_Checker_King.loadFromFile("RedCheckerKing.png");
    Checkers_Splashscreen.loadFromFile("Checkers_Splashscreen.png");
    YellowHighlight.loadFromFile("YellowHighlight.png");
    PurpleHighlight.loadFromFile("PurpleHighlight.png");
    bluewins.loadFromFile("bluewins.png");
    redwins.loadFromFile("redwins.png");

	//dirty sprites
    Sprite White_Square_Sprite(White_Square);
    Sprite Black_Square_Sprite(Black_Square);
    Sprite Blue_Checker_Sprite(Blue_Checker);
    Sprite Red_Checker_Sprite(Red_Checker);
    Sprite Blue_Checker_King_Sprite(Blue_Checker_King);
    Sprite Red_Checker_King_Sprite(Red_Checker_King);
    Sprite Checkers_Splashscreen_Sprite(Checkers_Splashscreen);
    Sprite YellowHighlight_Sprite(YellowHighlight);
    Sprite PurpleHighlight_Sprite(PurpleHighlight);
    Sprite bluewins_Sprite(bluewins);
    Sprite redwins_Sprite(redwins);

    //splashscreen
    RenderWindow splash(VideoMode(621, 618), "Rules and Controls");

    Event splashevent;

    while (splash.isOpen())
    {
        while (splash.pollEvent(splashevent))
        {
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                start = true;
                splash.close();
            }
        }

        //get window ready for next render
        splash.clear();

        //draw splash
        splash.draw(Checkers_Splashscreen_Sprite);

        //display the window
        splash.display();
    }

    game activeGame;

    RenderWindow window(VideoMode(w, h), "Checkers in C++");

    Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (Keyboard::isKeyPressed(Keyboard::Left) && !done_selecting_checker && selection_index > 0)
            {
                selection_index--;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left) && path_index > 0 && done_selecting_checker)
            {
                //check if in bounds
                if (activeGame.valid_move(selection_index, (path_index - 1), blueNotred) || activeGame.valid_jump(selection_index, (path_index - 1), blueNotred))
                {
                    path_index--;
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left) && path_index == 0 && done_selecting_checker && (activeGame.Blue_Side[selection_index].getKing() || activeGame.Red_Side[selection_index].getKing()))
            {
                //check if in bounds
                if (activeGame.valid_move(selection_index, (path_index - 1), blueNotred) || activeGame.valid_jump(selection_index, (path_index - 1), blueNotred))
                {
                    path_index = -1;
                }
            }

            if ((Keyboard::isKeyPressed(Keyboard::Right)) && !done_selecting_checker && selection_index < 11)
            {
                selection_index++;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Right) && path_index < 1 && done_selecting_checker)
            {
                //check if in bounds
                if (activeGame.valid_move(selection_index, (path_index + 1), blueNotred) || activeGame.valid_jump(selection_index, (path_index + 1), blueNotred))
                {
                    path_index++;
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Right) && path_index == 1 && done_selecting_checker && (activeGame.Blue_Side[selection_index].getKing() || activeGame.Red_Side[selection_index].getKing()))
            {
                //check if in bounds
                if (activeGame.valid_move(selection_index, (path_index + 1), blueNotred) || activeGame.valid_jump(selection_index, (path_index + 1), blueNotred))
                {
                    path_index = 2;
                }
            }

            if ((Keyboard::isKeyPressed(Keyboard::Space)) && !done_selecting_checker)
            {
                done_selecting_checker = true;
            }

            if ((Keyboard::isKeyPressed(Keyboard::RShift)) && done_selecting_checker && !done_selecting_path && ((activeGame.valid_move(selection_index, path_index, blueNotred)) || activeGame.valid_jump(selection_index, path_index, blueNotred)))
            {
                done_selecting_path = true;
            }

            else if ((Keyboard::isKeyPressed(Keyboard::Enter)))
            {
                done_selecting_checker = false;
            }

            if ((activeGame.win()) || event.type == Event::Closed)
            {
                window.close();
            }
        }

        //make sure starting path index is OK
        if (start_of_turn)
        {
            if ((activeGame.Blue_Side[selection_index].getKing() || activeGame.Red_Side[selection_index].getKing()))
            {
                for (int i = -1; i <= 2; i++)
                {
                    if ((activeGame.valid_move(selection_index, i, blueNotred) == true) || (activeGame.valid_jump(selection_index, i, blueNotred) == true))
                    {
                        path_index = i;
                    }
                }
            }
            else
            {
                for (int i = 0; i <= 1; i++)
                {
                    if ((activeGame.valid_move(selection_index, i, blueNotred) == true) || (activeGame.valid_jump(selection_index, i, blueNotred) == true))
                    {
                        path_index = i;
                    }
                }
            }
            start_of_turn = false;
        }

        //*****************
        if (done_selecting_path)
        {
            if (activeGame.valid_move(selection_index, path_index, blueNotred))
            {
                activeGame.move(selection_index, path_index, blueNotred);
            }
            else if (activeGame.valid_jump(selection_index, path_index, blueNotred))
            {
                activeGame.jump(selection_index, path_index, blueNotred);
            }
            selection_index = 0;
            path_index = 0;
            done_selecting_path = false;
            done_selecting_checker = false;
            start_of_turn = true;
            if (blueNotred == true)
            {
                blueNotred = false;
            }
            else if (blueNotred == false)
            {
                blueNotred = true;
            }
        }

        activeGame.be_king();
        activeGame.kingCopy();

        //get window ready for next render
        window.clear();

        //render checker board
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (alternate)
                {
                    White_Square_Sprite.setPosition(i * size, j * size);  window.draw(White_Square_Sprite);
                    alternate = false;
                }
                else
                {
                    Black_Square_Sprite.setPosition(i * size, j * size);  window.draw(Black_Square_Sprite);
                    alternate = true;
                }
            }
            if (alternate)
            {
                alternate = false;
            }
            else
            {
                alternate = true;
            }
        }

        //render blue peices
        for (int i = 0; i < 12; i++)
        {
            if (!activeGame.Blue_Side[i].getKilled() && !activeGame.Blue_Side[i].getKing())
            {
                Blue_Checker_Sprite.setPosition((activeGame.Blue_Side[i].getCol()) * size, (activeGame.Blue_Side[i].getRow()) * size);
                window.draw(Blue_Checker_Sprite);
            }
            else if (!activeGame.Blue_Side_Kings[i].getKilled())
            {
                Blue_Checker_King_Sprite.setPosition((activeGame.Blue_Side_Kings[i].getCol()) * size, (activeGame.Blue_Side_Kings[i].getRow()) * size);
                window.draw(Blue_Checker_King_Sprite);
            }
        }

        //render red peices
        for (int i = 0; i < 12; i++)
        {
            if (!activeGame.Red_Side[i].getKilled() && !activeGame.Red_Side[i].getKing())
            {
                Red_Checker_Sprite.setPosition((activeGame.Red_Side[i].getCol()) * size, (activeGame.Red_Side[i].getRow()) * size);
                window.draw(Red_Checker_Sprite);
            }
            else if (!activeGame.Red_Side_Kings[i].getKilled())
            {
                Red_Checker_King_Sprite.setPosition((activeGame.Red_Side_Kings[i].getCol()) * size, (activeGame.Red_Side_Kings[i].getRow()) * size);
                window.draw(Red_Checker_King_Sprite);
            }
        }

        //highlight active blue checker piece
        if (!activeGame.Blue_Side[selection_index].getKilled() && blueNotred)
        {
            YellowHighlight_Sprite.setPosition((activeGame.Blue_Side[selection_index].getCol()) * size, (activeGame.Blue_Side[selection_index].getRow()) * size);
            window.draw(YellowHighlight_Sprite);
        }
        //highlight active red checker piece
        else if (!activeGame.Red_Side[selection_index].getKilled() && !blueNotred)
        {
            YellowHighlight_Sprite.setPosition((activeGame.Red_Side[selection_index].getCol()) * size, (activeGame.Red_Side[selection_index].getRow()) * size);
            window.draw(YellowHighlight_Sprite);
        }

        //show path for selected checker peice
        if (done_selecting_checker)
        {
            if (!done_selecting_path)
            {
                if (path_index == 0)
                {
                    if (blueNotred)
                    {
                        PurpleHighlight_Sprite.setPosition((activeGame.Blue_Side[selection_index].getCol() - 1) * size, (activeGame.Blue_Side[selection_index].getRow() + 1) * size);
                        window.draw(PurpleHighlight_Sprite);
                    }
                    else
                    {
                        PurpleHighlight_Sprite.setPosition((activeGame.Red_Side[selection_index].getCol() - 1)* size, (activeGame.Red_Side[selection_index].getRow() - 1)* size);
                        window.draw(PurpleHighlight_Sprite);
                    }
                }
                else if (path_index == 1)
                {
                    if (blueNotred)
                    {
                        PurpleHighlight_Sprite.setPosition((activeGame.Blue_Side[selection_index].getCol() + 1) * size, (activeGame.Blue_Side[selection_index].getRow() + 1) * size);
                        window.draw(PurpleHighlight_Sprite);
                    }
                    else
                    {
                        PurpleHighlight_Sprite.setPosition((activeGame.Red_Side[selection_index].getCol() + 1)* size, (activeGame.Red_Side[selection_index].getRow() - 1)* size);
                        window.draw(PurpleHighlight_Sprite);
                    }
                }
                else if (path_index == 2)
                {
                    if (blueNotred)
                    {
                        PurpleHighlight_Sprite.setPosition((activeGame.Blue_Side[selection_index].getCol() + 1) * size, (activeGame.Blue_Side[selection_index].getRow() - 1) * size);
                        window.draw(PurpleHighlight_Sprite);
                    }
                    else
                    {
                        PurpleHighlight_Sprite.setPosition((activeGame.Red_Side[selection_index].getCol() + 1)* size, (activeGame.Red_Side[selection_index].getRow() + 1)* size);
                        window.draw(PurpleHighlight_Sprite);
                    }
                }
                else if (path_index == -1)
                {
                    if (blueNotred)
                    {
                        PurpleHighlight_Sprite.setPosition((activeGame.Blue_Side[selection_index].getCol() - 1)* size, (activeGame.Blue_Side[selection_index].getRow() - 1)* size);
                        window.draw(PurpleHighlight_Sprite);
                    }
                    else
                    {
                        PurpleHighlight_Sprite.setPosition((activeGame.Red_Side[selection_index].getCol() - 1)* size, (activeGame.Red_Side[selection_index].getRow() + 1)* size);
                        window.draw(PurpleHighlight_Sprite);
                    }
                }
            }
        }

        //display the window
        window.display();
    }

    if (activeGame.bluewinsNotred() && (activeGame.win()))
    {
        //blue wins
        RenderWindow bluewins(VideoMode(452, 290), "Blue Wins!!!");

        Event bluewinsevent;

        while (bluewins.isOpen())
        {
            while (bluewins.pollEvent(bluewinsevent))
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter) || bluewinsevent.type == Event::Closed)
                {
                    bluewins.close();
                }
            }

            //get window ready for next render
            bluewins.clear();

            //draw splash
            bluewins.draw(bluewins_Sprite);

            //display the window
            bluewins.display();
        }
    }
    else if (!activeGame.bluewinsNotred() && (activeGame.win()))
    {
        //red wins
        RenderWindow redwins(VideoMode(447, 300), "Red Wins!!!");

        Event bluewinsevent;

        while (redwins.isOpen())
        {
            while (redwins.pollEvent(bluewinsevent))
            {
                if (Keyboard::isKeyPressed(Keyboard::Enter) || bluewinsevent.type == Event::Closed)
                {
                    redwins.close();
                }
            }

            //get window ready for next render
            redwins.clear();

            //draw splash
            redwins.draw(redwins_Sprite);

            //display the window
            redwins.display();
        }
    }
 

    return 0;
}