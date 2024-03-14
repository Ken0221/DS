#include <stdio.h>

#include <iostream>
using namespace std;
const int NULLNUM = -1;
const int ERROR_INDEX = -1;

class hashTable {
   private:
    int* hashT;
    int* dataIndex;
    int length;
    int size;
    int target;
    int hashfunciton(int data) {
        if (target % data == 0) {
            return (target / data);
        } else {
            int index = target % data;
            while (target % index == 0) {
                index++;
            }
            return index;
        }
    } // return index
    bool Iscollide(int index) {
        return (hashT[index] == NULLNUM) ? false : true;
    }
    void expandsize(int newsize) {
        int* newarr = new int[newsize];
        for (int i = 0; i < newsize; i++) {
            if (i < size) {
                newarr[i] = hashT[i];
            } else {
                newarr[i] = NULLNUM;
            }
        }
        delete[] hashT;
        hashT = newarr;

        int* newindexarr = new int[newsize];
        for (int i = 0; i < newsize; i++) {
            if (i < size) {
                newindexarr[i] = dataIndex[i];
            } else {
                newindexarr[i] = NULLNUM;
            }
        }
        delete[] dataIndex;
        dataIndex = newindexarr;

        size = newsize;
    }

   public:
    hashTable();
    ~hashTable();
    void setTarget(int);
    void insert(const int, const int);
    int search(int);
    int getDataIndex(int);
};

int main(int argc, char* argv[]) {
    int target;
    hashTable ht;
    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        cout << "Can't open file." << endl;
        exit(1);
    }
    fscanf(fp, "%d", &target);
    ht.setTarget(target);
    int dataindex = 0;
    int arr_data;
    while (fscanf(fp, "%d", &arr_data) != EOF) {
        ht.insert(arr_data, dataindex);
        dataindex++;
    }
    fclose(fp);

    int fac_num = 0;
    for (int i = 1; i * i <= target; i++) {
        if (target % i == 0) {
            fac_num++;
            if (i != target % i) {
                fac_num++;
            }
        }
    }

    int* factor = new int[fac_num];
    int fac_i = 0;
    for (int i = 1; i < target / 2; i++) {
        if (target % i == 0) {
            factor[fac_i] = i;
            factor[fac_num - 1 - fac_i] = target / i;
            fac_i++;
            if (fac_i >= fac_num) {
                cout << "factor number error!" << endl;
                exit(1);
            }
        }
    }

    int ans1 = NULLNUM, ans2 = NULLNUM;
    for (int i = 0; i < fac_num; i++) {
        if (ht.search(factor[i]) == target / factor[i] &&
            ht.search(target / factor[i]) == factor[i]) {
            if ((ans1 == NULLNUM && ans2 == NULLNUM) ||
                (ans1 > ht.getDataIndex(factor[i]))) {
                ans1 = ht.getDataIndex(factor[i]);
                ans2 = ht.getDataIndex(target / factor[i]);
            }
        }
    }
    cout << ans1 << " " << ans2 << endl;

    delete[] factor;
    ht.~hashTable();
    return 0;
}

hashTable::hashTable() {
    size = 100;
    length = 0;
    hashT = new int[size];
    for (int i = 0; i < size; i++) {
        hashT[i] = NULLNUM;
    }
    dataIndex = new int[size];
    for (int i = 0; i < size; i++) {
        dataIndex[i] = NULLNUM;
    }
}

hashTable::~hashTable() {}

void hashTable::setTarget(int t) { target = t; }

void hashTable::insert(const int data, const int dataindex) {
    int index = hashfunciton(data);
    if (size <= length) {
        expandsize(2 * size);
    }
    if (index < size) {
        while (Iscollide(index)) {
            do {
                index++;
            } while (target % index == 0);
        }
    }
    if (index >= size) {
        expandsize(2 * index);
    }
    hashT[index] = data;
    dataIndex[index] = dataindex;
    length++;
}

int hashTable::search(int data) {
    int index = hashfunciton(data);
    while (hashT[index] != data) {
        index++;
        if (index >= size) {
            return ERROR_INDEX;
        }
    }
    return index;
}

int hashTable::getDataIndex(int data) { return dataIndex[search(data)]; }