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
    count = 0; //有几个不同的景点
    //建立邻接表
    while (!OutFile.eof()) {
        string first_name, second_name; //两个相连的景点名字
        int length; //两个景点之间的距离
        OutFile >> first_name >> second_name >> length;
        int first_index, second_index; //两个景点在图G中的下标
        first_index = name.FindIndex(first_name);
        second_index = name.FindIndex(second_name);
        if (first_index == -1) { //还未读入该景点
            vector < edge > v;
            G.push_back(v);
            name.Insert(event < string, int > (first_name, count));
            info.push_back(first_name);
            first_index = count;
            count++;
        }
        if (second_index == -1) { //还未读入该景点
            vector < edge > v;
            G.push_back(v);
            name.Insert(event < string, int > (second_name, count));
            info.push_back(second_name);
            second_index = count;
            count++;
        }
        G[first_index].push_back(edge(second_index, length)); //邻接表
        G[second_index].push_back(edge(first_index, length)); //邻接表
    }
    //建立邻接矩阵
    M.resize(count);
    for (int i = 0; i < count; i++) {
        M[i].resize(count);
        for (int j = 0; j < count; j++) {
            M[i][j] = INF;
        }
    }
    for (int i = 0, len1 = (int) G.size(); i < len1; i++) {
        for (int j = 0, len2 = (int) G[i].size(); j < len2; j++) {
            M[i][G[i][j].to] = G[i][j].length;
        }
    }
    OutFile.close();
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

//SPFA求最短路，返回值为最短距离和最短路径由起点到终点路径组成的二元组, 若二元组第一个元素返回-1，代表没找到start，返回-2代表没找到end，-3代表都没找到
pair < int, vector < string > > Graph::SPFA(const string start, const string end) const {
    vector < string > path;
    int s = name.FindIndex(start), e = name.FindIndex(end); //获取起始点和终止点下标
    if(s == -1 && e == -1) { //start和end都不存在
        return make_pair(-3, path);
    } else if (s == -1) { //start不存在
        return make_pair(-1, path);
    } else if (e == -1) { //end不存在
        return make_pair(-2, path);
    }
    //start和end都存在，开始计算最短路径
    int dis[count], inq[count], pre[count];
    for (int i = 0; i < count; i++) {
        dis[i] = INF;
    }
    memset(inq, 0, sizeof(inq));
    memset(pre, 0, sizeof(pre));
    queue < int > Q;
    Q.push(s);
    inq[s] = 1;
    dis[s] = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        inq[u] = 0;
        int v, w;
        for (int i = 0; i < G[u].size(); i++) {
            v = G[u][i].to;
            w = G[u][i].length;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pre[v] = u;
                if (!inq[v]) {
                    Q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    StorePath(e, s, pre, path);
    return make_pair(dis[e], path);
}

//Dijkstra求最短路，返回值为最短距离和最短路径由起点到终点路径组成的二元组, 若二元组第一个元素返回-1，代表没找到start，返回-2代表没找到end，-3代表都没找到
pair < int, vector < string > > Graph::Dijkstra(const string start, const string end) const {
    vector < string > path;
    int s = name.FindIndex(start), e = name.FindIndex(end); //获取起始点和终止点下标
    if(s == -1 && e == -1) { //start和end都不存在
        return make_pair(-3, path);
    } else if (s == -1) { //start不存在
        return make_pair(-1, path);
    } else if (e == -1) { //end不存在
        return make_pair(-2, path);
    }
    //start和end都存在，开始计算最短路径
    int dis[count], done[count], pre[count];
    for (int i = 0; i < count; i++)
        dis[i] = INF;
    memset(done, 0, sizeof(done));
    memset(pre, 0, sizeof(pre));
    dis[s] = 0;
    //下标、与s距离，前驱
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, function<bool(const tuple<int, int, int>&, tuple<int, int, int>&)>> Q([&] (const tuple<int, int, int> a, const tuple<int, int, int> b) {return get<1>(a) > get<1>(b);});
    Q.push(make_tuple(s, 0, -1));
    while (!Q.empty()) {
        tuple<int, int, int> t = Q.top();
        Q.pop();
        if (done[get<0>(t)])
            continue;
        dis[get<0>(t)] = get<1>(t);
        pre[get<0>(t)] = get<2>(t);
        if (get<0>(t) == e)
            break;
        done[get<0>(t)] = 1;
        int a, b;
        for (int i = 0, len = (int) G[get<0>(t)].size(); i < len; i++) {
            a = G[get<0>(t)][i].to;
            b = G[get<0>(t)][i].length;
            if (done[a] == 0) {
                Q.push(make_tuple(a, get<1>(t) + b, get<0>(t)));
            }
        }
    }
    StorePath(e, s, pre, path);
    return make_pair(dis[e], path);//明德楼 操场
}

//求最短路时讲路径从起点到终点存到数组中
void Graph::StorePath(int x, int s, int pre[], vector < string > &path) const {
    if (x == s) {
        path.push_back(info[x]);
        return;
    }
    StorePath(pre[x], s, pre, path);
    path.push_back(info[x]);
}

//Floyd求最短路，返回值为最短距离和最短路径由终点到起点路径组成的二元组, 若二元组第一个元素返回-1，代表没找到start，返回-2代表没找到end，-3代表都没找到
pair < int , vector < string > > Graph::Floyd(const string start, const string end) const {
    vector < string > path;
    int s = name.FindIndex(start), e = name.FindIndex(end); //获取起始点和终止点下标
    if(s == -1 && e == -1) { //start和end都不存在
        return make_pair(-3, path);
    } else if (s == -1) { //start不存在
        return make_pair(-1, path);
    } else if (e == -1) { //end不存在
        return make_pair(-2, path);
    }
    //start和end都存在，开始计算最短路径
    vector<vector<int>> g = M;
    int pre[count][count];
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (g[i][j] != INF && i != j)
                pre[i][j] = i;
        }
    }
    for (int k = 0; k < count; k++) {
        for (int i = 0; i < count; i++) {
            if (g[i][k] != INF) {
                for (int j = 0; j < count; j++) {
                    if (g[i][j] > g[i][k] + g[k][j]) {
                        g[i][j] = g[i][k] + g[k][j];
                        pre[i][j] = pre[k][j];
                    }
                }
            }
        }
    }
    int a = s, b = e;
    while (a != b) {
        path.push_back(info[b]);
        b = pre[a][b];
    }
    path.push_back(info[a]);
    return make_pair(g[s][e], path);
}

