// This cpp file is a separate file that handles all the functions & classes (along with its attributes) of the header file
// It's a good practice to separate the big project into separate, smaller, more digestible and manageable parts
// Just like with eating food: so that your organism/the developer/the code viewer isn't stressed with the puzzle-headed & convoluted food/code

#include "FantasyRPG.h"
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <cstdlib>
#include <windows.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <ctime>

#define WHITE al_map_rgb (255, 255, 255)
#define BLACK al_map_rgb (0, 0, 0)

// Pointers
ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_FONT *font;
ALLEGRO_FONT *fontSmall;
ALLEGRO_FONT *fontMid;

// Define bitmaps
ALLEGRO_BITMAP *warriorFight = nullptr;
ALLEGRO_BITMAP *warriorTreasure = nullptr;
ALLEGRO_BITMAP *warriorFood = nullptr;
ALLEGRO_BITMAP *warriorGladiator= nullptr;
ALLEGRO_BITMAP *hunterFight = nullptr;
ALLEGRO_BITMAP *hunterTreasure = nullptr;
ALLEGRO_BITMAP *hunterFood = nullptr;
ALLEGRO_BITMAP *hunterGladiator= nullptr;

using namespace std;

// Constructor for parent class
Person::Person() {
    /*
    Making the game more unique by altering the maximum stats (however, it's worth noting that for the best practice possible,
    instead of making stats, such as fame, money, and health public and declaring them for each class, I would better use
    public methods that serve as a transit as opposed to messing up with OOP
    */

    fame = 15;
}

/*
Optional destructor for parent class (overriding children classes)

Person::~Person() {
    Cout whatever is needed (here it is not required)
}
*/

// Allowing actual getters to function for our skeleton coded in "FantasyRPG.h"
int Person::getHealth() {
    return health;
}

int Person::getFame() {
    return fame;
}

int Person::getMoney() {
    return money;
}

// Allowing actual setters to function for our skeleton coded in "FantasyRPG.h"
void Person::setHealth(int newHealth) {
    health = newHealth;
}

void Person::setFame(int newFame) {
    fame = newFame;
}

void Person::setMoney(int newMoney) {
    money = newMoney;
}

// Our menu that will serve as a basis for communication with the user
void Person::Menu() {
    int wants;

    toString();

    cout << "What would you like to do?" << endl << endl;
    cout << "   1.  Hunt for food" << endl;
    cout << "   2.  Fight monsters" << endl;
    cout << "   3.  Search for treasure" << endl;

    if(name == "Warrior") {
        // Our warrior has an access to modern medicine and tons of money, and so can allow to buy and use a kit
        cout << "   4.  Utilize a first-aid medical kit in the hospital" << endl << endl;
    }
    else if(name == "Hunter") {
        // Our hunter has more health, so he has an ability to perform a battle and gain some money as an actor
        cout << "   4.  Save poor Italian civilians from a lion in the middle of Colosseum" << endl << endl;
    }

    cout << "Please type up your answer here: ";
    cin >> wants;

    // Updating the screen for the sake of the user
    system("CLS");

    // Our sort of an even queue of sorts/processing the input of the user
    if(wants == 1) {
        findFood();
    }
    else if(wants == 2) {
        fightMonsters();
    }
    else if(wants == 3) {
        searchTreasure();
    }
    else if(wants == 4) {
        if(name == "Warrior") {
            useMedicalKit();
        }
        else if(name == "Hunter") {
            gladiatorFight();
        }
        else {
            system("CLS");

            cout << "Error Occured!";

            exit(0);
        }
    }
    else {
        // Wiping out the screen
        system("CLS");

        cout << "No such deed exists! Please restart the game!" << endl;

        // Exiting the game (with respect to zero) as if we returned zero in our non-void function
        exit(0);
    }

    cout << endl;
}

