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
#include "Trie.hpp"

int main() {
#ifdef debug
    clock_t s, e;
    s = clock();
#endif
    Graph G;
    G.InitGraph(); //只创建一次地图
#ifdef debug
    e = clock();
    di("InitGraph")
    rt(s, e);
#endif

#ifdef debug
    s = clock();
#endif
    Trie T;
    T.InitTrie(); //创建字典树
#ifdef debug
    e = clock();
    di("InitTrie")
    rt(s, e);
#endif
    Menu M;
    M.MenuRun(G, T);
    return 0;
}



//const int N = 1e3;
//const int M = 1e5;
//const int MAX_LEN = 500;
//pair<int, int> e[M + 5];
//map<pair<int, int>, int> h;

//    freopen("/Users/xumingfei/Desktop/git/Campus-navigation/基于清华大学的校园导游系统/SQL/data.txt", "w", stdout);
//    for (int i = 1; i < N; i++) {
//        int fa = rand() % i + 1;
//        e[i] = make_pair(fa, i + 1);
//        h[e[i]] = h[make_pair(i + 1, fa)] = rand() % MAX_LEN + 1;
//    }
//    for (int i = N; i <= M; i++) {
//        int x, y;
//        do {
//            x = rand() % N + 1;
//            y = rand() % N + 1;
//        } while (x == y || h[make_pair(x, y)]);
//        e[i] = make_pair(x, y);
//        h[e[i]] = h[make_pair(y, x)] = rand() % MAX_LEN + 1;
//    }
//    printf("%d\n", N);
//    for (int i = 1; i <= N; i++) {
//        printf("%d\n", i);
//    }
//    random_shuffle(e + 1, e + M + 1);
//    for (int i = 1; i <= M; i++) {
//        auto it = h.find(e[i]);
//        printf("%d %d %d\n", e[i].first, e[i].second, it->second);
//    }
//    fclose(stdout);


//    const int N = 10000000;
//    clock_t s, e;
//    s = clock();
//    RBTree<int, int> T1;
//    for (int i = 0; i < N; i++) {
//        T1.Insert(event<int, int>(i, i));
//    }
//    e = clock();
//    di("MyMapInsert")
//    rt(s, e);
//
//    s = clock();
//    map<int, int> T2;
//    for (int i = 0; i < N; i++) {
//        T2.insert(pair<int, int>(i, i));
//    }
//    e = clock();
//    di("C++MapInsert")
//    rt(s, e);
//
//    s = clock();
//    for (int i = 0; i < N; i++) {
//        auto it = T1.Find(i);
//    }
//    e = clock();
//    di("MyMapFind")
//    rt(s, e);
//
//    s = clock();
//    for (int i = 0; i < N; i++) {
//        auto it = T2.find(i);
//    }
//    e = clock();
//    di("C++MapFind")
//    rt(s, e);
//
//    cout << T1.FindIndex(100) << '\n';
//    Trie T;
//    for (int i = 0; i < 10; i++) {
//        printf("%d\n", i);
//        string str;
//        cin >> str;
//        T.Insert(str);
//        cin >> str;
//        auto p = T.Find(str);
//        T.Insert(str);
//        if (p.first == -1) {
//            printf("未找到相关结果\n");
//        } else {
//            printf("结果如下\n");
//            sort(p.second.begin(), p.second.end());
//            for (int i = 0; i < p.second.size(); i++) {
//                cout << p.second[i].info << "  " << p.second[i].val << endl;
//            }
//        }
//    }
//    T.SaveTrie();
//
//    ACautomaton AC;
//    string a = "北京好";
//    string b = "京好";
//    string c = "北八舍";
//    string d = "北京坏";
//    string e = "京好坏";
//    AC.Insert(a);
//    AC.Insert(a);
//    AC.Insert(b);
//    AC.Insert(c);
//    AC.Insert(d);
//    AC.Insert(e);
//    printf("sffsdf\n");
//    AC.GetFail();
//    printf("sffsdf\n");
//    string str = "舍八北京好坏京北";
//    int x = AC.Query(str);
//    printf("%d\n", x);
//    北京
//    北八
//    北西
//    北
//    Trie T;
//    string a = "我", b = "我家在济南", c = "你家在哪", e = "我家在莱州";
//    //string a = "1234", b = "1345", c = "233";
//    T.Insert(a);
//    T.Insert(b);
//    T.Insert(c);
//    T.Insert(e);
//    //T.Puts();
//    string d = "我";
//    pair<int, vector<string>> p = T.Find(d);
//    for (int i = 0; i < p.second.size(); i++) {
//        cout << p.second[i] << endl;
//    }


//const int N = 10000000;
//cout << '\n' << "                                                测试10000000个点" << '\n';
//clock_t s, e;
//s = clock();
//RBTree<int, int> T1;
//for (int i = 0; i < N; i++) {
//    T1.Insert(event<int, int>(i, i));
//}
//e = clock();
//di("MyMapInsert")
//rt(s, e);
//cout << '\n';
//s = clock();
//map<int, int> T2;
//for (int i = 0; i < N; i++) {
//    T2.insert(pair<int, int>(i, i));
//}
//e = clock();
//di("C++MapInsert")
//rt(s, e);
//cout << '\n';
//s = clock();
//for (int i = 0; i < N; i++) {
//    auto it = T1.Find(i);
//}
//e = clock();
//di("MyMapFind")
//rt(s, e);
//cout << '\n';
//s = clock();
//for (int i = 0; i < N; i++) {
//    auto it = T2.find(i);
//}
//e = clock();
//di("C++MapFind")
//rt(s, e);
//cout << '\n';
//s = clock();
//for (int i = 0; i < N; i++) {
//    T1.Delete(i);
//}
//e = clock();
//di("MyMapDelete")
//rt(s, e);
//cout << '\n';
//s = clock();
//for (int i = 0; i < N; i++) {
//    T2.erase(i);
//}
//e = clock();
//di("C++MapDelete")
//rt(s, e);
