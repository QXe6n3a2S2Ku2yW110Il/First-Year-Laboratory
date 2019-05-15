#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int DELETED = (int) (-1e9 - 7), NOT_PUSH = (int) (-1e9 - 9);

template<typename T>
class binaryHeap {
 private:
    vector<pair<T, int>> a;
    vector<int> op;

 public:
    bool empty() {
        return a.empty();
    }

    void siftUp(int x) {
        int iPrev = x, i = (x - 1) / 2;
        while (iPrev > 0 && a[iPrev] < a[i]) {
            swap(a[iPrev], a[i]);
            swap(op[a[iPrev].second], op[a[i].second]);
            iPrev = i;
            i = (i - 1) / 2;
        }
    }

    void siftDown(int i) {
        int mini = i;
        if (i * 2 + 1 < (int) a.size() && a[i * 2 + 1] < a[mini])
            mini = i * 2 + 1;
        if (i * 2 + 2 < (int) a.size() && a[i * 2 + 2] < a[mini])
            mini = i * 2 + 2;
        if (mini != i) {
            swap(a[i], a[mini]);
            swap(op[a[i].second], op[a[mini].second]);
            siftDown(mini);
        }
    }

    void pushOP(int opNum) {
        op.push_back(opNum - 1);
    }

    void push(pair<T, int> x) {
        a.push_back(x);
        pushOP((int) a.size());
        siftUp((int) a.size() - 1);
    }

    pair<T, int> extractMin() {
        pair<T, int> ans = a[0];
        a[0] = a.back();
        op[a.back().second] = 0;
        a.pop_back();
        op[ans.second] = DELETED;

        siftDown(0);

        return ans;
    }

    void decreaseKey(int ind, T val) {
        if (op[ind] < 0 || a[op[ind]].first < val)
            return;

        a[op[ind]] = {val, ind};
        siftUp(op[ind]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // first - val, second - operation number (push)
    binaryHeap<int> heap;
    heap.pushOP(NOT_PUSH);
    string s;
    int num = 0;
    while (cin >> s) {
        ++num;
        if (s == "push") {
            int val;
            cin >> val;

            heap.push({val, num});
        } else {
            heap.pushOP(NOT_PUSH);
        }
        if (s == "extract-min") {
            if (heap.empty()) {
                cout << "*\n";
                continue;
            }

            auto res = heap.extractMin();

            cout << res.first << ' ' << res.second << '\n';
        }
        if (s == "decrease-key") {
            int ind, newVal;
            cin >> ind >> newVal;

            heap.decreaseKey(ind, newVal);
        }
    }

    return 0;
}