// A function to be called in the menu function (info printer)
void Person::toString() {
    cout << "Character: " << name << endl << endl;
    cout << "Health: " << getHealth() << maxHealth << endl << endl;
    cout << "Fame: " << getFame() << "/15" << endl << endl;
    cout << "Money: " << getMoney() << maxMoney << endl << endl;
}

// Different options of what to do so as to allow the user to remain alive and continue playing
void Person::findFood() {
    if(name == "Warrior") {
        // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
        srand(time(0));

        // Random number between 0 and 2 inclusive
        int r = rand() % 2 + 1;

        if(r == 1) {
            /*
            The reason why I'm setting such a ridiculously large number is because I'm subtracting 3 each day, so to balance things out,
            this will throw the compiler into my ternary operations/operators and set the health to 15 automatically
            */
            setHealth(10000000);

            cout << "You manage to come home after a bountiful feast feeling replenished.\n";

            // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
            srand(time(0));
        }
        else if(r == 2) {
            // Nothing happens
            cout << "You spend the day searching for food, but unfortunately found nothing.\n";

            // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
            srand(time(0));
        }
        else {
            // An error handler just in case
            cout << "Error occurred!";
        }
    }
    else if(name == "Hunter") {
        // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
        srand(time(0));

        int r = rand() % 6 + 6;

        // Random number between 0 and 5 inclusive, but shifted to the right by 6, so from 6 to 11 inclusive;
        setHealth(getHealth() + r);

        cout << "You manage to come home after a bountiful feast feeling replenished. You have received " << r << " HP\n";

        // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
        srand(time(0));
    }
    else {
        cout << "Error! No such character exists!\n";
    }
}

void Person::fightMonsters() {
    // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
    srand(time(0));

    // Random number between 0 and 7 inclusive, but shifted to the right by 7, so from 7 to 14 inclusive;
    int k = rand() % 2 + 1;

    if(k == 1) {
        if(name == "Warrior") {
            // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
            srand(time(0));

            // Random number between 0 and 7 inclusive, but shifted to the right by 7, so from 7 to 14 inclusive;
            int r = rand() % 8 + 7;

            setFame(getFame() + r);

            setHealth(getHealth() - 2);

            cout << "You found a worthy opponent but managed to beat it after a lengthy battle. \nYou lost 2 HP in the process, but gained " << r << " fame points.\n";

            // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
            srand(time(0));
        }
        else if(name == "Hunter") {
            // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
            srand(time(0));

            // Random number between 6 and 10
            int r = rand() % 5 + 6;

            setFame(getFame() + r);

            setHealth(getHealth() - r / 2);

            cout << "You found a worthy opponent but managed to beat it after a lengthy battle. \nYou lost " << r / 2 << " HP in the process, but gained " << r << " fame points.\n";

            // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
            srand(time(0));
        }
        else {
            cout << "Error! No such character exists!\n";
        }
    }
    else if(k == 2) {
        if(name == "Warrior") {
            //Error handling so that the user doesn't end up fighting for monsters and being beaten up infinitely
            if(getHealth() != 1) {
                cout << "Unfortunately, the monster happened to be too powerful. You are beaten up!\n";

                setHealth(4);
                setFame(getFame() - 3);

                // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
                srand(time(0));
            }
        }
        else if(name == "Hunter") {
            //Error handling so that the user doesn't end up fighting for monsters and being beaten up infinitely
            if(getHealth() != 1) {
                cout << "Unfortunately, the monster happened to be too powerful. You are beaten up!\n";

                setHealth(4);
                setFame(getFame() - 3);

                // Seed the random number generator with the current time so that we get a unique set of random integers each time the program runs
                srand(time(0));
            }
        }
    }
    else {
        cout << "Error!\n";

        exit(0);
    }
}

void Person::searchTreasure() {
    if(name == "Warrior") {
        setMoney(getMoney() + 5);
        cout << "Lucky you! Congrats, you have just found 5 treasure points!\n";
    }
    else if(name == "Hunter") {
        setMoney(getMoney() + 7);
        cout << "Lucky you! Congrats, you have just found 7 treasure points!\n";
    }
    else {
        cout << "Error! No such character exists!\n";
    }
}

