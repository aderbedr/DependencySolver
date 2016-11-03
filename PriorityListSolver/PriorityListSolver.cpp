#include "stdafx.h"
#include "scheduler.h"

int _tmain(int argc, _TCHAR*argv[])
{
   if (argc < 2) {
      std::cout << "No dependency file found.";
      return 1;
   }
   TCHAR *dependencyPath = argv[1];

   std::ifstream myReadFile;
   myReadFile.open(dependencyPath);
   if (myReadFile.is_open()) {
      // Construct the node map
      std::unordered_map<int, Node *> nodes;
      while (!myReadFile.eof()) {
         int child = INT_MAX;
         int parent = INT_MAX;
         myReadFile >> child;
         myReadFile >> parent;
         if (child == INT_MAX || parent == INT_MAX) {
            std::cout << "Invalid dependency file format. Format should be lines formatted of '<x> <y>', where x depends on y.";
            return 1;
         }
         Node *childNode = FindOrInsert(child, nodes);
         Node *parentNode = FindOrInsert(parent, nodes);
         childNode->parents.push_back(parentNode);
         parentNode->children.push_back(childNode);
      }
      myReadFile.close();

      Node *current = new Node(0);
      for (std::pair<int, Node *> n : nodes){
         if (n.second->parents.empty()){
            current->children.push_back(n.second);
            n.second->parents.push_back(current);
         }
      }

      Element *head = new Element();
      std::queue<Node *> leaves;
      ConstructTree(head, current, leaves);
      head->PrintPossibilities();

      FreeTree(head);
      for (std::pair<int, Node *> n : nodes){
         delete n.second;
      }
      delete current;
   }
   return 0;
}

Node *FindOrInsert(int data, std::unordered_map<int, Node *> &nodes){
   std::unordered_map<int, Node *>::const_iterator got = nodes.find(data);
   if (got == nodes.end()){
      Node *parentNode = new Node(data);
      nodes.insert({ data, parentNode });
      return parentNode;
   }
   else {
      return got->second;
   }
}


void ConstructTree(Element *head, Node *current, std::queue<Node *> leaves) {
   for (Node *child : current->children){
      for (Node *parent : child->parents){
         if (parent->data != 0 && !head->HasAncestor(parent->data)){
            break;
         }
         leaves.push(child);
      }
   }

   while (!leaves.empty()){
      Node *leaf = leaves.front();
      leaves.pop();
      if (head->children.find(leaf->data) != head->children.end())
         continue;
      if (head->HasAncestor(leaf->data) || leaf->data == head->data)
         continue;
      Element *leafElement = new Element(leaf->data);
      head->children.insert({ leaf->data, leafElement });
      leafElement->parent = head;
      ConstructTree(leafElement, leaf, leaves);
      leaves.push(leaf);
   }
}

void FreeTree(Element *head){
   for (std::pair<int, Element *> child : head->children){
      FreeTree(child.second);
   }
   delete head;
}

void Element::PrintPossibilities(){
   for (std::pair<int, Element *> child : this->children){
      child.second->PrintPossibilities();
   }

   if (this->children.empty()){
      Element *current = this;
      while (current->parent != nullptr){
         std::cout << current->data;
         current = current->parent;
         if (current->parent != nullptr)
            std::cout << "->";
      }
      std::cout << std::endl;
   }
}

bool Element::HasAncestor(int goalAncestor){
   if (this->data == goalAncestor)
      return true;
   else if (this->parent == nullptr)
      return false;
   return this->parent->HasAncestor(goalAncestor);
}