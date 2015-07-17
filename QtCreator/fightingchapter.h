#ifndef FIGHTINGCHAPTER_H
#define FIGHTINGCHAPTER_H

#include <vector>

#include "monster.h"

///A chapter in which a fight takes place
struct FightingChapter
{
  FightingChapter();

  void AddMonster(const Monster& monster);

  ///Battle the monsters one by one
  bool DoFightSequentially() const noexcept { return m_fight_sequentially; }

  const std::vector<Monster>& GetMonsters() const noexcept { return m_monsters; }

  ///At which round can the player escape? 1000 if player cannot
  int GetRoundsToEscape() const noexcept { return m_rounds_to_escape; }

  ///If the player escapes, which chapter will he/she go to? -1 if player cannot escape
  int GetEscapeToChapter() const noexcept { return m_escape_chapter; }

  void SetEscapeToChapter(const int escape_to_chapter);

  void SetFightSequentially(const bool fight_sequentially) { m_fight_sequentially = fight_sequentially; }

  void SetRoundsToEscape(const int rounds_to_escape);

  private:

  ///If the player escapes a monster fight, to which chapter?
  int m_escape_chapter;

  ///Is the fight sequentially (one after one) or are the monster fought both at the same time?
  bool m_fight_sequentially;

  std::vector<Monster> m_monsters;
  int m_rounds_to_escape;
};

#endif // FIGHTINGCHAPTER_H