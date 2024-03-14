#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;

void display(vector<int> a){
    for(int i = 0; i < a.size(); i++){
        cout << a[i];
    }
    cout << endl;
}

void divide_by_2(vector<int> &v){
    int d = 2;//除數
    int n = 1;//除數的倍數
    int r = 0;//被除數-除數*倍數 的餘數
    vector<int> ans;
    for(int i = 0; i < v.size(); i++){
        n = 1;
        while(d * n <= r * 10 + v[i]){
            n++;
        }
        n--;
        ans.push_back(n);
        r = (r * 10 + v[i]) - (d * n);
    }
    v.clear();
    for(int i = 0; i < ans.size(); i++){
        if(i == 0 && ans[i] == 0)   continue;
            v.push_back(ans[i]);
    }
};

void m_IsBigger(vector<int> &n, vector<int> &m){
    int r = 0;
    if(n.size() == m.size()){
        for(int i = 0; i < n.size(); i++){
            if(n[i] == m[i])
                continue;
            if(n[i] > m[i])
                r = 1;
            break;
        }
    }
    else if(n.size() > m.size())
        r = 1;
    if(r == 1){
        vector<int> t;
        for(int i = 0; i < n.size(); i++){
            t.push_back(n[i]);
        }
        n.clear();
        for(int i = 0; i < m.size(); i++){
            n.push_back(m[i]);
        }
        m.clear();
        for(int i = 0; i < t.size(); i++){
            m.push_back(t[i]);
        }
    }
};

vector<int> Subtract(vector<int> a, vector<int> b){//a >= b
   vector<int> ans;
   int d = 0;
   for(int i = a.size() - 1, j = b.size() - 1; i >= 0; i--, j--){
        d = 0;
        int t = (j >= 0)? b[j]: 0;
        if(a[i] < t){
            d = 10;
            a[i-1]--;
        }
        ans.insert(ans.begin(),d + a[i] - t);
   }
   while(ans.size() != 0 && ans[0] == 0){
        ans.erase(ans.begin());
   }
   if(ans.size() == 0)
       ans.push_back(0);
   return ans;
}

vector<int> Multiply(vector<int> a, vector<int> b){
    vector<int> ans(a.size() + b.size(), 0);
    vector<int> ta(a.size());
    vector<int> tb(b.size());
    for(int i = 0; i < a.size(); i++){
        ta[i] = a[a.size() - 1 - i];
    }

    for(int i = 0; i < b.size(); i++){
        tb[i] = b[b.size() - 1 - i];
    }
    for(int i = 0; i < b.size(); i++){
        for(int j = 0; j < a.size(); j++){
            ans[i + j] += tb[i] * ta[j];
            /*cout << "Mul_ans = ";
            display(ans);*/
            if(ans[i + j] >= 10){
                //cout << "in" << endl;
                ans[i + j + 1] += ans[i + j] / 10;
                ans[i + j] %= 10;
            }   
        } 
    }

    vector<int> r = ans;
    for(int i = 0; i < ans.size(); i++){
        ans[i] = r[ans.size() - 1 - i];
    }
    /*cout << "r = ";
    display(ans);*/
    while(ans.size() != 0 && ans[0] == 0){
        ans.erase(ans.begin());
    }
    if(ans.size() == 0)
        ans.push_back(0);
    return ans;
}

int main(){
    vector<int> n, m;
    char x;
    vector<int> ans = {1};
    const vector<int> two = {2};
    while(scanf("%c", &x) && x != ' '){
        n.push_back(x - '0');
    }
    while(scanf("%c", &x)!=EOF && x != '\n'){
        m.push_back(x - '0');
    }
    do{
        if(n.back() % 2 == 0 && m.back() % 2 == 0){
            ans = Multiply(ans, two);
            divide_by_2(n);
            divide_by_2(m);

            /*cout << "1st if, ans = ";
            display(ans);
            cout << "1st if" << endl;
            display(n);
            display(m);*/
        }
        else if(n.back() % 2 == 0){
            divide_by_2(n);
            /*cout << "2nd if" << endl;
            display(n);*/
        }
        else if(m.back() % 2 == 0){
            divide_by_2(m);
            /*cout << "3rd if" << endl;
            display(m);*/
        }
        m_IsBigger(n, m);
        /*cout << "Bigger: " << endl << "m: ";
        display(m);
        cout<< "n: ";
        display(n);*/
        m = Subtract(m, n);
        /*cout<< "sub" << endl;
        display(m);*/
        //break;//for test
    }
    while(n[0] != 0 && m[0] != 0);
   
   /* cout << "n = ";
    display(n);*/
    ans = Multiply(n, ans);
    display(ans);
    return 0;
}