//状态压缩dp求解旅行商问题
pair < int , vector < string > > Graph::TSP(const string start) const {
    vector<string> path;
    if (count > 15)
        return make_pair(-1, path);
    int st = name.FindIndex(start);
    if(st == -1) { //start不存在
        return make_pair(-2, path);
    }
    vector<vector<int>> g = M;
    int pre[count][count];
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (g[i][j] != INF && i != j) {
                pre[i][j] = i;
            }
        }
    }
    for (int k = 0; k < count; k++) {
        for (int i = 0; i < count; i++) {
            if (g[i][k] != INF) {
                for (int j = 0; j < count; j++) {
                    if (g[i][j] > g[i][k] + g[k][j]) {
                        g[i][j] = g[i][k] + g[k][j];
                        pre[i][j] = pre[k][j];
                    }
                }
            }
        }
    }
    const int maxn = count;
    int dp[1 << maxn][maxn];
    int front[1 << maxn][maxn];
    memset(dp, 0x3f, sizeof(dp));
    memset(front, -1, sizeof(front));
    dp[(1 << maxn) - 1][st] = 0;
    for (int s = (1 << maxn) - 2; s >= 0; s--) {
        for (int i = 0; i < maxn; i++) {
            if ((s >> i & 1) || s == 0)
                for (int j = 0; j < maxn; j++) {
                    if (!(s >> j & 1)) {
                        if (dp[s][i] > dp[s | 1 << j][j] + g[i][j]) {
                            dp[s][i] = dp[s | 1 << j][j] + g[i][j];
                            front[s][i] = j;
                        }
                    }
                }
        }
    }
    path.push_back(info[st]);
    vector<int> r;
    for (int i = 0, s = 0, now = st, p; ; i++) {
        p = now;
        now = front[s][now];
        if (now == -1)
            break;
        int a = p, b = now;
        r.clear();
        while (a != b) {
            r.push_back(b);
            b = pre[a][b];
        }
        for (int i = (int) r.size() - 1; i >= 0; i--)
            path.push_back(info[r[i]]);
        s = s | 1 << now;
    }
    return make_pair(dp[0][st], path);
}