// This function allows the player (given Warrior) to utilize modern first-aid medical kit
void Person::useMedicalKit() {
    setHealth(getHealth() + 11);
    setMoney(getMoney() - 7); // So that with 3 subtracted it will end up in negative 10, could have easily done on top of 3

    // Improvisations
    cout << "Medicine is extremely deficit yet vital for warriors! Therefore you are alive but almost bankrupt!\n";
}

// This function expands the menu by allowing the player (given Hunter) to fight in Rome
void Person::gladiatorFight() {
    setHealth(getHealth() - 7);
    setMoney(getMoney() + 11);

    // Some creative expression of communication
    cout << "You have got quite a significant compensation from saving innocent people's lives. Perfecto!" << endl << "The 24-hour fight made you so exhausted---you are starving now!\n";
}

// Inherited constructor implementation for Warrior
Warrior::Warrior() : Person() {
    name = "Warrior";

    setHealth(15);
    setMoney(20);

    maxHealth = "/15";
    maxMoney = "/20";
}

// Inherited constructor implementation for Hunter
Hunter::Hunter() : Person() {
    name = "Hunter";

    setHealth(20);
    setMoney(15);

    maxHealth = "/20";
    maxMoney = "/15";
}

// Non-OOP function required (allows the user to choose to play again)
bool wantsToPlay() {
    string answer;

    // Allowing the user to play again
    cout << "Do you want to play again?" << endl << endl;
    cout << "Please type up your answer here: ";
    cin >> answer;

    // Using transform() function and ::tolower in STL so that my response is not case-sensitive
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

    // Checking whether the wish to play again (lower-cased) starts with "y" or "n"
    if(answer.rfind("y", 0) == 0) {
        // Cleaning up the screen every time the game starts
        system ("CLS");

        return true;
    }
    else if(answer.rfind("n", 0) == 0) {
        // Cleaning up the screen every time the game starts
        system ("CLS");
    }
    else {
        system ("CLS");

        cout << "Error! Invalid input!";

        exit(0);
    }

    return false;
}

// Non-OOP function that provides with a brief description of the game and basic choices
int choiceOption() {
    int desire = 0;

    // General greetings
    cout << "Welcome to the Fantasy Character Game! You can play as one of two characters." << endl;
    cout << "You will need to manage your health, fame, and money in order to survive!" << endl;

    Sleep(10000);

    // Wiping the screen off
    system("CLS");

    cout << "IMPORTANT NOTE: PLEASE TURN YOUR VOLUME ON!" << endl << endl;
    cout << "For you, my dear user, to experience this game in the best way possible, it is highly recommended to type up Winmm in:" << endl << "Code::Blocks -> Settings -> Compiler -> Linker Settings -> Link Libraries -> Add -> Ok" << endl << endl;

    Sleep(10000);

    // Wiping the screen off
    system("CLS");

    // Allowing the user to choose between models
    cout << "Who would you like to play as?" << endl << endl;
    cout << "  1.  Warrior (has a lot of money from serving on the front lines)" << endl;
    cout << "  2.  Hunter (his long walks in the wildlife made him very ressistant)" << endl << endl;
    cout << "Please type up your answer here: ";
    cin >> desire;
    cout << endl;

    if(desire == 1) {
        // Wiping the screen off
        system("CLS");

        cout << "You have selected Warrior!" << endl << endl;

        // Pausing for three seconds for better user experience
        Sleep(3000);

        // Wiping the screen off
        system("CLS");
    }
    else if(desire == 2) {
        // Wiping the screen off
        system("CLS");

        cout << "You have selected Hunter!" << endl << endl;

        // Pausing for three seconds for better user experience
        Sleep(3000);

        // Wiping the screen off
        system("CLS");
    }
    else {
        system("CLS");

        cout << "You crashed the system! Please restart the game!" << endl;
    }

    return desire;
}

