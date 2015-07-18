#include "condition.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "character.h"

Condition::Condition()
  : m_gold_needed{0},
    m_items_needed{},
    m_items_not_needed{},
    m_provisions_needed{0}
{

}

void Condition::AddItemNeeded(const Item item)
{
  assert(
    std::count(
      std::begin(m_items_needed),
      std::end(m_items_needed),
      item
    ) == 0
  );
  m_items_needed.push_back(item);
}

void Condition::AddItemNotNeeded(const Item item)
{
  assert(
    std::count(
      std::begin(m_items_not_needed),
      std::end(m_items_not_needed),
      item
    ) == 0
  );
  m_items_not_needed.push_back(item);
}

bool Condition::IsSatisfied(const Character &character) const
{
  if (GetGoldNeeded() > character.GetGold()) return false;
  if (GetProvisionsNeeded() > character.GetProvisions()) return false;
  for (const auto item_needed: GetItemsNeeded())
  {
    if (!character.HasItem(item_needed)) return false;
  }
  for (const auto item_not_needed: GetItemsNotNeeded())
  {
    if (character.HasItem(item_not_needed)) return false;
  }
  return true;
}

void Condition::SetGoldNeeded(const int gold_needed)
{
  assert(gold_needed > 0);
  m_gold_needed = gold_needed;
}

void Condition::SetProvisionsNeeded(const int provisions_needed)
{
  assert(provisions_needed > 0);
  m_provisions_needed = provisions_needed;
}

std::ostream& operator<<(std::ostream& os, const Condition& condition)
{
  os
    << "gold needed: " << condition.GetGoldNeeded()
    << ", items needed: {"
  ;
  for (const auto item: condition.GetItemsNeeded())
  {
    os << ToStr(item) << ", ";
  }
  os << "}, items not_needed: {";
  for (const auto item: condition.GetItemsNotNeeded())
  {
    os << ToStr(item) << ", ";
  }
  os << "}";
  return os;
}
