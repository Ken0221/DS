#include <stdio.h>

#include <iostream>
using namespace std;

enum DIR { right = 0, down = 1, left = 2, up = 3 };

struct pos {
    int x;
    int y;
};

class Stack {
   private:
    struct Node {
        int data;
        Node* next;
    };
    Node* head;
    void Delete(Node**);

   public:
    Stack();
    ~Stack();
    bool IsEmpty() const;
    void push(const int&);
    int top() const;
    void pop();
};

int main() {
    char dir_name[4][6] = {"right", "down", "left", "up"}; // output direction
    int map_size = 0;
    cin >> map_size;
    // create map
    char** map = new char*[map_size];
    for (int i = 0; i < map_size; i++) {
        map[i] = new char[map_size];
    }
    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            cin >> map[i][j];
        }
    }

    pos start = {0, 1};
    pos dest = {map_size - 1, map_size - 2};
    pos dir[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // right, down, left, up

    Stack path;
    int** sym = new int*[map_size];
    for (int i = 0; i < map_size; i++) {
        sym[i] = new int[map_size];
    }
    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            if (map[i][j] == '.')
                sym[i][j] = 0;
            else
                sym[i][j] = 1;
        }
    }
    pos cur = start;
    sym[cur.x][cur.y] = -1;
    while (!(cur.x == dest.x && cur.y == dest.y)) {
        if (path.IsEmpty())
            cout << "Push " << dir_name[DIR::down] << " " << cur.x << " "
                 << cur.y << endl;
        int dir_count = -1;
        for (int i = 0; i < 4; i++) {
            if (cur.x + dir[i].x < map_size && cur.x + dir[i].x >= 0 &&
                cur.y + dir[i].y < map_size && cur.y + dir[i].y >= 0) {
                pos next = {cur.x + dir[i].x, cur.y + dir[i].y};
                if (sym[next.x][next.y] == 0) {
                    path.push(i);
                    cur = next;
                    sym[cur.x][cur.y] = -1;
                    cout << "Push " << dir_name[path.top()] << " " << cur.x
                         << " " << cur.y << endl;
                    dir_count = i;
                    break;
                }
            }
        }
        if (dir_count == -1) {
            if (path.IsEmpty()) {
                cout << "path not found" << endl;
                exit(1);
            }
            sym[cur.x][cur.y] = -2;
            cur.x -= dir[path.top()].x;
            cur.y -= dir[path.top()].y;
            cout << "Pop " << dir_name[path.top()] << " " << cur.x << " "
                 << cur.y << endl;
            path.pop();
        }
    }
    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            if (sym[i][j] == -1) map[i][j] = '+';
            cout << map[i][j];
        }
        cout << endl;
    }

    // delete map
    for (int i = 0; i < map_size; i++) {
        delete[] map[i];
    }
    delete[] map;

    for (int i = 0; i < map_size; i++) {
        delete[] sym[i];
    }
    delete[] sym;

    path.~Stack();

    return 0;
}

Stack::Stack() { head = nullptr; }

void Stack::Delete(Node** headRef) {
    Node* ptr = *headRef;
    Node* next;
    while (ptr != NULL) {
        next = ptr->next;
        delete ptr;
        ptr = next;
    }
    *headRef = NULL;
}

Stack::~Stack() { Delete(&head); }

bool Stack::IsEmpty() const {
    if (head == nullptr) {
        return true;
    }
    return false;
}

void Stack::push(const int& a) {
    Node* newNode = new Node;
    newNode->data = a;
    newNode->next = head;
    head = newNode;
}

int Stack::top() const { return head->data; }

void Stack::pop() {
    Node* ptr = head;
    head = head->next;
    delete ptr;
}