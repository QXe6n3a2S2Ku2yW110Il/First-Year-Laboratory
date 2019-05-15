#include <stdio.h>
#include <vector>

using namespace std;

template <typename T>
class heap {
 private:
    vector<T> a;

 public:
    bool isEmpty() {
        return a.empty();
    }

    void SiftUp(int x) {
        int i = x;
        while (i > 0 && a[i] < a[(i - 1) / 2]) {
            swap(a[i], a[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void SiftDown(int i) {
        int mini = i;
        if (i * 2 + 1 < (int)a.size() && a[i * 2 + 1] < a[mini]) mini = i * 2 + 1;
        if (i * 2 + 2 < (int)a.size() && a[i * 2 + 2] < a[mini]) mini = i * 2 + 2;
        if (mini != i) {
            swap(a[i], a[mini]);
            SiftDown(mini);
        }
    }

    void push(T x) {
        a.push_back(x);
        SiftUp((int)a.size() - 1);
    }

    T extractMin() {
        T ans = a[0];
        a[0] = a.back();
        a.pop_back();
        SiftDown(0);
        return ans;
    }

    T minElement() {
        return a[0];
    }
};

struct sub {
    int leftP, rightP, val;

    sub(int l, int r, int v): leftP(l), rightP(r), val(v) {}

    bool operator < (const sub &s) const {
        // if (leftP == s.leftP)
            // return val < s.val;
        return leftP < s.leftP;
    }
};

struct elem {
    int leftP, rightP, val;

    elem(sub s): leftP(s.leftP), rightP(s.rightP), val(s.val) {}

    bool operator < (const elem &e) const {
        return val > e.val;
    }
};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    heap<sub> a;
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);

        a.push(sub(--x, --y, z));
    }

    heap<elem> subs;
    for (int i = 0; i < n; ++i) {
        while (!a.isEmpty()) {
            sub currSub = a.minElement();
            if (currSub.leftP > i)
                break;

            subs.push(currSub);
            a.extractMin();
        }

        while (!subs.isEmpty() && subs.minElement().rightP < i)
            subs.extractMin();

        if (subs.isEmpty())
            printf("0 ");
        else
            printf("%d ", subs.minElement().val);
    }

    return 0;
}
