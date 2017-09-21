#include <iostream>
#include <vector>

using namespace std;

template <typename T = long long, typename Op = plus<T>, typename RevOp = minus<T> >
class FenwickTree{
private:
    vector<T> t;
    int n;
    Op func;
    RevOp rev_func;
public:
    explicit FenwickTree(const vector<T>&);
    void update(int, T); //adds to old value
    void modify(int, T); //replaces old value with new (given)
    T query(int) const;
    T query(int, int) const;
};

template <typename T, typename Op, typename RevOp>
void FenwickTree<T, Op, RevOp>::update(int k, T d) {
    while(k < n){
        t[k] = func(d, t[k]);
        k = k|(k + 1);
    }
}

template <typename T, typename Op, typename RevOp>
void FenwickTree<T, Op, RevOp>::modify(int k, T val) {
    T diff = rev_func(val, query(k, k));
    update(k, diff);
}

template <typename T, typename Op, typename RevOp>
T FenwickTree<T, Op, RevOp>::query(int k) const{
    T result = T(0);
    while(k >= 0){
        result = func(result, t[k]);
        k = (k & (k + 1)) - 1;
    }
    return result;
}

template <typename T, typename Op, typename RevOp>
T FenwickTree<T, Op, RevOp>::query(int i, int k) const{
    return rev_func(query(k), query(i - 1));
}

template <typename T, typename Op, typename RevOp>
FenwickTree<T, Op, RevOp>::FenwickTree(const vector<T> &v) {
    n = v.size();
    t.resize(n);
    for (int i = 0; i < n; ++i)
        t[i] = T(0);
    for (int i = 0; i < n; ++i)
        update(i, v[i]);
};

int main() {
    int n, m, p, q, k;
    char cmd;
    vector<long long> v;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> k;
        v.push_back(k);
    }
    FenwickTree<> ft(v);
    cin >> m;
    for (int i = 0; i < m; ++i){
        cin >> cmd >> p >> q;
        if (cmd == 's')
            cout << ft.query(p - 1, q - 1) << endl;
        else if (cmd == 'u')
            ft.modify(p - 1, q);
    }
    return 0;
}