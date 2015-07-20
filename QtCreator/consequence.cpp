#include "consequence.h"

#include <cassert>
#include <iostream>

#include "character.h"
#include "helper.h"

Consequence::Consequence()
  :
    m_add_items{},
    m_change_arrows{0},
    m_change_dex{0},
    m_change_gold{0},
    m_change_luck{0},
    m_change_provisions{0},
    m_change_sta{0},
    m_next_chapter{-1},
    m_remove_items{}
{

}

void Consequence::Add(const Consequence& other)
{
  this->m_change_arrows += other.m_change_arrows;
  this->m_change_dex += other.m_change_dex;
  this->m_change_gold += other.m_change_gold;
  this->m_change_luck += other.m_change_luck;
  this->m_change_provisions += other.m_change_provisions;

  this->m_change_sta += other.m_change_sta;
  for (const auto item_to_add: other.GetItemsToAdd())
  {
    this->m_add_items.push_back(item_to_add);
  }
  for (const auto item_to_remove: other.GetItemsToRemove())
  {
    this->m_remove_items.push_back(item_to_remove);
  }

}

void Consequence::AddItemToAdd(const Item& item)
{
  m_add_items.push_back(item);
}

void Consequence::AddItemToRemove(const Item& item)
{
  m_remove_items.push_back(item);
}

void Consequence::Apply(Character& character) const
{
  #ifndef NDEBUG
  const bool verbose{false};
  #else
  const bool verbose{false};
  #endif

  if (GetNextChapter() != -1)
  {
    character.SetChapter(GetNextChapter());
  }

  //Arrows
  {
    const int change_arrows{GetChangeArrows()};
    if (change_arrows > 0)
    {
      if (verbose) { std::clog << "Changing arrows by " << change_arrows << std::endl; }
      character.ChangeArrows(change_arrows);
      const int delta_stamina{-3 * change_arrows}; //Each arrow damages three stamina
      if (verbose) { std::clog << "Changing stamina due to arrows by " << delta_stamina << std::endl; }
      character.ChangeStamina(delta_stamina);
    }
    else if (change_arrows < 0)
    {
      if (verbose) { std::clog << "Changing arrows by " << character.GetArrows() << std::endl; }
      character.ChangeArrows(-character.GetArrows());
      const int delta_stamina{2 * character.GetArrows()}; //Each arrow is healed by two stamina
      if (verbose) { std::clog << "Changing stamina due to arrows by " << delta_stamina << std::endl; }
      character.ChangeStamina(delta_stamina);
    }
  }
  //Dex
  {
    const int change_dex{GetChangeDexterity()};
    if (change_dex != 0)
    {
      if (verbose) { std::clog << "Changing dexterity by " << change_dex << std::endl; }
      character.ChangeDexterity(change_dex);
    }
  }
  //Gold
  {
    const int change_gold{GetChangeGold()};
    if (change_gold != 0)
    {
      if (verbose) { std::clog << "Changing gold by " << change_gold << std::endl; }
      character.ChangeGold(change_gold);
    }
  }
  //Luck
  {
    const int change_luck{GetChangeLuck()};
    if (change_luck != 0)
    {
      if (verbose) { std::clog << "Changing luck by " << change_luck << std::endl; }
      character.ChangeLuck(change_luck);
    }
  }
  //Provisions
  {
    const int change_provisions{GetChangeProvisions()};
    if (change_provisions != 0)
    {
      if (verbose) { std::clog << "Changing provisions by " << change_provisions << std::endl; }
      character.ChangeProvisions(change_provisions);
    }
  }
  //Stamina
  {
    const int change_sta{GetChangeStamina()};
    if (change_sta != 0)
    {
      if (verbose) { std::clog << "Changing stamina by " << change_sta << std::endl; }
      character.ChangeStamina(change_sta);
    }
  }
  for (const auto item: this->GetItemsToAdd())
  {
    if (verbose) { std::clog << "Obtained item " << ToPrettyStr(item) << std::endl; }
    character.AddItem(item);
  }
  for (const auto item: this->GetItemsToRemove())
  {
    if (item == Item::all_gold)
    {
      if (verbose) { std::clog << "Removing all gold" << std::endl; }
      character.ChangeGold(-character.GetGold());
      continue;
    }
    if (item == Item::all_provisions)
    {
      if (verbose) { std::clog << "Removing all provisions" << std::endl; }
      character.ChangeProvisions(-character.GetProvisions());
      continue;
    }
    if (item == Item::random_item_or_one_gold)
    {
      //if (verbose) { std::clog << "Removing random item or 1 gold" << std::endl; }
      const auto items = character.GetItems();
      const int n_items{static_cast<int>(items.size())};
      if (n_items == 0) continue;
      if (n_items == 0 || (std::rand() >> 4) % 2)
      {
        if (character.GetGold() > 0)
        {
          if (verbose) { std::clog << "Removed 1 gold" << std::endl; }
          character.ChangeGold(-1);
        }
        else
        {
          //if (verbose) { std::clog << "Removing random item or 1 gold failed: character has neither" << std::endl; }
        }
      }
      else
      {
        auto iter = items.cbegin();
        const int item_index{(std::rand() >> 4) % n_items};
        for (int j=0; j!=item_index; ++j) { ++iter; }
        if (verbose) { std::clog << "Removed item " << ToPrettyStr(*iter) << std::endl; }
        character.RemoveItem(*iter);
      }
      continue;
    }
    if (item == Item::two_random_items)
    {
      //if (verbose) { std::clog << "Removing two random items" << std::endl; }
      for (int i=0; i!=2; ++i)
      {
        const auto items = character.GetItems();
        const int n_items{static_cast<int>(items.size())};
        if (n_items == 0) continue;
        auto iter = items.cbegin();
        const int item_index{(std::rand() >> 4) % n_items};
        for (int j=0; j!=item_index; ++j) { ++iter; }
        if (verbose) { std::clog << "Lost  " << ToPrettyStr(*iter) << std::endl; }
        character.RemoveItem(*iter);
      }
      continue;
    }
    //if (verbose) { std::clog << "Removing item " << ToStr(item) << std::endl; }
    if (verbose) { std::clog << "Removed item " << ToPrettyStr(item) << std::endl; }
    character.RemoveItem(item);
  }
}