// A function that turns the music on (while working with the object itself by referencing it, so that no unnecessary copies are created)
// NOTE: Add a Winmm library in the linker tabs in the compiler settings for this to work
// Function to play music repeatedly
void musicOnRepeat(const string& soundFile) {
    // Prototype
    bool fileExists(const string&);

    // SND_LOOP to play repeatedly
    if(fileExists(soundFile)) {
        PlaySoundA(soundFile.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }
    else {
        cout << "Error: File '" << soundFile << "' not found." << endl;
    }
}

// Function to play music once
void musicOn(const string& soundFile) {
    // Prototype
    bool fileExists(const string&);

    // SND_LOOP to play repeatedly
    if(fileExists(soundFile)) {
        PlaySoundA(soundFile.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    }
    else {
        cout << "Error: File '" << soundFile << "' not found." << endl;
    }
}

// Function to check if a file exists
bool fileExists(const string& filename) {
    ifstream file(filename);

    return file.good();
}

// This function initializes the display of Allegro with the size of width*height and name of title
int initializeAllegro(int width, int height, string title) {
    // Prototypes of functions
    void musicOn(const string&);
    int drawWarriorImages();
    int drawHunterImages();
    int drawWarriorText();
    int drawHunterText();
    bool enterKeypress();

    // Assigning value to string title
    const int length = title.length();

    // Declaring character array (+1 for null terminator)
    char* nameOfWindow = new char[length + 20];

    // Copying the contents of the
    // String to char array
    strcpy(nameOfWindow, title.c_str());

    //Initialize Allegro
    al_init();

    //Initialize display
    display = al_create_display(width, height);

    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);

        return -1;
    }

    // Initialize the title
    al_set_window_title(display, nameOfWindow);

    //Initialize keyboard routines
	if(!al_install_keyboard()) {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}

   	// Initialize addons
   	if(!al_init_primitives_addon()) {
        cerr << "Failed to initialize primitives addon." << endl;
        return 0;
    }

    // Initialize event queue
    event_queue = al_create_event_queue();

    if(!event_queue) {
        al_show_native_message_box(NULL, NULL, NULL, "Failed to create event queue!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Register display close event source
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    // Addons
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    // Font declaration
    font = al_load_font("Arial.ttf", 80, 0);
    fontMid = al_load_font("Arial.ttf", 50, 0);
    fontSmall = al_load_font("Arial.ttf", 33, 0);

    if(!font) {
        cout << "Failed to load font.\n";

        al_destroy_display(display);

        return -1;
    }

    // Defining initial colors
    float redFactor = 1.0f;
    float greenFactor = 0.0f;

    // Drawing fading rainbow background: cool and fantastic (hence the fantasy name)!
    for(int i = 0; i < height; i++) {
        // Updating color components
        redFactor -= 0.001f;
        greenFactor += 0.001f;

        // Creating color
        ALLEGRO_COLOR color = al_map_rgb(255 * redFactor, 255 * greenFactor, 255);

        // Drawing rectangle
        al_draw_filled_rectangle(0, i, width, i + 1, color);

        // Update the display to show the changes (every second the picture slides down)
        al_flip_display();
    }

    // Drawing "Welcome" text at the top of the screen
    al_draw_text(fontSmall, WHITE, width / 2, 10, ALLEGRO_ALIGN_CENTER, "Hi there! Welcome to the Fantasy Game! You can do a whole lot here! :) For instance, as a Warrior, you can: ");

    // Drawing "Press 'Enter' to continue!" text below the "Welcome" text
    al_draw_text(font, WHITE, width / 2, 805, ALLEGRO_ALIGN_CENTER, "Please press 'Enter' to continue!");

    // Drawing character
    drawWarriorImages();
    drawWarriorText();

    // Update the display to show the changes
    al_flip_display();

    // Turning on the appropriate music
    musicOnRepeat("eyeOfTheTiger.wav");

    // Window closes when pressed "ENTER"
    while(!enterKeypress()) {
        al_rest(0.1);
    }

    // Defining initial colors
    float green1Factor = 1.0f;
    float blue1Factor = 0.0f;

    // Drawing fading rainbow background: cool and fantastic (hence the fantasy name)!
    for(int i = 0; i < height; i++) {
        // Updating color components
        green1Factor -= 0.001f;
        blue1Factor += 0.001f;

        // Creating color
        ALLEGRO_COLOR color = al_map_rgb(255, 200 * green1Factor, 125 * blue1Factor);

        // Drawing rectangle
        al_draw_filled_rectangle(0, i, width, i + 1, color);

        // Update the display to show the changes (every second the picture slides down)
        al_flip_display();
    }

    // Drawing "Welcome" text at the top of the screen
    al_draw_text(fontMid, WHITE, width / 2, 10, ALLEGRO_ALIGN_CENTER, "You can also be a Hunter! He can do the following: ");

    // Drawing "Press 'Enter' to continue!" text below the "Welcome" text
    al_draw_text(font, WHITE, width / 2, 805, ALLEGRO_ALIGN_CENTER, "Please press 'Enter' to continue!");

    // Displaying characters one by one
    drawHunterImages();
    drawHunterText();

    // Update the display to show the changes
    al_flip_display();

    // Window closes when pressed "ENTER"
    while(!enterKeypress()) {
        al_rest(0.1);
    }

    // Defining initial colors
    float green2Factor = 0.0f;
    float blue2Factor = 1.0f;

    // Drawing fading rainbow background: cool and fantastic (hence the fantasy name)!
    for(int i = 0; i < height; i++) {
        // Updating color components
        green2Factor += 0.001f;
        blue2Factor -= 0.001f;

        // Creating color
        ALLEGRO_COLOR color = al_map_rgb(255, 125 * green2Factor, 200 * blue2Factor);

        // Drawing rectangle
        al_draw_filled_rectangle(0, i, width, i + 1, color);

        // Update the display to show the changes (every second the picture slides down)
        al_flip_display();
    }

    // Drawing
    al_draw_text(font, WHITE, width / 2, 10, ALLEGRO_ALIGN_CENTER, "Good Luck Have Fun! :)");

    // Drawing
    al_draw_text(font, WHITE, width / 2, 805, ALLEGRO_ALIGN_CENTER, "Please press 'Enter' to continue!");

    al_flip_display();

    // Window closes when pressed "ENTER"
    while(!enterKeypress()) {
        al_rest(0.1);
    }

    // Destroying the window (our pointer to allegro window)
    al_destroy_display(display);

    // Music off after the display is closed
    PlaySoundA(NULL, NULL, 0);

    return 0;
}

// Return true when enter key is pressed or window closed x
bool enterKeypress() {
    ALLEGRO_KEYBOARD_STATE key_state;
    ALLEGRO_EVENT ev;

    al_wait_for_event(event_queue, &ev);

    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return true;
    }

    al_get_keyboard_state(&key_state);

    return al_key_down(&key_state, ALLEGRO_KEY_ENTER);
}

int drawWarriorImages() {
    // Loading the hunting for food warrior
    warriorFood = al_load_bitmap("WarriorFood.png");

    // Getting the actual size of the image
    int warriorFoodWidth = al_get_bitmap_width(warriorFood);
    int warriorFoodHeight = al_get_bitmap_height(warriorFood);

    // Error handling
    if(!warriorFood) {
        cout << "No hunting for food warrior!" << endl;

        return -1;
    }

    // Define the desired width and height for drawing the image
    // Width/Height ratio has also remained the same (arithmetic calculations)
    int warriorFoodDesiredWidth = 266;
    int warriorFoodDesiredHeight = 213;

    // Drawing the hunting-for-food warrior with scaling
    al_draw_scaled_bitmap(warriorFood, 0, 0, warriorFoodWidth, warriorFoodHeight, 10, 200, warriorFoodDesiredWidth, warriorFoodDesiredHeight, 0);

    /////For better communication and vision (separating code)/////

    // Loading the hunting-for-food warrior
    warriorFight = al_load_bitmap("WarriorAttack.png");

    // Getting the actual size of the image
    int warriorFightWidth = al_get_bitmap_width(warriorFight);
    int warriorFightHeight = al_get_bitmap_height(warriorFight);

    // Error handling
    if(!warriorFight) {
        cout << "No fighting warrior!" << endl;

        return -1;
    }

    // Define the desired width and height for drawing the image
    // Width/Height ratio has also remained the same (arithmetic calculations)
    int warriorFightDesiredWidth = 213;
    int warriorFightDesiredHeight = 226;

    // Drawing the fighting warrior with scaling
    al_draw_scaled_bitmap(warriorFight, 0, 0, warriorFightWidth, warriorFightHeight, 410, 200, warriorFightDesiredWidth, warriorFightDesiredHeight, 0);

    /////For better communication and vision (separating code)/////

    // Loading the hunting for gold warrior
    warriorTreasure = al_load_bitmap("WarriorTreasure.png");

    // Getting the actual size of the image
    int warriorTreasureWidth = al_get_bitmap_width(warriorTreasure);
    int warriorTreasureHeight = al_get_bitmap_height(warriorTreasure);

    // Error handling
    if(!warriorTreasure) {
        cout << "No looking for treasure warrior!" << endl;

        return -1;
    }

    // Define the desired width and height for drawing the image
    // Width/Height ratio has also remained the same (arithmetic calculations)
    int warriorTreasureDesiredWidth = 293;
    int warriorTreasureDesiredHeight = 285;

    // Drawing the hunting for gold warrior with scaling
    al_draw_scaled_bitmap(warriorTreasure, 0, 0, warriorTreasureWidth, warriorTreasureHeight, 710, 170, warriorTreasureDesiredWidth, warriorTreasureDesiredHeight, 0);

    /////For better communication and vision (separating code)/////

    // Loading the fighting with tiger warrior
    warriorGladiator = al_load_bitmap("GladiatorWarrior.png");

    // Getting the actual size of the image
    int warriorGladiatorWidth= al_get_bitmap_width(warriorGladiator);
    int warriorGladiatorHeight = al_get_bitmap_height(warriorGladiator);

    // Error handling
    if(!warriorGladiator) {
        cout << "No fighting with Tiger warrior!" << endl;

        return -1;
    }

    // Define the desired width and height for drawing the image
    // Width/Height ratio has also remained the same (arithmetic calculations)
    int warriorGladiatorDesiredWidth = 466;
    int warriorGladiatorDesiredHeight = 266;

    // Drawing the hunting for gold warrior with scaling
    al_draw_scaled_bitmap(warriorGladiator, 0, 0, warriorGladiatorWidth, warriorGladiatorHeight, 1110, 170, warriorGladiatorDesiredWidth, warriorGladiatorDesiredHeight, 0);

    /////For better communication and vision (separating code)/////

    return 0;
}

int drawHunterImages() {
    // Loading the hunting for food Hunter
    hunterFood = al_load_bitmap("HunterFood.png");

    // Getting the actual size of the image
    int hunterFoodWidth = al_get_bitmap_width(hunterFood);
    int hunterFoodHeight = al_get_bitmap_height(hunterFood);

    // Error handling
    if(!hunterFood) {
        cout << "No hunting for food hunter!" << endl;

        return -1;
    }

    // Define the desired width and height for drawing the image
    // Width/Height ratio has also remained the same (arithmetic calculations)
    int hunterFoodDesiredWidth = 266;
    int hunterFoodDesiredHeight = 213;

    // Drawing the hunting-for-food hunter with scaling
    al_draw_scaled_bitmap(hunterFood, 0, 0, hunterFoodWidth, hunterFoodHeight, 10, 200, hunterFoodDesiredWidth, hunterFoodDesiredHeight, 0);

    /////For better communication and vision (separating code)/////

    // Loading the hunting-for-food hunter
    hunterFight = al_load_bitmap("HunterAttack.png");

    // Getting the actual size of the image
    int hunterFightWidth = al_get_bitmap_width(hunterFight);
    int hunterFightHeight = al_get_bitmap_height(hunterFight);

    // Error handling
    if(!hunterFight) {
        cout << "No fighting hunter!" << endl;

        return -1;
    }

    // Define the desired width and height for drawing the image
    // Width/Height ratio has also remained the same (arithmetic calculations)
    int hunterFightDesiredWidth = 213;
    int hunterFightDesiredHeight = 226;

    // Drawing the fighting warrior with scaling
    al_draw_scaled_bitmap(hunterFight, 0, 0, hunterFightWidth, hunterFightHeight, 410, 200, hunterFightDesiredWidth, hunterFightDesiredHeight, 0);

    /////For better communication and vision (separating code)/////

    // Loading the hunting for gold hunter
    hunterTreasure = al_load_bitmap("HunterTreasure.png");

    // Getting the actual size of the image
    int hunterTreasureWidth = al_get_bitmap_width(hunterTreasure);
    int hunterTreasureHeight = al_get_bitmap_height(hunterTreasure);

    // Error handling
    if(!hunterTreasure) {
        cout << "No looking for treasure hunter!" << endl;

        return -1;
    }

    // Define the desired width and height for drawing the image
    // Width/Height ratio has also remained the same (arithmetic calculations)
    int hunterTreasureDesiredWidth = 293;
    int hunterTreasureDesiredHeight = 285;

    // Drawing the hunting for gold warrior with scaling
    al_draw_scaled_bitmap(hunterTreasure, 0, 0, hunterTreasureWidth, hunterTreasureHeight, 710, 170, hunterTreasureDesiredWidth, hunterTreasureDesiredHeight, 0);

    /////For better communication and vision (separating code)/////

    // Loading the fighting with tiger hunter
    hunterGladiator = al_load_bitmap("GladiatorHunter.png");

    // Getting the actual size of the image
    int hunterGladiatorWidth= al_get_bitmap_width(hunterGladiator);
    int hunterGladiatorHeight = al_get_bitmap_height(hunterGladiator);

    // Error handling
    if(!warriorGladiator) {
        cout << "No fighting with Tiger hunter!" << endl;

        return -1;
    }

    // Define the desired width and height for drawing the image
    // Width/Height ratio has also remained the same (arithmetic calculations)
    int hunterGladiatorDesiredWidth = 466;
    int hunterGladiatorDesiredHeight = 266;

    // Drawing the hunting for gold warrior with scaling
    al_draw_scaled_bitmap(hunterGladiator, 0, 0, hunterGladiatorWidth, hunterGladiatorHeight, 1110, 170, hunterGladiatorDesiredWidth, hunterGladiatorDesiredHeight, 0);

    /////For better communication and vision (separating code)/////

    return 0;
}

int drawWarriorText() {
    // Drawing description to images
    al_draw_text(fontSmall, BLACK, 90, 450, 0, "look for food");

    // Drawing description to images
    al_draw_text(fontSmall, BLACK, 400, 460, 0, "fight monsters");

    // Drawing description to images
    al_draw_text(fontSmall, BLACK, 750, 480, 0, "look for treasure");

    // Drawing description to images
    al_draw_text(fontSmall, BLACK, 1170, 500, 0, "protect innocent people");

    return 0;
}

int drawHunterText() {
    // Drawing description to images
    al_draw_text(fontSmall, BLACK, 90, 450, 0, "look for food");

    // Drawing description to images
    al_draw_text(fontSmall, BLACK, 400, 460, 0, "fight monsters");

    // Drawing description to images
    al_draw_text(fontSmall, BLACK, 750, 480, 0, "look for treasure");

    // Drawing description to images
    al_draw_text(fontSmall, BLACK, 1170, 500, 0, "protect innocent people");

    return 0;
}

// Finally
