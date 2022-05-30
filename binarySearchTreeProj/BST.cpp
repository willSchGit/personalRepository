// CMSC 341 - Spring 2020 - Project 3

#include "BST.h"

// Constructor for the BNode nested class
BST::BNode::BNode(string ch, int rank, int height, int size) {
  _data = ch;
  _key = rank;
  _height = height;
  _size = size;
  _right = nullptr;
  _left = nullptr;
}

// Constructor for the BST class; requires a balance function
BST::BST(balfn_t imbalanced) {
  _root = nullptr;
  _imbalanced = imbalanced;
}

BST::~BST(){
    empty(_root);
}

BST::BST(const BST& rhs) {
    this->_root = nullptr;
    _imbalanced = rhs._imbalanced;
    BNode* temp = rhs._root;
    this->_root = bstCopyHelp(this->_root, temp);
}

BST& BST::operator=(const BST& rhs){
    this->_root = nullptr;
    BNode* temp = rhs._root;
  if(this->_root != temp){
      this->~BST();
      this->_root = bstCopyHelp(this->_root, temp);
      _imbalanced = rhs._imbalanced;
  }
  return *this;
}

// Insert a (character, rank) pair
bool BST::insert(string ch,int rank) {
    bool placed;
    placed =  insertHelp(_root, ch, rank, 0);
    return placed;
}

int BST::size() const {
  return ( _root == nullptr ? 0 : _root->_size-1 );
}

int BST::height() const {
  return ( _root == nullptr ? -1 : _root->_height );
}

void BST::dump(bool verbose) const {
    dumpHelp(_root, verbose);
    cout << endl;
}

void BST::dumpHelp(BST::BNode *print, bool verbose) const {
    if(!verbose) {
        if (print != nullptr) {
            dumpHelp(print->_left, verbose);
            cout << print->_data;
            dumpHelp(print->_right, verbose);
        }
    }else{
        if (print != nullptr) {
            cout << "(";
            dumpHelp(print->_left, verbose);
            cout << print->_data << " Height: " << print->_height << " Size: " << print->_size;
            dumpHelp(print->_right, verbose);
            cout << ")";
        }
    }
}

bool BST::insertHelp(BST::BNode * &move,const string &ch,const int &rank, const int &height) {
    if (move == nullptr) {
        move = new BNode(ch, rank);
        return true;
    }else if( move->_key == rank) {
        return false;
    } else if (rank < move->_key){
        insertHelp(move->_left, ch, rank, height);
        move->_size = sizeHelp(move);
        move->_height = heightHelp(move);
        if(move->_left == nullptr){
            if(_imbalanced(-1,move->_right->_height,-1,move->_right->_size)){
                _arr = new BNode*[move->_size];
                BNode* temp = balance(move);
                if(move != temp) {
                    empty(move);
                }
                move = temp;
            }
        }else if(move->_right == nullptr){
            if(_imbalanced(move->_left->_height,-1,move->_left->_size,-1)){
                _arr = new BNode*[move->_size];
                BNode* temp = balance(move);
                empty(move);
                move = temp;
            }
        }else{
            if(_imbalanced(move->_left->_height,move->_right->_height,move->_left->_size,move->_right->_size)){
                _arr = new BNode*[move->_size];
                BNode* temp = balance(move);
                empty(move);
                move = temp;
            }
        }
    } else if (rank > move->_key){
        insertHelp(move->_right, ch, rank, height);
        move->_size = sizeHelp(move);
        move->_height = heightHelp(move);
        if(move->_left == nullptr){
            if(_imbalanced(-1,move->_right->_height,-1,move->_right->_size)){
                _arr = new BNode*[move->_size];
                BNode* temp = balance(move);
                empty(move);
                move = temp;
            }
        }else if(move->_right == nullptr){
            if(_imbalanced(move->_left->_height,-1,move->_left->_size,-1)){
                _arr = new BNode*[move->_size];
                BNode* temp = balance(move);
                empty(move);
                move = temp;
            }
        }else{
            if(_imbalanced(move->_left->_height,move->_right->_height,move->_left->_size,move->_right->_size)){
                _arr = new BNode*[move->_size];
                BNode* temp = balance(move);
                empty(move);
                move = temp;
            }
        }
    }
    return true;
}

