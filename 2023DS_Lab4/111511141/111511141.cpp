#include <iostream>
#include <map>
#include <vector>
using namespace std;

class treeNode {
   private:
    int data;
    treeNode* parent;
    vector<treeNode*> child;

   public:
    treeNode();
    treeNode(int);
    void setData(int);
    int getData();
    void addChild(treeNode*);
    void setParent(treeNode*);
    vector<treeNode*> getChild();
    treeNode* getParnet();
};

class tree {
   private:
    treeNode* root;
    map<int, treeNode*> Node_map;

   public:
    tree();
    ~tree();
    bool addChild(int, int);
    bool IsEmpty();
    void setRoot(int);
    treeNode* getroot();
    int lowerest_commom_ancestor(int, int, int);
    // int getNodeHeight(int);
    // void print_tree();
};

struct edge {
    int A, B;
    bool IsUsed;
};

int main() {
    int N, Q, S, R;
    cin >> N >> Q >> S >> R;

    edge* road = new edge[N - 1]; // record road
    for (int i = 0; i < N - 1; i++) {
        cin >> road[i].A >> road[i].B;
        road[i].IsUsed = false;
    }

    int* query = new int[Q]; // record query
    for (int i = 0; i < Q; i++) {
        cin >> query[i];
    }

    for (int count_Q = 0; count_Q < Q; count_Q++) {
        for (int i = 0; i < N - 1; i++) {
            road[i].IsUsed = false;
        }
        tree C_root;
        C_root.setRoot(query[count_Q]);
        int RoadOKnum = 0;
        int roadnum = 0;
        while (RoadOKnum < N - 1) {
            if (!(road[roadnum].IsUsed) &&
                C_root.addChild(road[roadnum].A, road[roadnum].B)) {
                RoadOKnum++;
                road[roadnum].IsUsed = true;
            }
            roadnum = (roadnum + 1) % (N - 1);
        }
        cout << C_root.lowerest_commom_ancestor(R, S, N) << endl;
        C_root.~tree(); // delete map
    }

    delete[] road;  // delete road
    delete[] query; // delete query
    return 0;
}

treeNode::treeNode() { parent = nullptr; };
treeNode::treeNode(int ini_data) {
    data = ini_data;
    parent = nullptr;
}
void treeNode::setData(int input) { data = input; }
int treeNode::getData() { return data; }
void treeNode::addChild(treeNode* ch) { child.push_back(ch); }
void treeNode::setParent(treeNode* pr) { parent = pr; }
vector<treeNode*> treeNode::getChild() { return child; }
treeNode* treeNode::getParnet() { return parent; }

tree::tree() { root = nullptr; }
tree::~tree() { Node_map.clear(); }
bool tree::IsEmpty() {
    if (root == nullptr) return true;
    return false;
}
bool tree::addChild(int A, int B) {
    treeNode* node_A = new treeNode;
    treeNode* node_B = new treeNode;
    node_A->setData(A);
    node_B->setData(B);
    if (Node_map.find(A) == Node_map.end() &&
        Node_map.find(B) == Node_map.end()) {
        return false;
    }
    map<int, treeNode*>::iterator itr;
    for (itr = Node_map.begin(); itr != Node_map.end(); itr++) {
        if (itr->second->getData() == A) {
            if (node_B->getParnet() != nullptr) {
                cout << "AddChild Error!" << endl;
                exit(1);
            }
            Node_map[A]->addChild(node_B);
            Node_map[B] = node_B;
            Node_map[B]->setParent(Node_map[A]);
            return true;
        } else if (itr->second->getData() == B) {
            if (node_A->getParnet() != nullptr) {
                cout << "AddChild Error!" << endl;
                exit(1);
            }
            Node_map[B]->addChild(node_A);
            Node_map[A] = node_A;
            Node_map[A]->setParent(Node_map[B]);
            return true;
        }
    }
    cout << "FIND ERROR!!!!!!!!!!!!!!!!!!!" << endl;
    return false;
}
void tree::setRoot(int rt) {
    treeNode* newnode = new treeNode;
    root = newnode;
    root->setData(rt);
    root->setParent(nullptr);
    treeNode* forrt = new treeNode;
    forrt->setData(rt);
    Node_map[rt] = forrt;
    return;
}

treeNode* tree::getroot() { return root; }

int tree::lowerest_commom_ancestor(int A, int B, int N) {
    treeNode* nodeA = Node_map[A];
    treeNode* nodeB = Node_map[B];
    bool* check_anc = new bool[N + 1];
    for(int i = 0 ; i < N + 1; i++){
        check_anc[i] = false;
    }
    while(nodeA != nullptr){
        check_anc[nodeA->getData()] = true;
        nodeA = nodeA->getParnet();
    }
    while(nodeB != nullptr){
        if(check_anc[nodeB->getData()]){
            return nodeB->getData();
        }
        nodeB = nodeB->getParnet();
    }
    cout << "No commom ancestor, Error." << endl;
    return -1;
}

/* int tree::getNodeHeight(int num) {
    if (Node_map.find(num) != Node_map.end()) {
        treeNode* ptr = Node_map.find(num)->second;
        int Height = -1;
        while (ptr != nullptr) {
            ptr = ptr->getParnet();
            Height++;
        }
        return Height;
    }
    cout << "can't find node!" << endl;
    exit(1);
}*/

/*void tree::print_tree() {
    cout << "root: " << root->getData() << endl;
    bool empty = true;
    for (int i = 0; i < Node_map.size(); i++) {
        empty = true;
        cout << i << ": ";
        for (int j = 1; j <= Node_map.size(); j++) {
            if (getNodeHeight(Node_map[j]->getData()) == i) {
                cout << Node_map[j]->getData() << " ";
                empty = false;
            }
        }
        cout << endl;
        if (empty) break;
    }
}*/
