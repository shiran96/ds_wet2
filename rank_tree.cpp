#include "rank_tree.h"

static int getMax(int first, int second)
{
    return (first>second)?first:second;
}

int AvlRankTree::calculateBalanceFactor(Node* node) const
{
    return getNodeHeight(node->left)-getNodeHeight(node->right);
}

AvlRankTree::Node* AvlRankTree::getMinNode(Node* node) const
{   
    if(node==nullptr)
    {
        return nullptr;
    }
    if(node->left==nullptr)
    {
        return node;
    }
    return getMinNode(node->left);
}

AvlRankTree::Node* AvlRankTree::getMaxNode(Node* node) const
{
    if(node==nullptr)
    {
        return nullptr;
    }
    if(node->right==nullptr)
    {
        return node;
    }
    return getMaxNode(node->right);   
}

int AvlRankTree::getNodeLevel(Node* node) const
{
    return (node==nullptr)?-1:node->level;
}

int AvlRankTree::getNodeSize(const Node* node) const
{   
    return (node==nullptr)?0:node->size;
}

int AvlRankTree::getNodeHeight(const Node* node) const
{
    return (node==nullptr)?0:node->height;
}

int AvlRankTree::getNodeNumPeopleAtLevel(const Node* node) const
{
    return(node==nullptr)?0:node->numPeopleAtLevel;
}

int AvlRankTree::getNodeNumPeopleAtAtSubTree(const Node* node) const
{
    return (node==nullptr)?0:node->numPeopleAtSubTree;
}
int AvlRankTree::getNodeSumOfLevelsInSubTree(const Node* node) const
{
    return (node==nullptr)?0:node->sumOfLevelsInSubTree;
}

void AvlRankTree::increaseScoreAtGroupScoreArr(Node* node,int score)
{
    node->groupScoreArr[score]++;
}

void AvlRankTree::decreaseScoreAtGroupScoreArr(Node* node,int score)
{
    node->groupScoreArr[score]--;
}
void AvlRankTree::increaseScoreAtSubTreeGroupScoreArr(Node* node,int score)
{
    node->subTreeGroupScoreArr[score]++;
}
void AvlRankTree::decreaseScoreAtSubTreeGroupScoreArr(Node* node,int score)
{
    node->subTreeGroupScoreArr[score]--;
}

void AvlRankTree::increaseNumOfPeopleAtLevel(Node* node)
{
    node->numPeopleAtLevel++;
}

void AvlRankTree::decreaseNumOfPeopleAtLevel(Node* node)
{
    node->numPeopleAtLevel--;   
}

AvlRankTree::Node* AvlRankTree::createNode(int level)
{
    Node* new_node=new Node;
    new_node->level=level;
    new_node->father=nullptr;
    new_node->left=nullptr;
    new_node->right=nullptr;
    new_node->height=0;
    new_node->size=0;
    new_node->numPeopleAtLevel=0;
    new_node->numPeopleAtSubTree=0;
    new_node->sumOfLevelsInSubTree=0;
    new_node->groupScoreArr=new int[scale+1](); //initialize to zero
    new_node->subTreeGroupScoreArr=new int[scale+1](); //initialize to zero
    return new_node;
}

AvlRankTree::Node* AvlRankTree::duplicateNode(Node* node)
{
    if(node==nullptr)
    {
        return nullptr;
    }
    Node* left_copy=duplicateNode(node->left);
    Node* right_copy=duplicateNode(node->right);
    Node* new_node=createNode(node->level);
    new_node->numPeopleAtLevel=node->numPeopleAtLevel;
    for(int i=0;i<scale+1;i++)
    {
        new_node->groupScoreArr[i]=node->groupScoreArr[i];
    }
    new_node->left=left_copy;
    if(new_node->left!=nullptr)
    {
        new_node->left->father=new_node;
    }
    new_node->right=right_copy;
    if(new_node->right!=nullptr)
    {
        new_node->right->father=new_node;
    }
    new_node->size=getNodeSize(new_node->right)+getNodeSize(new_node->left)+1;
    new_node->height=getNodeHeight(new_node->right)+getNodeHeight(new_node->left)+1;
    new_node->numPeopleAtSubTree=getNodeNumPeopleAtAtSubTree(new_node->right)
        +getNodeNumPeopleAtAtSubTree(new_node->left)+new_node->numPeopleAtLevel;
    new_node->sumOfLevelsInSubTree=getNodeSumOfLevelsInSubTree(new_node->right)
        +getNodeSumOfLevelsInSubTree(new_node->left)
        +(new_node->numPeopleAtLevel)*(new_node->level);
    for(int i=0;i<scale+1;i++)
    {
        new_node->subTreeGroupScoreArr[i]=0;
        new_node->subTreeGroupScoreArr[i]+=new_node->groupScoreArr[i];
        new_node->subTreeGroupScoreArr[i]+=(new_node->right==nullptr)?0:new_node->right->subTreeGroupScoreArr[i];
        new_node->subTreeGroupScoreArr[i]+=(new_node->left==nullptr)?0:new_node->left->subTreeGroupScoreArr[i];

    }
    return new_node;
}

