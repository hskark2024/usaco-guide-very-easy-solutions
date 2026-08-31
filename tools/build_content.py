from pathlib import Path
import re
import shutil
import textwrap

ROOT = Path(__file__).resolve().parents[1]

COMMON = """#include <algorithm>
#include <array>
#include <cstdio>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
"""


def cpp(body: str) -> str:
    return COMMON + "\n" + textwrap.dedent(body).strip() + "\n"


PROBLEMS = [
    {
        "id": "ys-ZAlgorithm",
        "name": "Z Algorithm",
        "source": "YS",
        "url": "https://judge.yosupo.jp/problem/zalgorithm",
        "tags": ["Strings", "Z Algorithm"],
        "summary": "Given a string, compute the Z-array, where z[i] is the length of the longest prefix of the string that starts again at i.",
        "analysis": "A naive comparison from every position can revisit the same characters many times. The Z-algorithm keeps the rightmost interval [l, r] known to match the prefix. If i is inside that interval, the already computed value at i-l gives a lower bound, clipped by r-i+1. Then we extend with direct comparisons only past r. Each successful extension moves r to the right, so the total number of character comparisons is linear.",
        "visualization": "Picture a sliding prefix-match window. Positions inside the current window can borrow information from the matching prefix segment; positions outside start fresh and may create a new window.",
        "diagram": "flowchart LR\n  A[Position i] --> B{inside current Z box?}\n  B -- yes --> C[copy clipped value from prefix]\n  B -- no --> D[start with 0]\n  C --> E[extend by comparing new chars]\n  D --> E\n  E --> F[update l,r if match goes farther]",
        "verification": "Checked with strings where all characters differ, all characters match, and overlapping repeats such as abacaba.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = (int)s.size();
    vector<int> z(n);
    if (n) z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << z[i];
    }
    cout << '\n';
    return 0;
}
'''),
    },
    {
        "id": "ys-StaticRangeSum",
        "name": "Static Range Sum",
        "source": "YS",
        "url": "https://judge.yosupo.jp/problem/static_range_sum",
        "tags": ["Prefix Sums"],
        "summary": "Answer many range sum queries on an immutable array.",
        "analysis": "Because the array never changes, we can precompute pref[i] as the sum of the first i values. The sum on the half-open interval [l, r) is pref[r] - pref[l]. This moves all repeated work into one linear preprocessing pass.",
        "visualization": "The prefix array is a ruler of cumulative sums; a query cuts out the segment between two tick marks.",
        "diagram": "flowchart LR\n  A[a0 a1 a2 ...] --> B[pref0 pref1 pref2 ...]\n  B --> C[sum l..r-1 = pref[r]-pref[l]]",
        "verification": "Checked empty-length style intervals, single elements, and full-array ranges.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        pref[i + 1] = pref[i] + x;
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << pref[r] - pref[l] << '\n';
    }
    return 0;
}
'''),
    },
    {
        "id": "usaco-807",
        "name": "Teleportation",
        "source": "Bronze",
        "url": "http://www.usaco.org/index.php?page=viewproblem2&cpid=807",
        "tags": ["Math"],
        "summary": "Move from a to b either directly or by using one bidirectional teleporter with endpoints x and y.",
        "analysis": "There are only three meaningful routes: direct, enter at x and leave at y, or enter at y and leave at x. Taking any extra walking around the teleporter cannot help, so the answer is the minimum of those three distances.",
        "visualization": "Place the four points on a number line. The teleporter folds x and y together, so compare the straight walk with the two possible ways to reach that fold.",
        "diagram": "flowchart LR\n  A[direct a to b] --> M[min]\n  B[a to x, teleport, y to b] --> M\n  C[a to y, teleport, x to b] --> M",
        "verification": "Checked cases where the teleporter helps, hurts, and has reversed endpoint order.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (FILE *f = fopen("teleport.in", "r")) {
        fclose(f);
        freopen("teleport.in", "r", stdin);
        freopen("teleport.out", "w", stdout);
    }

    long long a, b, x, y;
    cin >> a >> b >> x >> y;
    long long ans = llabs(a - b);
    ans = min(ans, llabs(a - x) + llabs(b - y));
    ans = min(ans, llabs(a - y) + llabs(b - x));
    cout << ans << '\n';
    return 0;
}
'''),
    },
    {
        "id": "usaco-715",
        "name": "Why Did the Cow Cross the Road II",
        "source": "Silver",
        "url": "https://usaco.org/index.php?page=viewproblem2&cpid=715",
        "tags": ["Prefix Sums", "Sliding Window"],
        "summary": "Given broken traffic signals along a road, find the minimum number to repair so there is a consecutive block of K working signals.",
        "analysis": "Mark broken signals with 1 and working signals with 0. For any window of length K, the number of repairs needed is the sum of that window. A sliding window or prefix sum gives every window total in constant time after a linear pass.",
        "visualization": "Slide a length-K frame over the road. The best frame is the one containing the fewest broken markers.",
        "diagram": "flowchart LR\n  A[broken positions] --> B[0/1 road array]\n  B --> C[length K window sums]\n  C --> D[min repairs]",
        "verification": "Checked the sample pattern and edge windows at the beginning and end.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (FILE *f = fopen("maxcross.in", "r")) {
        fclose(f);
        freopen("maxcross.in", "r", stdin);
        freopen("maxcross.out", "w", stdout);
    }

    int n, k, b;
    cin >> n >> k >> b;
    vector<int> broken(n + 1, 0);
    for (int i = 0; i < b; i++) {
        int x;
        cin >> x;
        broken[x] = 1;
    }
    int cur = 0;
    for (int i = 1; i <= k; i++) cur += broken[i];
    int ans = cur;
    for (int r = k + 1; r <= n; r++) {
        cur += broken[r];
        cur -= broken[r - k];
        ans = min(ans, cur);
    }
    cout << ans << '\n';
    return 0;
}
'''),
    },
    {
        "id": "usaco-691",
        "name": "Hoof Paper Scissors",
        "source": "Silver",
        "url": "http://www.usaco.org/index.php?page=viewproblem2&cpid=691",
        "tags": ["Prefix Sums"],
        "summary": "Choose one gesture before a switch point and another gesture after it to maximize wins against a known sequence.",
        "analysis": "For a fixed interval, the best gesture is determined only by how many H, P, and S appear there. Prefix counts let us evaluate every split in O(1): best wins in the prefix plus best wins in the suffix.",
        "visualization": "Imagine a vertical cut through the games. Left of the cut gets one best gesture; right of the cut gets another.",
        "diagram": "flowchart LR\n  A[count H/P/S prefixes] --> B[try split i]\n  B --> C[best gesture left]\n  B --> D[best gesture right]\n  C --> E[max total]\n  D --> E",
        "verification": "Checked no switch, switch at ends, and sequences dominated by each gesture.",
        "code": cpp(r'''
int wins(const array<int, 3> &cnt) {
    int playH = cnt[2];
    int playP = cnt[0];
    int playS = cnt[1];
    return max(playH, max(playP, playS));
}

int idx(char c) {
    if (c == 'H') return 0;
    if (c == 'P') return 1;
    return 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (FILE *f = fopen("hps.in", "r")) {
        fclose(f);
        freopen("hps.in", "r", stdin);
        freopen("hps.out", "w", stdout);
    }

    int n;
    cin >> n;
    vector<array<int, 3>> pref(n + 1);
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        pref[i + 1] = pref[i];
        pref[i + 1][idx(c)]++;
    }
    int ans = 0;
    for (int split = 0; split <= n; split++) {
        array<int, 3> left = pref[split];
        array<int, 3> right;
        for (int j = 0; j < 3; j++) right[j] = pref[n][j] - pref[split][j];
        ans = max(ans, wins(left) + wins(right));
    }
    cout << ans << '\n';
    return 0;
}
'''),
    },
    {
        "id": "usaco-572",
        "name": "Breed Counting",
        "source": "Silver",
        "url": "http://www.usaco.org/index.php?page=viewproblem2&cpid=572",
        "tags": ["Prefix Sums"],
        "summary": "For many intervals, report how many cows of each of three breeds appear.",
        "analysis": "Maintain three prefix-count arrays. For query [l, r], subtract counts before l from counts through r for each breed. The query work is constant because the number of breeds is fixed.",
        "visualization": "Each breed has its own cumulative counter line; an interval answer is the rise between two x-positions.",
        "diagram": "flowchart LR\n  A[breed sequence] --> B[prefix count breed 1]\n  A --> C[prefix count breed 2]\n  A --> D[prefix count breed 3]\n  B --> E[query subtract]\n  C --> E\n  D --> E",
        "verification": "Checked singleton intervals and full-range totals.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (FILE *f = fopen("bcount.in", "r")) {
        fclose(f);
        freopen("bcount.in", "r", stdin);
        freopen("bcount.out", "w", stdout);
    }

    int n, q;
    cin >> n >> q;
    vector<array<int, 3>> pref(n + 1);
    for (int i = 1; i <= n; i++) {
        int b;
        cin >> b;
        pref[i] = pref[i - 1];
        pref[i][b - 1]++;
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        for (int b = 0; b < 3; b++) {
            if (b) cout << ' ';
            cout << pref[r][b] - pref[l - 1][b];
        }
        cout << '\n';
    }
    return 0;
}
'''),
    },
    {
        "id": "spoj-DynamicConnectivity",
        "name": "Dynamic Connectivity",
        "source": "SPOJ",
        "url": "https://www.spoj.com/problems/DYNACON1",
        "tags": ["LCT", "Tree"],
        "summary": "Maintain a forest under edge insertions, edge removals, and connectivity queries.",
        "analysis": "Because every add operation connects two different trees, the graph remains a forest. A link-cut tree represents each tree with splay trees. `makeroot` reroots a represented tree, `link` adds an edge, `cut` removes a known tree edge, and `findroot` identifies the represented-tree root for connectivity.",
        "visualization": "Think of the forest as flexible paths. Access operations expose exactly the path we need, then link or cut rewires one edge while preserving the rest.",
        "diagram": "flowchart LR\n  A[add u v] --> B[makeroot u]\n  B --> C[link u under v]\n  D[rem u v] --> E[makeroot u]\n  E --> F[expose v path]\n  F --> G[cut edge]\n  H[conn u v] --> I[findroot u == findroot v]",
        "verification": "Checked the SPOJ-style sample sequence from the mirrored statement and repeated add/remove cycles.",
        "code": cpp(r'''
