//
//  Graph.cpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "Graph.hpp"

//读取文件建立图: 邻接表与邻接矩阵
void Graph::InitGraph() {
    ifstream OutFile; //读文件
    OutFile.open(GRAPH_INFO_FILE_NAME);
    int cnt = 0; //有几个不同的景点
    //建立邻接表
    while (!OutFile.eof()) {
        string first_name, second_name; //两个相连的景点名字
        int length; //两个景点之间的距离
        OutFile >> first_name >> second_name >> length;
        int first_index, second_index; //两个景点在图G中的下标
        pair < event < string*, int* >, bool >* it1;
        it1 = name.Find(first_name);
        if (it1->second == false) { //还未读入该景点
            vector < edge > v;
            name.Insert(event < string, int > (first_name, cnt));
            G.push_back(v);
            info.push_back(first_name);
            first_index = cnt;
            cnt++;
        } else {
            first_index = *it1->first.second; //该景点在图中下标
        }
        delete it1;
        pair < event < string*, int* >, bool >* it2;
        it2 = name.Find(second_name);
        if (it2->second == false) { //还未读入该景点
            vector < edge > v;
            name.Insert(event < string, int > (second_name, cnt));
            G.push_back(v);
            info.push_back(second_name);
            second_index = cnt;
            cnt++;
        } else {
            second_index = *it2->first.second; //该景点在图中下标
        }
        delete it2;
        G[first_index].push_back(edge(second_index, length)); //邻接表
        G[second_index].push_back(edge(first_index, length)); //邻接表
    }
    //建立邻接矩阵
    M.resize(cnt);
    for (int i = 0; i < cnt; i++) {
        M[i].resize(cnt);
        for (int j = 0; j < cnt; j++) {
            M[i][j] = INF;
        }
    }
    for (int i = 0, len1 = (int) G.size(); i < len1; i++) {
        for (int j = 0, len2 = (int) G[i].size(); j < len2; j++) {
            M[i][G[i][j].to] = G[i][j].length;
        }
    }
}

//BFS周围点保存图以防止保存重复信息
void Graph::BfsInFile(const int &index, vector < int > &done, ofstream &Infile, bool &flag) const {
    int len = int(G[index].size());
    for (int i = 0; i < len; i++) {
        if (!done[G[index][i].to]) {
            if (flag == false) {
                flag = true;
            } else {
                Infile << '\n';
            }
            Infile << info[index] << ' ' << info[G[index][i].to] << ' ' << G[index][i].length;
        }
    }
}

//写入文件保存图
void Graph::SaveGraph() const {
    ofstream InFile; //写入
    InFile.open(GRAPH_INFO_FILE_NAME);
    bool flag = false; //控制写入文件的开头时是否换行
    int len = int(G.size());
    vector < int > done(len);
    for (int i = 0; i < len; i++) {
        BfsInFile(i, done, InFile, flag);
        done[i] = 1;
    }
}

//图信息输出遍历
void Graph::Input() const {
    int len1 = int(G.size());
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < G[i].size(); j++) {
            cout << info[i] << "->" << info[G[i][j].to] << "  " << G[i][j].length << '\n';
        }
    }
}