AvlRankTree::Node* AvlRankTree::insertNode(Node* new_node,Node* target,Node* parent)
{
    /*insert like in a binary tree before fixing by rolling*/ 
    if(target==nullptr)
    {
        new_node->father=parent;
        new_node->size=getNodeSize(new_node->left)+getNodeSize(new_node->right)+1;
        //new_node->numPeopleAtLevel+=1; //equall to 1
        new_node->height=getNodeHeight(new_node->right)+getNodeHeight(new_node->left)+1;
        new_node->numPeopleAtSubTree=getNodeNumPeopleAtAtSubTree(new_node->left)
        +getNodeNumPeopleAtAtSubTree(new_node->right)+new_node->numPeopleAtLevel; 
        new_node->sumOfLevelsInSubTree=getNodeSumOfLevelsInSubTree(new_node->left)
        +getNodeSumOfLevelsInSubTree(new_node->right)
        +(new_node->level)*(new_node->numPeopleAtLevel);
        for(int i=0;i<scale+1;i++)
        {
            new_node->subTreeGroupScoreArr[i]=0;
            new_node->subTreeGroupScoreArr[i]+=new_node->groupScoreArr[i];
            new_node->subTreeGroupScoreArr[i]+=(new_node->right==nullptr)?0:new_node->right->subTreeGroupScoreArr[i];
            new_node->subTreeGroupScoreArr[i]+=(new_node->left==nullptr)?0:new_node->left->subTreeGroupScoreArr[i];
        }
        return new_node;
    }
    if(new_node->level < target->level)
    {
        target->left=insertNode(new_node,target->left,target);
    }
    else //we call this function only if level doesnt allready exist
    {     //so there will not be two nodes with the same level
        target->right=insertNode(new_node,target->right,target);
    }
    /*balance the tree- fix by rolling,
    will only get here and enter the if-condition if a balance was changed 
    after adding a node to the tree, will correct recursively until the root*/ 
    if(calculateBalanceFactor(target)>1)  //changed
    {
        if(calculateBalanceFactor(target->left)>=0)
        {
            return rollLeftLeft(target);
        }
        else //BF(root->left)=-1
        {
            return rollLeftRight(target);
        }
    }
    else if(calculateBalanceFactor(target)<-1) //changed
    {
        if(calculateBalanceFactor(target->right)<=0)
        {
            return rollRightRight(target);
        }
        else //BF(root->right)=1
        {
            return rollRightLeft(target);
        }
    }
    /*correct height and other fields*/
    target->height=getMax(getNodeHeight(target->right),getNodeHeight(target->left))+1;
    target->size=getNodeSize(target->left)+getNodeSize(target->right)+1;
    target->numPeopleAtSubTree=getNodeNumPeopleAtAtSubTree(target->right)+
        getNodeNumPeopleAtAtSubTree(target->left)+target->numPeopleAtLevel;
    target->sumOfLevelsInSubTree=getNodeSumOfLevelsInSubTree(target->right)
        +getNodeSumOfLevelsInSubTree(target->left)
        +(target->numPeopleAtLevel)*(target->level);
    for(int i=0;i<scale+1;i++)
    {
        target->subTreeGroupScoreArr[i]=0; //initialization
        if(target->right!=nullptr)
        {
            target->subTreeGroupScoreArr[i]+=target->right->subTreeGroupScoreArr[i];
        }
        if(target->left!=nullptr)
        {
            target->subTreeGroupScoreArr[i]+=target->left->subTreeGroupScoreArr[i];
        }
        target->subTreeGroupScoreArr[i]+=target->groupScoreArr[i];
    }
    return target;

}

AvlRankTree::Node* AvlRankTree::findNode(Node* node,int level)const
{
    if(node==nullptr)
    {
        return nullptr; //the level is not in the tree
    }
    if(node->level==level)
    {
        return node;
    }
    if(node->level > level)
    {
        return findNode(node->left,level);
    }
    if(node->level < level) 
    {
        return findNode(node->right,level);
    }
    return nullptr;
}

AvlRankTree::Node* AvlRankTree::deleteNode(Node* target, Node* to_remove)
{
    if(target==nullptr || to_remove== nullptr)  //if(to_remove==nullptr)-did segmentation
    {                                          //need to check target not to remove...
        return nullptr;
    }
    //remove the node
    if (to_remove->level == target->level) //target==to remove
    {
        if(target->left==nullptr && target->right==nullptr) //a leaf
        {
            delete[] target->groupScoreArr;
            delete[] target->subTreeGroupScoreArr;
            delete target;
            return nullptr;
        }
        else if(target->left==nullptr)
        {
            Node* tempNode=target->right;   
            target->level=tempNode->level;
            target->numPeopleAtLevel=tempNode->numPeopleAtLevel;
            for(int i=0;i<scale+1;i++)
            {
                target->groupScoreArr[i]=tempNode->groupScoreArr[i];
            }
            target->right=deleteNode(target->right,target);
            //i dont think we need to update more fields 
            //if there is an error- check if need to update
            //num people at level and scoreGroupArr from tempNode
        }
        else if(target->right==nullptr)
        {
            Node* tempNode=target->left;
            target->level = tempNode->level;
            target->numPeopleAtLevel=tempNode->numPeopleAtLevel;
            for(int i=0;i<scale+1;i++)
            {
                target->groupScoreArr[i]=tempNode->groupScoreArr[i];
            }
            target->left = deleteNode(target->left,target);
        }
        else //there is a left son and a right son
        {
            Node* tempNode=getMinNode(target->right);
            target->level = tempNode->level;
            target->numPeopleAtLevel=tempNode->numPeopleAtLevel;
            for(int i=0;i<scale+1;i++)
            {
                target->groupScoreArr[i]=tempNode->groupScoreArr[i];
            }
            target->right=deleteNode(target->right,target);
        }
    }
    else if(to_remove->level >= target->level)
    {
        target->right=deleteNode(target->right,to_remove);
    }
    else
    {
        target->left=deleteNode(target->left,to_remove);
    }
    //fix
    target->height=getMax(getNodeHeight(target->right),getNodeHeight(target->left))+1;
    target->size=getNodeSize(target->right)+getNodeSize(target->left)+1;
    target->numPeopleAtSubTree=getNodeNumPeopleAtAtSubTree(target->right)
        +getNodeNumPeopleAtAtSubTree(target->left)+target->numPeopleAtLevel;
    target->sumOfLevelsInSubTree=getNodeSumOfLevelsInSubTree(target->right)
        +getNodeSumOfLevelsInSubTree(target->left)
        +(target->level)*(target->numPeopleAtLevel);
    for(int i=0;i<scale+1;i++)
    {
        target->subTreeGroupScoreArr[i]=0;
        target->subTreeGroupScoreArr[i]+=(target->right==nullptr)?0:target->right->subTreeGroupScoreArr[i];
        target->subTreeGroupScoreArr[i]+=(target->left==nullptr)?0:target->left->subTreeGroupScoreArr[i];
        target->subTreeGroupScoreArr[i]+=target->groupScoreArr[i];
    }
    //balance the tree
    if(calculateBalanceFactor(target)>1) //changed
    {
        if(calculateBalanceFactor(target->left)>=0)
        {
            return rollLeftLeft(target);
        }
        else
        {
            return rollLeftRight(target);
        }
    }
    else if(calculateBalanceFactor(target)<-1)  //changed
    {
        if(calculateBalanceFactor(target->right)==1)
        {
            return rollRightLeft(target);
        }
        else
        {
            return rollRightRight(target);
        }
    }
    return target;   
    }

AvlRankTree::Node* AvlRankTree::selectNodeOperation(Node* node, int index) const
{
    if(getNodeSize(node->left)==index-1) //the prev to node got the prev index
    {
        return node;
    }
    else if(getNodeSize(node->left) < index-1) // go more left
    {
        return selectNodeOperation(node->right, index- (getNodeSize(node->left)+1));
    }
    else  //go more right to biggers ranks
    {
        return selectNodeOperation(node->left,index);
    }   
}

