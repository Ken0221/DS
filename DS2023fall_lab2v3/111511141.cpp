const int null_value = 0;
#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;

class List
{
private:
	class Node 
	{
	public:
		int data;
		Node* next;
	};
	Node head;
	int index = -1;
public:
	List();
	~List();
	List(const List& orgList);
	List& operator= (const List& orgList);
	bool empty() const;
	void Insertion(int, int);
	void Display(ostream&) const;
	List Addition(List&);
	List Subtraction(List&);
	List Multiplication(List&);
	int Evaluation(int);

};

ostream& operator<< (ostream & out, const List & aList);

int main(int argc, char* argv[]) {
    char input[100][100];
    int iin = 0;
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        cout << "Can not open file." << endl;
        exit(1);
    }
    while(fscanf(fp, "%s", input[iin]) != EOF) {
        //cout << input[iin] << endl;
        iin++;
    }
    fclose(fp);
	List poly1, poly2;
	int currpoly = 1;
	int x = 0;
	for (int i = 0; i < iin - 1; i++) {
		if (strcmp(input[i], "Poly1") == 0) { //poly1部分
			currpoly = 1;
			continue;
		}
		if (strcmp(input[i], "Poly2") == 0) { //poly2部分
			currpoly = 2;
			continue;
		}
		if (strcmp(input[i], "x") == 0) { //輸入x後停止
			x = atoi(input[i + 1]);
			break;
		}
		if (currpoly == 1) {
			poly1.Insertion(atoi(input[i]), atoi(input[i + 1]));
			i++;
		}
		else if (currpoly == 2) {
			poly2.Insertion(atoi(input[i]), atoi(input[i + 1]));
			i++;
		}
	}
    List temp1_add, temp1_sub, temp1_mul;
    temp1_add = poly1;
    temp1_sub = poly1;
    temp1_mul = poly1;

    List temp2_add, temp2_sub, temp2_mul;
    temp2_add = poly2;
    temp2_sub = poly2;
    temp2_mul = poly2;
	
    cout << "Polynomial 1: " << poly1 << endl;
	cout << "Polynomial 2: " << poly2 << endl;
    cout << "Addition: " << temp1_add.Addition(temp2_add) << endl;
    cout << "Subtraction: " << temp1_sub.Subtraction(temp2_sub) << endl;
    cout << "Multiplication: " << temp1_mul.Multiplication(temp2_mul) << endl;
    cout << "Evaluation of Polynomial 1 at x = " << x << " is: " <<  poly1.Evaluation(x) << endl;
    cout << "Evaluation of Polynomial 2 at x = " << x << " is: " <<  poly2.Evaluation(x) << endl;
    return 0;
} 

List::List() {
	head.data = null_value;
	head.next = NULL;
	index = -1;
}

List::~List() {
	Node* ptr = head.next;
    Node* next;
	while (ptr != NULL) {
		next = ptr->next;
		//delete ptr;
        ptr = next;
	}
	head.data = null_value;
	head.next = NULL;
	index = -1;
}

List::List(const List& orgList) {
    index = orgList.index;
    Node* ptr = &head;
    Node* orgptr = orgList.head.next;
    head.data = orgList.head.data;
    while (ptr->next == NULL && orgptr != NULL) {
        Node* newNode = new Node;
        newNode->data = orgptr->data;
        ptr->next = newNode;
        ptr = ptr->next;
        orgptr = orgptr->next;
    }

}

List& List::operator= (const List& orgList) {
	if (this != &orgList) {
        index = orgList.index;
        Node* ptr = &head;
        Node* orgptr = orgList.head.next;
        head.data = orgList.head.data;
		while (ptr->next == NULL && orgptr != NULL) {
            Node* newNode = new Node;
            newNode->data = orgptr->data;
            ptr->next = newNode;
            ptr = ptr->next;
            orgptr = orgptr->next;
		}
    }
    return *this;
}

bool List::empty() const {
	return (head.next == NULL) ? true : false;
}

