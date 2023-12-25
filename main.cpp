/* CE2 Assignment 3 Testing File
 * Authors: Sean McGoff, Darragh Elliott
 * To use, make this your main entry point for a compiled executable
 */
#include "TextAnalyser.h"
#include "UnsortedWordList.h"
#include <iostream>
#include <sstream>
#include <vector>

class testCase {
private:
  void (*tf)();   // Test Function (test1, test2, etc.)
  std::string eo; // Expected Output
public:
  // Constructor
  testCase(void (*test_func)(), std::string expected_output)
      : tf(test_func), eo(expected_output){};
  // Get Expected Output
  std::string getExpectedOutput() { return this->eo; };
  // Stream Buffer Madness (NOT THREAD SAFE AT ALL)
  std::string captureOutput() {
    std::stringstream b;
    std::streambuf *old = std::cout.rdbuf(b.rdbuf());
    tf();
    std::string o = b.str();
    std::cout.rdbuf(old);
    return o;
  }
  // The Actual Test Function
  bool test() { return captureOutput() == this->eo; }
};
// test cases one two and three are the ones provided.
void test1() {
  UnsortedWordList list;
  list.CountWord("Ultimate");
  list.CountWord("Question");
  list.CountWord("to");
  list.CountWord("Life");
  list.CountWord("Universe");
  list.CountWord("and");
  list.CountWord("Everything");
  list.CountWord("Question");
  list.Print();
}

void test2() {
  TextAnalyser textAnalyser;
  UnsortedWordList list;
  textAnalyser.ReadFile("hitchhiker.txt");
  list = textAnalyser.listA;
  list.Print();
  std::cout << "Does the list contain 'the'? " << list.Contains("the")
            << std::endl;
  std::cout << "Does the list contain 'them'? " << list.Contains("them")
            << std::endl;
}

void test3() {
  TextAnalyser textAnalyser;
  textAnalyser.ReadFile("hitchhiker.txt");
  textAnalyser.ReadFile("rings.txt");
  textAnalyser.Intersection();
  textAnalyser.listC.Print();
  textAnalyser.Union();
  textAnalyser.listC.Print();
}
void test4() { // Test all functions when there is nothing in the list
  TextAnalyser textAnalyser;
  std::cout << "Is the list Empty? " << textAnalyser.listA.IsEmpty()
            << std::endl;
  std::cout << "What is its length? " << textAnalyser.listA.Length()
            << std::endl;
  std::cout << "Is there a front node? "
            << ((textAnalyser.listA.Front() == nullptr) ? "Yes" : "No")
            << std::endl;
  std::cout << "Is there an end node? "
            << ((textAnalyser.listA.Back() == nullptr) ? "Yes" : "No")
            << std::endl;
  std::cout << "Does it contain \"Test\"? "
            << textAnalyser.listA.Contains("Test") << std::endl;
  std::cout << "Does it find \"Test\"? "
            << ((textAnalyser.listA.FindWord("Test") == nullptr) ? "Yes" : "No")
            << std::endl;
  std::cout << "What is the MaxWord? " << textAnalyser.listA.MaxWord()
            << std::endl;
  std::cout << "What is the MaxCount? " << textAnalyser.listA.MaxCount()
            << std::endl;
  textAnalyser.listA.Print();
  textAnalyser.listA.DeleteAll();
  textAnalyser.listA.DeleteWord("Null");
  textAnalyser.listA.CountWord("One");
  textAnalyser.listA.DeleteAll();
  textAnalyser.listA.InsertFirst("One");
  textAnalyser.listA.DeleteAll();
  textAnalyser.listA.Print();
}

