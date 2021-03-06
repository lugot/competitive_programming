#include<bits/stdc++.h>
using namespace std;

struct union_find {
	vector<int> p, rank, size_of_set;
    int num_sets;

    union_find(int N) { 
        p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i;
        rank.assign(N, 0);
        size_of_set.assign(N, 1);
        num_sets = N;
    }
    int find_set(int i) {
        return (p[i] == i) ? i : (p[i] = find_set(p[i])); 
    }
    bool same_set(int i, int j) {
        return find_set(i) == find_set(j);
    }
    int set_size(int i) {
        return size_of_set[find_set(i)];
    }
    void union_set(int i, int j) {
        if (!same_set(i, j)){ 
            int x = find_set(i), y = find_set(j);
            if (rank[x] > rank[y]) swap(x,y);
            p[x] = y;
            if (rank[x] == rank[y]) rank[y]++;
            size_of_set[y] += size_of_set[x];
            num_sets--;
    }} 
};

typedef int wtype; // change weighttype

typedef tuple<wtype, int, int> edge;
typedef vector<edge> edgelist;

typedef pair<int, wtype> iw;
typedef pair<wtype, int> wi;
typedef vector<iw> viw;
typedef vector<int> vi;
typedef vector<viw> adjlist;

int n, m;  
edgelist elist;
adjlist alist;

// KRUSKAL, O(mlogm)
union_find uf(0);
wtype kruskal() {
    wtype mst_cost = 0;

    sort(elist.begin(), elist.end());
    uf = union_find(n);

    for (int i=0; i<m; i++) {
        auto [w, u, v] = elist[i];

        if (uf.same_set(u, v)) continue;

        mst_cost += w;
        uf.union_set(u, v);
    }

    return mst_cost;
}

// PRIM, O(mlogm)
vi taken;
priority_queue<wi, vector<wi>, greater<wi>> pq;

void process(int x) {
    taken[x] = 1;
    for (auto [u, w]: alist[x]) {
        if (taken[u]) continue; 
        pq.push({w, u});
    } 
}
wtype prim() { // O(mlogm)
    wtype mst_cost = 0;

    taken = vi(n, 0);
    int num_taken = 0;

    process(0);

    while (!pq.empty()) { 
        auto [w, u] = pq.top(); pq.pop();

        if (taken[u]) continue;

        mst_cost += w;
        process(u);

        num_taken++;
        if (num_taken == n-1) break;
    }

    return mst_cost;
}

int main() {

    int T;
    cin >> T;

    while (T--) {
        int M, C;
        cin >> M >> C;
    
        alist = adjlist(C);
        n = C;
        m = C*(C-1)/2;

        int comb = C*(C-1)/2;
        while (comb--) {
            int i, j, D;
            cin >> i >> j >> D;

            alist[i].push_back({j, D});
            alist[j].push_back({i, D});
            elist.push_back({D, i, j});
        }

        //if (kruskal() + C <= M) cout << "yes" << endl;
        //else                cout << "no" << endl;
        if (prim() + C <= M) cout << "yes" << endl;
        else             cout << "no" << endl;
    }
    



    return 0;
}
