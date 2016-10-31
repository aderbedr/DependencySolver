#include "stdafx.h"
#include "scheduler.h"

int _tmain(int argc, _TCHAR* argv[])
{
   if (argc < 2) {
      std::cout << "No dependency file found.";
      return 1;
   }
   TCHAR *dependencyPath = argv[1];

   std::ifstream myReadFile;
   myReadFile.open(dependencyPath);
   if (myReadFile.is_open()) {
      std::unordered_map<int, std::shared_ptr<Node>> nodes;
      std::stack<std::shared_ptr<Node>> toProcess;
      while (!myReadFile.eof()) {
         int child = INT_MAX;
         int parent = INT_MAX;
         myReadFile >> child;
         myReadFile >> parent;
         if (child == INT_MAX || parent == INT_MAX) {
            std::cout << "Invalid dependency file format. Format should be lines formatted of '<x> <y>', where x depends on y.";
            return 1;
         }
         std::shared_ptr<Node> childNode = findOrInsert(child, nodes);
         std::shared_ptr<Node> parentNode = findOrInsert(parent, nodes);
         childNode->parents.push_back(parentNode);
      }
      myReadFile.close();
      for (auto n : nodes){
         toProcess.push(n.second);
      }
      std::deque<int> resolved;
      while (!toProcess.empty()){
         std::shared_ptr<Node> node = toProcess.top();
         if (std::find(resolved.begin(), resolved.end(), node->data) == resolved.end()){
            resolveDependency(toProcess.top(), resolved);
         }
         toProcess.pop();
      }

      std::deque<int>::iterator it = resolved.end();
      while (it != resolved.begin()){
         std::cout << *--it << std::endl;
      }
   }
   return 0;
}

std::shared_ptr<Node> findOrInsert(int data, std::unordered_map<int, std::shared_ptr<Node>> &nodes){
   std::unordered_map<int, std::shared_ptr<Node>>::const_iterator got = nodes.find(data);
   if (got == nodes.end()){
      std::shared_ptr<Node> parentNode = std::make_unique <Node>(data);
      nodes.insert({ data, parentNode });
      return parentNode;
   }
   else {
      return got->second;
   }
}

void resolveDependency(std::shared_ptr<Node> node, std::deque<int> &resolved){
   for (std::shared_ptr<Node> neighbor : node->parents){
      auto foo = neighbor->data;
      auto bar = std::find(resolved.begin(), resolved.end(), foo);
      auto end = resolved.end();
      if (std::find(resolved.begin(), resolved.end(), neighbor->data) == resolved.end()){
         resolveDependency(neighbor, resolved);
      }
   }
   resolved.push_front(node->data);
}