struct LinkCutTree {
    struct Node {
        int ch[2] = {0, 0};
        int p = 0;
        bool rev = false;
    };

    vector<Node> t;

    explicit LinkCutTree(int n) : t(n + 1) {}

    bool is_root(int x) {
        int p = t[x].p;
        return p == 0 || (t[p].ch[0] != x && t[p].ch[1] != x);
    }

    void push(int x) {
        if (!x || !t[x].rev) return;
        swap(t[x].ch[0], t[x].ch[1]);
        if (t[x].ch[0]) t[t[x].ch[0]].rev ^= 1;
        if (t[x].ch[1]) t[t[x].ch[1]].rev ^= 1;
        t[x].rev = false;
    }

    void rotate(int x) {
        int p = t[x].p, g = t[p].p;
        int dir = (t[p].ch[1] == x);
        int b = t[x].ch[dir ^ 1];
        if (!is_root(p)) t[g].ch[t[g].ch[1] == p] = x;
        t[x].p = g;
        t[x].ch[dir ^ 1] = p;
        t[p].p = x;
        t[p].ch[dir] = b;
        if (b) t[b].p = p;
    }

    void splay(int x) {
        vector<int> st;
        int y = x;
        st.push_back(y);
        while (!is_root(y)) {
            y = t[y].p;
            st.push_back(y);
        }
        while (!st.empty()) {
            push(st.back());
            st.pop_back();
        }
        while (!is_root(x)) {
            int p = t[x].p, g = t[p].p;
            if (!is_root(p)) {
                bool zigzig = (t[p].ch[0] == x) == (t[g].ch[0] == p);
                rotate(zigzig ? p : x);
            }
            rotate(x);
        }
    }

    void access(int x) {
        int last = 0;
        for (int y = x; y; y = t[y].p) {
            splay(y);
            t[y].ch[1] = last;
            last = y;
        }
        splay(x);
    }

    void makeroot(int x) {
        access(x);
        t[x].rev ^= 1;
    }

    int findroot(int x) {
        access(x);
        while (true) {
            push(x);
            if (!t[x].ch[0]) break;
            x = t[x].ch[0];
        }
        splay(x);
        return x;
    }

    bool connected(int u, int v) {
        return findroot(u) == findroot(v);
    }

    void link(int u, int v) {
        makeroot(u);
        if (findroot(v) != u) t[u].p = v;
    }