AvlRankTree::Node* AvlRankTree::rollLeftLeft(Node* node)
{ //rotate
    Node* tempNode = node->left;
    node->left->father=node->father;
    node->father=tempNode;
    if(tempNode->right!=nullptr)
    {
        tempNode->right->father=node;
    }
    node->left =node->father->right;
    node->father->right=node;
    //update height and other fields
    node->height=getMax(getNodeHeight(node->left),getNodeHeight(node->left))+1;
    node->size=getNodeSize(node->right)+getNodeSize(node->left)+1;
    node->numPeopleAtSubTree=getNodeNumPeopleAtAtSubTree(node->right)
        +getNodeNumPeopleAtAtSubTree(node->left)+node->numPeopleAtLevel;
    node->sumOfLevelsInSubTree=getNodeSumOfLevelsInSubTree(node->right)
        +getNodeSumOfLevelsInSubTree(node->left)
        +(node->numPeopleAtLevel)*(node->level);
    for(int i=0;i<scale+1;i++)
    {
        node->subTreeGroupScoreArr[i]=0;
        node->subTreeGroupScoreArr[i]+=(node->right==nullptr)?0:node->right->subTreeGroupScoreArr[i];
        node->subTreeGroupScoreArr[i]+=(node->left==nullptr)?0:node->left->subTreeGroupScoreArr[i];
        node->subTreeGroupScoreArr[i]+=node->groupScoreArr[i];
    }
    if(node->father != nullptr)
    {
        node->father->height=getMax(getNodeHeight(node->father->right),getNodeHeight(node->father->left))+1;
        node->father->size=getNodeSize(node->father->right)+getNodeSize(node->father->left)+1;
        node->father->numPeopleAtSubTree=getNodeNumPeopleAtAtSubTree(node->father->right)
        +getNodeNumPeopleAtAtSubTree(node->father->left)+node->father->numPeopleAtLevel;
        node->father->sumOfLevelsInSubTree=getNodeSumOfLevelsInSubTree(node->father->right)
        +getNodeSumOfLevelsInSubTree(node->father->left)
        +(node->father->numPeopleAtLevel)*(node->father->level);
        for(int i=0;i<scale+1;i++)
        {
            node->father->subTreeGroupScoreArr[i]=0;
            node->father->subTreeGroupScoreArr[i]+=(node->father->right==nullptr)?0:node->father->right->subTreeGroupScoreArr[i];
            node->father->subTreeGroupScoreArr[i]+=(node->father->left==nullptr)?0:node->father->left->subTreeGroupScoreArr[i];
            node->father->subTreeGroupScoreArr[i]+=node->father->groupScoreArr[i];
        }
    }
    return node->father;
}
AvlRankTree::Node* AvlRankTree::rollRightRight(Node* node)
{
    //rotate
    Node* temp=node->right;
    node->right->father=node->father;
    node->father=temp;
    node->right=node->father->left;
    if(node->right!=nullptr)
    {
        node->right->father = node;
    }
    node->father->left = node;
    //update heights and such
    node->size=getNodeSize(node->right)+getNodeSize(node->left)+1;
    node->height=getNodeHeight(node->right)+getNodeSize(node->left)+1;
    node->numPeopleAtSubTree=getNodeNumPeopleAtAtSubTree(node->right)
        +getNodeNumPeopleAtAtSubTree(node->left)+node->numPeopleAtLevel;
    node->sumOfLevelsInSubTree=getNodeSumOfLevelsInSubTree(node->right)
        +getNodeSumOfLevelsInSubTree(node->left)
        +(node->numPeopleAtLevel)*(node->level);
    for(int i=0;i<scale+1;i++)
    {
        node->subTreeGroupScoreArr[i]=0;
        node->subTreeGroupScoreArr[i]+=(node->right==nullptr)?0:node->right->subTreeGroupScoreArr[i];
        node->subTreeGroupScoreArr[i]+=(node->left==nullptr)?0:node->left->subTreeGroupScoreArr[i];
        node->subTreeGroupScoreArr[i]+=node->groupScoreArr[i];
    }
    if(node->father != nullptr)
    {
        node->father->height=getMax(getNodeHeight(node->father->right),getNodeHeight(node->father->left))+1;
        node->father->size=getNodeSize(node->father->right)+getNodeSize(node->father->left)+1;
        node->father->numPeopleAtSubTree=getNodeNumPeopleAtAtSubTree(node->father->right)
        +getNodeNumPeopleAtAtSubTree(node->father->left)+node->father->numPeopleAtLevel;
        node->father->sumOfLevelsInSubTree=getNodeSumOfLevelsInSubTree(node->father->right)
        +getNodeSumOfLevelsInSubTree(node->father->left)
        +(node->father->numPeopleAtLevel)*(node->father->level);
        for(int i=0;i<scale+1;i++)
        {
            node->father->subTreeGroupScoreArr[i]=0;
            node->father->subTreeGroupScoreArr[i]+=(node->father->right==nullptr)?0:node->father->right->subTreeGroupScoreArr[i];
            node->father->subTreeGroupScoreArr[i]+=(node->father->left==nullptr)?0:node->father->left->subTreeGroupScoreArr[i];
            node->father->subTreeGroupScoreArr[i]+=node->father->groupScoreArr[i];
        }
    }
    return node->father;  
}

//combination of a single left rotation followed by a single right rotation
AvlRankTree::Node* AvlRankTree::rollRightLeft(Node* node)
{
    node->right = rollLeftLeft(node->right);
    return rollRightRight(node);
}

//combination of a single right rotation followed by a single left rotation
AvlRankTree::Node* AvlRankTree::rollLeftRight(Node* node)
{
    node->left = rollRightRight(node->left);
    return rollLeftLeft(node);
}

void AvlRankTree::emptyTreeAux(Node* node)
{
    if(node==nullptr)
    {
        return;
    }
    if(node->right!=nullptr)
    {
        emptyTreeAux(node->right);
    }
    if(node->left!=nullptr)
    {
        emptyTreeAux(node->left);
    }
    delete[] node->groupScoreArr; 
    delete[] node->subTreeGroupScoreArr;
    delete node;
    return;
}
AvlRankTree::Node* AvlRankTree::convertSortedArrayToTreeAux(Node* sorted_array[],int start,int end,Node* father)
{
    if(start>end)
    {
        return nullptr;
    }
    int middle=(start+end)/2;
    Node* new_element_in_tree=createNode(getNodeLevel(sorted_array[middle]));
    new_element_in_tree->numPeopleAtLevel=(sorted_array[middle])->numPeopleAtLevel;
    for(int i=0;i<scale+1;i++)
    {
        new_element_in_tree->groupScoreArr[i]=(sorted_array[middle])->groupScoreArr[i];
    }
    new_element_in_tree->father=father;
    new_element_in_tree->right = convertSortedArrayToTreeAux(sorted_array, middle + 1, end, new_element_in_tree);
    new_element_in_tree->left = convertSortedArrayToTreeAux(sorted_array, start, middle - 1, new_element_in_tree);
    new_element_in_tree->height=getMax(getNodeHeight(new_element_in_tree->right),getNodeHeight(new_element_in_tree->left))+1;
    new_element_in_tree->size =getNodeSize(new_element_in_tree->right)+getNodeHeight(new_element_in_tree->left)+1;
    new_element_in_tree->numPeopleAtSubTree= getNodeNumPeopleAtAtSubTree(new_element_in_tree->right)
        + getNodeNumPeopleAtAtSubTree(new_element_in_tree->left)
        +new_element_in_tree->numPeopleAtLevel;
    new_element_in_tree->sumOfLevelsInSubTree= getNodeSumOfLevelsInSubTree(new_element_in_tree->right)
        + getNodeSumOfLevelsInSubTree(new_element_in_tree->left)
        +(new_element_in_tree->level)*(new_element_in_tree->numPeopleAtLevel);
    for(int i=0;i<scale+1;i++)
    {
        new_element_in_tree->subTreeGroupScoreArr[i]=0;
        new_element_in_tree->subTreeGroupScoreArr[i]+=(new_element_in_tree->right==nullptr)?0:new_element_in_tree->right->subTreeGroupScoreArr[i];
        new_element_in_tree->subTreeGroupScoreArr[i]+=(new_element_in_tree->left==nullptr)?0:new_element_in_tree->left->subTreeGroupScoreArr[i];
        new_element_in_tree->subTreeGroupScoreArr[i]+=new_element_in_tree->groupScoreArr[i];
    }
    return new_element_in_tree;
}

