//
//  Graph.hpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include "Global.hpp"
#include "RBTree.hpp"

const int INF = 0x3f3f3f3f;

//边
struct edge {
    int to;
    int length;
    edge(int a, int b) {
        to = a;
        length = b;
    }
};

//图类
class Graph {
 public:
    Graph() {}; //默认构造函数
    void InitGraph(); //读取文件建立图: 邻接表与邻接矩阵
    void SaveGraph() const; //保存地图至文件(用邻接表)
    void BfsInFile(const int &index, vector < int > &done, ofstream &Infile, bool &flag) const; //BFS周围点保存图以防止保存重复信息
    void Input() const;
    pair < int , vector < string > > SPFA(const string start, const string end) const;//SPFA最短路
    pair < int , vector < string > > Dijkstra(const string start, const string end) const; //Dijkstra最短路
    pair < int , vector < string > > Floyd(const string start, const string end) const; //Floyd最短路
    void StorePath(int x, int s, int pre[], vector < string > &path) const; //最短路径存到容器中
    pair < int , vector < string > > TSP(const string start) const; //状态压缩dp求解旅行商问题
    ~Graph() {}; //析构函数
 private:
    RBTree < string , int > name; //名字对应表
    vector < string > info; //数字对应景点名字
    vector < vector < edge > > G; //邻接表
    vector < vector < int > > M;//邻接矩阵
    int count; //景点数量
};

#endif /* Graph_hpp */