    void cut(int u, int v) {
        makeroot(u);
        access(v);
        if (t[v].ch[0] == u && t[u].ch[1] == 0) {
            t[v].ch[0] = 0;
            t[u].p = 0;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    LinkCutTree lct(n);
    while (m--) {
        string op;
        int a, b;
        cin >> op >> a >> b;
        if (op == "add") lct.link(a, b);
        else if (op == "rem") lct.cut(a, b);
        else cout << (lct.connected(a, b) ? "YES" : "NO") << '\n';
    }
    return 0;
}
'''),
    },
    {
        "id": "lc-FindPivotIndex",
        "name": "Find Pivot Index",
        "source": "LC",
        "url": "https://leetcode.com/problems/find-pivot-index",
        "tags": ["Prefix Sums"],
        "summary": "Find an index where the sum to its left equals the sum to its right.",
        "analysis": "Let total be the sum of the full array and left be the sum before the current index. The right sum is total - left - nums[i]. Scan left to right and return the first index where the two sides match.",
        "visualization": "The current element is a hinge; the left pan holds all previous values and the right pan holds all later values.",
        "diagram": "flowchart LR\n  A[total sum] --> B[scan i]\n  B --> C[left]\n  B --> D[total-left-a[i]]\n  C --> E{equal?}\n  D --> E",
        "verification": "Checked examples with a pivot, no pivot, and pivot at the first position.",
        "code": cpp(r'''
int pivotIndex(const vector<int> &nums) {
    long long total = accumulate(nums.begin(), nums.end(), 0LL);
    long long left = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        long long right = total - left - nums[i];
        if (left == right) return i;
        left += nums[i];
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> nums(n);
    for (int &x : nums) cin >> x;
    cout << pivotIndex(nums) << '\n';
    return 0;
}
'''),
    },
    {
        "id": "kattis-BasketballOneOnOne",
        "name": "Basketball One on One",
        "source": "Kattis",
        "url": "https://open.kattis.com/problems/basketballoneonone",
        "tags": ["Strings"],
        "summary": "Given a compact scoring log, determine which player has the larger final score.",
        "analysis": "The input alternates player letter and point digit. Accumulate points for A and B, then print the player with the larger score.",
        "visualization": "Read the score log as score tokens: A2, B1, A1, and so on. Each token adds to one scoreboard column.",
        "diagram": "flowchart LR\n  A[score string] --> B[token player+points]\n  B --> C[score A / score B]\n  C --> D[winner]",
        "verification": "Checked logs ending with A ahead and B ahead.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int a = 0, b = 0;
    for (int i = 0; i + 1 < (int)s.size(); i += 2) {
        if (s[i] == 'A') a += s[i + 1] - '0';
        else b += s[i + 1] - '0';
    }
    cout << (a > b ? 'A' : 'B') << '\n';
    return 0;
}
'''),
    },
    {
        "id": "ioi-08-TypePrinter",
        "name": "Type Printer",
        "source": "IOI",
        "url": "https://oj.uz/problem/view/IOI08_printer",
        "tags": ["Trie", "Strings"],
        "summary": "Print a set of words using operations that type a letter, print the current word, or delete the last letter, while minimizing operations.",
        "analysis": "All words share prefixes, so a trie captures every useful typed prefix exactly once. A DFS types an edge, prints at terminal nodes, and backspaces after finished side branches. To save operations, finish on a longest word path; those final letters never need to be deleted.",
        "visualization": "The trie is a keyboard travel map. Side branches are round trips; the longest final branch is a one-way ending route.",
        "diagram": "flowchart LR\n  A[insert words in trie] --> B[mark path to longest word]\n  B --> C[DFS side children first]\n  C --> D[type letter / recurse / backspace]\n  C --> E[follow longest path last]\n  E --> F[no final backspaces]",
        "verification": "Checked words with shared prefixes, a single word, and terminal nodes that also have children.",
        "code": cpp(r'''
struct Node {
    array<int, 26> nxt;
    int parent = -1;
    char ch = 0;
    bool terminal = false;
    Node() { nxt.fill(-1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Node> trie(1);
    int deepest = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int u = 0;
        for (char c : s) {
            int id = c - 'a';
            if (trie[u].nxt[id] == -1) {
                trie[u].nxt[id] = (int)trie.size();
                trie.push_back(Node());
                trie.back().parent = u;
                trie.back().ch = c;
            }
            u = trie[u].nxt[id];
        }
        trie[u].terminal = true;
        if (s.size() > (size_t)depth(deepest)) deepest = u;
    }

    vector<int> keep(trie.size(), 0);
    for (int u = deepest; u != 0; u = trie[u].parent) keep[u] = 1;

    vector<char> ops;
    function<void(int)> dfs = [&](int u) {
        if (trie[u].terminal) ops.push_back('P');
        int special = -1;
        for (int c = 0; c < 26; c++) {
            int v = trie[u].nxt[c];
            if (v == -1) continue;
            if (keep[v]) special = v;
            else {
                ops.push_back(trie[v].ch);
                dfs(v);
                ops.push_back('-');
            }
        }
        if (special != -1) {
            ops.push_back(trie[special].ch);
            dfs(special);
        }
    };

    dfs(0);
    cout << ops.size() << '\n';
    for (char op : ops) cout << op << '\n';
    return 0;
}
''').replace("if (s.size() > (size_t)depth(deepest)) deepest = u;", "int dep = 0; for (int x = u; x; x = trie[x].parent) dep++;\n        int best_dep = 0; for (int x = deepest; x; x = trie[x].parent) best_dep++;\n        if (dep > best_dep) deepest = u;"),
    },
    {
        "id": "hr-BubbleSort",
        "name": "Bubble Sort",
        "source": "HR",
        "url": "https://www.hackerrank.com/challenges/ctci-bubble-sort/problem",
        "tags": ["Sorting"],
        "summary": "Run bubble sort, count swaps, and report the first and last elements after sorting.",
        "analysis": "Bubble sort repeatedly swaps adjacent inversions. Counting each performed swap gives the required total. After all passes, the array is sorted, so the first and last positions are the min and max.",
        "visualization": "Large elements drift right one adjacent swap at a time, like bubbles moving to the end of the array.",
        "diagram": "flowchart LR\n  A[array] --> B[scan adjacent pairs]\n  B --> C{out of order?}\n  C -- yes --> D[swap and count]\n  C -- no --> E[continue]\n  D --> E",
        "verification": "Checked already sorted, reverse sorted, and mixed arrays.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    long long swaps = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + 1 < n; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swaps++;
            }
        }
    }
    cout << "Array is sorted in " << swaps << " swaps.\n";
    cout << "First Element: " << a.front() << "\n";
    cout << "Last Element: " << a.back() << "\n";
    return 0;
}
'''),
    },
    {
        "id": "hdu-5306",
        "name": "Gorgeous Sequence",
        "source": "HDU",
        "url": "https://vjudge.net/problem/HDU-5306",
        "tags": ["SegTree Beats"],
        "summary": "Support range cap updates, range maximum queries, and range sum queries.",
        "analysis": "Segment Tree Beats stores the largest value, second largest value, count of largest values, and sum for each node. A range chmin can be applied lazily when the cap lies strictly between the largest and second largest values: only the current maximum values change. Otherwise we push deeper. This keeps the amortized number of hard descents low.",
        "visualization": "Each segment has a tallest bar and a second-tallest bar. If the new ceiling only cuts the tallest bars, the segment can be updated at once.",
        "diagram": "flowchart LR\n  A[range chmin x] --> B{segment outside or max <= x?}\n  B -- yes --> C[stop]\n  B -- no --> D{x > second max and fully covered?}\n  D -- yes --> E[lower only max bars]\n  D -- no --> F[push to children]",
        "verification": "Checked range caps against a brute-force array on small custom cases.",
        "code": cpp(r'''
struct SegTree {
    struct Node {
        long long sum = 0;
        int mx = 0;
        int second = -1;
        int cnt_mx = 0;
    };

    int n;
    vector<Node> st;

    explicit SegTree(const vector<int> &a) {
        n = (int)a.size() - 1;
        st.resize(4 * n + 4);
        build(1, 1, n, a);
    }

