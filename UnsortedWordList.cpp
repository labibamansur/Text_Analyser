#include "UnsortedWordList.h"
#include <iostream>


UnsortedWordList::UnsortedWordList(): length(0), first(nullptr), last(nullptr) {;}// default constructor

UnsortedWordList::~UnsortedWordList()// destructor, frees memory space
{
    DeleteAll();
    delete first;
    delete last;
} 

bool UnsortedWordList::IsEmpty() const { return (length == 0); }// returns true if the list is empty, else false

int UnsortedWordList::Length() const { return length; } // returns the number of nodes in the list

Node* UnsortedWordList::Front() const { return first;} // returns the first node in the 

Node* UnsortedWordList::Back() const {return last;}// returns the last node in the list

bool UnsortedWordList::Contains(string word) // returns true if the list contains the word <word>, else wrong
{
    Node* current = first;
    
    while(current != nullptr)
    {
        if(word.compare(current->word) == 0)
        {
            return true;
        }

        current = current->link;
    }

    return false;


}


// returns the pointer to the node with the word <word>
// if there is no node with that word, it returns nullptr
Node* UnsortedWordList::FindWord(string word) 
{
    Node* current = first;
    
    while(current != nullptr)
    {
        if(word.compare(current->word) == 0)
        {
            return current;
        }

        current = current->link;
    }

    return nullptr;


}

// if exactly one word with the highest count exists -- returns that word with the highest count
// if multiple words exist that all have the maximum count -- returns "undefined" (without the quotes)
// if the list is empty -- returns "undefined" (without the quotes)
string UnsortedWordList::MaxWord() const 
{
    int maxCount = 0;
    string maxWord = "undefined";
    Node* current = first;

    if (IsEmpty())
    {
        return maxWord;
    }
    
    while (current != nullptr)
    {
        if ((current->count) > maxCount)
        {
            maxCount = current->count;
            maxWord = current->word;

        }
        else if((current->count) == maxCount)
        {
            maxWord = "undefined";
        }

        current = current->link;

    }

    return maxWord;
}

// returns the highest count
int UnsortedWordList::MaxCount() const
{
    int maxCount = 0;
    Node* current = first;

    if (IsEmpty())
    {
        return maxCount;
    }
    
    while (current != nullptr)
    {
        if ((current->count) > maxCount)
        {
            maxCount = current->count;

        }

        current = current->link;

    }

    return maxCount;

}


// Will print a summary of the list.
// Words are printed in order, as in the list, which might not be alphabetical.
// The format is, e.g., as follows (for a list with words aaa ccc bbb, with counts 2 5 1):
// WordList(
// length=3
// Word(aaa,2)
// Word(ccc,5)
// Word(bbb,1)
// )
void UnsortedWordList::Print() const
{
    cout << "WordList(" << endl;
    cout << "length=" << length << endl;

    Node* current = first;
    while (current != nullptr)
    {
        cout << "Word(" << (current -> word);
        cout << "," << (current -> count) << ")" <<endl;

        current = current->link;

    }

    cout << ")" << endl;  
}

// counts the word <word>, numReadFiles.e., searches the list to find the first node that has word <word>
// If such a node is found -- the counter of that node incremented by 1
// Otherwise -- adds a new node with word <word> at the end of the list
void UnsortedWordList::CountWord(string word)
{
    if (FindWord(word) != nullptr)
    {
        ((FindWord(word)) -> count) += 1;
    }
    else
    {
        Node* newNode = new Node(word,1);

        if(IsEmpty())
        {
           first = newNode;
           last = newNode;
        } 
        else
        {
            (last -> link) = newNode;
            last = newNode;
        }

        length++;

    }

}

// If such a node is not found, creates a new node with word <word> and inserts it at the beginning of the list.
// sets count to 1.
void UnsortedWordList::InsertFirst(string word)
{

   if(IsEmpty())
        {
           Node* newNode = new Node(word,1);
           first = newNode;
           last = newNode;

           length ++;
        } 
   else if (FindWord(word) == nullptr)
    {
        Node* newNode = new Node(word,1);
        newNode->link = first;
        first = newNode;

        length ++;
    }
    else 
    {
        CountWord(word);
    }
   
}

// deletes all nodes in the list, the UnsortedWordList object is NOT deleted/destroyed
void UnsortedWordList::DeleteAll()
{

    Node* current = first;

    while (current != nullptr)
    {
        Node* needDelete = current;
        current = current -> link;

        delete needDelete; 
    }

    length = 0;
    first = nullptr;
    last = nullptr;
}

// deletes node with word <word> and updates other pointers etc
void UnsortedWordList::DeleteWord(string word)
{
    Node* targetWord = FindWord(word);
    if (targetWord != nullptr)
    {
        if (targetWord == first)//first
        {
            first = targetWord ->link;
  
        }
        else if (targetWord == last)//last
        {
            Node* secondlast = first;

            while ((secondlast->link) != last)
            {
                secondlast = secondlast -> link;
            }

            last = secondlast;
            secondlast -> link = nullptr;
        }
        else//middle
        {
           Node* next =  targetWord -> link;
           Node* before = first;

            while ((before->link) != targetWord)
            {
                before = before -> link;
            }

            before -> link = next;

        }

        delete targetWord;
        length --;
    }
     

}
