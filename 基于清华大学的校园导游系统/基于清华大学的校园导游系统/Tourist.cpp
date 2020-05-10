//
//  Tourist.cpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "Tourist.hpp"

void Tourist::ShowMap(const Graph &G) const {
    G.PutsMap();
}

//路线推荐
void Tourist::Recommend(const Graph &G) const {
    cout << NEXT_BLANK; printf("      ①  经典路线\n\n");
    cout << NEXT_BLANK; printf("      ②  最快游览路线\n\n\n");
    cout << "                                                       ";
    string str;
    cin >> str;
    if (!CHECK_INT(str) || str.size() > 1) {
        cout << NEXT_BLANK; printf("         你的输入有误\n");
        return;
    }
    int ch = str[0];
    if (ch == '1') {
        printf("\n经典路线为：\n东门->图书馆->行政楼->明德楼->弘毅楼->篮球场->操场->南苑餐厅->南一->小山->信息楼->警务亭->驾校->北苑餐厅->北八\n");
    } else if (ch == '2') {
        TSP(G);
    }
}

//搜索提示
void Tourist::SearchTip(Trie &T) {
    cout << NEXT_BLANK; printf("     请输入关键词:");
    string str;
    cin >> str;
    
#ifdef debug
    clock_t s, e;
    s = clock();
#endif
    
    auto p = T.Find(str);
    T.Insert(str);
    if (p.first == -1) {
        cout << NEXT_BLANK; printf("     未找到相关搜索信息\n\n");
        return;
    }
    sort(p.second.begin(), p.second.end());
    cout << NEXT_BLANK; printf("        搜索提示如下:");
    int cnt = 1;
    for (auto it = p.second.begin(); it != p.second.end(); ++it) {
        cout << NEXT_BLANK; cout << "          + " << it->info;
        if (cnt++ > 10) {
            break;
        }
    }
    cout << '\n' << '\n';
    
#ifdef debug
    e = clock();
    di("Trie")
    di("Find")
    rt(s, e);
    cout << '\n';
#endif
}

//热门景点
void Tourist::HotSights(const Graph &G, Trie &T) {
#ifdef debug
    clock_t st, e;
    st = clock();
#endif
    
    ACautomaton AC;
    vector<string> sights = G.GetSights();
    for (int i = 0; i < sights.size(); i++) {
        AC.Insert(sights[i]);
    }
    AC.GetFail();
    string s = "", str;
    auto p = T.Find(s);
    for (auto it = p.second.begin(); it != p.second.end(); ++it) {
        for (int i = 0; i < it->val; i++) {
            str += it->info;
        }
    }
    AC.RecordSearch(str);
    p = AC.Find(s); //空字符串
    int x = (int) p.second.size();
    if (x == 0) {
        cout << NEXT_BLANK; printf("        暂无热门景点\n");
        return;
    }
    if (x > 5) {
        cout << NEXT_BLANK; printf("      热门景点排名前5:\n\n");
    } else {
        cout << NEXT_BLANK; printf("      热门搜索排名前%d:\n\n", x);
    }
    sort(p.second.begin(), p.second.end());
    x = 1;
    printf("\n                            排 名                      热 度                      景 点\n");
    for (auto it = p.second.begin(); it != p.second.end(); ++it) {
        printf("\n                             %2d                         %-2d", x, it->val);
        cout << "                        " << it->info << '\n';
        if (x++ == 5)
            break;
    }
    cout << '\n' << '\n';
    
#ifdef debug
    e = clock();
    di("ACautomaton")
    di("Insert")
    di("Record")
    di("Find")
    rt(st, e);
    cout << '\n';
#endif
}

//热门搜索
void Tourist::HotSearch(Trie &T) {
#ifdef debug
    clock_t s, e;
    s = clock();
#endif
    
    string str = "";
    auto p = T.Find(str);
    int x = (int) p.second.size();
    if (x == 0) {
        cout << NEXT_BLANK; printf("        暂无搜索记录\n");
        return;
    }
    if (x > 10) {
        cout << NEXT_BLANK; printf("      热门搜索排名前10:\n");
    } else {
        cout << NEXT_BLANK; printf("      热门搜索排名前%d:\n", x);
    }
    sort(p.second.begin(), p.second.end());
    x = 1;
    printf("\n                            排 名                      热 度                      信 息\n");
    for (auto it = p.second.begin(); it != p.second.end(); ++it) {
        printf("\n                             %2d                         %-2d", x, it->val);
        cout << "                        " << it->info << '\n';
        if (x++ == 10)
            break;
    }
    cout << '\n' << '\n';
    
#ifdef debug
    e = clock();
    di("Trie")
    di("Find")
    rt(s, e);
    cout << '\n';
#endif
}