    Node merge(Node l, Node r) {
        Node res;
        res.sum = l.sum + r.sum;
        if (l.mx == r.mx) {
            res.mx = l.mx;
            res.cnt_mx = l.cnt_mx + r.cnt_mx;
            res.second = max(l.second, r.second);
        } else if (l.mx > r.mx) {
            res.mx = l.mx;
            res.cnt_mx = l.cnt_mx;
            res.second = max(l.second, r.mx);
        } else {
            res.mx = r.mx;
            res.cnt_mx = r.cnt_mx;
            res.second = max(l.mx, r.second);
        }
        return res;
    }

    void build(int p, int l, int r, const vector<int> &a) {
        if (l == r) {
            st[p].sum = st[p].mx = a[l];
            st[p].second = -1;
            st[p].cnt_mx = 1;
            return;
        }
        int m = (l + r) / 2;
        build(p * 2, l, m, a);
        build(p * 2 + 1, m + 1, r, a);
        st[p] = merge(st[p * 2], st[p * 2 + 1]);
    }

    void apply_chmin(int p, int x) {
        if (x >= st[p].mx) return;
        st[p].sum -= 1LL * (st[p].mx - x) * st[p].cnt_mx;
        st[p].mx = x;
    }

    void push(int p) {
        apply_chmin(p * 2, st[p].mx);
        apply_chmin(p * 2 + 1, st[p].mx);
    }

    void range_chmin(int p, int l, int r, int ql, int qr, int x) {
        if (qr < l || r < ql || x >= st[p].mx) return;
        if (ql <= l && r <= qr && x > st[p].second) {
            apply_chmin(p, x);
            return;
        }
        push(p);
        int m = (l + r) / 2;
        range_chmin(p * 2, l, m, ql, qr, x);
        range_chmin(p * 2 + 1, m + 1, r, ql, qr, x);
        st[p] = merge(st[p * 2], st[p * 2 + 1]);
    }

    int range_max(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return st[p].mx;
        push(p);
        int m = (l + r) / 2;
        return max(range_max(p * 2, l, m, ql, qr), range_max(p * 2 + 1, m + 1, r, ql, qr));
    }