void List::Insertion(int num, int pos) {
	if (index < pos) index = pos;
	Node* ptr = &head;

	if (pos == 0) {
		ptr->data = num;
		return;
	}
	int count = 1;
  	bool Isinsert = false;
   	while (!Isinsert) {
        while (ptr->next != NULL) {
        	if (pos == count) {
	    		ptr->next->data = num;
                Isinsert = true;
		    	break;
	    	}
	   		ptr = ptr->next;
	   		count++;
	   	}
   		if (!Isinsert) {
            Node* last = new Node;
    		last->data = 0;
    		last->next = NULL;
   			ptr->next = last;
   		}
    }
}

void List::Display(ostream& out) const {
	int count = index;
	while (count > 0) {
		Node* ptr = head.next;
		for (int i = 0; i < count - 1; i++) {
			ptr = ptr->next;
		}
		if (count == index) {
			out << ptr->data << "x^" << count;
		}
		else {
			if (ptr->data == 0) {
				count--;
				continue;
			}
			if (ptr->data > 0)
				out << " + ";
			else
				out << " - ";
			out << abs(ptr->data) << "x^" << count;
		}
		count--;
	}
	if (head.data == 0) 
		return;
	if (head.data > 0)
		out << " + ";
	else
		out << " - ";
	out << abs(head.data) << "x^" << count;
}


List List::Addition(List& a) {
	Node* ptr = (index > a.index) ? &head : &a.head;
	Node* ptr2 = (index > a.index) ? &a.head : &head;
    Node* init = ptr;
	int Min_index = (index < a.index) ? index : a.index;
	for (int i = 0; i < Min_index + 1; i++) {
		ptr->data = ptr->data + ptr2->data;
        if (i < Min_index) {
			ptr = ptr->next;
			ptr2 = ptr2->next;
		}
	}

    List ans;
	ans.index = (index > a.index) ? index : a.index;
	ans.head = *init;
    return ans;
}

List List::Subtraction(List& a) {
	Node* ptr = (index > a.index) ? &head : &a.head;
	Node* ptr2 = (index > a.index) ? &a.head : &head;
    Node* init = ptr;
	int Min_index = (index < a.index) ? index : a.index;
	for (int i = 0; i < Min_index + 1; i++) {
   		ptr->data = ptr->data - ptr2->data;
        if (i < Min_index) {
			ptr = ptr->next;
			ptr2 = ptr2->next;
		}
	}
    Node* cul = init;
    int nt = (index > a.index)? 1: -1;
    while(cul != NULL){
        cul->data *= nt;
        cul = cul->next;
    }

    List ans;
	ans.index = (index > a.index) ? index : a.index;
	ans.head = *init;
    return ans;

}

List List::Multiplication(List& a) {
    List ans;
    ans.index = index + a.index;
    ans.head.data = head.data * a.head.data;
    for(int i = 0; i <= index; i++){
        for(int j = 0; j <= a.index; j++){
            if(i + j == 0)
                continue;
            Node* cptr = &head;
            Node* captr = &a.head;
            for(int k = 0; k < i; k++){
                cptr = cptr->next;
            }
            for(int l = 0; l < j; l++){
                captr = captr->next;
            }
            Node* ptr = &ans.head;
            int OK = false;
            int count = 1;
            while(!OK){
                while(ptr->next != NULL){
                    if(i + j == count){
                        //cout << i+j << ": " << cptr->data << " * " << captr->data << endl;
                        ptr->next->data += cptr->data * captr->data;
                        OK = true;
                        break;
                    }
                    ptr = ptr->next;
                    count++;
                }
                if(!OK){
                    Node* newNode = new Node;
                    newNode->data = 0;
                    newNode->next = NULL;
                    ptr->next = newNode;
                }
            }
        }
    }
	return ans;
}

int List::Evaluation(int x) {
    Node* ptr = &head;
    int y = 0;
    int count = 0;
    while(ptr != NULL){
        int t = 1;
        for(int i = 0; i < count; i++){
            t *= x;
        }
        y += ptr->data * t;
        ptr = ptr->next;
        count++;
    }
	return y;
}

ostream& operator<< (ostream& out, const List& aList) {
	aList.Display(out);
	return out;
}