//多关键词搜索
void Tourist::MultiKeywordSearch(const Graph &G, Trie &T) {
#ifdef debug
    clock_t s, e;
    s = clock();
#endif
    
    cout << NEXT_BLANK; printf("    请输入关键字的个数:");
    string sum;
    cin >> sum;
    if (!CHECK_INT(sum)) {
        cout << NEXT_BLANK; printf("        你的输入有误\n\n");
        return;
    }
    ACautomaton AC;
    int n = TO_INT(sum);
    string str;
    for (int i = 0; i < n; i++) {
        cout << NEXT_BLANK; printf("   请输入第%d个关键词:", i + 1);
        cin >> str;
        AC.Insert(str);
        T.Insert(str);
    }
    AC.GetFail();
    auto it = G.MultiKeySearch(AC);
    if (it.first.size() == 0) {
        cout << NEXT_BLANK; printf("      未搜索到相关信息\n");
        return;
    }
    cout << NEXT_BLANK; printf("   为您找到如下匹配信息:\n\n");
    for (int i = 0; i < it.first.size(); i++) {
        cout << NEXT_BLANK; cout << "   " << i + 1 << " " << it.second.first[i] << "  匹配度为:" << it.first[i] << '\n' << '\n';
        cout << "    " << it.second.second[i] << '\n' << '\n';
    }
    cout << '\n';
    
#ifdef debug
    e = clock();
    di("ACautomaton")
    di("Insert")
    di("Query")
    rt(s, e);
    cout << '\n';
#endif
}

//景点间最短路径
void Tourist::MinLength(const Graph &G) const{
    cout << NEXT_BLANK; printf(" 请输入起点和终点：");
    string start, end;
    cin >> start >> end;
    
#ifdef debug
    clock_t s, e;
    s = clock();
#endif

    pair < int , vector < string > > p = G.SPFA(start, end);
    if (p.first > 0) {
        cout << NEXT_BLANK; printf("     最短路径长度为：%d\n", p.first);
        cout << NEXT_BLANK; printf("         该路径为:\n\n");
        for (int i = 0, len = (int) p.second.size(); i < len; i++) {
            if (i % 3 == 0)
                cout << "\n\n                                               ";
            if (i != 0)
                cout << "->";
            cout << p.second[i];
        }
        cout << '\n';
    } else if (p.first == -1) {
        cout << NEXT_BLANK; cout << "        " << start << "不存在" << '\n';
    } else if (p.first == -2) {
        cout << NEXT_BLANK; cout << "        " << end << "不存在" << '\n';
    } else {
        cout << NEXT_BLANK; cout << "    " << start << "和" << end << "都不存在" << '\n';
    }
    cout << '\n';
    
#ifdef debug
    e = clock();
    di("SPFA")
    rt(s, e);
    
    s = clock();
    pair < int , vector < string > > q = G.Dijkstra(start, end);
//    if (q.first > 0) {
//        cout << NEXT_BLANK; printf("     最短路径长度为：%d\n", q.first);
//        cout << NEXT_BLANK; printf("         该路径为:\n\n");
//        for (int i = 0, len = (int) q.second.size(); i < len; i++) {
//            if (i % 3 == 0)
//                cout << "\n\n                                               ";
//            if (i != 0)
//                cout << "->";
//            cout << q.second[i];
//        }
//    } else if (q.first == -1) {
//        cout << NEXT_BLANK; cout << "        " << start << "不存在" << '\n';
//    } else if (q.first == -2) {
//        cout << NEXT_BLANK; cout << "        " << end << "不存在" << '\n';
//    } else {
//        cout << NEXT_BLANK; cout << "    " << start << "和" << end << "都不存在" << '\n';
//    }
//    cout << '\n';
    
    e = clock();
    di("Dijkstra")
    rt(s, e);
    
    s = clock();
    
    pair < int , vector < string > > r = G.Floyd(start, end);
//    if (r.first > 0) {
//        cout << NEXT_BLANK; printf("     最短路径长度为：%d\n", r.first);
//        cout << NEXT_BLANK; printf("         该路径为:\n\n");
//        for (int i = (int) r.second.size() - 1; i >= 0; i--) {
//            if (i % 3 == 0)
//                cout << "\n\n                                               ";
//            if (i != 0)
//                cout << "->";
//            cout << r.second[i];
//        }
//    } else if (r.first == -1) {
//        cout << NEXT_BLANK; cout << "        " << start << "不存在" << '\n';
//    } else if (r.first == -2) {
//        cout << NEXT_BLANK; cout << "        " << end << "不存在" << '\n';
//    } else {
//        cout << NEXT_BLANK; cout << "    " << start << "和" << end << "都不存在" << '\n';
//    }
    cout << '\n';
    
    e = clock();
    di("Floyd")
    rt(s, e);
    cout << '\n';
#endif
}

void Tourist::TSP(const Graph &G) const {
    cout << NEXT_BLANK; printf("     请输入起点：");
    string start;
    cin >> start;
    
#ifdef debug
    clock_t s, e;
    s = clock();
#endif

    pair < int , vector < string > > p = G.TSP(start);
    if (p.first == -1) {
        cout << NEXT_BLANK; printf("  图的规模大于15无法求解\n");
    } else if (p.first == -2) {
        cout << NEXT_BLANK; cout << "       " << start << "不存在" << '\n';
    } else {
        cout << NEXT_BLANK; printf(" 最快游览路线的长度为%d\n", p.first);
        cout << NEXT_BLANK; printf("        该路径为:\n\n");
        for (int i = 0, len = (int) p.second.size(); i < len; i++) {
            if (i % 6 == 0)
                cout << "\n\n                                ";
            if (i != 0)
                cout << "->";
            cout << p.second[i];
        }
        cout << '\n';
    }

#ifdef debug
    e = clock();
    di("TSP")
    rt(s, e);
    cout << '\n';
#endif
}
