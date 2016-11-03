#include <fstream>
#include <windows.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <memory>
#include <queue>
#include <vld.h>

class Node {
public:
   int data;
   Node(int d) : data(d){ }
   std::vector<Node *> parents;
   std::vector<Node *> children;
};

class Element {
public:
   int data;
   Element *parent;
   std::unordered_map<int, Element *> children;
   Element(){};
   Element(int d) : data(d) { };
   bool HasAncestor(int goalAncestor);
   void PrintPossibilities();
};

void ConstructTree(Element *head, Node *current, std::queue<Node *> leaves);
Node *FindOrInsert(int data, std::unordered_map<int, Node *> &nodes);
void FreeTree(Element *head);