void test5() {
  TextAnalyser textAnalyser;
  textAnalyser.ReadFile("rings.txt");
  textAnalyser.listA.Print();
  textAnalyser.listA.DeleteWord(
      "Engineering"); // Tests to see if it handles non existent word
  textAnalyser.listA.DeleteWord("Ring"); // See if it deletes existing word
  textAnalyser.listA.Print();
}
void test6() {
  TextAnalyser textAnalyser;
  textAnalyser.ReadFile("rings.txt");
  textAnalyser.listA.Print();
  std::cout << "Does it contain \"Rings\"? "
            << textAnalyser.listA.Contains("Rings") << std::endl;
  std::cout << "MaxWord is \"" << textAnalyser.listA.MaxWord() << "\"."
            << std::endl;
  std::cout << "It apears " << textAnalyser.listA.MaxCount() << " times."
            << std::endl;
}
void test7() {
  TextAnalyser textAnalyser;
  textAnalyser.ReadFile("rings.txt");
  textAnalyser.listA.Print();
  textAnalyser.listA.InsertFirst("Ring");
  textAnalyser.listA.InsertFirst("FirstWord");
  textAnalyser.listA.Print();
}
void test8() {
  TextAnalyser textAnalyser;
  std::cout << "List A is empty: " << textAnalyser.listA.IsEmpty() << std::endl;
  textAnalyser.ReadFile("rings.txt");
  textAnalyser.listA.Print();
  std::cout << "List A is empty: " << textAnalyser.listA.IsEmpty() << std::endl;
  std::cout << "Calling Delete All" << std::endl;
  textAnalyser.listA.DeleteAll();
  std::cout << "List A is empty: " << textAnalyser.listA.IsEmpty() << std::endl;
}

