#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <queue>
#include <math.h>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

class TreeInfo {
public:
    int h;
    int  d;

    TreeInfo(int he, int di) {
        h = he;
        d = di;
    }
};

class BinaryTree {
public:
    int i;
    BinaryTree(){
        i = -1;
    }
    Node* buildtree(vector<int> &a) {
        i++;
        if(a[i] == -1) {
            return NULL;
        }

        Node* newNode = new Node(a[i]);
        newNode->left = buildtree(a);
        newNode->right = buildtree(a);

        return newNode;
    }

    void leaves(Node* root) {
        if (root==NULL) {
            return;
        }
        if (root->left == NULL && root->right == NULL) {
            cout<<root->data<<" ";
            return;
        } else {
            leaves(root->left);
            leaves(root->right);
            return;
        }
    }

    void inorder(Node* root) {
        if (root == NULL) {
            return;
        }
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
    void postorder(Node* root) {
        if (root == NULL) {
            return;
        }
        postorder(root->left);
        postorder(root->right);
        cout<<root->data<<" ";
    }

    void levelorder(Node* root) {
        if (root == NULL) return;
        queue<Node*> q;
        q.push(root);
        q.push(NULL);

        while(!q.empty()) {
            Node* curr = q.front();
            q.pop();
            if (curr == NULL) {
                cout<<endl;
                if (q.empty()) {
                    break;
                } else {
                    q.push(NULL);
                }
            } else {
                cout<<curr->data<<" ";
                if (curr->left != NULL) {
                    q.push(curr->left);
                }
                if (curr-> right != NULL) {
                    q.push(curr->right);
                }
            }
        }
    }

    int numberNodes(Node* root) {
        int count = 0;

        if (root == NULL) {
            return 0;
        }

        count += numberNodes(root->left);
        count += numberNodes(root->right);
        count += 1;
        return count;
    }

    int sumNodes(Node* root) {
        if (root == NULL) return 0;

        int sum = 0;

        sum += sumNodes(root->left);
        sum += sumNodes(root->right);

        return sum + root->data;
    }

    int height(Node* root) {
        if (root == NULL) return 0;

        int h = 1;
        int h1 = height(root->left);
        int h2 = height(root->right);

        if (h1 > h2) return (h+h1);
        else return (h+h2);
    }

    int diameter(Node* root) { //O(N^2)
        if (root == NULL) return 0;

        int d1 = diameter(root->left);
        int d2 = diameter(root->right);
        int d3 = height(root->left) + height(root->right) + 1;

        return max(d1, max(d2, d3));
    }

    TreeInfo* diameter2(Node* root) { //O(N)
        if (root == NULL) {
            TreeInfo* ans = new TreeInfo(0, 0);
            return ans;
        }

        TreeInfo* left = diameter2(root->left);
        TreeInfo* right = diameter2(root->right);

        int myHeight = max(left->h, right->h) + 1;

        int dia1 = left->d;
        int dia2 = right->d;
        int dia3 = left->h + right->h + 1;

        int myDia = max(max(dia1, dia2), dia3);

        TreeInfo* ans = new TreeInfo(myHeight, myDia);

        return ans;
    }
    int isEqual(Node* r1, Node* r2) {
        if (r1 == NULL && r2 == NULL) return 1;
        if (r1 == NULL || r2 == NULL) return 0;

        if (r1->data != r2->data) return 0;
        else {
            return isEqual(r1->left, r2->left) && isEqual(r1->right, r2->right);
        }
    }

    bool isSubtree(Node* root, Node* subroot) {
        if (subroot == NULL) return true;
        if (root == NULL) return false;

        if (root->data == subroot->data) {
            if (isEqual(root, subroot)) return true;
            else return false;
        } else {
            return (isSubtree(root->left, subroot) || isSubtree(root->right, subroot));
        }
    }
};

class BinarySearchTree {
public:
    Node* buildBST(Node* root, int val) {
        if (root == NULL) {
            root = new Node(val);
            return root;
        }

        if (root->data > val) {
            root->left = buildBST(root->left, val);
        } else {
            root->right = buildBST(root->right, val);
        }
        return root;
    }

