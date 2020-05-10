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
#include "ACautomaton.hpp"

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
    pair < int , vector < string > > SPFA(const string start, const string end) const;//SPFA最短路
    pair < int , vector < string > > Dijkstra(const string start, const string end) const; //Dijkstra最短路
    pair < int , vector < string > > Floyd(const string start, const string end) const; //Floyd最短路
    void StorePath(int x, int s, int pre[], vector < string > &path) const; //最短路径存到容器中
    pair < int , vector < string > > TSP(const string start) const; //状态压缩dp求解旅行商问题
    pair<vector<int>, pair<vector<string>, vector<string>>> MultiKeySearch(ACautomaton &AC) const;
    pair<int, pair<vector<string>, vector<string>>> AddNode(const string str, const string sight_info, const vector<string> &sight, const vector<int> &len); //增加景点
    int AddEdge(const string str1, const string str2, const int length); //增加边
    vector<string> GetSights() const; //返回所有景点到游客类构造出AC自动机
    void BfsInFile(const int &index, vector < int > &done, ofstream &Infile); //BFS周围点保存图以防止保存重复信息
    void InitGraph(); //读取文件建立图: 邻接表与邻接矩阵
    void SaveGraph(); //保存地图至文件(用邻接表)
    void LoadTag(); //加载标记数组
    void SaveTag(); //保存标记数组
    void LoadSightInfo(); //加载景点信息
    void SaveSightInfo(); //保存景点信息
    void Puts(); //输出图的所有信息
    
    int changelength(string NAME1,string NAME2,int newlength);//路径长度修改
    int changename(string NAME,string newname);//景点名称修改
    int G_delete(string NAME); //删除景点
    int E_delete(string NAME1,string NAME2); //删除边
    int G_Attractions(string NAME)const; //景点介绍
    void G_name()const;
    int changeinfo(string NAME,string newinformation); //修改景点信息
    void PutsMap() const; //输出地图

    
    
    
    
    
    
    
    
    
    ~Graph() {}; //析构函数
 private:
    RBTree < string , int > name; //名字对应表
    vector < string > info; //数字对应景点名字
    vector < vector < edge > > G; //邻接表
    vector < vector < int > > M; //邻接矩阵
    vector < int > Tag; //标记数组
    vector < string > SightInfo; //景点信息
    int count; //景点数量
};

#endif /* Graph_hpp */