int main() {
  vector<testCase> tests;
  tests.push_back(testCase{
      &test1, "WordList(\n"s + "length=7\n"s + "Word(Ultimate,1)\n"s +
                  "Word(Question,2)\n"s + "Word(to,1)\n"s + "Word(Life,1)\n"s +
                  "Word(Universe,1)\n"s + "Word(and,1)\n"s +
                  "Word(Everything,1)\n"s + ")\n"s});
  tests.push_back(testCase{
      &test2, "TextAnalyser::ReadFile, filename='hitchhiker.txt'.\n"s +
                  "WordList(\n"s + "length=25\n"s + "Word(The,2)\n"s +
                  "Word(Hitchhiker's,1)\n"s + "Word(Guide,1)\n"s +
                  "Word(to,1)\n"s + "Word(the,5)\n"s + "Word(Galaxy,1)\n"s +
                  "Word(Restaurant,1)\n"s + "Word(at,1)\n"s + "Word(End,1)\n"s +
                  "Word(of,1)\n"s + "Word(Universe,2)\n"s + "Word(Life,,1)\n"s +
                  "Word(and,2)\n"s + "Word(Everything,1)\n"s + "Word(So,1)\n"s +
                  "Word(Long,,1)\n"s + "Word(Thanks,1)\n"s + "Word(for,1)\n"s +
                  "Word(All,1)\n"s + "Word(Fish,1)\n"s + "Word(Mostly,1)\n"s +
                  "Word(Harmless,1)\n"s + "Word(And,1)\n"s +
                  "Word(Another,1)\n"s + "Word(Thing,1)\n"s + ")\n"s +
                  "Does the list contain 'the'? 1\n"s +
                  "Does the list contain 'them'? 0\n"s});
  tests.push_back(testCase{
      &test3,
      "TextAnalyser::ReadFile, filename='hitchhiker.txt'.\n"s +
          "TextAnalyser::ReadFile, filename='rings.txt'.\n"s + "WordList(\n"s +
          "length=3\n"s + "Word(The,2)\n"s + "Word(the,2)\n"s +
          "Word(of,1)\n"s + ")\n"s + "WordList(\n"s + "length=31\n"s +
          "Word(The,5)\n"s + "Word(Hitchhiker's,1)\n"s + "Word(Guide,1)\n"s +
          "Word(to,1)\n"s + "Word(the,7)\n"s + "Word(Galaxy,1)\n"s +
          "Word(Restaurant,1)\n"s + "Word(at,1)\n"s + "Word(End,1)\n"s +
          "Word(of,3)\n"s + "Word(Universe,2)\n"s + "Word(Life,,1)\n"s +
          "Word(and,2)\n"s + "Word(Everything,1)\n"s + "Word(So,1)\n"s +
          "Word(Long,,1)\n"s + "Word(Thanks,1)\n"s + "Word(for,1)\n"s +
          "Word(All,1)\n"s + "Word(Fish,1)\n"s + "Word(Mostly,1)\n"s +
          "Word(Harmless,1)\n"s + "Word(And,1)\n"s + "Word(Another,1)\n"s +
          "Word(Thing,1)\n"s + "Word(Fellowship,1)\n"s + "Word(Ring,1)\n"s +
          "Word(Two,1)\n"s + "Word(Towers,1)\n"s + "Word(Return,1)\n"s +
          "Word(King,1)\n"s + ")\n"s});
  tests.push_back(testCase{
      &test4,
      "Is the list Empty? 1\n"s + "What is its length? 0\n"s +
          "Is there a front node? Yes\n"s + "Is there an end node? Yes\n"s +
          "Does it contain \"Test\"? 0\n"s + "Does it find \"Test\"? Yes\n"s +
          "What is the MaxWord? undefined\n"s + "What is the MaxCount? 0\n"s +
          "WordList(\n"s + "length=0\n"s + ")\n"s + "WordList(\n"s +
          "length=0\n"s + ")\n"s});
  tests.push_back(testCase{
      &test5, "TextAnalyser::ReadFile, filename='rings.txt'.\n"s +
                  "WordList(\n"s + "length=9\n"s + "Word(The,3)\n"s +
                  "Word(Fellowship,1)\n"s + "Word(of,2)\n"s + "Word(the,2)\n"s +
                  "Word(Ring,1)\n"s + "Word(Two,1)\n"s + "Word(Towers,1)\n"s +
                  "Word(Return,1)\n"s + "Word(King,1)\n"s + ")\n"s +
                  "WordList(\n"s + "length=8\n"s + "Word(The,3)\n"s +
                  "Word(Fellowship,1)\n"s + "Word(of,2)\n"s + "Word(the,2)\n"s +
                  "Word(Two,1)\n"s + "Word(Towers,1)\n"s + "Word(Return,1)\n"s +
                  "Word(King,1)\n"s + ")\n"s});
  tests.push_back(testCase{
      &test6, "TextAnalyser::ReadFile, filename='rings.txt'.\n"s +
                  "WordList(\n"s + "length=9\n"s + "Word(The,3)\n"s +
                  "Word(Fellowship,1)\n"s + "Word(of,2)\n"s + "Word(the,2)\n"s +
                  "Word(Ring,1)\n"s + "Word(Two,1)\n"s + "Word(Towers,1)\n"s +
                  "Word(Return,1)\n"s + "Word(King,1)\n"s + ")\n"s +
                  "Does it contain \"Rings\"? 0\n"s + "MaxWord is \"The\".\n"s +
                  "It apears 3 times.\n"s});
  tests.push_back(testCase{
      &test7, "TextAnalyser::ReadFile, filename='rings.txt'.\n"s +
                  "WordList(\n"s + "length=9\n"s + "Word(The,3)\n"s +
                  "Word(Fellowship,1)\n"s + "Word(of,2)\n"s + "Word(the,2)\n"s +
                  "Word(Ring,1)\n"s + "Word(Two,1)\n"s + "Word(Towers,1)\n"s +
                  "Word(Return,1)\n"s + "Word(King,1)\n"s + ")\n"s +
                  "WordList(\n"s + "length=10\n"s + "Word(FirstWord,1)\n"s +
                  "Word(The,3)\n"s + "Word(Fellowship,1)\n"s + "Word(of,2)\n"s +
                  "Word(the,2)\n"s + "Word(Ring,2)\n"s + "Word(Two,1)\n"s +
                  "Word(Towers,1)\n"s + "Word(Return,1)\n"s +
                  "Word(King,1)\n"s + ")\n"s});
  tests.push_back(testCase{
      &test8, "List A is empty: 1\n"s +
                  "TextAnalyser::ReadFile, filename='rings.txt'.\n"s +
                  "WordList(\n"s + "length=9\n"s + "Word(The,3)\n"s +
                  "Word(Fellowship,1)\n"s + "Word(of,2)\n"s + "Word(the,2)\n"s +
                  "Word(Ring,1)\n"s + "Word(Two,1)\n"s + "Word(Towers,1)\n"s +
                  "Word(Return,1)\n"s + "Word(King,1)\n"s + ")\n"s +
                  "List A is empty: 0\n"s + "Calling Delete All\n"s +
                  "List A is empty: 1\n"s});
  bool didCasePass;
  for (int i = 0; i < tests.size(); ++i) {
    std::cout << "Test Case " << i + 1 << ":\n-------------\n";
    didCasePass = tests[i].test();
    std::cout << "Test Case " << i + 1 << " "
              << (didCasePass ? "Passed!" : "Failed") << "\n";
    if (!didCasePass) {
      std::cout << "Expected Output:\n" << tests[i].getExpectedOutput() << "\n";
      std::cout << "Student Output:\n" << tests[i].captureOutput() << "\n";
    }
    std::cout << "\n\n";
  }
}
