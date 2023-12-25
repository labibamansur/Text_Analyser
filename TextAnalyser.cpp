#include "TextAnalyser.h"
#include <iostream>
#include <fstream>
using namespace std;

// at the beginning prints a diagnostic message of the form
// TextAnalyser::ReadFile, filename='<name of the file>'
//
// reads in a file and puts the words in listA or listB
//
// alternates readIntoA between true and false to control which list is used
void TextAnalyser::ReadFile(string filename) {
cout << "TextAnalyser::ReadFile, filename='" << filename << "'." << endl;
ifstream file;
file.open(filename);
if (!file.is_open()) {
cout << "unable to open file with filename='" << filename << "'." << endl;
return;
}
string word;

while (file >> word) {

    if (readIntoA)
    {
        listA.CountWord(word);
    }
    else
    {
        listB.CountWord(word);
    }

}

readIntoA = !readIntoA;
}

// determines intersection of A and B, i.e.
// it puts all words that appear in listA *and* listB in listC
// for each word it takes the minimum of word counts in A and B for C
void TextAnalyser::Intersection()
{
    listC.DeleteAll();//need to fresh listC
    if ((!listA.IsEmpty()) && (!listB.IsEmpty()))
    {
        Node* elementinA = listA.Front();
        
        while (elementinA != nullptr)
        {
            Node* elementinB = listB.FindWord(elementinA->word);
            if (elementinB != nullptr)
            {
                int countA = elementinA -> count;
                int countB = elementinB -> count;
                Node* elementtoC = (countA<countB)?elementinA:elementinB;
                listC.CountWord(elementtoC -> word);
                (listC.Back()) -> count = elementtoC -> count;

            }

            elementinA = elementinA -> link;
 
        }
        
    }

}

// determines union of A and B, i.e.
// it puts all words that appear in listA *or* listB in listC
// for each word it takes the sum of word counts in A and B (not the maximum!) for C
// i.e., it has the same result as reading both files that were source for A and B
void TextAnalyser::Union()
{
    listC.DeleteAll();//need to fresh listC
    Node* elementinA = listA.Front();
    while (elementinA != nullptr)
    {
        listC.CountWord(elementinA -> word);
        (listC.Back()) -> count = elementinA -> count;

        elementinA = elementinA -> link;

    }

    Node* elementinB = listB.Front();
    while (elementinB != nullptr)
    {
        Node* elementinC = listC.FindWord(elementinB->word);
        if (elementinC != nullptr)
        {
           elementinC -> count = (elementinC -> count) + (elementinB -> count);
        }
        else
        {
           listC.CountWord(elementinB -> word);
           (listC.Back()) -> count = elementinB -> count;
        }
        
        elementinB = elementinB -> link;
    }
    


    

}