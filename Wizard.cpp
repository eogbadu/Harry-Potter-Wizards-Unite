#include "Wizard.h"

// Default constructor
Wizard::Wizard()
{
  m_name = "Ekele";
  SetToughness((rand() % (MAX_START_TOUGH + 1 - MIN_START_TOUGH)) + MIN_START_TOUGH);
  m_level = 1;
  m_wins = 0;
  m_losses = 0;
}

Wizard::Wizard(string name)
{
  Wizard();
  SetName(name);
}

// Returns m_name
string Wizard::GetName()
{
  return(m_name);
}

// Returns m_toughness
int Wizard::GetToughness()
{
  return(m_toughness);
}

// Returns m_level
int Wizard::GetLevel()
{
  return(m_level);
}

// Returns m_wins
int Wizard::GetWins()
{
  return(m_wins);
}

// Returns m_losses
int Wizard::GetLosses()
{
  return(m_losses);
}

// Updates m_name
void Wizard::SetName(string name)
{
  m_name = name;
}

// Updates m_toughness
void Wizard::SetToughness(int toughness)
{
  m_toughness = toughness;
}

// Adds copy Foundable to m_foundables
void Wizard::InsertFoundable(Foundable newFoundable)
{
  m_foundables[m_wins - 1] = newFoundable;  
}

// Returns true if exists in m_foundables else false
bool Wizard::CheckFoundable(Foundable newFoundable)
{
  for (int i = 0; i < m_wins; i++)
  {
    if (m_foundables[i].GetName() == newFoundable.GetName())
      return true;
  }
  
  return false;
}

// Compares Wizard toughness to the enemy toughness
// (tie goes to enemy) Returns result of comparison
bool Wizard::AttackFoundable(Foundable enemy)
{
  // If wizard toughness is greater than Foundale toughness
  // player wins.
  if (m_toughness > enemy.GetToughness())
  {
    IncreaseLevel();
    return true;
  }
  m_losses += 1;
  return false;
}

// Displays a list of all foundables found by Wizard else
// indicates that there are none found
void Wizard::PrintMyFoundables()
{
  for (int i = 0; i < m_wins; i++)
  {
    cout << i + 1 << ". ";
    cout << m_foundables[i].GetName() << '|';
    cout << m_foundables[i].GetType() << '|';
    cout << m_foundables[i].GetRarity() << '|';
    cout << m_foundables[i].GetToughness() << endl;
  }

}

// Updates m_level by one and increases toughness from 0 to 100
void Wizard::IncreaseLevel()
{
  m_level += 1;
  m_wins += 1;
  m_toughness += (rand() % LEVEL_TOUGH_INCREASE + 1 - 0) + 0;
}
