#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class TreeNode{
    private:
    int value;
    TreeNode* left;
    TreeNode* right;

    public:
    TreeNode(){
    }
    TreeNode(int value){
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
    void nodeSetLeft(TreeNode* newLeft){
        left = newLeft;
    }
    TreeNode* getLeft(){
        return left;
    }
    TreeNode* getRight(){
        return right;
    }
    int getValue(){
        return value;
    }
    void nodeSetRight(TreeNode* newRight){
        right = newRight;
    }
};

class HuffTree{
    private:
    TreeNode* parent;

    public:
    HuffTree(int value){
        parent = new TreeNode(value);
    }
    TreeNode* getRoot(){
        return parent;
    }
};

HuffTree* makeTree(vector<int> inOrderList, vector<int> levelOrderList){
vector<int> rightSideInOrder;
vector<int> leftSideInOrder;
vector<int> rightSideLevelOrder;
vector<int> leftSideLevelOrder;
bool flag = false;
//splits inOrderList into two separate vectors, one containing all values left of the root node and the other containing all values right of the root node
for(int i = 0; i < inOrderList.size(); i++){
    if(inOrderList.at(i) == levelOrderList.at(0)){
        flag = true;
    }
    if(!flag){
        leftSideInOrder.push_back(inOrderList.at(i));
    }
    if(flag && inOrderList.at(i) != levelOrderList.at(0)){
        rightSideInOrder.push_back(inOrderList.at(i));
    }
}
flag = false;
//searches the level order list and sorts values in the order that they appear in the level order into either the left or right tree
for(int i = 1; i < levelOrderList.size(); i++){
    for(int x = 0; x < leftSideInOrder.size(); x++){
        if(levelOrderList.at(i) == leftSideInOrder.at(x)){
            flag = true;
        }
    }
        if(flag){
            leftSideLevelOrder.push_back(levelOrderList.at(i));
        }
        if(!flag){
            rightSideLevelOrder.push_back(levelOrderList.at(i));
        }
    flag = false;
}
// for(int i = 0; i < rightSideInOrder.size(); i++){
//     cout << rightSideInOrder.at(i) << endl;
// }

if(levelOrderList.size() != 0){
    HuffTree* tree = new HuffTree(levelOrderList.at(0));
    if(leftSideLevelOrder.size() != 0){
      tree->getRoot()->nodeSetLeft(makeTree(leftSideInOrder, leftSideLevelOrder)->getRoot());
    }
    if(rightSideLevelOrder.size() != 0){
      tree->getRoot()->nodeSetRight(makeTree(rightSideInOrder, rightSideLevelOrder)->getRoot());
    }
    return tree;
}
return nullptr;
}

int main(int argc, char* argv[]){
    ifstream inOrderTrav;
    ifstream levelOrderTrav;
    ifstream encText;
    vector<int> inOrderList;
    vector<int> levelOrderList;
    vector<char> encTextList;
    int buffer;
    string charBuffer;
    char cast;

    inOrderTrav.open(argv[1]);
    levelOrderTrav.open(argv[2]);
    encText.open(argv[3]);
    while(inOrderTrav >> buffer){
        inOrderList.push_back(buffer);
    }
    while(levelOrderTrav >> buffer){
        levelOrderList.push_back(buffer);
    }
    
    while(encText >> charBuffer){
    for(int i = 0; i < charBuffer.length(); i++){
        encTextList.push_back(charBuffer[i]);
    }
    }
    inOrderTrav.close();
    levelOrderTrav.close(); 
    encText.close();

    HuffTree* tree = makeTree(inOrderList, levelOrderList);
    TreeNode* root = tree->getRoot();
    for(int i = 0; i < encTextList.size(); i++){
        if(encTextList.at(i) == '0'){
            if(root->getLeft() != nullptr){
                // cout << "yes" << endl;
            root = root->getLeft();
            }
            else{
                // cout << "test1" << endl;
                // cout << "no" << endl;
                // cast = root->getValue();
                // cout << cast << endl;
            }
        }
        if(encTextList.at(i) == '1'){
            if(root->getRight() != nullptr){
            // cout << "yes" << endl;
            root = root->getRight();
            }
            else{
                // cout << "test" << endl;
                // cout << "no" << endl;
            }
        }
        if(root->getLeft() == nullptr && root->getRight() == nullptr){
                cast = root->getValue();
                cout << cast;
                root = tree->getRoot();
        }
    }

    return 0;
}