    long long range_sum(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return st[p].sum;
        push(p);
        int m = (l + r) / 2;
        return range_sum(p * 2, l, m, ql, qr) + range_sum(p * 2 + 1, m + 1, r, ql, qr);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        SegTree seg(a);
        while (m--) {
            int op, l, r;
            cin >> op >> l >> r;
            if (op == 0) {
                int x;
                cin >> x;
                seg.range_chmin(1, 1, n, l, r, x);
            } else if (op == 1) {
                cout << seg.range_max(1, 1, n, l, r) << '\n';
            } else {
                cout << seg.range_sum(1, 1, n, l, r) << '\n';
            }
        }
    }
    return 0;
}
'''),
    },
    {
        "id": "cses-2079",
        "name": "Finding a Centroid",
        "source": "CSES",
        "url": "https://cses.fi/problemset/task/2079",
        "tags": ["Tree"],
        "summary": "Find a tree vertex whose removal leaves every component with at most n/2 vertices.",
        "analysis": "Root the tree anywhere and compute subtree sizes. Starting from root, if a child subtree is larger than n/2, the centroid must be inside that child, so move there. This strictly moves downward and stops at a centroid.",
        "visualization": "Walk toward the only side that is too heavy. Once no side is too heavy, the current node balances the tree.",
        "diagram": "flowchart LR\n  A[compute subtree sizes] --> B[start at 1]\n  B --> C{child subtree > n/2?}\n  C -- yes --> D[move to that child]\n  D --> C\n  C -- no --> E[current node is centroid]",
        "verification": "Checked paths, stars, and balanced trees.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> sz(n + 1);
    function<void(int, int)> dfs = [&](int u, int p) {
        sz[u] = 1;
        for (int v : g[u]) if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    };
    dfs(1, 0);
    int u = 1, p = 0;
    bool moved = true;
    while (moved) {
        moved = false;
        for (int v : g[u]) if (v != p && sz[v] > n / 2) {
            p = u;
            u = v;
            moved = true;
            break;
        }
    }
    cout << u << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cses-1753",
        "name": "String Matching",
        "source": "CSES",
        "url": "https://cses.fi/problemset/task/1753",
        "tags": ["Strings", "KMP"],
        "summary": "Count how many times a pattern appears in a text.",
        "analysis": "Build the prefix function for pattern + separator + text. Whenever the prefix-function value equals the pattern length, an occurrence ends at that position. KMP avoids backing up in the text.",
        "visualization": "The prefix function measures how much of the pattern is currently matched as the scan moves through the text.",
        "diagram": "flowchart LR\n  A[pattern#text] --> B[prefix function]\n  B --> C{value == pattern length?}\n  C -- yes --> D[count occurrence]",
        "verification": "Checked overlapping matches like aaa in aaaaa and no-match cases.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text, pat;
    cin >> text >> pat;
    string s = pat + "#" + text;
    vector<int> pi(s.size());
    for (int i = 1; i < (int)s.size(); i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    int ans = 0;
    for (int x : pi) if (x == (int)pat.size()) ans++;
    cout << ans << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cses-1733",
        "name": "Finding Periods",
        "source": "CSES",
        "url": "https://cses.fi/problemset/task/1733/",
        "tags": ["Strings", "Z Algorithm"],
        "summary": "List all prefix lengths that can serve as a period of the whole string.",
        "analysis": "A length p is a period when the suffix beginning at p matches the prefix for all remaining characters. That condition is exactly z[p] >= n-p. The full length n is always a period.",
        "visualization": "Shift the string left by p. If every overlapping character still matches, p is a valid period.",
        "diagram": "flowchart LR\n  A[compute Z array] --> B[try p from 1 to n-1]\n  B --> C{z[p] >= n-p?}\n  C -- yes --> D[print p]\n  D --> E[print n]",
        "verification": "Checked periodic strings like ababab and non-periodic strings.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = (int)s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    for (int p = 1; p < n; p++) {
        if (z[p] >= n - p) cout << p << ' ';
    }
    cout << n << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cses-1660",
        "name": "Subarray Sums I",
        "source": "CSES",
        "url": "https://cses.fi/problemset/task/1660",
        "tags": ["Two Pointers"],
        "summary": "Count subarrays with sum exactly x when all values are positive.",
        "analysis": "Positive values make the window sum monotonic as the right end moves. Expand right, then shrink left while the sum is too large. Each pointer only moves forward, giving linear time.",
        "visualization": "A flexible window slides over the array, stretching to include new values and shrinking when it becomes too heavy.",
        "diagram": "flowchart LR\n  A[extend right] --> B[sum too large?]\n  B -- yes --> C[move left]\n  C --> B\n  B -- no --> D{sum == x?}\n  D -- yes --> E[count]",
        "verification": "Checked x met by single items, full array, and multiple windows.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x;
    cin >> n >> x;
    vector<int> a(n);
    for (int &v : a) cin >> v;
    long long sum = 0, ans = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum > x && l <= r) sum -= a[l++];
        if (sum == x) ans++;
    }
    cout << ans << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cses-1647",
        "name": "Static Range Minimum Queries",
        "source": "CSES",
        "url": "https://cses.fi/problemset/task/1647",
        "tags": ["Sparse Table"],
        "summary": "Answer minimum queries on a fixed array.",
        "analysis": "A sparse table stores the minimum for every power-of-two interval. Any query interval can be covered by two overlapping intervals of length 2^k, where k is the largest power fitting in the query.",
        "visualization": "The table is a stack of interval layers: length 1, 2, 4, 8, and so on. A query grabs two blocks from one layer.",
        "diagram": "flowchart LR\n  A[array] --> B[build power-of-two minima]\n  B --> C[query length len]\n  C --> D[k=floor log2 len]\n  D --> E[min left block, right block]",
        "verification": "Checked single-element ranges and ranges whose lengths are not powers of two.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> lg(n + 1);
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
    int K = lg[n] + 1;
    vector<vector<int>> st(K, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) cin >> st[0][i];
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        }
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        int k = lg[r - l + 1];
        cout << min(st[k][l], st[k][r - (1 << k) + 1]) << '\n';
    }
    return 0;
}
'''),
    },
    {
        "id": "cses-1634",
        "name": "Minimizing Coins",
        "source": "CSES",
        "url": "https://cses.fi/problemset/task/1634",
        "tags": ["DP", "Knapsack"],
        "summary": "Find the fewest coins needed to form a target sum, or report impossible.",
        "analysis": "Let dp[s] be the minimum coins needed for sum s. For each sum, try taking each coin last: dp[s] = min(dp[s-c] + 1). This is an unbounded coin DP because each coin value may be used repeatedly.",
        "visualization": "Every sum is a node; a coin creates an edge from s-c to s with cost one coin.",
        "diagram": "flowchart LR\n  A[dp[0]=0] --> B[for sum 1..x]\n  B --> C[try each coin]\n  C --> D[min previous + 1]",
        "verification": "Checked reachable targets, impossible targets, and coin 1 cases.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;
    vector<int> coins(n);
    for (int &c : coins) cin >> c;
    const int INF = 1e9;
    vector<int> dp(x + 1, INF);
    dp[0] = 0;
    for (int s = 1; s <= x; s++) {
        for (int c : coins) if (s >= c) {
            dp[s] = min(dp[s], dp[s - c] + 1);
        }
    }
    cout << (dp[x] == INF ? -1 : dp[x]) << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cses-1633",
        "name": "Dice Combinations",
        "source": "CSES",
        "url": "https://cses.fi/problemset/task/1633",
        "tags": ["DP"],
        "summary": "Count ordered sequences of dice rolls that sum to n.",
        "analysis": "Let dp[s] count ordered sequences summing to s. The last roll can be 1 through 6, so dp[s] is the sum of dp[s-d] over valid d. Take all values modulo 1e9+7.",
        "visualization": "A path to sum s ends by jumping from one of the previous six sums.",
        "diagram": "flowchart LR\n  A[dp[0]=1] --> B[sum s]\n  B --> C[last roll 1..6]\n  C --> D[add dp[s-roll]]",
        "verification": "Checked n=1, n=3, and larger values against a small brute-force recurrence.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    const int MOD = 1000000007;
    vector<int> dp(n + 1);
    dp[0] = 1;
    for (int s = 1; s <= n; s++) {
        long long ways = 0;
        for (int d = 1; d <= 6 && d <= s; d++) ways += dp[s - d];
        dp[s] = ways % MOD;
    }
    cout << dp[n] << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cses-1631",
        "name": "Reading Books",
        "source": "CSES",
        "url": "https://cses.fi/problemset/task/1631/",
        "tags": ["Greedy"],
        "summary": "Two readers must read all books; compute the minimum total elapsed time.",
        "analysis": "The answer is at least the total reading time, because all work must be done, and at least twice the longest book, because both readers must spend that much combined time around the longest book. These bounds are achievable, so answer max(sum, 2*max).",
        "visualization": "The longest book can dominate the schedule; otherwise the total workload dominates.",
        "diagram": "flowchart LR\n  A[sum all times] --> C[max]\n  B[longest time] --> D[2*longest]\n  C --> E[answer]\n  D --> E",
        "verification": "Checked one book, dominant longest book, and balanced books.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    long long sum = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        sum += x;
        mx = max(mx, x);
    }
    cout << max(sum, 2 * mx) << '\n';
    return 0;
}
'''),
    },
    {
        "id": "coci-21-vlak",
        "name": "Vlak",
        "source": "COCI",
        "url": "https://oj.uz/problem/view/COCI20_vlak",
        "tags": ["Trie", "DP", "Game Theory"],
        "summary": "Two players append letters to a growing word. On each turn, the current word must be a prefix of one of that player's own words. The player unable to move loses.",
        "analysis": "Insert both players' word sets into one trie, marking every node that is a valid prefix for Nina and/or Emilija. A state is the current trie node and the player to move. It is winning for that player if there is at least one child that is valid for that player and losing for the other player. Compute these states bottom-up.",
        "visualization": "The trie is the game board. Nina can move only along edges into Nina-marked prefixes; Emilija can move only into Emilija-marked prefixes.",
        "diagram": "flowchart LR\n  A[combined trie] --> B[mark valid prefixes per player]\n  B --> C[DFS from leaves]\n  C --> D{exists legal child losing for opponent?}\n  D -- yes --> E[winning]\n  D -- no --> F[losing]",
        "verification": "Checked tiny games where one player has no first move and shared-prefix games where the winning move changes by turn.",
        "code": cpp(r'''
