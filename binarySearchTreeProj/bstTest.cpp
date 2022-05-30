#include "BST.h"

bool imbalfn(int leftHeight, int rightHeight, int leftSize, int rightSize) {
    return (leftHeight > rightHeight + 1) || (rightHeight > leftHeight + 1);
}

int main(){
    BST bst( imbalfn );

     bst.dump(true);

   bst.insert("A", 50);
   bst.insert("B", 10);
   bst.insert("f", 15);
   bst.insert("D", 27);
   bst.insert("E", 30);
   bst.insert("j", 40);
   bst.insert("G", 350);
   bst.insert("q", 60);
   bst.insert("I", 60);
   bst.insert("z", 70);
   bst.insert("K", 22);
   bst.insert("L", 80);
     bst.insert("L", 80);
     bst.insert("L", 80);
     bst.insert("@", -1);
     bst.insert("m", 0);


   bst.dump();
   bst.dump(true);

     BST bst1(bst);
     BST bst2(bst1);

   cout << "size = " << bst.size() << endl;
   cout << "height = " << bst.height() << endl;

   bst.~BST();

     bst1.dump();
     bst.insert("m", 1);
     bst1.dump(true);

     bst2.dump();
     bst2.dump(true);
   return 0;
}