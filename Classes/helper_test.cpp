#include "helper.h"

#include <memory>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "ai.h"
#include "chapter.h"
#include "dice.h"
#include "game.h"
#include "item.h"

#ifndef NDEBUG
void Helper::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const Helper h;
  const bool verbose{false};
  if (verbose) { std::clog << __func__ << std::endl; }
  if (verbose) { std::clog << "StripFirstChar" << std::endl; }
  {
    const std::vector<std::string> original = { "AB" };
    const std::vector<std::string> result = h.StripFirstChar(original);
    const std::vector<std::string> expected = { "B" };
    assert(result == expected);
  }
  if (verbose) { std::clog << "StripFirstChar" << std::endl; }
  {
    const std::vector<std::string> original = { "AB", "CDEF" };
    const std::vector<std::string> result = h.StripFirstChar(original);
    const std::vector<std::string> expected = { "B", "CDEF" };
    assert(result == expected);
  }
  if (verbose) { std::clog << "IsInt" << std::endl; }
  {
    assert(!h.IsInt("2+fire"));
  }
  const bool test_timer{false};
  if (test_timer)
  {
    if (verbose) { std::clog << "Wait" << std::endl; }
    {
      for (int i=0; i!=10; ++i)
      {
        if (verbose) { std::clog << "Waiting for 100 msecs" << std::endl; }
        h.Wait(0.1);
      }
      for (int i=0; i!=3; ++i)
      {
        if (verbose) { std::clog << "Waiting for 1000 msecs" << std::endl; }
        h.Wait(1.0);
      }
    }
  }
  if (verbose) { std::clog << "StrToLines" << std::endl; }
  {
    assert(h.StrToLines("Hello",5) == "Hello");
    assert(h.StrToLines("Hello World",5) == "Hello\nWorld");
    assert(h.StrToLines("Hi to you",5) == "Hi to\nyou");
    assert(h.StrToLines("Hi to you again",5) == "Hi to\nyou\nagain");
    assert(h.StrToLines("Toolong",4) == "Tool\nong");
    assert(h.StrToLines("[7] Solve game",80) == "[7] Solve game");
    assert(h.StrToLines("[6] Create graph",80) == "[6] Create graph");
    assert(h.StrToLines("01\n23\n45",4) == "01\n23\n45");
    assert(h.StrToLines("The walk to Port Blacksand takes you west some fifty miles",32) == "The walk to Port Blacksand takes\nyou west some fifty miles");
  }
  if (verbose) { std::clog << "Finished " << __func__ << std::endl; }
}
#endif