struct Node {
    array<int, 26> next;
    bool ok[2] = {false, false};
    bool win[2] = {false, false};
    Node() { next.fill(-1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Node> trie(1);
    auto insert_word = [&](const string &s, int player) {
        int u = 0;
        for (char c : s) {
            int id = c - 'a';
            if (trie[u].next[id] == -1) {
                trie[u].next[id] = (int)trie.size();
                trie.push_back(Node());
            }
            u = trie[u].next[id];
            trie[u].ok[player] = true;
        }
    };

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        insert_word(s, 0);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        insert_word(s, 1);
    }

    function<void(int)> dfs = [&](int u) {
        for (int v : trie[u].next) if (v != -1) dfs(v);
        for (int player = 0; player < 2; player++) {
            trie[u].win[player] = false;
            for (int v : trie[u].next) {
                if (v != -1 && trie[v].ok[player] && !trie[v].win[player ^ 1]) {
                    trie[u].win[player] = true;
                }
            }
        }
    };
    dfs(0);
    cout << (trie[0].win[0] ? "Nina" : "Emilija") << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cfgym-102951B",
        "name": "Studying Algorithms",
        "source": "CF",
        "url": "https://codeforces.com/gym/102951/problem/B",
        "tags": ["Greedy", "Sorting"],
        "summary": "Choose the maximum number of algorithms to study within a fixed time budget.",
        "analysis": "To maximize the count, study the shortest algorithms first. If an optimal answer used a longer algorithm while skipping a shorter one, swapping them would not increase time and would keep the count. Sort durations and greedily take while the budget allows.",
        "visualization": "Pack the smallest time blocks into the budget bar before considering larger blocks.",
        "diagram": "flowchart LR\n  A[durations] --> B[sort ascending]\n  B --> C[take while total <= X]\n  C --> D[count]",
        "verification": "Checked the Codeforces sample and budgets that stop exactly at an item boundary.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int &v : a) cin >> v;
    sort(a.begin(), a.end());
    int count = 0;
    for (int v : a) {
        if (x >= v) {
            x -= v;
            count++;
        }
    }
    cout << count << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cf-546A",
        "name": "Soldier and Bananas",
        "source": "CF",
        "url": "https://codeforces.com/problemset/problem/546/A",
        "tags": ["Math"],
        "summary": "Compute how much money is missing to buy bananas with linearly increasing prices.",
        "analysis": "The total cost is k * (1 + 2 + ... + w) = k*w*(w+1)/2. Borrowing needed is max(0, total - current money).",
        "visualization": "Banana prices form a staircase; sum the staircase and compare it to the wallet.",
        "diagram": "flowchart LR\n  A[k,n,w] --> B[total = k*w*(w+1)/2]\n  B --> C[max 0 total-n]",
        "verification": "Checked cases requiring no borrow and positive borrow.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long k, n, w;
    cin >> k >> n >> w;
    long long total = k * w * (w + 1) / 2;
    cout << max(0LL, total - n) << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cf-4A",
        "name": "Watermelon",
        "source": "CF",
        "url": "https://codeforces.com/problemset/problem/4/A",
        "tags": ["Math"],
        "summary": "Decide whether an even weight can be split into two positive even parts.",
        "analysis": "The smallest positive even part is 2. Therefore the split is possible exactly when w is even and greater than 2.",
        "visualization": "Reserve 2 for one person; the remainder must also be positive and even.",
        "diagram": "flowchart LR\n  A[w] --> B{w even and w > 2?}\n  B -- yes --> C[YES]\n  B -- no --> D[NO]",
        "verification": "Checked w=2, odd weights, and larger even weights.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int w;
    cin >> w;
    cout << (w > 2 && w % 2 == 0 ? "YES" : "NO") << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cf-279B",
        "name": "Books",
        "source": "CF",
        "url": "https://codeforces.com/contest/279/problem/B",
        "tags": ["Two Pointers"],
        "summary": "Find the longest contiguous block of books readable within total time t.",
        "analysis": "All reading times are positive, so a sliding window works. Add each right endpoint, shrink the left endpoint while the sum exceeds t, and track the maximum window length.",
        "visualization": "A window expands over consecutive books until it exceeds the time budget, then slides forward.",
        "diagram": "flowchart LR\n  A[add next book] --> B{sum > t?}\n  B -- yes --> C[drop left book]\n  C --> B\n  B -- no --> D[update best length]",
        "verification": "Checked all books fit, no book fits, and several best windows.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long t;
    cin >> n >> t;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    long long sum = 0;
    int ans = 0, l = 0;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum > t && l <= r) sum -= a[l++];
        ans = max(ans, r - l + 1);
    }
    cout << ans << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cf-231A",
        "name": "Team",
        "source": "CF",
        "url": "https://codeforces.com/problemset/problem/231/A",
        "tags": ["Math"],
        "summary": "Count problems where at least two of three teammates are sure about the solution.",
        "analysis": "For each row of three binary values, sum them. If the sum is at least two, the team implements the problem.",
        "visualization": "Each problem is a three-vote ballot; two or more votes pass it.",
        "diagram": "flowchart LR\n  A[three votes] --> B[sum]\n  B --> C{sum >= 2?}\n  C -- yes --> D[count]",
        "verification": "Checked all possible vote counts from zero to three.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int ans = 0;
    while (n--) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a + b + c >= 2) ans++;
    }
    cout << ans << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cf-2257C",
        "name": "Spying On The Beaver",
        "source": "CF",
        "url": "https://codeforces.com/problemset/problem/2257/C",
        "tags": ["Tree", "Greedy"],
        "summary": "Place the minimum number of cameras on rooted-tree edges so the set of observed camera edges uniquely identifies which marked destination was reached.",
        "analysis": "Two destination groups below different child subtrees of a node need different observations before they diverge. If the current node itself is a destination, every marked child subtree needs its entering edge selected; otherwise one child subtree can inherit the current observation code and all other marked child subtrees need selected entering edges. Apply this independently bottom-up/top-down over all nodes with marked descendants.",
        "visualization": "A selected edge gives every destination below it one extra bit of identity. At each branching point, all but possibly one marked branch need a new bit; if the branch point is also a destination, every marked branch needs one.",
        "diagram": "flowchart LR\n  A[node u] --> B[count marked child subtrees]\n  B --> C{u is marked?}\n  C -- yes --> D[select every marked child edge]\n  C -- no --> E[leave one unselected, select rest]\n  D --> F[recurse]\n  E --> F",
        "verification": "Checked against the Codeforces sample structure and tiny ancestor/branching cases.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<vector<int>> child(n + 1);
        for (int v = 2; v <= n; v++) {
            int p;
            cin >> p;
            child[p].push_back(v);
        }
        int m;
        cin >> m;
        vector<int> marked(n + 1, 0);
        for (int i = 0; i < m; i++) {
            int a;
            cin >> a;
            marked[a] = 1;
        }
        vector<int> sub(n + 1, 0), ans;
        function<void(int)> calc = [&](int u) {
            sub[u] = marked[u];
            for (int v : child[u]) {
                calc(v);
                sub[u] += sub[v];
            }
        };
        calc(1);
        function<void(int)> choose = [&](int u) {
            vector<int> useful;
            for (int v : child[u]) if (sub[v] > 0) useful.push_back(v);
            int start = marked[u] ? 0 : min(1, (int)useful.size());
            for (int i = start; i < (int)useful.size(); i++) ans.push_back(useful[i]);
            for (int v : child[u]) choose(v);
        };
        choose(1);
        cout << ans.size();
        for (int v : ans) cout << ' ' << v;
        cout << '\n';
    }
    return 0;
}
'''),
    },
    {
        "id": "cf-20C",
        "name": "Dijkstra",
        "source": "CF",
        "url": "https://codeforces.com/problemset/problem/20/C",
        "tags": ["Shortest Path"],
        "summary": "Find a shortest path from vertex 1 to vertex n in a weighted undirected graph.",
        "analysis": "All edge weights are nonnegative, so Dijkstra's algorithm is appropriate. Store parent pointers whenever a distance improves, then reconstruct the path from n back to 1.",
        "visualization": "The priority queue repeatedly commits the currently closest unsettled node, growing a shortest-path tree outward from node 1.",
        "diagram": "flowchart LR\n  A[dist[1]=0] --> B[pq min distance]\n  B --> C[relax outgoing edges]\n  C --> D[store parent on improvement]\n  D --> E[reconstruct path to n]",
        "verification": "Checked reachable and unreachable graphs plus multiple-edge choices.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }
    const long long INF = numeric_limits<long long>::max() / 4;
    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    if (dist[n] == INF) {
        cout << -1 << '\n';
        return 0;
    }
    vector<int> path;
    for (int u = n; u != -1; u = parent[u]) path.push_back(u);
    reverse(path.begin(), path.end());
    for (int i = 0; i < (int)path.size(); i++) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}
'''),
    },
    {
        "id": "cf-1593A",
        "name": "Election",
        "source": "CF",
        "url": "https://codeforces.com/problemset/problem/1593/A",
        "tags": ["Math"],
        "summary": "For each candidate, compute the minimum extra votes needed to become strictly first.",
        "analysis": "A candidate needs zero extra votes only if they are already strictly greater than both others. Otherwise they need one more than the current maximum minus their current votes.",
        "visualization": "Raise each candidate's bar just above the tallest competing bar.",
        "diagram": "flowchart LR\n  A[votes a,b,c] --> B[current max]\n  B --> C[for each candidate]\n  C --> D{strictly alone at max?}\n  D -- yes --> E[0]\n  D -- no --> F[max+1-votes]",
        "verification": "Checked ties, one clear winner, and all equal.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        vector<int> a(3);
        for (int &x : a) cin >> x;
        for (int i = 0; i < 3; i++) {
            int best_other = 0;
            for (int j = 0; j < 3; j++) if (i != j) best_other = max(best_other, a[j]);
            int need = max(0, best_other + 1 - a[i]);
            if (i) cout << ' ';
            cout << need;
        }
        cout << '\n';
    }
    return 0;
}
'''),
    },
    {
        "id": "cf-1560B",
        "name": "Who's Opposite?",
        "source": "CF",
        "url": "https://codeforces.com/problemset/problem/1560/B",
        "tags": ["Math"],
        "summary": "Given two opposite positions on a circle and a third position, find the position opposite the third or report impossible.",
        "analysis": "If a and b are opposite, their distance is half the circle size. Thus n = 2*abs(a-b). Any label above n is impossible. The opposite of c is c plus or minus n/2, wrapped within 1..n.",
        "visualization": "The known opposite pair fixes the diameter length; rotating that same diameter through c gives c's opposite point.",
        "diagram": "flowchart LR\n  A[a,b,c] --> B[d=abs(a-b)]\n  B --> C[n=2d]\n  C --> D{labels valid?}\n  D -- no --> E[-1]\n  D -- yes --> F[c opposite by +/- d]",
        "verification": "Checked invalid labels and both sides of the circle wrap.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int a, b, c;
        cin >> a >> b >> c;
        int d = abs(a - b);
        int n = 2 * d;
        if (a > n || b > n || c > n || d == 0) {
            cout << -1 << '\n';
        } else {
            int ans = c + d;
            if (ans > n) ans -= n;
            cout << ans << '\n';
        }
    }
    return 0;
}
'''),
    },
    {
        "id": "cf-1020B",
        "name": "Div 2 B - Badge",
        "source": "CF",
        "url": "https://codeforces.com/contest/1020/problem/B",
        "tags": ["Functional Graph"],
        "summary": "For every starting vertex in a functional graph, output the first vertex visited twice.",
        "analysis": "Each node has exactly one outgoing edge. Starting from i, follow pointers while marking vertices seen during this walk. The first repeated vertex is the answer for i. The constraints are small enough for O(n^2) simulation.",
        "visualization": "Following pointers creates a tail leading into a cycle; the first repeated node is where the walk enters the already-seen part.",
        "diagram": "flowchart LR\n  A[start i] --> B[follow p[u]]\n  B --> C{seen in this walk?}\n  C -- no --> B\n  C -- yes --> D[answer u]",
        "verification": "Checked self-loops, pure cycles, and tails into cycles.",
        "code": cpp(r'''
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];
    for (int start = 1; start <= n; start++) {
        vector<int> seen(n + 1, 0);
        int u = start;
        while (!seen[u]) {
            seen[u] = 1;
            u = p[u];
        }
        if (start > 1) cout << ' ';
        cout << u;
    }
    cout << '\n';
    return 0;
}
'''),
    },
]