void AvlRankTree::printTreeAux(Node* root) const //print inorder style
{
    if(root==nullptr)
    {
        return;
    }
    printTreeAux(root->left);
    std::cout<< "level:"<< root->level <<" numPeopleAtLevel:"<< root->numPeopleAtLevel<<std::endl;
    std::cout<<"num of people in sub tree:"<<root->numPeopleAtSubTree<<std::endl;
    std::cout<<"sum of levels in sub tree:"<<root->sumOfLevelsInSubTree <<std::endl;
    for(int i=0; i<scale+1;i++)
    {
        if(root->groupScoreArr[i]!=0)
        {
            std::cout<< "with score "<< i <<":"<<root->groupScoreArr[i]<<std::endl;
        }
        if(root->subTreeGroupScoreArr[i]!=0)
        {
            std::cout<< "with score "<< i<< " at subtree:" <<root->subTreeGroupScoreArr[i]<<std::endl;
        }
    }
    std::cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<std::endl;
    printTreeAux(root->right);
}

bool AvlRankTree::isTreeEmpty() const
{
    return (size_of_tree==0);
}
void AvlRankTree::empty()
{
    if(size_of_tree > 0)
    {
    emptyTreeAux(root);
    }
    root = nullptr;
    size_of_tree = 0;
    max = nullptr;
    min=nullptr;
}

AvlRankTree::AvlRankTree(int scale):scale(scale),size_of_tree(0),root(nullptr),max(nullptr),min(nullptr){}

AvlRankTree::AvlRankTree(const AvlRankTree& other):scale(other.scale),size_of_tree(other.size_of_tree),root(nullptr),max(nullptr),min(nullptr)
{
    //size_of_tree=other.size_of_tree;
    root=duplicateNode(other.root);
    max=getMaxNode(root);
    min=getMinNode(root);
}

AvlRankTree::~AvlRankTree()
{
    empty();  
}

AvlRankTree& AvlRankTree::operator=(const AvlRankTree &other)
{
    empty();
    scale=other.scale;
    root = duplicateNode(other.root);
    size_of_tree = other.size_of_tree;
    max=getMaxNode(root);
    min=getMinNode(root);
    return *this;
}

//it's on the user that the tree will be empty 
void AvlRankTree::convertSortedArrayToTree(Node* dataArr[],int arrSize)
{
    root=convertSortedArrayToTreeAux(dataArr,0,arrSize-1,nullptr);
    size_of_tree=arrSize;
    max=getMaxNode(root);
    min=getMinNode(root);
}

//we call this function knowing the data of the certain player isnt in the tree
void AvlRankTree::insert(int level,int score)
{
    Node* level_node=findNode(root,level);
    //if the level doesnt exist- create and insert a new level to the tree
    //with the info of the player
    if(level_node==nullptr)
    {
        Node* new_level=createNode(level); //groupScoreArr is empty, numOfPeopleAtlevel=0
        increaseScoreAtGroupScoreArr(new_level,score);
        increaseNumOfPeopleAtLevel(new_level); //=1
        root=insertNode(new_level,root,nullptr);
        min = getMinNode(root);
        max = getMaxNode(root);
        size_of_tree++;
    }
    else //the level exist-> make a copy with same GroupScoreArr and numPeopleAtLevel
    {   //delete the level and reInsert after updating and adding the new data
        Node* updated_level_node=createNode(level);//groupScoreArr empty, numOfPeopleAtlevel=0
        updated_level_node->numPeopleAtLevel=level_node->numPeopleAtLevel;
        increaseNumOfPeopleAtLevel(updated_level_node); //we insert a new player
        for(int i=0;i<scale+1;i++)
        {
            updated_level_node->groupScoreArr[i]=level_node->groupScoreArr[i];
        }
        increaseScoreAtGroupScoreArr(updated_level_node,score);//we insert a new player
        root=deleteNode(root,level_node);
        max= getMaxNode(root);
        min= getMinNode(root);
        size_of_tree--;
        root=insertNode(updated_level_node,root,nullptr);
        min = getMinNode(root);
        max = getMaxNode(root);
        size_of_tree++;
    }
}


AvlRankTree::Node* AvlRankTree::find(int level)
{
    Node* node=findNode(root,level);
    return node; //may be null
}

//we call this function knowing the data of the certain player is in the tree
void AvlRankTree::remove(int level,int score)
{
    Node* to_delete=find(level);
    if(to_delete== nullptr)
    {
        return;
    }
    if(to_delete->numPeopleAtLevel==1) //we remove the only player in the level
    {                                  //and need to remove the level
        root=deleteNode(root,to_delete);
        size_of_tree--;
        min= getMinNode(root);
        max= getMaxNode((root));
    }
    else //we remove the player's data but not the level itself
    {
        //make a copy of the level, decrease relevent field, delete the level,
        //and insert the updated level
        Node* updated_level=createNode(level);
        updated_level->numPeopleAtLevel=to_delete->numPeopleAtLevel;
        decreaseNumOfPeopleAtLevel(updated_level); //we remove a player
        for(int i=0;i<scale+1;i++)
        {
            updated_level->groupScoreArr[i]=to_delete->groupScoreArr[i];
        }
        decreaseScoreAtGroupScoreArr(updated_level,score);//we remove a player
        root=deleteNode(root,to_delete);
        max= getMaxNode(root);
        min= getMinNode(root);
        root=insertNode(updated_level,root,nullptr);
        max= getMaxNode(root);
        min= getMinNode(root);
    }
}

