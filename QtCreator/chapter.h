#ifndef CHAPTER_H
#define CHAPTER_H

#include <string>
#include <vector>

#include "chaptertype.h"
#include "character.h"
//#include "monster.h"
#include "fightingchapter.h"
#include "optionschapter.h"
#include "consequence.h"

struct Chapter
{
  Chapter(const std::string& filename);

  ///Let the player do this chapter
  void Do(Character& character, const bool auto_play) const;


  ///The text displayed at the end of the chapter
  const std::string& GetByeText() const noexcept { return m_bye_text; }

  const Consequence& GetConsequence() const noexcept { return m_consequence; }

  int GetNextChapter() const noexcept { return m_next_chapter; }

  const FightingChapter& GetFighting() const noexcept { return m_fighting_chapter; }
  FightingChapter& GetFighting() noexcept { return m_fighting_chapter; }

  const OptionsChapter& GetOptions() const noexcept { return m_options_chapter; }
  OptionsChapter& GetOptions() noexcept { return m_options_chapter; }

  std::string GetText() const noexcept { return m_text; }

  ChapterType GetType() const noexcept { return m_chapter_type; }

  private:
  ///The text displayed at the end of the chapter
  std::string m_bye_text;

  Consequence m_consequence;

  ChapterType m_chapter_type;

  FightingChapter m_fighting_chapter;


  int m_next_chapter; //When there is no choice

  OptionsChapter m_options_chapter;


  std::string m_text;
};

std::ostream& operator<<(std::ostream& os, const Chapter& chapter);

#endif // CHAPTER_H