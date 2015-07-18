#ifndef CONDITION_H
#define CONDITION_H

#include <vector>

#include "item.h"

struct Character;

///Something that is true or false
struct Condition
{
  Condition();

  ///Must have this item
  void AddItemNeeded(const Item item);

  ///Must not have this item
  void AddItemNotNeeded(const Item item);

  int GetGoldNeeded() const noexcept { return m_gold_needed; }
  int GetProvisionsNeeded() const noexcept { return m_provisions_needed; }
  const std::vector<Item>& GetItemsNeeded() const noexcept { return m_items_needed; }
  const std::vector<Item>& GetItemsNotNeeded() const noexcept { return m_items_not_needed;; }

  bool IsSatisfied(const Character& character) const;

  void SetGoldNeeded(const int amount);
  void SetProvisionsNeeded(const int amount);

  private:
  int m_gold_needed;
  std::vector<Item> m_items_needed;
  std::vector<Item> m_items_not_needed;
  int m_provisions_needed;
};

std::ostream& operator<<(std::ostream& os, const Condition& condition);

#endif // CONDITION_H
