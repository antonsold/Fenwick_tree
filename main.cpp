#include <iostream>
#include <vector>

using namespace std;

template <typename T = int, typename Op = plus<T>, typename RevOp = minus<T> >
class FenwickTree{
private:
    vector<T> t;
    int n;
    Op func;
    RevOp rev_func;
public:
    explicit FenwickTree(const vector<T>&);
    void update(int k, int d);
    T query(int);
    T query(int, int);
};

template <typename T, typename Op, typename RevOp>
void FenwickTree<T, Op, RevOp>::update(int k, int d) {
    while(k < n){
        t[k] = func(d, t[k]);
        k = k|(k + 1);
    }
}

template <typename T, typename Op, typename RevOp>
T FenwickTree<T, Op, RevOp>::query(int k) {
    T result = T(0);
    while(k >= 0){
        result = func(result, t[k]);
        k = k & (k + 1) - 1;
    }
    return result;
}

template <typename T, typename Op, typename RevOp>
T FenwickTree<T, Op, RevOp>::query(int i, int k) {
    return rev_func(query(k), query(i));
}

template <typename T, typename Op, typename RevOp>
FenwickTree<T, Op, RevOp>::FenwickTree(const vector<T> &v) {
    n = v.size();
    Op func;
    for (int i = 0; i < n; ++i)
        t[i] = T(0);
    for (int i = 0; i < n; ++i)
        update(i, v[0]);
};
//

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}