//the user need to make sure the index is valid before calling this function
//invalid: index<0 or index> size_of_tree
AvlRankTree::Node* AvlRankTree::select(int index) const
{
    Node* node=selectNodeOperation(root,index);
    return node;
}

int AvlRankTree::getHeight() const
{
    return (root==nullptr)?0:root->height;
}

int AvlRankTree::getMaxlevel() const
{
    return getNodeLevel(this->max);
}

void AvlRankTree::printTree() const
{
    printTreeAux(root);
}

AvlRankTree::Iterator::Iterator(Node* node, Node* last):node(node),last(last){}

AvlRankTree::Iterator& AvlRankTree::Iterator::operator=(const Iterator& other_iter)
{
    if(*this == other_iter)
    {
        return *this;
    }
    last = other_iter.last;
    node = other_iter.node;
    return *this;
}

AvlRankTree::Iterator::Iterator(const Iterator& other_iter):node(other_iter.node),
                                            last(other_iter.last){}

AvlRankTree::Node* AvlRankTree::Iterator::operator*() //may return null-the user 
{                                                     //need to be careful
    return node;
}

bool AvlRankTree::Iterator::operator==(const Iterator& iter) const
{
    if(node==iter.node)
    {
        return true;
    }
    return false;
}
bool AvlRankTree::Iterator::operator!=(const Iterator& iter) const
{
    return !(*this == iter);
}

AvlRankTree::Iterator& AvlRankTree::Iterator::operator++()
{
    if(node == last)
    {
        node = nullptr;
    }
    else
    {
        if(node->right!= nullptr)
        {
            node=node->right;
            while(node->left!= nullptr)
            {
                node=node->left;
            }
        }
        else
        {
            Node* tempNode=node;
            node=node->father;
            while((node->father!= nullptr) && (node->right==tempNode)) //came from right son
            {
                tempNode=node;
                node=node->father;
            }
        }

    }
    return *this;
}

AvlRankTree::Iterator AvlRankTree::begin() const
{
    return Iterator(this->min, this->max);
}
AvlRankTree::Iterator AvlRankTree::end() const
{
    return Iterator(nullptr, nullptr);
}

//will merge 2 tree to one in O(n) - on the user to delete the source's trees
AvlRankTree::AvlRankTree(const AvlRankTree& firstTree, const AvlRankTree& secondTree):
        scale(firstTree.scale),size_of_tree(0),root(nullptr),max(nullptr),min(nullptr)
{
    Iterator firstIter=firstTree.begin();
    Iterator secondIter=secondTree.begin();
    int size=firstTree.size_of_tree+secondTree.size_of_tree;
    Node** sortedArr = new Node*[size]; //will hold copies!!
    int index=0;
   // int realSize=0;
    while(firstIter!=firstTree.end() && secondIter!=secondTree.end()) //merge
    {
        if( ((*firstIter)->level) < ((*secondIter)->level) )
        {
            Node* copy=createNode(((*firstIter)->level));
            //copy only the fields that arent dependent in the sub tree
            copy->numPeopleAtLevel=(*firstIter)->numPeopleAtLevel;
            for(int i=0;i<scale+1;i++)
            {
                copy->groupScoreArr[i]=((*firstIter)->groupScoreArr[i]);
            }
            sortedArr[index]=copy;
            ++firstIter;
        }
        else
        {
            Node* copy=createNode(((*secondIter)->level));
            //copy only the fields that arent dependent in the sub tree
            copy->numPeopleAtLevel=(*secondIter)->numPeopleAtLevel;
            for(int i=0;i<scale+1;i++)
            {
                copy->groupScoreArr[i]=((*secondIter)->groupScoreArr[i]);
            }
            sortedArr[index]=copy;
            ++secondIter;
        }
        index++; 
    }

    while(firstIter != firstTree.end())
    {
        Node* copy=createNode(((*firstIter)->level));
        //copy only the fields that arent dependent in the sub tree
        copy->numPeopleAtLevel=(*firstIter)->numPeopleAtLevel;
        for(int i=0;i<scale+1;i++)
        {
            copy->groupScoreArr[i]=((*firstIter)->groupScoreArr[i]);
        }
        sortedArr[index]=copy;
        ++firstIter;
        index++;
    }

    while(secondIter != secondTree.end()) 
    {
        Node* copy=createNode(((*secondIter)->level));
        //copy only the fields that arent dependent in the sub tree
        copy->numPeopleAtLevel=(*secondIter)->numPeopleAtLevel;
        for(int i=0;i<scale+1;i++)
        {
            copy->groupScoreArr[i]=((*secondIter)->groupScoreArr[i]);
        }
        sortedArr[index]=copy;
        ++secondIter;
        index++;
    }
    //now we have a sorted array but it may contain duplicated levels
    //- we will merge same leves's data. -O(num of levels)
    Node** sortedUniqeLevelsArr = new Node*[size]; //will hold copies!!
    int j=0; //index at sortedArr
    int k=0; //index at sortedUniqeLevelsArr
    while(j<size)
    {
        if(j<size-1)
        {
            if( ((sortedArr[j])->level) == ((sortedArr[j+1])->level) )
            {
                Node* copy=createNode((sortedArr[j])->level);
                copy->numPeopleAtLevel=(sortedArr[j]->numPeopleAtLevel)
                    +(sortedArr[j+1]->numPeopleAtLevel);
                for(int t=0;t<scale+1;t++)
                {
                    copy->groupScoreArr[t]=sortedArr[j]->groupScoreArr[t]
                    +sortedArr[j+1]->groupScoreArr[t];
                }
                sortedUniqeLevelsArr[k]=copy;
                j+=2; //skip the same level
            }
            else
            {
                Node* copy=createNode((sortedArr[j])->level);
                copy->numPeopleAtLevel=(sortedArr[j]->numPeopleAtLevel);
                for(int t=0;t<scale+1;t++)
                {
                    copy->groupScoreArr[t]=(sortedArr[j])->groupScoreArr[t];
                }
                sortedUniqeLevelsArr[k]=copy;
                j+=1;
            }
            k++;
        }
        else if(j==size-1) //if j>size-1 ->we copied everyones
        { //if we are the prev level was different (because otherwise j=size)
            Node* copy=createNode((sortedArr[j])->level);
            copy->numPeopleAtLevel=(sortedArr[j]->numPeopleAtLevel);
            for(int t=0;t<scale+1;t++)
            {
                copy->groupScoreArr[t]=(sortedArr[j])->groupScoreArr[t];
            }
            sortedUniqeLevelsArr[k]=copy; 
            k++;
            j++;         
        }
    }
    //k hold the true size of the array
    //delete sortedArr - we dont need it anymore
    for(int i=0;i<size;i++) //destroy the copies we made
    {
        delete[] (sortedArr[i])->groupScoreArr;
        delete[] (sortedArr[i])->subTreeGroupScoreArr;
        delete (sortedArr[i]);
    }
    delete[] sortedArr;
    convertSortedArrayToTree(sortedUniqeLevelsArr,k); //make copies for itself
    //delete sortedUniqeLevelsArr
    for(int i=0;i<k;i++) //destroy the copies we made
    {
        delete[] (sortedUniqeLevelsArr[i])->groupScoreArr;
        delete[] (sortedUniqeLevelsArr[i])->subTreeGroupScoreArr;
        delete (sortedUniqeLevelsArr[i]);
    }
    delete[] sortedUniqeLevelsArr;
}