void Consequence::SetNextChapter(const int next_chapter) noexcept
{
  m_next_chapter = next_chapter;
  if (m_next_chapter < 2) { std::cerr << "WARNING: next_chapter incorrect\n"; }
}

Consequence ParseConsequence(std::stringstream &s)
{
  Consequence consequence;
  const std::string what{ReadString(s)};
  if (what == "add")
  {
    const std::string item_name{ReadString(s)};
    if (!IsItem(item_name))
    {
      std::cerr << "Unknown item: " << item_name << std::endl;
      assert(!"Should not get here");
    }
    const Item item{ToItem(item_name)};
    consequence.AddItemToAdd(item);
  }
  else if (what == "arrows" || what == "arrow")
  {
    const std::string value{ReadString(s)};
    if (value == "random[1-6]")
    {
      const int n_arrows{1 + ((std::rand() >> 4) % 6)};
      consequence.SetChangeArrows(n_arrows);
    }
    else if (value == "remove_all")
    {
      consequence.SetChangeArrows(-6);
    }
    else
    {
      assert(!"Should not get here");
    }
  }
  else if (what == "dexterity" || what == "dex")
  {
    const int change_dex{ReadInt(s)};
    consequence.SetChangeDexterity(change_dex);
  }
  else if (what == "gold")
  {
    const int change_gold{ReadInt(s)};
    consequence.SetChangeGold(change_gold);
  }
  else if (what == "luck")
  {
    const int change_luck{ReadInt(s)};
    consequence.SetChangeLuck(change_luck);
  }
  else if (what == "provision" || what == "provisions")
  {
    const int change_provisions{ReadInt(s)};
    consequence.SetChangeProvisions(change_provisions);
  }
  else if (what == "remove")
  {
    const std::string item_name{ReadString(s)};
    if (!IsItem(item_name))
    {
      std::cerr << "Unknown item: " << item_name << std::endl;
      assert(!"Should not get here");
    }
    const Item item{ToItem(item_name)};
    consequence.AddItemToRemove(item);
  }
  else if (what == "stamina" || what == "sta")
  {
    const std::string value{ReadString(s)};
    if (IsInt(value))
    {
      consequence.SetChangeStamina(std::stoi(value));
    }
    else
    {
      assert(value == "random[1-6]");
      consequence.SetChangeStamina(1 + ((std::rand() >> 4) % 6));
    }
  }
  else
  {
    std::cerr << "Unknown what: " << what << std::endl;
    assert(!"Should not get here");
  }
  return consequence;
}
