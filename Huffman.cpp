//
//  main.cpp
//  Huffman
//
//  Created by Guo Xin on 15/4/28.
//  Copyright (c) 2015 Guo Xin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <queue>
#include <cctype>
#include <utility>

// struct Node to build binary trees
struct Node
{
    char ch;
    int weight;
    Node* left;
    Node* right;
    std::string bits;
    
    Node (char c, int w, Node *l = NULL, Node *r = NULL, std::string b = ""):
    ch(c), weight(w), left(l), right(r), bits(b) { };
    void addbits(std::string s) {
        bits += s;
    }
};

// overload class function call operator for priority_queue
class CompareNodes {
public:
    bool operator() (const Node *lhs, const Node *rhs) {
        return rhs->weight < lhs->weight;
    }
};


void encode(Node* node) {
    if (node->left != NULL) {
        node->left->addbits(node->bits);
        node->left->addbits("0");
        encode(node->left);
    }
    if (node->right != NULL) {
        node->right->addbits(node->bits);
        node->right->addbits("1");
        encode(node->right);
    }
}

// print huffman coding;

void printCoding(Node* root, std::map<char, std::string>& codetable) {
    if (root == NULL)
        return;
    if (root->ch != '*') {
        codetable[root->ch] = root->bits;
    }
    printCoding(root->left, codetable);
    printCoding(root->right, codetable);
}


// calculate bit counts
int bitsCount(std::map<char, int> &wordCount, std::map<char, std::string> &codetable) {
    int sum = 0;
    for (auto it = wordCount.begin(); it != wordCount.end(); ++it) {
        int len = static_cast<int>(codetable[it->first].length());
        sum += it->second * len;
    }
    return sum;
}



int main() {
	std::cout << "Can't open file, Please try agian!" << std::endl;
	std::cout << "Enter filename: ";
	std::string filename1;
	std::cin >> filename1;
    // read text from file
    std::ifstream input(filename1);
    while (!input) {
        std::cout << "Can't open file, Please try agian!" << std::endl;
        std::cout << "Enter filename: ";
        std::string filename;
        std::cin >> filename;
        input.open(filename.c_str()); // convert std::string to C-Style
    }
    
    // read file char by char and count coresponding frequency
    char temp;
    std::map<char, int> wordCount;
    while (input >> temp) {
        if(isalnum(temp))
            ++wordCount[temp];
    }
    
    // create file to save the results
    std::ofstream output("output.dat");
    
    // create Node based on frequency and put it into priority_queue
    std::cout << "Frequency table of source text: " << std::endl;
    output << "Frequency table of source text: " << std::endl;
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> qnodes;
    for (auto it = wordCount.cbegin(); it != wordCount.cend(); ++it) {
        std::cout << it->first << " : " << it->second << std::endl;
        output << it->first << " : " << it->second << std::endl;
        Node *temp = new Node(it->first, it->second);
        qnodes.push(temp);
    }
    
    // build a binary tree based on priority_queue
    while (qnodes.size() >= 2) {
        // fetch top 2 nodes from priority_queue
        Node *a = qnodes.top();
        qnodes.pop();
        Node *b = qnodes.top();
        qnodes.pop();
        // merge to new node, then add it back to priority_queue
        Node *c = new Node('*', a->weight + b->weight, a, b);
        qnodes.push(c);
    }
    
    Node* root = qnodes.top();
    
    // test priority queue right
    encode(root);
    std::map<char, std::string> codetable;
    std::cout << "Huffman coding for the text: " << std::endl;
    output << "Frequency table of source text: " << std::endl;
    printCoding(root, codetable);
    for (auto it = codetable.begin(); it != codetable.end(); ++it) {
        output << it->first << " : " << it->second << std::endl;
        std::cout << it->first << " : " << it->second << std::endl;
    }
    int sumcounts = bitsCount(wordCount, codetable);
    std::cout << "The total length of coded message in bits is: " << sumcounts << std::endl;
    output << "The total length of coded message in bits is: " << sumcounts << std::endl;
    input.close();
    output.close();
    return 0;
}