//on the user: "this" is empty (call empty before using)
void AvlRankTree::fillFromTree(const AvlRankTree& src)
{
    Node** sortedSrcArr = new Node*[src.size_of_tree];
    int index=0;
    AvlRankTree::Iterator itr=src.begin();
    while(itr!=src.end())
    {
        Node* copy=createNode(((*itr)->level));
        //copy only the fields that arent dependent in the sub tree
        copy->numPeopleAtLevel=(*itr)->numPeopleAtLevel;
        for(int i=0;i<scale+1;i++)
        {
            copy->groupScoreArr[i]=((*itr)->groupScoreArr[i]);
        }
        sortedSrcArr[index]=copy;
        ++itr;
        index++;
    }
    this->convertSortedArrayToTree(sortedSrcArr,src.size_of_tree); //make copies for itself
    for(int i=0;i<src.size_of_tree;i++) //destroy the copies we made
    {
        delete[] (sortedSrcArr[i])->groupScoreArr;
        delete[] (sortedSrcArr[i])->subTreeGroupScoreArr;
        delete (sortedSrcArr[i]);
    }
    delete[] sortedSrcArr;
    this->size_of_tree=src.size_of_tree;
    max=getMaxNode(this->root);
    min=getMinNode(this->root);
}

//we call this function knowing first and second are in the tree- isn't empty
AvlRankTree::Node* AvlRankTree::getCommonFather(Node* first,Node* second,Node* origin)//o(logn)
{
//    if(origin== nullptr)
//    {
//        return nullptr;
//    }
    //if both first and second are smaller than the origin ,
    // the common father is at the left size
    if((origin->level > first->level) && (origin->level > second-> level))
    {
        if(origin->left== nullptr)
        {
            return origin;
        }
        else
        {
            return getCommonFather(first,second,origin->left);
        }

    }
    //if both first and second are bigger than the origin ,
    // the common father is at the right size
    if((origin->level < first->level) && (origin->level < second-> level))
    {
        if(origin->right== nullptr)
        {
            return origin;
        }
        else
        {
            return getCommonFather(first,second,origin->right);
        }
    }
    return origin;
}

////error: if score<0 or score>scale and num of people between bounds is 0
////or if the bounds exist but there are no people between them (regardless the score)
////return (num of people with score between bounds / num of people between bounds)
//double AvlRankTree::getPrecentOfPlayersWithScoreBetweenBounds(int score,int lowLevel,int highLevel,
//                       int* error, int numPeopleAtZero, int numPeopleAtZeroWithScore)
//{
//    bool score_invalid=false;
//    if (score <= 0 || score > this->scale)
//    {
//        score_invalid=true;
//    }
//    bool low_high_same=false;
//    if(lowLevel==highLevel)
//    {
//        low_high_same=true;
//    }
//    int numOfPeopleWithScore =(lowLevel<=0)?numPeopleAtZeroWithScore:0;
//    int numOfPeopleBetweenBounds =(lowLevel<=0)?numPeopleAtZero:0;
//    Node *low = findNode(this->root, lowLevel);
//    Node *high = findNode(this->root, highLevel);
//    int numsOfFakeLevels = 0; //in order to reduce them from the count
//    bool removeLow=false;
//    bool removeHigh=false;
//    if (low == nullptr) {
//       // if(score_invalid==true)
//        //{
//            this->insert(lowLevel, 0); //will add a fake level with score //may throw bad alloc
//                                      //we use 0 because score 0 is invalid score
//            low = findNode(this->root, lowLevel); //low point to the fake level
//            numsOfFakeLevels++;
//            removeLow=true;
//       // }
////        else
////        {
////            this->insert(lowLevel, score); //will add a fake level with score //may throw bad alloc
////            low = findNode(this->root, lowLevel); //low point to the fake level
////            numsOfFakeLevels++;
////            removeLow=true;
////        }
//    }
//    if (high == nullptr) {
//        if( low_high_same==true) //no need to insert two- will make problems because insert  first remove
//        {
//            high=low;
//        }
//        else
//        {
//         //   if(score_invalid==true)
//           // {
//                this->insert(highLevel, 0); //will add a fake level with score
//                high = findNode(this->root, highLevel); //high point to the fake level
//                numsOfFakeLevels++;
//                removeHigh=true;
//            //}
////            else
////            {
////                this->insert(highLevel, score); //will add a fake level with score
////                high = findNode(this->root, highLevel); //high point to the fake level
////                numsOfFakeLevels++;
////                removeHigh=true;
////            }
//        }
//
//    }
//    if (lowLevel == highLevel) {
//        if (score <= 0 || score > this->scale) //numOfPeopleWithScore==0
//        {
//            numOfPeopleBetweenBounds += low->numPeopleAtLevel - numsOfFakeLevels;
//            *error = (numOfPeopleBetweenBounds == 0) ? -1 : 0;
//            if(removeLow==true)
//            {
//                this->remove(lowLevel,score);
//            }
//            if(removeHigh==true)
//            {
//                this->remove(highLevel,score);
//            }
//            return 0;
//        }
//        else //score is a valid num
//        {
//            numOfPeopleBetweenBounds += low->numPeopleAtLevel - numsOfFakeLevels;
//            numOfPeopleWithScore += low->groupScoreArr[score]; // - numsOfFakeLevels;
//            if (numOfPeopleBetweenBounds == 0)
//            {
//                if(removeLow==true)
//                {
//                    this->remove(lowLevel,score);
//                }
//                if(removeHigh==true)
//                {
//                    this->remove(highLevel,score);
//                }
//                *error = -1;
//                return 0;
//            }
//            else
//            {
//                if(removeLow==true)
//                {
//                    this->remove(lowLevel,score);
//                }
//                if(removeHigh==true)
//                {
//                    this->remove(highLevel,score);
//                }
//                *error=0;
//                return (((double) numOfPeopleWithScore) / ((double) numOfPeopleBetweenBounds))*100;
//
//            }
//        }
//    } else //low and high are not the same node
//    {
//        Node* commonFather = getCommonFather(low, high, root);
//        int numOfPlayersAtCommonFatherSubTree=commonFather->numPeopleAtSubTree;
//        int numOfPlayersUnderLow=(low->left== nullptr)?0:low->left->numPeopleAtSubTree;
//        int numOfPlayersAboveHigh=(high->right== nullptr)?0:high->right->numPeopleAtSubTree;
//        numOfPeopleBetweenBounds+=numOfPlayersAtCommonFatherSubTree-numOfPlayersAboveHigh
//                -numOfPlayersUnderLow-numsOfFakeLevels;
//        if (score <= 0 || score > this->scale) //numOfPeopleWithScore==0 (score is invalid)
//        {
//            if(removeLow==true)
//            {
//                this->remove(lowLevel,score);
//            }
//            if(removeHigh==true)
//            {
//                this->remove(highLevel,score);
//            }
//                *error = (numOfPeopleBetweenBounds == 0) ? -1 : 0;
//                return 0;
//        }
//        else //score is valid
//        {
//            int numWithScoreAtCommonFatherSubTree=commonFather->subTreeGroupScoreArr[score];
//            int numWithScoreUnderLow=(low->left== nullptr)?0:low->left->subTreeGroupScoreArr[score];
//            int numWithScoreAboveHigh=(high->right== nullptr)?0:high->right->subTreeGroupScoreArr[score];
//            numOfPeopleWithScore+=numWithScoreAtCommonFatherSubTree-numWithScoreAboveHigh
//                    -numWithScoreUnderLow; //-numsOfFakeLevels;
//            if(numOfPeopleBetweenBounds==0)
//            {
//                if(removeLow==true)
//                {
//                    this->remove(lowLevel,score);
//                }
//                if(removeHigh==true)
//                {
//                    this->remove(highLevel,score);
//                }
//                *error=-1;
//                return 0;
//            }
//            else
//            {
//                if(removeLow==true)
//                {
//                    this->remove(lowLevel,score);
//                }
//                if(removeHigh==true)
//                {
//                    this->remove(highLevel,score);
//                }
//                *error=0;
//                return 100*(((double)numOfPeopleWithScore)/((double)numOfPeopleBetweenBounds));
//            }
//        }
//    }
//}