    bool searchBST(Node* root, int key) {
        if (root == NULL) {
            return false;
        }

        if (root->data > key) {
            return searchBST(root->left, key);
        } else if (root->data == key) {
            return true;
        } else {
            return searchBST(root->right, key);
        }
    }
    Node* inorderSUCC(Node* root) {
        if (root->left == NULL) {
            return root;
        }

        return root->left;
    }
    Node* deleteNODE(Node* root, int val) {
        if (root == NULL) {
            return root;
        }

        if (root->data > val) {
            root->left = deleteNODE(root->left, val);
        } else if (root->data == val) {
            if (root->left == NULL && root->right == NULL) {
                root = NULL;
            } else if (root->left == NULL) {
                root = root->right;
            } else if (root->right == NULL) {
                root = root->left;
            } else {
                root->data = inorderSUCC(root->right)->data;
                root->right = deleteNODE(root->right, inorderSUCC(root->right)->data);
            }
        } else {
            root->right = deleteNODE(root->right, val);
        }
        return root;
    }

    void PrintInRange(Node* root, int x, int y) {
        if (root == NULL) return;

        if (root->data >= x && root->data <=y) {
            PrintInRange(root->left, x, y); //this will give the numbers in ascending order
            cout<<root->data<<" ";
            PrintInRange(root->right, x, y);
        } else if (root->data < x) {
            PrintInRange(root->right, x, y);
        } else {
            PrintInRange(root->left, x, y);
        }
    }

    void PrintRootToLeaf(Node* root, vector<int> path) {
        if (root == NULL) return;

        path.push_back(root->data);
        if (root->left == NULL && root->right == NULL) {
            //leaf reached
            for(int i = 0; i<path.size(); i++){
                cout<<path[i]<<" ";
            }
            cout<<endl;
            path.pop_back();
        }

        PrintRootToLeaf(root->left, path);
        PrintRootToLeaf(root->right, path);
        path.pop_back();
    }
};

int main() {

    int len, temp; cin>>len;
    vector<int> nodes;

    for(int i = 0; i<len; i++) {
        cin>>temp;
        nodes.push_back(temp);
    }
    BinaryTree tree;
    Node* root = tree.buildtree(nodes);
    
    Node* n = new Node(2);
    n->right = new Node(5);
    n->left = new Node(4);

    tree.leaves(root);
    cout<<endl;
    tree.levelorder(root);
    cout<<tree.numberNodes(root)<<endl;
    cout<<tree.sumNodes(root)<<endl;
    cout<<tree.height(root)<<endl;
    cout<<tree.diameter(root)<<endl;
    cout<<tree.diameter2(root)->d<<endl;
    cout<<tree.isSubtree(root, n)<<endl;

    //Binary Search Tree
    int len2; cin>>len2;
    vector<int> bst(len2, 0);

    for(int i = 0; i<len2; i++) {
        cin>>bst[i];
    }
    BinarySearchTree tree2;
    Node* root2 = NULL;
    for(int i = 0; i<len2; i++) {
        root2 = tree2.buildBST(root2, bst[i]);
    }
    tree.inorder(root2);
    cout<<endl;
    cout<<tree2.searchBST(root2, 2)<<endl;
    cout<<tree2.searchBST(root2, 199)<<endl;
    root2 = tree2.deleteNODE(root2, 5);
    tree.inorder(root2);
    cout<<endl;
    root2 = tree2.deleteNODE(root2, 4);
    tree.inorder(root2);
    cout<<endl;
    tree2.PrintInRange(root2, 2, 3);
    cout<<endl;
    tree2.PrintInRange(root2, 1, 8);
    cout<<endl;


    BinarySearchTree tree3;
    Node* root3 = NULL;
    int len3; cin>>len3;
    vector<int> arr(len3);
    for(int i = 0; i<len3; i++) {
        cin>>arr[i];
    }
    for(int i = 0; i<len3; i++) {
        root3 = tree3.buildBST(root3, arr[i]);
    }
    vector<int> path;
    tree3.PrintRootToLeaf(root3, path);

    return 0;
}