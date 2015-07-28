#include "dicegamechapter.h"

#include "chapter.h"
#include "character.h"
#include "dice.h"
#include "helper.h"

DiceGameChapter::DiceGameChapter(Chapter& chapter)
  : m_chapter{chapter}
{

}

void DiceGameChapter::Do(Character& character) const
{
  if (character.GetGold() < 2)
  {
    m_chapter.m_signal_show_text("You cannot afford to play this game.\n");
    return;
  }

  m_chapter.m_signal_show_text("Do you want to play?\n");
  {
    const auto options = CreateYesNoOptions();
    const auto chosen = *m_chapter.m_signal_request_option(options);
    if (chosen.GetConsequence().GetType() == ConsequenceType::no) { return; }
  }

  const int n_rounds{4};
  for (int round = 0; round != 4; ++round)
  {
    m_chapter.m_signal_show_text("Round #" + std::to_string(round + 1) + "/" + std::to_string(n_rounds) + "\n");
    //You
    const int dice_you{Dice::Get()->Throw()};
    const int dice_1{Dice::Get()->Throw()};
    const int dice_2{Dice::Get()->Throw()};
    const int dice_3{Dice::Get()->Throw()};
    m_chapter.m_signal_show_text("You throw: " + std::to_string(dice_you) + "\n");
    m_chapter.m_signal_wait();
    m_chapter.m_signal_show_text("Dwarf 1 throws: " + std::to_string(dice_1) + "\n");
    m_chapter.m_signal_wait();
    m_chapter.m_signal_show_text("Dwarf 2 throws: " + std::to_string(dice_2) + "\n");
    m_chapter.m_signal_wait();
    m_chapter.m_signal_show_text("Dwarf 3 throws: " + std::to_string(dice_3) + "\n");
    m_chapter.m_signal_wait();
    if (dice_you > dice_1 && dice_you > dice_2 && dice_you > dice_3)
    {
      m_chapter.m_signal_show_text("You won! You collect your 6 gold pieces from the three dwarves.\n");
      character.ChangeGold(6);
      m_chapter.m_signal_wait();
    }
    else if (dice_you < dice_1 || dice_you < dice_2 || dice_you < dice_3)
    {
      m_chapter.m_signal_show_text("You Lost! You lose 2 gold pieces to the three dwarves.\n");
      character.ChangeGold(-2);
      m_chapter.m_signal_wait();
    }
    else
    {
      m_chapter.m_signal_show_text("A draw. You keep your gold\n");
      m_chapter.m_signal_wait();
    }

    if (character.GetGold() < 2)
    {
      m_chapter.m_signal_show_text("You cannot afford to play another round.\n");
      break;
    }

    if (round == 3) break;

    //Play again?
    {
      m_chapter.m_signal_show_text("Do you want to play another round?\n");
      const auto options = CreateYesNoOptions();
      const auto chosen = *m_chapter.m_signal_request_option(options);
      if (chosen.GetConsequence().GetType() == ConsequenceType::no) { return; }
    }
  }
}