//helper func for getPrecentOfPlayersWithScoreBetweenBounds-sum from root until HighLevel
void AvlRankTree::sumUntilReachHighLevel(Node* start,int highLevel, int* with_score,int* in_range,int score)
{
    if(start->level==highLevel) //we already counted before calling this function
    {
        *with_score=0;
        *in_range=0;
        return;
    }
    else
    {
        int in_range_temp=0;
        int with_score_temp=0;
        Node* curr=start;
        while(curr!= nullptr) // like while(1)- we stop before reaching null
        {
            if(curr->level < highLevel)
            {
                if(curr != start)
                {
                    in_range_temp+=(curr->left== nullptr)?0:curr->left->numPeopleAtSubTree;
                    in_range_temp+=curr->numPeopleAtLevel;
                    if(score>0 && score<=this->scale) //valid
                    {
                     with_score_temp+=curr->groupScoreArr[score];
                     with_score_temp+=(curr->left== nullptr)?0:curr->left->subTreeGroupScoreArr[score];
                    }
                }
                curr=curr->right; //exist because the path to the highLevel exist
            }
            else if(curr->level > highLevel)
            {
//                in_range_temp+=curr->numPeopleAtLevel;
//                if(score>0 && score<=this->scale)
//                {
//                    with_score_temp+=curr->groupScoreArr[score];
//                }
                curr=curr->left; //exist because the path to the highLevel exist
            }
            else if(curr-> level == highLevel) //found
            {
                in_range_temp+=curr->numPeopleAtLevel;
                in_range_temp+=(curr->left== nullptr)?0:curr->left->numPeopleAtSubTree;
                if(score>0 && score<=this->scale) //valid
                {
                    with_score_temp+=curr->groupScoreArr[score];
                    with_score_temp+=(curr->left== nullptr)?0:curr->left->subTreeGroupScoreArr[score];
                }
                *with_score=with_score_temp;
                *in_range=in_range_temp;
                return;
            }
        }
    }
}

//helper func for getPrecentOfPlayersWithScoreBetweenBounds-sum from root until lowLevel
void AvlRankTree::sumUntilReachLowLevel(Node* start,int lowLevel, int* with_score,int* in_range,int score)
{
    if(start->level==lowLevel) //we already counted before calling this function
    {
        *with_score=0;
        *in_range=0;
        return;
    }
    else
    {
        int in_range_temp=0;
        int with_score_temp=0;
        Node* curr=start;
        while(curr != nullptr) // like while(1)- we stop before reaching null
        {
            if(curr->level > lowLevel)
            {
                if(curr != start)
                {
                    in_range_temp+=(curr->right== nullptr)?0:curr->right->numPeopleAtSubTree;
                    in_range_temp+=curr->numPeopleAtLevel;
                    if(score>0 && score<=this->scale) //valid
                    {
                        with_score_temp+=curr->groupScoreArr[score];
                        with_score_temp+=(curr->right== nullptr)?0:curr->right->subTreeGroupScoreArr[score];
                    }
                }
                curr=curr->left; //exist because the path to the lowLevel exist
            }
            else if(curr->level < lowLevel)
            {
                curr=curr->right; //exist because the path to the highLevel exist
                //nothing to sum
            }
            else if(curr-> level == lowLevel) //found
            {
                in_range_temp+=curr->numPeopleAtLevel;
                in_range_temp+=(curr->right== nullptr)?0:curr->right->numPeopleAtSubTree;
                if(score>0 && score<=this->scale) //valid
                {
                    with_score_temp+=curr->groupScoreArr[score];
                    with_score_temp+=(curr->right== nullptr)?0:curr->right->subTreeGroupScoreArr[score];
                }
                *with_score=with_score_temp;
                *in_range=in_range_temp;
                return;
            }
        }
    }
}

