//
//  main.cpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "Menu.hpp"
#include "Graph.hpp"
#include "RBTree.hpp"

//const int N = 1e3;
//const int M = 1e5;
//const int MAX_LEN = 500;
//pair<int, int> e[M + 5];
//map<pair<int, int>, int> h;

int main() {
//    freopen("/Users/xumingfei/Desktop/git/Campus-navigation/基于清华大学的校园导游系统/SQL/data.txt", "w", stdout);
//    for (int i = 1; i < N; i++) {
//        int fa = rand() % i + 1;
//        e[i] = make_pair(fa, i + 1);
//        h[e[i]] = h[make_pair(i + 1, fa)] = MAX_LEN;
//    }
//    for (int i = N; i <= M; i++) {
//        int x, y;
//        do {
//            x = rand() % N + 1;
//            y = rand() % N + 1;
//        } while (x == y || h[make_pair(x, y)]);
//        e[i] = make_pair(x, y);
//        h[e[i]] = h[make_pair(y, x)] = rand() % MAX_LEN;
//    }
//    random_shuffle(e + 1, e + M + 1);
//    for (int i = 1; i <= M; i++) {
//        auto it = h.find(e[i]);
//        printf("%d %d %d\n", e[i].first, e[i].second, it->second);
//    }
//    fclose(stdout);
    

    clock_t s, e;
    s = clock();
    Graph G;
    G.InitGraph(); //只创建一次地图
    e = clock();
    di("InitGraph")
    rt(s, e);

    Menu M;
    M.MenuRun(G);
    return 0;
}