int BST::sizeHelp(BST::BNode * &move) {
    if(move == nullptr){
        return 0;
    }else{
        return sizeHelp(move->_left) + sizeHelp(move->_right) + 1;
    }
}


int BST::heightHelp(BST::BNode * &move) const{
    if (move == nullptr){
        return -1;
    }
    int nodesL = heightHelp(move->_left);
    int nodesR = heightHelp(move->_right);
    return ( nodesR > nodesL ? nodesR+1 : nodesL+1 );
}

void BST::empty(BST::BNode * &move){
    if( move != NULL )
    {
        empty( move->_left );
        empty( move->_right );
        delete move;
        move = nullptr;
    }
}

void BST::arrFill(BST::BNode* &move, int &index){
    if(move != nullptr) {
        arrFill(move->_left, index);
        _arr[index] = new BNode(move->_data,move->_key);
        index++;
        arrFill(move->_right, index);
    }else{
        return;
    }
}

BST::BNode* BST::balance(BST::BNode * &move){
    int index = 0;
    arrFill(move, index);
    BNode* temp = bstFill(_arr, 0, move->_size-1);
    for(int i = 0; i < move->_size; i++){
        _arr[i]->_height = heightHelp(_arr[i]);
        _arr[i]->_size = sizeHelp(_arr[i]);
        _arr[i] = nullptr;
    }
    delete [] _arr;
    return temp;
}

BST::BNode* BST::bstFill(BNode* sort[], int begin, int back) {
    if(begin > back){
        return nullptr;
    }

    int root = (begin + back)/2;
    BNode* temp = sort[root];

    temp->_left = bstFill(_arr, begin, root-1);
    temp->_right = bstFill(_arr, root+1, back);

    return temp;
}

BST::BNode* BST::bstCopyHelp(BNode* &myRoot, BST::BNode* &copyRoot){
    if(copyRoot == nullptr){
        return NULL;
    }
    BNode* copy = new BNode(copyRoot->_data, copyRoot->_key, copyRoot->_height, copyRoot->_size);
    copy->_left = bstCopyHelp(myRoot, copyRoot->_left);
    copy->_right = bstCopyHelp(myRoot, copyRoot->_right);
    return copy;
}

// A sample balance function.  This implements the height-balanced
// property from AVL trees.

 bool imbalfn(int leftHeight, int rightHeight, int leftSize, int rightSize) {
   return (leftHeight > rightHeight + 1) || (rightHeight > leftHeight + 1);
 }

// A sample main to exercise BST separately.  This is *NOT* a thorough
// test program

// int main() {
//
//   BST bst( imbalfn );
//
//     bst.dump(true);
//
//   bst.insert("A", 50);
//   bst.insert("B", 10);
//   bst.insert("f", 15);
//   bst.insert("D", 27);
//   bst.insert("E", 30);
//   bst.insert("j", 40);
//   bst.insert("G", 350);
//   bst.insert("q", 60);
//   bst.insert("I", 60);
//   bst.insert("z", 70);
//   bst.insert("K", 22);
//   bst.insert("L", 80);
//     bst.insert("L", 80);
//     bst.insert("L", 80);
//     bst.insert("@", -1);
//     bst.insert("m", 0);
//
//
//   bst.dump();
//   bst.dump(true);
//
//     BST bst1(bst);
//     BST bst2(bst1);
//
//   cout << "size = " << bst.size() << endl;
//   cout << "height = " << bst.height() << endl;
//
//   bst.~BST();
//
//     bst1.dump();
//     bst.insert("m", 1);
//     bst1.dump(true);
//
//     bst2.dump();
//     bst2.dump(true);
//   return 0;
// }
