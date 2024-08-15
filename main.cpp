/***************************************************************************************************************************
* Made by: Illia K                                                                                                         *
* Made for: Ms. Cullum                                                                                                     *
* Course: ICS4U                                                                                                            *
* Date: March 2024                                                                                                         *
* Fantasy RPG Assignment: Object Oriented Programming, this game allows the user to select and play as one                 *
* of the two characters (a warrior or a hunter). The character has three different fields (health, fame, and money).       *
* The player must keep all of these fields above 0 in order to survive.                                                    *
* Having 0 fame is just social media death, but that still matters in this game.                                           *
* Character’s stats will each be measured by an integer. EACH "DAY" the player plays will DECREASE EVERY STAT by 3 points. *
* The player can INCREASE one of these STATS EACH DAY by selecting ONE of three options:                                   *
* hunt for food;                                                                                                           *
* fight monsters;                                                                                                          *
* search for treasure;                                                                                                     *
* Each option functions slightly differently in the way that it increases the player's stats.                              *
****************************************************************************************************************************/

// This is the main file/program, which connects all the files, establishing a link to the CodeBlocks so as to execute the code

#include <iostream>
#include "FantasyRPG.h"
#include <cstdlib>
#include <ctime>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <windows.h>

#define WHITE al_map_rgb (255,255,255)
#define windowName "Fantasy Game"
#define width 1600
#define height 900

using namespace std;

int main() {
    // Function prototypes
    void musicOn(const string&);
    bool wantsToPlay();

    int choiceOption();
    int initializeAllegro (int, int, string);

    // Variables needed
    bool play = true;
    bool alive = true;

    int countDays = 0;
    int maxDaysAlive = 0;
    int fameAboveTenCount = 0;

    system("CLS");

    // Initializing Allegro (until "Enter" key is pressed)
    initializeAllegro(width, height, windowName);

    while(play) {
        // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
        srand(time(0));

        // Reseting to defaults
        countDays = 0;
        fameAboveTenCount = 0;

        // Default settings and variables
        // Initializing reference variable without specifying it
        Warrior warrior;
        Hunter hunter;

        // General greetings and choice options
        int choice = choiceOption();

        // Our main loop until our player fails to survive
        while(alive) {
            // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
            srand(time(0));

            // Checkpoints manipulation/behind the scenes for positive reinforcement for the user
            if(warrior.getFame() > 10 || hunter.getFame() > 10) {
                fameAboveTenCount++;
            }

            // Checkpoints for positive reinforcement for the user
            if(fameAboveTenCount == 8) {
                musicOn("taDaa.wav");

                cout << "You have successfully and smartly kept fame above 10 for more than a week!" << endl << endl;
                cout << "Keep up the good work!" << endl << endl;
                cout << "There is your Nobel Prize! Ta daa!" << endl << endl;
            }

            // Checkpoints for positive reinforcement for the user
            else if(fameAboveTenCount == 15) {
                musicOn("taDaa.wav");

                cout << "You have successfully and smartly kept fame above 10 for more than two weeks!" << endl << endl;
                cout << "Keep up the good work!" << endl << endl;
                cout << "There is your Nobel Prize! Ta daa!" << endl << endl;
            }

            // Checkpoints for positive reinforcement for the user
            else if(fameAboveTenCount == 22) {
                musicOn("taDaa.wav");

                cout << "You have successfully and smartly kept fame above 10 for more than three weeks!" << endl << endl;
                cout << "Keep up the good work!" << endl << endl;
                cout << "There is your Nobel Prize! Ta daa!" << endl << endl;
            }

            // If the user chooses the first character (Warrior), respective code is executed
            if(choice == 1) {
                // Making sure we are not running out of scope
                if(warrior.getHealth() < 1 || warrior.getFame() < 1 || warrior.getMoney() < 1) {
                    break;
                }

                countDays++;

                cout << "         DAY " << countDays << endl << endl;

                // Our main function/driver
                warrior.Menu();

                // Losing their stats every day (each by 3)
                warrior.setHealth(warrior.getHealth() - 3);
                warrior.setFame(warrior.getFame() - 3);
                warrior.setMoney(warrior.getMoney() - 3);

                // Now by ternary operators, something new
                warrior.setHealth(warrior.getHealth() > 15 ? 15 : warrior.getHealth());
                warrior.setFame(warrior.getFame() > 15 ? 15 : warrior.getFame());
                warrior.setMoney(warrior.getMoney() > 20 ? 20 : warrior.getMoney());
            }
            // If the user chooses the second character (Hunter), respective code is executed
            else if(choice == 2) {
                // Making sure we are not running out of scope
                if(hunter.getHealth() < 1 || hunter.getFame() < 1 || hunter.getMoney() < 1) {
                    break;
                }

                countDays++;

                cout << "         DAY " << countDays << endl << endl;

                // Our main function/driver
                hunter.Menu();

                // Losing their stats every day (each by 3)
                hunter.setHealth(hunter.getHealth() - 3);
                hunter.setFame(hunter.getFame() - 3);
                hunter.setMoney(hunter.getMoney() - 3);

                // Now by ternary operators, something new
                hunter.setHealth(hunter.getHealth() > 20 ? 20 : hunter.getHealth());
                hunter.setFame(hunter.getFame() > 15 ? 15 : hunter.getFame());
                hunter.setMoney(hunter.getMoney() > 15 ? 15 : hunter.getMoney());
            }
            else {
                return 0;
            }
        }

        Sleep(5000);

        // Turning on game-over sound effects
        musicOn("gameOver.wav");

        cout << "Despite all of that, the game is over. Unfortunately, you have gone broke. You have survived for " << countDays << " days.";

        // Keeping track of the best score so far (by ternary operators, again, just to have something new)
        // As I have previously been using if-statements and kind of fed up of even looking at them
        // If maxDaysAlive is indeed greater than countDays, then the default answer to that question is maxDaysAlive, countDays otherwise
        maxDaysAlive = (maxDaysAlive > countDays) ? maxDaysAlive : countDays;

        cout << "\n\nYour best score of days survived so far is: " << maxDaysAlive << " days\n\n";

        // Allowing the user to play again
        if(wantsToPlay() == true) {
            continue;
        }
        else {
            break;
        }
    }

    cout << "See you later! Have a nice day!" << endl;

    return 0;
}
