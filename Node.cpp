#include "Node.h"
#include <iostream>

Node::Node(string newWord): word(newWord), count(1), link(nullptr){;} // constructor with word

Node::Node(string newWord, int newCount): word(newWord), count(newCount), link(nullptr){;}// constructor with word and count




