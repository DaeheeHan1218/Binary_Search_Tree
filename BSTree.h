#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
#include<cmath>

struct Node
{
  int value;
  Node* left;
  Node* right;
  int search_time; //see the problem description

  // Node constructor
  Node(int val = 0, Node* l = nullptr, Node* r = nullptr)
    : value(val), left(l), right(r), search_time(0) {}
};

struct BSTree
{
public:
  BSTree();
  void clear(Node* tree);
  BSTree(const BSTree& other);
  // move constructor
  BSTree(BSTree&& other);
  // copy assignment
  BSTree& operator=(const BSTree& other);
  // move assignment
  BSTree& operator=(BSTree&& other);
  ~BSTree();
  
  const Node* get_root() const { return root; }
  const int get_size() const { return size; }
  Node* insert(int obj);
  Node* search(int obj);
  void set_search_time(Node* tree, int depth);
  void update_search_times();
  float get_average_search_time();
  void inorder_print(std::ostream& out, Node* tree);
  void inorder(std::ostream& out);
  int find_max_search(Node* tree);
  void level_push(std::vector<std::vector<std::string>>& node_queue, Node* tree);
  void print_level_by_level(std::ostream& out);

private:
  int size;
  Node* root;

  int get_total_search_time(Node* node);
  // you can add recursive helper functions to help you
  // this is one is implemented for you:
  void copy_helper(Node*& newNode, const Node* sourceNode);
};

// print a node
std::ostream& operator<<(std::ostream& out, Node& node);

// print a BSTree
std::ostream& operator<<(std::ostream& out, BSTree& tree);

// read in a tree from a file
std::istream& operator>>(std::istream& in, BSTree& tree);


#endif
