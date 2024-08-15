#include <string>

using namespace std;

// This is a header file that uses minimum memory and allocates the headers, getters, setters, and initializes the architecture of the program
// No functionality here, just initialization

// Class that serves as a parent class for "Warrior" and "Hunter" classes, this will be more efficient (for instance, no duplication)
class Person {
  public:
    // Constructor
    Person();

    // Optional destructor
    // ~Person();

    // Getters and Setters
    int getHealth();
    int getFame();
    int getMoney();

    // Functions
    void setHealth(int newHealth);
    void setFame(int newFame);
    void setMoney(int newMoney);
    void Menu();
    void toString();
    void findFood();
    void fightMonsters();
    void searchTreasure();
    void useMedicalKit();
    void gladiatorFight();

    // Variable "name" that we want to make public so that it is changeable throughout the children classes, along with some adjustments
    string name;
    string maxHealth;
    string maxMoney;

  private:
    // Other private stuff we don't want people to mess up with goes here
    // Variables needed
    int health;
    int fame;
    int money;
};

class Warrior : public Person {
  public:
    // Inherited constructor along with all of its functions
    Warrior();

  private:
    // Other private stuff we don't want people to mess up with goes here
};

// Explicit OOP declaration
class Hunter : public Person {
  public:
    // Inherited constructor along with all of its functions
    Hunter();

  private:
    // Other private stuff we don't want people to mess up with goes here
};
