// CMSC 341 - Spring 2020 - Project 3

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Scanner.h"

// Balance function for use with BSTs.  This implements the
// height-balance property for AVL trees.  Returns true if
// height-balance property is violated.
bool Scanner::heightImbalance(int leftHeight, int rightHeight, int leftSize, int rightSize) {
  return (leftHeight > rightHeight + 1) || (rightHeight > leftHeight + 1);
}

// SNode constructor.  bounds contains the upper and lower bounds on
// the weights for this BST.
Scanner::SNode::SNode(pair<int, int> bounds) {
  _bounds = bounds;
  _root = new BST(heightImbalance);
  _left = _right = nullptr;
}

Scanner::SNode::~SNode() {

}

// Initialize a Scanner object to process an image with 'lines' lines
// of text, each of which is 'range' characters long.  The ASCII
// characters corresponding to the character indices are passed in
// 'chars'.
Scanner::Scanner(int lines, int range, vector<string> chars) {
  _lines = lines;
  _forest = nullptr;
  _chars = chars;
  int index = 1;
  for(int i = 0; i < lines; i++){
      insertHelp(_forest, index, index+range-1);
      index += range;
  }
}

Scanner::~Scanner() {
    empty(_forest);
}

Scanner::Scanner(const Scanner& rhs) {
  
}

Scanner& Scanner::operator=(const Scanner& rhs) {
  // TBD
  return *this;
}

// Read the data files and insert into the datastructure.  File in
// 'ascii' contains the scrambled character indices; file 'weights'
// contains the corresponding weights.
bool Scanner::loadFiles(string ascii, string weights) {
    std::ifstream asciiFile(ascii);
    if(!asciiFile.is_open()){
        return false;
    }
    string fullLine;
    string letter;
    int index = 0;
    while(getline(asciiFile, fullLine)){
        std::stringstream line(fullLine);
        while(getline(line, letter, ',')) {
            _storage.push_back(letter);
            index++;
        }
    }
    asciiFile.close();
    std::ifstream weightFile(weights);
    if(!weightFile.is_open()){
        return false;
    }
    string fullWeight;
    string weight;
    index = 0;
    while(getline(weightFile, fullWeight)){
        std::stringstream line2(fullWeight);
        while(getline(line2, weight, ',')) {
            insert(stoi(weight), index);
            index++;
        }
    }
    weightFile.close();

  return true;
}

// Insert a node; splay the node that is inserted.
bool Scanner::insert(int weight, int ch) {
    if(weight < 1 || weight > (_lines * ((_forest->_bounds.second-_forest->_bounds.first)+1))){
        return false;
    }
//    inorder();
//    cout << "(" << weight << ")" <<endl;
//    cout << "Before Splay : (" << _forest->_bounds.first << ", " << _forest->_bounds.second << ")" <<endl;
    _forest = splayHelp(_forest, weight);
//    cout << "After Splay : (" << _forest->_bounds.first << ", " << _forest->_bounds.second << ")" <<endl;
    if(_storage[ch] == "1") {
        return _forest->_root->insert(_chars[0], weight);
    }else{
        return _forest->_root->insert(_chars[1], weight);
    }
}

void Scanner::dump() const {
    SNode* temp = _forest;
    dumpHelp(temp);
    cout << endl;
}

void Scanner::inorder() const {
    SNode* temp = _forest;
    inorderHelp(temp);
    cout << endl;
}

void Scanner::insertHelp(SNode* &move, int pair1, int pair2){
    if(move == nullptr){
        if(_forest == nullptr){
            move = new SNode(pair<int, int>(pair1, pair2));
            _forest = move;
        }else {
            move = new SNode(pair<int, int>(pair1, pair2));
        }
    }else if( pair1 < move->_bounds.first){
        insertHelp(move->_left, pair1, pair2);
    }else if(pair2 > move->_bounds.second){
        insertHelp(move->_right, pair1, pair2);
    }
}

Scanner::SNode* Scanner::splayHelp(SNode* &move, int weight) {

    if((weight >= move->_bounds.first && weight <= move->_bounds.second)){
        return move;
    }

    if(move->_bounds.first > weight){
        if(move->_left->_bounds.first > weight){
            move->_left->_left = splayHelp(move->_left->_left, weight);

            SNode* temp = move->_left;
            move->_left = temp->_right;
            temp->_right = move;
            move = temp;
        }else if(move->_left->_bounds.second < weight){
            move->_left->_right = splayHelp(move->_left->_right, weight);

            if(move->_left->_right != nullptr){
                SNode* temp = move->_left->_right;
                move->_left->_right = temp->_left;
                temp->_left = move->_left;
                move->_left = temp;
            }
        }
        if(move->_left != nullptr){
            SNode* temp = move->_left;
            move->_left = temp->_right;
            temp->_right = move;
            return temp;
        }else{
            return move;
        }
    }else{
        if(move->_right->_bounds.first > weight){
            move->_right->_left = splayHelp(move->_right->_left, weight);

            if(move->_right->_left != nullptr) {
                SNode *temp = move->_right->_left;
                move->_right->_left = temp->_right;
                temp->_right = move->_right;
                move->_right = temp;
            }
        } else if (move->_right->_bounds.second < weight){
            move->_right->_right = splayHelp(move->_right->_right, weight);

            SNode* temp = move->_right;
            move->_right = temp->_left;
            temp->_left = move;
            move = temp;
        }
        if(move->_right != nullptr){
            SNode* temp = move->_right;
            move->_right = temp->_left;
            temp->_left = move;
            return temp;
        }else{
            return move;
        }
    }
}

void Scanner::inorderHelp(Scanner::SNode * &print)const {
    if (print != nullptr) {
        cout << "(";
        inorderHelp(print->_left);
        cout << "(" << print->_bounds.first << ", " << print->_bounds.second << ")";
        inorderHelp(print->_right);
        cout << ")";
    }
}

void Scanner::dumpHelp(Scanner::SNode *&print) const {
    if (print != nullptr) {
        dumpHelp(print->_left);
        print->_root->dump();
        dumpHelp(print->_right);
    }
}

void Scanner::empty(Scanner::SNode* move){
    if( move != NULL )
    {
        empty( move->_left );
        empty( move->_right );
        move->_root->~BST();
        delete move;
        move = nullptr;
    }
}

//int main(){
//    vector<string> chars;
//    Scanner scan(15,34, chars);
//    cout << scan.loadFiles("scrambled.txt", "weights.txt");
//    scan.dump();
//    return 0;
//}


