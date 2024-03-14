#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int MAX_VERTEX_NUM = 71;
const int SOURCE = -1;
const int NORMAL = 0;
const int TARGET = -2;
const int NOTCONNECTED = -3;

class Vertex {
   private:
    int index;
    int state;
    int label;
    struct Edge {
        int time;
        Vertex* next;
    };
    vector<Edge> edge;

   public:
    Vertex() {
        state = SOURCE;
        edge.clear();
        label = 0;
    };
    void addEdge(Vertex*, int); // des, weight
    void findTargetAndNotconnect();
    int getIndex();
    void setIndex(int);
    void setState(int);
    int getState();
    void setLabel(int);
    int getLabel();
    Vertex* getOKNext();
    bool NextHave(Vertex*);
    int getEdgeTime(Vertex*);
    bool operator!=(const Vertex);
};

class graph {
   private:
    Vertex vertex[MAX_VERTEX_NUM];
    void clearAllLabel() {
        for (int i = 0; i < MAX_VERTEX_NUM; i++) {
            vertex[i].setIndex(i);
            vertex[i].setLabel(0);
        }
    }
    vector<Vertex*> getShortestPath(Vertex* str, Vertex* des) {
        vector<Vertex*> path;
        int i = 0;
        path.push_back(des);
        while (path.back() != str) {
            for (int j = 0; j < MAX_VERTEX_NUM; j++) {
                if (vertex[j].NextHave(path.back()) &&
                    path.back()->getLabel() -
                            vertex[j].getEdgeTime(path.back()) ==
                        vertex[j].getLabel()) {
                    i++;
                    path.push_back(&vertex[j]);
                }
            }
        }
        return path;
    }

   public:
    void setEdge(int, int, int); // str, des, weight
    void setVertexState();
    vector<Vertex*> findShortestPath();
};

int main(int agrc, char* argv[]) {
    FILE* fp = fopen(argv[1], "r");
    if (fp == nullptr) {
        cout << "Open file fail." << endl;
        exit(1);
    }
    graph network;
    int str, des, time;
    char useless_words[7];
    char useless_letter;
    while (fscanf(fp, "%d", &str) != EOF) {
        fscanf(fp, "%s %d %c %s %c %d", useless_words, &des, &useless_letter,
               useless_words, &useless_letter, &time);
        network.setEdge(str, des, time);
    }
    fclose(fp);

    network.setVertexState();
    vector<Vertex*> shortestPath = network.findShortestPath();
    if (shortestPath.empty()) {
        cout << "No Path!" << endl;
        exit(1);
    }

    FILE* outfp = fopen(argv[2], "w");
    fprintf(outfp, "Shortest Path Length:\n");
    fprintf(outfp, "%d\n", shortestPath.front()->getLabel());
    fprintf(outfp, "Shortest Path:\n");
    for (int i = shortestPath.size() - 1; i >= 0; i--) {
        fprintf(outfp, "%d", shortestPath[i]->getIndex());
        if (i != 0) {
            fprintf(outfp, " -> ");
        }
    }
    fprintf(outfp, "\n");
    fclose(outfp);
    return 0;
}

void Vertex::addEdge(Vertex* des, int time) {
    Edge e{time, des};
    edge.push_back(e);
}

void Vertex::findTargetAndNotconnect() {
    if (edge.empty()) {
        if (state == SOURCE)
            state = NOTCONNECTED;
        else
            state = TARGET;
    }
}

void Vertex::setIndex(int id) { index = id; }

int Vertex::getIndex() { return index; }

void Vertex::setState(int st) { state = st; }

int Vertex::getState() { return state; }

void Vertex::setLabel(int lb) { label = lb; }

int Vertex::getLabel() { return label; }

Vertex* Vertex::getOKNext() {
    for (int i = 0; i < edge.size(); i++) {
        if(i == index) return nullptr;
        if (edge[i].next->label == 0 ||
            edge[i].next->label > label + getEdgeTime(edge[i].next)) {
            return edge[i].next;
        }
    }
    return nullptr;
}

bool Vertex::NextHave(Vertex* nt) {
    for (int i = 0; i < edge.size(); i++) {
        if (edge[i].next == nt) {
            return true;
        }
    }
    return false;
}

int Vertex::getEdgeTime(Vertex* next) {
    for (int i = 0; i < edge.size(); i++) {
        if (edge[i].next == next) return edge[i].time;
    }
    cout << "getTime Error!" << endl;
    exit(1);
    return 0;
}

bool Vertex::operator!=(const Vertex v) {
    return (v.index != index) ? true : false;
}

void graph::setEdge(int str, int des, int time) {
    vertex[str].addEdge(&vertex[des], time);
    vertex[des].setState(NORMAL);
}

void graph::setVertexState() {
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        vertex[i].findTargetAndNotconnect();
    }
}

vector<Vertex*> graph::findShortestPath() {
    int dist = 0;
    vector<Vertex*> shorest;
    shorest.clear();
    int shortest_Dist = 0;
    for (int i = 0; i < MAX_VERTEX_NUM; i++) {
        if (vertex[i].getState() != SOURCE) continue;
        for (int j = 0; j < MAX_VERTEX_NUM; j++) {
            if (vertex[j].getState() == TARGET && i != j) {
                clearAllLabel();
                int vertex_num = 0;
                queue<Vertex*> path;
                path.push(&vertex[i]);
                while (!path.empty()) {
                    Vertex* current = path.front();
                    path.pop();
                    dist = current->getLabel();
                    Vertex* next = current->getOKNext();
                    while (next != nullptr && next != path.back()) {
                        next->setLabel(dist + current->getEdgeTime(next));
                        path.push(next);
                        next = current->getOKNext();
                    }
                }
                if (vertex[j].getLabel() == 0) continue; // no reach

                if (shorest.empty() || vertex[j].getLabel() < shortest_Dist) {
                    shorest.clear();
                    shorest = getShortestPath(&vertex[i], &vertex[j]);
                    shortest_Dist = vertex[j].getLabel();
                }
            }
        }
    }
    if(!shorest.empty())
        shorest.front()->setLabel(shortest_Dist);
    return shorest;
}