#include "Game.h"

// Default constructor
Game::Game()
{
  cout << "Welcome to Harry Potter: Wizards Unite" << endl;

  //Load Foundables from file and check that it loaded properly
  int foundablesLoaded = LoadFoundables(); 
  if (foundablesLoaded != 1)
  {
    cout << "Can't let you play right now, goodbye!" << endl; 
  }

  
  GetWizardName(); // Gets the wizard name from player
  MainMenu();      // Print out main menu
}

// Returns wizard name to wizard class
void Game::GetWizardName()
{
  string name;
  cout << "What is your wizard's name?" << endl;
  getline(cin, name);
  m_wizard.SetName(name);
}

// Manages win condition and game
void Game::MainMenu()
{
  // Print menu
  int choice;
  if (m_wizard.GetWins() < NUM_FOUNDABLE)
  {
    cout << "What would you like to do?" << endl;
    cout << "1. Wizard Information" << endl;
    cout << "2. List My Foundables" << endl;
    cout << "3. List All Foundables" << endl;
    cout << "4. Attack Foundable" << endl;
    cout << "5. Quit" << endl;

    // Get choice and validate it
    cin >> choice;
    while ((choice < 1) || (choice > 5))
    {
      cout << "Please enter a valid choice (1 - 5)" << endl;
      cout << "What would you like to do?" << endl;
      cout << "1. Wizard Information" << endl;
      cout << "2. List My Foundables" << endl;
      cout << "3. List All Foundables" << endl;
      cout << "4. Attack Foundable" << endl;
      cout << "5. Quit" << endl;

      cin >> choice;
    }
  
    if ((choice > 0) && (choice <= 5))
    {
      switch (choice)
      {
      case 1:
	WizardStat();
	break;
      case 2:
	PrintMyFoundables();
	break;
      case 3:
	PrintFoundables();
	break;
      case 4:
	AttackFoundable();
	break;
      case 5:
	exit(1);
	break;
      default:
	exit(1);
      }
    }
    else
      cout << "You entered an invalid choice" << endl;
  }
  else
  {
    cout << "You win!!!" << endl;
    exit(1);
  }
}


// Populates m_allFoundables from a file
int Game::LoadFoundables()
{
  ifstream inStream;
  inStream.open(FILE_NAME);
  if(inStream.fail())
  {
    cout << "Foundable file failed to load.\n";
    return 0;
  }
  else
  {
    for (int i = 0; i < NUM_FOUNDABLE; i++)
    {
      // Declare temp Foundable variables
      string name;
      string type;
      string rarity;
      string tough;

      // Use getline delimited by a comma ','
      getline(inStream, name, ',');
      getline(inStream, type, ',');
      getline(inStream, rarity, ',');
      getline(inStream, tough);

      m_allFoundables[i] = Foundable(name, type, stoi(rarity), stoi(tough));
    }
    
    cout << NUM_FOUNDABLE << " Foundables loaded" << endl;
    inStream.close();
    return 1;
  }
}

// Displays all Foundables in game
void Game::PrintFoundables()
{
  for (int i = 0; i < NUM_FOUNDABLE; i++)
  {
    cout << i + 1 << ". ";
    cout << m_allFoundables[i].GetName() << '|';
    cout << m_allFoundables[i].GetType() << '|';
    cout << m_allFoundables[i].GetRarity() << '|';
    cout << m_allFoundables[i].GetToughness() << endl;
  }
  MainMenu();
}

// Prints the wizard stats to the screen
void Game::WizardStat()
{ 
  float total = (m_wizard.GetWins() + m_wizard.GetLosses()) * 1.0;
  float winRate = (m_wizard.GetWins() / total) * 100;
  cout << "**********************************************************" << endl;
  cout << "Information About Wizard " << m_wizard.GetName() << endl;
  cout << "Level: " << m_wizard.GetLevel() << endl;
  cout << "Toughness: " << m_wizard.GetToughness() << endl;
  cout << "Foundables Found: " << m_wizard.GetWins() << endl;
  cout << "Wins: " << m_wizard.GetWins() << " ";
  cout << "Losses: " << m_wizard.GetLosses() << endl;
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  if ((m_wizard.GetWins() < 1) && (m_wizard.GetLosses() < 1))
  {
    cout << "Win Rate: 0%" << endl;
  }
  else
    cout << "Win Rate: " << winRate << "%" << endl;
  cout << noshowpoint;
  cout << "**********************************************************" << endl;

  MainMenu();
}

// Prints all the captured Foundables to screen
void Game::PrintMyFoundables()
{
  if (m_wizard.GetWins() > 0)
  {
    m_wizard.PrintMyFoundables();
  }
  else
  {
    cout << "You have not defeated any foundables yet." << endl;
  }
  MainMenu();
}

// Used to attack Foundables of a specific rarity
// No duplicate Foundables can be attacked.
void Game::AttackFoundable()
{
  int randomPos; // Random positions to attack foundables 
  int rarityFoundableCount = 0; // Total Foundables with particular rarity
  int wizardFoundableCount = 0; // Wizard Foundables with particular rarity
  int rarityLevel; // The rarity level of a Foundable
  bool win = false; // Checks to see if the wizard defeated the Foundable
  bool flag = false; // Checks if valid Foundable has been attacked

  // Get rarity and validate
  cout << "What rarity of Foundable would you like to challenge (1-5)?\n";
  cin >> rarityLevel;
  while ((rarityLevel < 1) || (rarityLevel > 5))
  {
    cout << "Please enter a valid rarity." << endl;
    cout << "What rarity of Foundable would you like to challenge (1-5)?\n";
    cin >> rarityLevel;
  }

  // Count total Foundables of a particular rarity
  for (int i = 0; i < NUM_FOUNDABLE; i++)
  {
    if (m_allFoundables[i].GetRarity() == rarityLevel)
    {
      rarityFoundableCount++;
    }
  }

  // Get random Foundable position
  randomPos = (rand() % NUM_FOUNDABLE + 1 - 0) + 0;

  // While a valid Foundable has not been attacked...repeat
  while (flag != true)
  {
    // If random Foundable is the right rarity
    if	(m_allFoundables[randomPos].GetRarity() == rarityLevel)
    {
      // if wizard has not defeated Foundable previously
      if (m_wizard.CheckFoundable(m_allFoundables[randomPos]) != true)
      {
	cout << "The Wizard " << m_wizard.GetName() << " attacks ";
	cout << m_allFoundables[randomPos].GetName() << "!!!" << endl;
	win = m_wizard.AttackFoundable(m_allFoundables[randomPos]);
	if (win == true)
	{
	  m_wizard.InsertFoundable(m_allFoundables[randomPos]);
	  cout << "You defeat the " << m_allFoundables[randomPos].GetName();
	  cout << "!!\n";
	}
	else
	{
	  cout << "You are unable to defeat ";
	  cout << m_allFoundables[randomPos].GetName();
	  cout << "!!\n";
	}

	flag = true;
      }
      // if Wizard has defeated Foundable previously, check if you
      // have captured all Foundable of that rarity
      else
      {
	wizardFoundableCount++;
	if (wizardFoundableCount == rarityFoundableCount)
	{
	  cout << "You have found all Foundables ";
	  cout << "at that level of rarity!"<< endl;
	  flag = true;
	}
      }
    }
    randomPos = (rand() % NUM_FOUNDABLE + 1 - 0) + 0;
  }
  MainMenu();
}
