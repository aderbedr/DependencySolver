#include <fstream>
#include <windows.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <memory>
#include <vld.h>

class Node {
public:
   int data;
   Node(int d) : data(d){ }
   std::vector<std::shared_ptr<Node>> parents;
};

std::shared_ptr<Node> findOrInsert(int data, std::unordered_map<int, std::shared_ptr<Node>> &nodes);
void dep_resolve(std::shared_ptr<Node> node, std::deque<int> &resolved);