def add_simple_problem(problem_id, name, source, url, tags, summary, analysis, visualization, diagram, verification, body):
    PROBLEMS.append({
        "id": problem_id,
        "name": name,
        "source": source,
        "url": url,
        "tags": tags,
        "summary": summary,
        "analysis": analysis,
        "visualization": visualization,
        "diagram": diagram,
        "verification": verification,
        "code": cpp(body),
    })


add_simple_problem(
    "cf-1020B-placeholder", "", "", "", [], "", "", "", "", "", "int main(){return 0;}"
)
PROBLEMS.pop()


def slug(s: str) -> str:
    return re.sub(r"[^a-z0-9]+", "-", s.lower()).strip("-")


def quote_mermaid_labels(diagram):
    """Quote flowchart node labels so GitHub Mermaid accepts punctuation safely."""
    out_lines = []
    for line in diagram.splitlines():
        rebuilt = []
        i = 0
        while i < len(line):
            if (
                line[i].isalpha()
                and (i == 0 or line[i - 1].isspace() or line[i - 1] == ">")
            ):
                j = i + 1
                while j < len(line) and (line[j].isalnum() or line[j] == "_"):
                    j += 1
                if j < len(line) and line[j] in "[{":
                    opener = line[j]
                    closer = "]" if opener == "[" else "}"
                    k = j + 1
                    end = -1
                    while True:
                        k = line.find(closer, k)
                        if k == -1:
                            break
                        tail = line[k + 1 :].lstrip()
                        if not tail or tail.startswith("--"):
                            end = k
                            break
                        k += 1
                    if end != -1:
                        label = line[j + 1 : end]
                        if label.startswith('"') and label.endswith('"'):
                            rebuilt.append(line[i : end + 1])
                        elif opener == "[":
                            rebuilt.append(f'{line[i:j]}["{label}"]')
                        else:
                            rebuilt.append(f'{line[i:j]}{{"{label}"}}')
                        i = end + 1
                        continue
            rebuilt.append(line[i])
            i += 1
        out_lines.append("".join(rebuilt))
    return "\n".join(out_lines)


def render_readme(p):
    tags = ", ".join(p["tags"])
    return f"""# {p['name']}

- Source: {p['source']}
- USACO Guide ID: `{p['id']}`
- Original problem: [{p['url']}]({p['url']})
- Tags: {tags}
- Solution: [`../../solutions/{p['id']}.cpp`](../../solutions/{p['id']}.cpp)

## Problem Summary

{p['summary']}

This is a paraphrase for study notes. Use the original problem link for the official statement, constraints, and judge-specific details.

## Visualization Description

{p['visualization']}

```mermaid
{quote_mermaid_labels(p['diagram'])}
```

## Approach

{p['analysis']}

## Correctness Notes

The solution keeps the invariant described in the approach and updates only the state that can affect future answers. For query-style problems, preprocessing stores exactly the aggregate needed to answer each query. For graph and tree problems, each selected data structure operation mirrors one allowed change in the represented structure.

## Complexity

See the comments and structure of the C++ solution for the exact loop/data-structure cost. The intended complexity is efficient for the official constraints of the linked problem.

## Verification

{p['verification']}
"""


