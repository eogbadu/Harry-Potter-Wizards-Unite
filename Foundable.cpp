#include "Foundable.h"

// Deafault constructor
Foundable::Foundable()
{
  SetName(" ");
  SetType(" ");
  SetRarity(1);
  SetToughness(1);
}

// Overloaded constructor
Foundable::Foundable(string name, string type, int rarity, int toughness)
{
  SetName(name);
  SetType(type);
  SetRarity(rarity);
  SetToughness(toughness);
}

// Returns m_name
string Foundable::GetName()
{
  return(m_name);
}

// Returns m_type
string Foundable::GetType()
{
  return(m_type);
}

// Returns m_rarity
int Foundable::GetRarity()
{
  return(m_rarity);
}

// Returns m_toughness
int Foundable::GetToughness()
{
  return(m_toughness);
}

// Sets a new name in m_name
void Foundable::SetName(string newName)
{
  m_name = newName;
}

// Sets a new type in m_type
void Foundable::SetType(string newType)
{
  m_type = newType;
}

// Sets a new rarity in m_rarity
void Foundable::SetRarity(int newRarity)
{
  m_rarity = newRarity;
}

// Sets a new toughness in m_toughness
void Foundable::SetToughness(int newToughness)
{
  m_toughness = newToughness;
}
