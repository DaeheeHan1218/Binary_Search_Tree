#include "BSTree.h"

#include <iostream>

using namespace std;
int height;
///////////////////////////////////
// Already Implemented Functions //
///////////////////////////////////

// These functions are already implemented for you. Scroll below to
// see the functions that you have to implement 


// constructors
BSTree::BSTree() : size(0), root(nullptr) {}

// input / output operators
ostream& operator<<(ostream& out, BSTree& tree)
{
    tree.print_level_by_level(out);
    return out;
}

ostream& operator<<(ostream& out, Node& node)
{
    return out << node.value << "[" << node.search_time << "]";
}

istream& operator>>(istream& in, BSTree& tree)
{
    /*
      take input from the in stream, and build your tree
      input will look like
      4 
      2 
      6 
      1 
      3 
      5 
      7
    */
    int next;
    while(in >> next) {
        tree.insert(next);
    }
    return in;
}

// Example recursive function
// If you try to use it without care, you will get a memory leak.
void BSTree::copy_helper(Node*& newNode, const Node* sourceNode) {
    if(sourceNode){
		newNode = new Node();
		newNode->value = sourceNode->value;
		newNode->search_time = sourceNode->search_time;
		if (sourceNode->left != nullptr){
			copy_helper(newNode->left, sourceNode->left);
		}
		if(sourceNode->right != nullptr){
			copy_helper(newNode->right, sourceNode->right);
		}
	}
}

// recursive function
int BSTree::get_total_search_time(Node* node)
{
  if (node != nullptr) {
    return node->search_time + get_total_search_time(node->left) + get_total_search_time(node->right);
  }
  return 0;
}

// implemented
float BSTree::get_average_search_time()
{
  int total_search_time = get_total_search_time(root);
  if(total_search_time == 0)
    return -1;
	
  return ((float)total_search_time)/size;
}


///////////////////////////////////
//     Functions to Implement    //
///////////////////////////////////

// These are the functions you should implement
// Feel free to call the functions above or create new helper functions

void BSTree::clear(Node* tree){
	if(tree != nullptr){//checks if Node is not empty
		clear(tree->left);
		clear(tree->right);
		tree->value = 0;
		tree->search_time = 0;
		tree->left = nullptr;
		tree->right = nullptr;
		delete tree;
	}
}

// copy constructor
BSTree::BSTree(const BSTree& other): size(other.size){
	if(other.root != nullptr){
		copy_helper(root, other.root);
	}
	else{
		root = nullptr;
	}
}

// move constructor
BSTree::BSTree(BSTree&& other): size(other.size), root(other.root){
	other.size = 0;
	other.root = nullptr;
}

//copy assignment
BSTree& BSTree::operator=(const BSTree& other){
	if(this != &other){
		clear(root);
		if(other.root != nullptr){
			copy_helper(root, other.root);
		}
		else{
			root = nullptr;
		}
		size = other.size;
	}
	return *this;
}

// move assignment
BSTree& BSTree::operator=(BSTree&& other){
	if(this != &other){
		clear(root);
		size = other.size;
		root = other.root;
		other.root = nullptr;
		other.size = 0;
	}
	return *this;
}

// destructor
BSTree::~BSTree(){
	clear(root);
	size = 0;
}

Node* BSTree::insert(int obj)
{
    /* insert a node into the tree
    first find where the node should go
    then modify pointers to connect your new node */
	Node* ins = new Node();
	ins->value = obj;
	if(root != nullptr){
		Node* temp = root;
		while(temp != nullptr){
			if(temp->value > obj){
				if(temp->left != nullptr){
					temp = temp->left;
				}
				else{
					ins->search_time = temp->search_time + 1;
					temp->left = ins;
					size++;
					break;
				}
			}
			else{
				if(temp->right != nullptr){
					temp = temp->right;
				}
				else{
					ins->search_time = temp->search_time + 1;
					temp->right = ins;
					size++;
					break;
				}
			}
		}
	}
	else{
		ins->search_time = 1;
		root = ins;
		size++;
	}
	return ins;
}

Node* BSTree::search(int obj)
{
    /* recursively search down the tree to find the node that contains obj
    if you don't find anything return nullptr */
	Node* tree = root;
	while(tree){
		if(tree->value == obj){
			return tree;
		}
		if(tree->value > obj){
			tree = tree->left;
		}
		else if(tree->value < obj){
			tree = tree->right;
		}
	}
	return tree;
}

void BSTree::set_search_time(Node* tree, int depth){
	if(tree){
		tree->search_time = depth + 1;
		set_search_time(tree->left, depth + 1);
		set_search_time(tree->right, depth + 1);
	}
}

void BSTree::update_search_times()
{
    /* do a BFS or DFS of your tree and update the search times of all nodes at once
    The root has a search time of 1, and each child is 1 more than its parent */
	set_search_time(root, 0);
}

void BSTree::inorder_print(ostream& out, Node* tree){
	if(tree){
		inorder_print(out, tree->left);
		out << *tree << " ";
		inorder_print(out, tree->right);
	}
}

void BSTree::inorder(ostream& out)
{
    /* print your nodes in infix order
    If our tree looks like this:

       4
     2   6
    1 3 5 7

    It should output:
    1[3] 2[2] 3[3] 4[1] 5[3] 6[2] 7[3]
    You can use the << operator to print the nodes in the format shown */
	inorder_print(out, root);
}

int BSTree::find_max_search(Node* tree){
    if(tree->left == nullptr && tree->right == nullptr){
        return tree->search_time;
    }
    if(tree->left == nullptr){
        return find_max_search(tree->right);
    }
    else if(tree->right == nullptr){
        return find_max_search(tree->left);
    }
    else{
        return max(find_max_search(tree->left), find_max_search(tree->right));
    }
}

void BSTree::level_push(vector<vector<string>>& level, Node* tree){
	if(tree != nullptr){
		string node = to_string(tree->value) + "[" + to_string(tree->search_time) + "]";
		level[tree->search_time - 1].push_back(node);
		if(tree->left != nullptr){
			level_push(level, tree->left);
		}
		else{
			for(int i = 0; i < (height - tree->search_time + 1); i++){
			    for(int j = 0; j < pow(2, i); j++){
			        level[tree->search_time + i].push_back("X");
			    }
			}
		}
		if(tree->right != nullptr){
			level_push(level, tree->right);
		}
		else{
			for(int i = 0; i < (height - tree->search_time + 1); i++){
			    for(int j = 0; j < pow(2, i); j++){
			        level[tree->search_time + i].push_back("X");
			    }
			}
		}
	}
}

void BSTree::print_level_by_level(ostream& out)
{
    /* Print the tree using a BFS so that each level contains the values for a level of the tree.
    Use X to mark empty positions. 
    
      if our tree looks like this:

       4
     2   6
    1   5 7
           9

    it should output:

    4[1]
    2[2] 6[2]
    1[3] X 5[3] 7[3]
    X X X X X X X 9[4]

    it might be helpful to do this part with the std::queue data structure.
    Hint: the Nth level contains 2^(N-1) nodes (with a value or with an X). Watch out
    for nodes like the left child of 6 above, and print the descendents of an empty
    node as also empty
    You can use the << operator to print nodes in the format shown */
    if(root != nullptr){
        height = find_max_search(root) - 1;
        vector<vector<string>> level(height + 1);
        level_push(level, root);
        for(int i = 0; i < level.size(); i++){
            for(int j = 0; j < level[i].size(); j++){
                out << level[i][j] << " ";
            }
            out << endl;
        }
    }
}
