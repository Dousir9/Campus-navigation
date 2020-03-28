//
//  Tourist.cpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "Tourist.hpp"

void Tourist::Travel(const Graph &G) const{
    cout << "是否遍历地图?(y/n)";
    char ch;
    cin >> ch;
    if (ch == 'y') {
        clock_t s, e;
        s = clock();
        G.Input();
        e = clock();
        di("Travel")
        rt(s, e);
    }
    MY_PAUSE();
}

void Tourist::MinLength(const Graph &G) const{
    printf("请输入起点和终点：");
    string start, end;
    cin >> start >> end;
    
    clock_t s, e;
    s = clock();
    pair < int , vector < string > > p = G.SPFA(start, end);
    if (p.first > 0) {
        printf("最短路径为：%d\n", p.first);
        printf("该路径为:\n");
        for (int i = 0, len = (int) p.second.size(); i < len; i++) {
            cout << p.second[i];
            if (i != len - 1) {
                printf("->");
            } else {
                printf("\n");
            }
        }
    } else if (p.first == -1) {
        cout << start << "不存在" << '\n';
    } else if (p.first == -2) {
        cout << end << "不存在" << '\n';
    } else {
        cout << start << "和" << end << "都不存在" << '\n';
    }
    e = clock();
    di("SPFA")
    rt(s, e);
    
    s = clock();
    pair < int , vector < string > > q = G.Dijkstra(start, end);
    if (q.first > 0) {
        printf("最短路径为：%d\n", q.first);
        printf("该路径为:\n");
        for (int i = 0, len = (int) q.second.size(); i < len; i++) {
            cout << q.second[i];
            if (i != len - 1) {
                printf("->");
            } else {
                printf("\n");
            }
        }
    } else if (q.first == -1) {
        cout << start << "不存在" << '\n';
    } else if (q.first == -2) {
        cout << end << "不存在" << '\n';
    } else {
        cout << start << "和" << end << "都不存在" << '\n';
    }
    e = clock();
    di("Dijkstra")
    rt(s, e);
    
    s = clock();
    pair < int , vector < string > > r = G.Floyd(start, end);
    if (r.first > 0) {
        printf("最短路径为：%d\n", r.first);
        printf("该路径为:\n");
        for (int i = (int) r.second.size() - 1; i >= 0; i--) {
            cout << r.second[i];
            if (i != 0) {
                printf("->");
            } else {
                printf("\n");
            }
        }
    } else if (r.first == -1) {
        cout << start << "不存在" << '\n';
    } else if (r.first == -2) {
        cout << end << "不存在" << '\n';
    } else {
        cout << start << "和" << end << "都不存在" << '\n';
    }
    e = clock();
    di("Floyd")
    rt(s, e);
    
    MY_PAUSE();
}

void Tourist::TSP(const Graph &G) const {
    printf("请输入起点：");
    string start;
    cin >> start;
    
    clock_t s, e;
    s = clock();
    pair < int , vector < string > > p = G.TSP(start);
    if (p.first == -1) {
        printf("图的规模大于15，无法求解\n");
    } else if (p.first == -2) {
        cout << start << "不存在" << '\n';
    } else {
        printf("最快游览路线的长度为%d\n", p.first);
        printf("该路径为:\n");
        for (int i = 0, len = (int) p.second.size(); i < len; i++) {
            cout << p.second[i];
            if (i != len - 1)
                printf("->");
            else
                printf("\n");
        }
    }
    e = clock();
    di("TSP")
    rt(s, e);
    
    MY_PAUSE();
}