double AvlRankTree::getPrecentOfPlayersWithScoreBetweenBounds(int score,int lowLevel,int highLevel,
                                                              int* error, int numPeopleAtZero, int numPeopleAtZeroWithScore)
{
    bool score_is_valid=(score<=0 || score>scale)?false:true;
    bool low_high_same_level=(lowLevel==highLevel)?true:false;
    int num_people_in_range=0;
    int num_people_with_score=0;
    if(numPeopleAtZero!=0 && highLevel>=0) //level 0 may be between the range , if we insert it, we will count it
    {
        Node* level_zero= createNode(0);
        level_zero->numPeopleAtLevel=numPeopleAtZero;
        if(score_is_valid)
        {
            level_zero->groupScoreArr[score]=numPeopleAtZeroWithScore; //may be zero
        }
        root=insertNode(level_zero,root, nullptr); //insert and update
                                                             //the root if needed
        if(low_high_same_level) //num people in range= num people at level low=high
        {
            Node *low = findNode(root, lowLevel);
            if (low == nullptr) //there are 0 people in the range in the tree
            {
                root = deleteNode(root, level_zero);
                *error = -1;
                return 0;
            }
            else //low isnt null-the level is in the tree and there is at least one person in range
            {
                num_people_in_range = low->numPeopleAtLevel;
                if (score_is_valid) {
                    num_people_with_score = low->groupScoreArr[score];
                }
                *error = 0;
                root = deleteNode(root, level_zero);
                double val = 100 * ((double(num_people_with_score)) / (double(num_people_in_range)));
                return val;
            }
        }
        else //low and high are not the same level
        {
            Node* low= findNode(root,lowLevel);
            Node* high= findNode(root,highLevel);
            int num_of_fake_levels=0;
            bool remove_fake_low=false;
            bool remove_fake_high=false;
            if(low== nullptr)
            {
                insert(lowLevel,0); //we insert a fake level with invalid score [0]
                low= findNode(root,lowLevel);
                num_of_fake_levels++;
                remove_fake_low=true;
            }
            if(high== nullptr)
            {
                insert(highLevel,0); //we insert a fake level with invalid score [0]
                high= findNode(root,highLevel);
                low= findNode(root,lowLevel); //the way we roll may change it
                num_of_fake_levels++;
                remove_fake_high=true;
            }
            Node* commonParent= getCommonFather(low,high,root);
            //high and low are different levels so the common father can't be null (it can be
            //some other node (like level 0 we inserted) or one of them)
            num_people_in_range=commonParent->numPeopleAtLevel;
            num_people_with_score=(score_is_valid)?commonParent->groupScoreArr[score]:0;
            int in_range_high=0;
            int with_score_high=0;
            sumUntilReachHighLevel(commonParent,highLevel, &with_score_high,&in_range_high,score);
            int in_range_low=0;
            int with_score_low=0;
            sumUntilReachLowLevel(commonParent,lowLevel, &with_score_low,&in_range_low,score);
             num_people_in_range=num_people_in_range+in_range_high+in_range_low-num_of_fake_levels;
             num_people_with_score=num_people_with_score+with_score_high+with_score_low;
            if(num_people_in_range==0)
            {
                if(remove_fake_high==true)
                {
                    remove(highLevel,0);
                }
                if(remove_fake_low==true)
                {
                    remove(lowLevel,0);
                }
                root = deleteNode(root, level_zero);
                *error=-1;
                return 0;
            }
            else
            {
                if(remove_fake_high==true)
                {
                    remove(highLevel,0);
                }
                if(remove_fake_low==true)
                {
                    remove(lowLevel,0);
                }
                root = deleteNode(root, level_zero);
                *error=0;
                double val=100*((double(num_people_with_score))/(double(num_people_in_range)));
                return val;
            }
        }
    }
    else //no need to insert level 0
    {
        if(low_high_same_level) //num people in range= num people at level low=high
        {
            Node *low = findNode(root, lowLevel);
            if (low == nullptr) //there are 0 people in the range in the tree
            {
                *error = -1;
                return 0;
            }
            else //low isnt null-the level is in the tree and there is at least one person in range
            {
                num_people_in_range = low->numPeopleAtLevel;
                if (score_is_valid) {
                    num_people_with_score = low->groupScoreArr[score];
                }
                *error = 0;
                double val = 100 * ((double(num_people_with_score)) / (double(num_people_in_range)));
                return val;
            }
        }
        else //low and high are not the same level
        {
            Node* low= findNode(root,lowLevel);
            Node* high= findNode(root,highLevel);
            int num_of_fake_levels=0;
            bool remove_fake_low=false;
            bool remove_fake_high=false;
            if(low== nullptr)
            {
                insert(lowLevel,0); //we insert a fake level with invalid score [0]
                low= findNode(root,lowLevel);
                num_of_fake_levels++;
                remove_fake_low=true;
            }
            if(high== nullptr)
            {
                insert(highLevel,0); //we insert a fake level with invalid score [0]
                high= findNode(root,highLevel);
                low= findNode(root,lowLevel); //the way we roll may change it
                num_of_fake_levels++;
                remove_fake_high=true;
            }
            Node* commonParent= getCommonFather(low,high,root);
            //high and low are different levels so the common father can't be null (it can be
            //some other node or one of them)
            num_people_in_range=commonParent->numPeopleAtLevel;
            num_people_with_score=(score_is_valid)?commonParent->groupScoreArr[score]:0;
            int in_range_high=0;
            int with_score_high=0;
            sumUntilReachHighLevel(commonParent,highLevel, &with_score_high,&in_range_high,score);
            int in_range_low=0;
            int with_score_low=0;
            sumUntilReachLowLevel(commonParent,lowLevel, &with_score_low,&in_range_low,score);
            num_people_in_range=num_people_in_range+in_range_high+in_range_low-num_of_fake_levels;
            num_people_with_score=num_people_with_score+with_score_high+with_score_low;
            if(num_people_in_range==0)
            {
                if(remove_fake_high==true)
                {
                    remove(highLevel,0);
                }
                if(remove_fake_low==true)
                {
                    remove(lowLevel,0);
                }
                *error=-1;
                return 0;
            }
            else
            {
                if(remove_fake_high==true)
                {
                    remove(highLevel,0);
                }
                if(remove_fake_low==true)
                {
                    remove(lowLevel,0);
                }
                *error=0;
                double val=100*((double(num_people_with_score))/(double(num_people_in_range)));
                return val;
            }
        }
    }
}
int AvlRankTree::getTotalNumPeopleAtTree() const
{
    return (root== nullptr)?0:root->numPeopleAtSubTree;
}

int AvlRankTree::getSumOfHighestMPlayerLevel(int sum,int m,Node* node)
{
    if(node->right!= nullptr)
    {
        if(node->right->numPeopleAtSubTree>=m)
        {
            return getSumOfHighestMPlayerLevel(sum ,m,node->right);
        }
        else
        {  //take all the right tree and see how much you can take from node
            sum+=node->right->sumOfLevelsInSubTree;
            m=m-node->right->numPeopleAtSubTree;
            if(node->numPeopleAtLevel>=m)  //m can be zero now- no problem
            {
                sum+=m*(node->level);
                return sum;
            }
            else
            {
                sum+=(node->level)*(node->numPeopleAtLevel);
                m=m-node->numPeopleAtLevel;
                return getSumOfHighestMPlayerLevel(sum,m,node->left); //node->left exist
                                                              //because m>= num people at three
            }
        }
    }
    else
    {
        if(node->numPeopleAtLevel>=m)
        {
            sum+=(node->level)*m;
            return sum;
        }
        else
        {
            sum+=(node->level)*(node->numPeopleAtLevel);
            m=m-node->numPeopleAtLevel;
            return getSumOfHighestMPlayerLevel(sum,m,node->left); //node->left surly exist
        }
    }
}

AvlRankTree::Node* AvlRankTree::getRoot() const
{
    return this->root;
}







