#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <vector>

#include "condition.h"
#include "item.h"
struct Character;

///An option the player may or may not choose
///Option [text]@ goto [chapter]@
///Option [text]@ if [conditionals] goto [chapter]@
///Option [text]@ then [consequences] goto [chapter]@
///Option [text]@ if [conditionals] then [consequences] goto [chapter]@
struct Option
{
  Option(
    const std::string& text,
    const int next_chapter
  );

  void AddCondition(const Condition& condition);

  bool CanChoose(const Character& character) const;

  void DoChoose(Character& character) const;

  int GetNextChapter() const noexcept { return m_next_chapter; }

  const std::string& GetText() const noexcept { return m_text; }


  private:
  std::vector<Condition> m_conditions;
  int m_next_chapter;
  std::string m_text;
};

#endif // OPTION_H