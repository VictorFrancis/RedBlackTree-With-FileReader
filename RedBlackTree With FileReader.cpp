#include<iostream>
#include<queue>
#include<fstream>


using namespace std;

enum Color{RED,BLACK};

struct Node{

    int data;
    Node *parent;
    Node *left;
    Node *right;
    bool color;

    //constructor for simply initialzing data, roots,left and right child

    Node(int data){

        this->data=data;
        parent=NULL;
        left=NULL;
        right=NULL;

    }


};

class RedBlackTree{

public:

    Node *root;

    RedBlackTree(){

        root=NULL;

    }

    //function to insert a new node into BST
    Node* BSTInsert(Node* root, Node *currentNodePointer){

    //if the tree is empty and it is the first node to be inserted, we return the inserted node itself
        if(root==NULL){
            return currentNodePointer;
        }

        //Recursing down the tree by checking all the left side of the tree until it finally recurse to root
        if(currentNodePointer->data < root->data){

            root->left = BSTInsert(root->left, currentNodePointer);
            root->left->parent = root;
        }

        else if(currentNodePointer->data > root->data){

            root->right = BSTInsert(root->right, currentNodePointer);
             //we are directly finding the finding the root's right child 's root and making it the current root
            root->right->parent = root;

        }

        //returns the node pointer
        return root;

    }

    void Insert(int data){

        Node *currentNodePointer = new Node(data);

        //regular insertion to a BST
        root=BSTInsert(root, currentNodePointer);

        //fixing Red Black Tree Violation
        FixViolation(root, currentNodePointer);

    }
    void InOrder(){

        inOrderHelper(root);
    }

    //a recursive function to do inorder traversal

    void inOrderHelper(Node *root){

        if(root==NULL){
            return;
        }

            inOrderHelper(root->left);
            cout<<root->data<<" ";
            inOrderHelper(root->right);
        }



    void LevelOder(){

        levelOrderHelper(root);
    }

    //a recursive function to do level order traversal

    void levelOrderHelper(Node *root){

        if(root==NULL){
            return;
        }

        queue<Node *> NodeQueue;
        NodeQueue.push(root);

        while(!NodeQueue.empty()){

            Node *temp = NodeQueue.front();
            cout<<temp->data<<" ";
            NodeQueue.pop();

            if(temp->left!=NULL){
                NodeQueue.push(temp->left);
            }

            if(temp->right!=NULL){
                NodeQueue.push(temp->right);
            }



        }


    }

    void RotateLeft(Node *&root, Node *&currentNodePointer){

        Node *right=currentNodePointer->right;

        currentNodePointer->right=right->left;

        if(currentNodePointer->right!=NULL){

            currentNodePointer->right->parent=currentNodePointer;
        }
        right->parent=currentNodePointer->parent;

        if(currentNodePointer->parent==NULL){

            root=right;
        }

        else if(currentNodePointer==currentNodePointer->parent->left){

            currentNodePointer->parent->left=right;
        }

        else{

            currentNodePointer->parent->right=right;
        }

        right->left=currentNodePointer;
        currentNodePointer->parent=right;

    }

    void RotateRight(Node *&root, Node *&currentNodePointer){

        Node *left=currentNodePointer->left;
        currentNodePointer->left=currentNodePointer->right;

        if(currentNodePointer->left!=NULL){

            currentNodePointer->left->parent=currentNodePointer;

        }
        left->parent=currentNodePointer->parent;

        if(currentNodePointer->parent==NULL){
            root=left;
        }

        else if(currentNodePointer=currentNodePointer->parent->left){

            currentNodePointer->parent->left=left;
        }

        else{
            currentNodePointer->parent->right=left;
        }

        left->right=currentNodePointer;
        currentNodePointer->parent=left;



    }

    void FixViolation(Node *&root, Node *&currentNodePointer){

        Node *parent=NULL;
        Node *grand_parent=NULL;

        while((currentNodePointer!=root) &&
              (currentNodePointer->color!=BLACK) &&
              (currentNodePointer->parent->color==RED)){

                parent=currentNodePointer->parent;
                grand_parent=currentNodePointer->parent->parent;

                //Case 1: Parent of currentNode is left child of Grand-parent of currentNode

                if(parent==grand_parent->left){

                    Node *uncle=grand_parent->right;

                    //when the uncle of current node is also red
                    //we will only recolor

                    if(uncle!=NULL && uncle->color==RED){

                        grand_parent->color=RED;
                        parent->color=BLACK;
                        uncle->color=BLACK;
                        currentNodePointer=grand_parent;
                    }
                    else{

                        //Case 2: current node is left child of its parent
                        //we will rotate left

                        if(currentNodePointer=parent->right){

                            RotateLeft(root, parent);
                            currentNodePointer=parent;
                            parent=currentNodePointer->parent;
                        }

                        //Case 3: currentNode is left child of its parent
                        //we will rotate right

                        RotateRight(root, grand_parent);
                        swap(parent->color, grand_parent->color);
                        currentNodePointer=parent;
                    }
                }

                //Case: 4 parent of currentNode is right child of grand parent of current node

                else{

                    Node *uncle=grand_parent->left;

                    //Case 1: The uncle of currentNode is also red
                    //Only recoloring will be performed

                    if((uncle!=NULL)&&(uncle->color==RED)){

                        grand_parent->color=RED;
                        parent->color=BLACK;
                        uncle->color=BLACK;
                        currentNodePointer=grand_parent;
                    }
                    else{

                        // Case 2: current node is left child of its parent
                        //we will rotate right

                        if(currentNodePointer==parent->left){

                            RotateRight(root, parent);
                            currentNodePointer=parent;
                            parent=currentNodePointer->parent;
                        }

                        //Case 3: current Node is right child of its parent
                        //we will left rotation

                        RotateLeft(root, grand_parent);
                        swap(parent->color, grand_parent->color);
                        currentNodePointer=parent;

                    }
                }
        }

            root->color=BLACK;
    }



};

int main(){

RedBlackTree Tree;

int nodeInputData;
ifstream file;

file.open("rbtinput.txt");

try{

    if(file.is_open()){

        while(file>>nodeInputData){

            Tree.Insert(nodeInputData);

        }

    }

    else{

        throw -1;
    }


}

catch(int){

    cout<<"File not found"<<endl;
}

cout << "Inoder Traversal of Created Tree"<<endl;
Tree.InOrder();
cout<<endl;

cout<<endl;
cout << "Level Order Traversal of Created Tree"<<endl;
Tree.LevelOder();
cout<<endl;


return 0;
}