def main():
    for folder in ["problems", "solutions", "tests"]:
        path = ROOT / folder
        if path.exists():
            shutil.rmtree(path)
        path.mkdir(parents=True, exist_ok=True)

    index_rows = []
    for p in PROBLEMS:
        pdir = ROOT / "problems" / p["id"]
        pdir.mkdir(parents=True, exist_ok=True)
        (pdir / "README.md").write_text(render_readme(p), encoding="utf-8")
        (ROOT / "solutions" / f"{p['id']}.cpp").write_text(p["code"], encoding="utf-8")
        index_rows.append(f"| `{p['id']}` | {p['source']} | [{p['name']}](problems/{p['id']}/README.md) | [{', '.join(p['tags'])}] | [C++](solutions/{p['id']}.cpp) |")

    readme = """# USACO Guide Very Easy Solutions

This repository contains study notes and C++ solutions for every problem currently returned by the USACO Guide problems page with `difficulty=Very Easy`.

Each problem folder includes:

- a paraphrased problem summary
- a visualization description
- a Mermaid diagram where it helps explain the idea
- an approach analysis
- correctness and verification notes
- a linked C++ solution

The official statements remain at their original judge links. These notes intentionally avoid copying full problem statements.

## Problem Index

| ID | Source | Problem | Tags | Solution |
| --- | --- | --- | --- | --- |
""" + "\n".join(index_rows) + """

## Local Verification

Compile all solutions:

```bash
python3 tests/compile_all.py
```

Run the small smoke tests:

```bash
python3 tests/smoke_tests.py
```

The smoke tests are not a replacement for judge submission, but they catch syntax errors and check representative sample-style cases.
"""
    (ROOT / "README.md").write_text(readme, encoding="utf-8")

    compile_script = r'''from pathlib import Path
import subprocess
import sys

root = Path(__file__).resolve().parents[1]
build = root / "tests" / "build"
build.mkdir(exist_ok=True)
failed = []

for src in sorted((root / "solutions").glob("*.cpp")):
    out = build / src.stem
    cmd = ["g++", "-std=c++17", "-O2", "-Wall", "-Wextra", str(src), "-o", str(out)]
    res = subprocess.run(cmd, capture_output=True, text=True)
    if res.returncode != 0:
        failed.append((src.name, res.stderr))
    else:
        print(f"compiled {src.name}")

if failed:
    for name, err in failed:
        print(f"\nFAILED {name}\n{err}", file=sys.stderr)
    sys.exit(1)
'''
    (ROOT / "tests" / "compile_all.py").write_text(compile_script, encoding="utf-8")

    smoke_script = r'''from pathlib import Path
import subprocess
import sys

root = Path(__file__).resolve().parents[1]
build = root / "tests" / "build"

tests = {
    "cf-4A": ("8\n", "YES\n"),
    "cf-546A": ("3 17 4\n", "13\n"),
    "cfgym-102951B": ("6 15\n4 3 8 4 7 3\n", "4\n"),
    "ys-StaticRangeSum": ("5 3\n1 2 3 4 5\n0 5\n1 3\n2 2\n", "15\n5\n0\n"),
    "ys-ZAlgorithm": ("ababa\n", "5 0 3 0 1\n"),
    "cf-1593A": ("3\n0 0 0\n10 75 15\n13 13 17\n", "1 1 1\n66 0 61\n5 5 0\n"),
    "cf-1560B": ("4\n2 6 4\n4 3 2\n6 2 4\n2 4 10\n", "8\n-1\n8\n-1\n"),
    "cf-231A": ("3\n1 1 0\n1 1 1\n1 0 0\n", "2\n"),
    "cf-279B": ("4 5\n3 1 2 1\n", "3\n"),
    "cses-1633": ("3\n", "4\n"),
    "cses-1634": ("3 11\n1 5 7\n", "3\n"),
    "cses-1660": ("5 7\n2 4 1 2 7\n", "3\n"),
    "cses-1733": ("ababab\n", "2 4 6\n"),
    "cses-1753": ("aaaaa\naa\n", "4\n"),
    "cses-1631": ("3\n2 8 3\n", "16\n"),
    "kattis-BasketballOneOnOne": ("A2B1A2B2A1B2A2B1A2B2A1\n", "A\n"),
    "lc-FindPivotIndex": ("6\n1 7 3 6 5 6\n", "3\n"),
    "usaco-807": ("3 10 8 2\n", "3\n"),
    "cf-1020B": ("5\n2 3 4 5 3\n", "3 3 3 4 5\n"),
    "spoj-DynamicConnectivity": ("5 11\nconn 1 5\nadd 1 2\nadd 1 3\nadd 3 4\nadd 5 4\nconn 1 5\nrem 4 5\nconn 1 5\nrem 3 4\nadd 3 5\nconn 1 5\n", "NO\nYES\nNO\nYES\n"),
    "usaco-715": ("5 3 2\n2\n4\n", "1\n"),
    "usaco-691": ("5\nH\nP\nS\nH\nP\n", "3\n"),
    "usaco-572": ("5 3\n1\n2\n3\n2\n1\n1 5\n2 4\n3 3\n", "2 2 1\n0 2 1\n0 0 1\n"),
    "cses-1647": ("5 3\n5 2 4 1 3\n1 5\n2 3\n4 4\n", "1\n2\n1\n"),
    "cses-2079": ("4\n1 2\n1 3\n1 4\n", "1\n"),
    "hr-BubbleSort": ("3\n3 2 1\n", "Array is sorted in 3 swaps.\nFirst Element: 1\nLast Element: 3\n"),
    "hdu-5306": ("1\n5 5\n1 5 3 4 2\n2 1 5\n1 2 4\n0 2 4 3\n1 1 5\n2 2 4\n", "15\n5\n3\n9\n"),
    "cf-20C": ("5 6\n1 2 2\n2 5 5\n1 3 4\n3 4 1\n4 5 1\n2 3 1\n", "1 2 3 4 5\n"),
    "cf-2257C": ("1\n3\n1 1\n3\n1 2 3\n", "2 2 3\n"),
    "coci-21-vlak": ("1\na\n1\nb\n", "Nina\n"),
    "ioi-08-TypePrinter": ("1\nab\n", "3\na\nb\nP\n"),
}

failed = []
for stem, (inp, expected) in tests.items():
    exe = build / stem
    if not exe.exists():
        failed.append((stem, "missing executable; run compile_all.py first"))
        continue
    res = subprocess.run([str(exe)], input=inp, capture_output=True, text=True)
    if res.stdout != expected:
        failed.append((stem, f"expected {expected!r}, got {res.stdout!r}, stderr {res.stderr!r}"))
    else:
        print(f"passed {stem}")

if failed:
    for stem, err in failed:
        print(f"\nFAILED {stem}: {err}", file=sys.stderr)
    sys.exit(1)
'''
    (ROOT / "tests" / "smoke_tests.py").write_text(smoke_script, encoding="utf-8")


if __name__ == "__main__":
    main()
