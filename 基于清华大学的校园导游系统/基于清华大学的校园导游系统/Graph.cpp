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
    OutFile >> count; //有几个不同的景点
    info.resize(count);
    for (int i = 0; i < count; i++) {
        OutFile >> info[i];
        name.Insert(event<string, int>(info[i], i));
    }
    //建立邻接表
    for (int i = 0; i < count; i++) {
        vector<edge> e;
        G.push_back(e);
    }
    while (!OutFile.eof()) {
        string first_name, second_name; //两个相连的景点名字
        int length; //两个景点之间的距离
        OutFile >> first_name >> second_name >> length;
        //两个景点在图G中的下标
        int first_index = name.FindIndex(first_name);
        int second_index = name.FindIndex(second_name);
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
    LoadSightInfo();
}

//BFS周围点保存图以防止保存重复信息
void Graph::BfsInFile(const int &index, vector < int > &done, ofstream &Infile) {
    int len = int(G[index].size());
    for (int i = 0; i < len; i++) {
        if (!done[G[index][i].to]) {
            Infile << '\n' << info[index] << ' ' << info[G[index][i].to] << ' ' << G[index][i].length;
        }
    }
}

//写入文件保存图
void Graph::SaveGraph() {
    ofstream InFile; //写入
    InFile.open(GRAPH_INFO_FILE_NAME);
    InFile << count - Tag.size();
    vector<int> visit(count, 0);
    for (int i = 0; i < Tag.size(); i++) {
        visit[Tag[i]] = 1;
    }
    for (int i = 0; i < count; i++) {
        if (visit[i] == 0) {
            InFile << '\n' << info[i];
        }
    }
    int len = int(G.size());
    vector < int > done(len);
    for (int i = 0; i < len; i++) {
        BfsInFile(i, done, InFile);
        done[i] = 1;
    }
    SaveSightInfo();
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
//            if (done[a] == 0 && dis[a] > dis[get<0>(t)] + b) {
                //pre[a] = get<0>(t);
                //dis[a] = get<1>(t) + b;
                Q.push(make_tuple(a, get<1>(t) + b, get<0>(t)));
            }
        }
    }
    StorePath(e, s, pre, path);
    return make_pair(dis[e], path);
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

//增加景点，已存在返回-1，增加成功返回1
pair<int, pair<vector<string>, vector<string>>> Graph::AddNode(const string str, const string sight_info, const vector<string> &sight, const vector<int> &len) {
    int x = name.FindIndex(str);
    vector<string> yes, no;
    if (x != -1)
        return make_pair(-1, make_pair(yes, no));
    if (Tag.size() == 0) {
        name.Insert(event<string, int>(str, count)); //红黑树插入
        vector<edge> v;
        G.push_back(v); //邻接表增加
        info.push_back(str); //数字对应景点名字增加
        SightInfo.push_back(sight_info);
        count++; //景点数加1
        //增大邻接矩阵
        //之前的每行增加1个空间
        for (int i = 0; i < count - 1; i++) {
            M[i].push_back(INF);
        }
        //为最后一行（新增加的那一行）分配内存
        vector<int> m;
        M.push_back(m);
        M[count - 1].resize(count);
        for (int i = 0; i < count; i++) {
            M[count - 1][i] = INF;
        }
        for (int i = 0; i < sight.size(); i++) {
            int x = AddEdge(str, sight[i], len[i]);
            if (x == 1) {
                yes.push_back(sight[i]);
            } else {
                no.push_back(sight[i]);
            }
        }
    } else {
        int index = Tag.back();
        Tag.pop_back();
        name.Insert(event<string, int>(str, index)); //红黑树插入
        vector<edge> v;
        G.push_back(v); //邻接表增加
        info[index] = str; //数字对应景点名字增加
        SightInfo[index] = sight_info;
        for (int i = 0; i < sight.size(); i++) {
            int x = AddEdge(str, sight[i], len[i]);
            if (x == 1) {
                yes.push_back(sight[i]);
            } else {
                no.push_back(sight[i]);
            }
        }
    }
    return make_pair(1, make_pair(yes, no));
}

//增加边
int Graph::AddEdge(const string str1, const string str2, const int length) {
    int x = name.FindIndex(str1);
    int y = name.FindIndex(str2);
    if(x == -1 && y == -1) { //str1和str2都不存在
        return -1;
    } else if (x == -1) { //str1不存在
        return -2;
    } else if (y == -1) { //str2不存在
        return -3;
    }
    //str1和str2都存在
    //检查边是否存在
    if (M[x][y] != INF) {
        return -4; //边已经存在
    }
    //边不存在，开始增加边
    M[x][y] = M[y][x] = length;
    G[x].push_back(edge(y, length));
    G[y].push_back(edge(x, length));
    return 1;
}

//加载景点信息
void Graph::LoadSightInfo() {
    ifstream OutFile;
    OutFile.open(SIGHT_INFO_FILE_NAME);
    SightInfo.resize(count);
    string a, b;
    int x;
    while (!OutFile.eof()) {
        OutFile >> a >> b;
        x = name.FindIndex(a);
        SightInfo[x] = b;
    }
    OutFile.close();
}

//将景点信息写入文件
void Graph::SaveSightInfo() {
    ofstream InFile;
    InFile.open(SIGHT_INFO_FILE_NAME);
    vector<int> visit(count, 0);
    int cnt = (int) Tag.size();
    for (int i = 0; i < cnt; i++) {
        visit[Tag[i]] = 1;
    }
    for (int i = 0, j = 0; i < count; i++) {
        if (visit[i] == 0) {
            InFile << info[i] << " " << SightInfo[i];
            if (j != count - cnt - 1)
                InFile << '\n';
            j++;
        }
    }
    InFile.close();
}

//多关键词搜索，返回匹配的内容明德
pair<vector<int>, pair<vector<string>, vector<string>>> Graph::MultiKeySearch(ACautomaton &AC) const {
    vector<string> sights, sights_info;
    vector<int> val;
    vector<pair<int, int>> p;
    vector<int> visit(count, 0);
    for (int i = 0; i < Tag.size(); i++) {
        visit[Tag[i]] = 1;
    }
    for (int i = 0; i < count; i++) {
        if (visit[i] == 0) {
            int x = AC.Query(info[i] + SightInfo[i]);
            if (x != 0)
                p.push_back(make_pair(x, i));
        }
    }
    sort(p.begin(), p.end(), [&] (const pair<int, int> a, const pair<int, int> b) {
        return a.first > b.first;
    });
    for (int i = 0; i < p.size(); i++) {
        val.push_back(p[i].first);
        sights.push_back(info[p[i].second]);
        sights_info.push_back(SightInfo[p[i].second]);
    }
    return make_pair(val, make_pair(sights, sights_info));
}

//用所有景点构造出AC自动机
vector<string> Graph::GetSights() const {
    vector<string> sights;
    for (int i = 0; i < count; i++) {
        sights.push_back(info[i]);
    }
    return sights;
}

//删除景点
int Graph::G_delete(string NAME)
{
    int n=name.FindIndex(NAME);//计算景点下标
    if(n==-1) return -1;//找不到下标
    for(int i=0; i<G.size(); i++)//寻找并删除与之相连的边
        for (auto it=G[i].begin(); it!=G[i].end(); ++it)
            if((*it).to==n)
            {
                G[i].erase(it);
                break;
            }
    G[n].clear();//清空结点
    //重置邻接矩阵
    for (int i = 0; i < count; i++) {
        M[i][n] = INF;
        M[n][i] = INF;
    }
    name.Delete(NAME);//红黑树删除
    Tag.push_back(n);//标记下标
    return 1;
}

int Graph::E_delete(string NAME1,string NAME2)//边删除
{
    int n1 = name.FindIndex(NAME1), n2 = name.FindIndex(NAME2);//计算景点下标
    int flag = 0;
    if (n1 == -1 && n2 == -1) {
        return -1;
    } else if (n1 == -1) {
        return -2;
    } else if (n2 == -1) {
        return -3;
    }
    for (auto it = G[n1].begin(); it != G[n1].end(); ++it) {
        if ((*it).to == n2) {
            flag = 1;
            G[n1].erase(it);
            for (auto itt = G[n2].begin(); itt != G[n2].end(); ++itt) {
                if ((*itt).to == n1) {
                    G[n2].erase(itt);
                    break;
                }
            }
            break;
        }
    }
    if (flag == 0) {
        return -4;
    }
    M[n1][n2] = M[n2][n1] = INF;//修改邻接矩阵
    return 1;
}

void Graph::Puts() {
    printf("count = %d\n", count);
    vector<int> visit(count, 0);
    for (int i = 0; i < Tag.size(); i++) {
        visit[Tag[i]] = 1;
    }
    for (int i = 0; i < count; i++) {
        if (visit[i] == 0) {
            cout << i << "  " << info[i] << '\n';
            cout << SightInfo[i] << '\n' << '\n';
        }
    }
    printf("\n");
    for (int i = 0; i < Tag.size(); i++) {
        printf("tag %d\n", Tag[i]);
    }
    printf("\n");
    for (int i = 0; i < count; i++) {
        if (visit[i] == 0) {
            cout << info[i] << '\n';
            for (int j = 0; j < G[i].size(); j++) {
                cout << info[i] << "->" << info[G[i][j].to] << "  " << G[i][j].length << '\n';
            }
            cout << '\n';
        }
    }
}

int Graph::changelength(string NAME1,string NAME2,int newlength)//修改路径长度
{
    int n1=name.FindIndex(NAME1),n2=name.FindIndex(NAME2);//计算景点的下标
    int flag=-1;//记录是否找到下标
    int i,j;
    if(n1 == -1 && n2 == -1) {
        return -1;
    } else if (n1 == -1) {
        return -2;
    } else if (n2 == -1) {
        return -3;
    }
    for(i=0; i<G[n1].size(); i++)//判断n1与n2是否相连，并找出n2是n1的第几个结点
    {
        if(G[n1][i].to==n2)
        {
            flag=1;
            break;
        }
    }
    if(flag==1)//n1与n2相连
    {
        
        for(j=0; j<G[n2].size(); j++)//找出n1是n2的第几个结点
            if(G[n2][j].to==n1)
                break;
        G[n1][i].length=newlength;//赋值
        G[n2][j].length=newlength;
        M[n1][n2]=newlength;
        M[n2][n1]=newlength;
        //SaveGraph();//保存
    }
    else
        return -4;
    return 1;
}
int Graph::changename(string NAME,string newname)//修改景点名称
{
    int n=name.FindIndex(NAME);//计算景点的下标
    if(n==-1)return -1;//找不到下标
    name.ModifyKey(info[n],newname);//修改红黑树
    info[n]=newname;//赋值
    //SaveGraph();//保存
    return 1;
}

//景点介绍
int Graph::G_Attractions(string NAME)const
{
    int n=name.FindIndex(NAME);
    if(n==-1) return -1;
    cout<<SightInfo[n];
    return 1;
}
void Graph::G_name()const
{
    for(int i=0; i<count; i++)
    {
        cout.setf(ios::left);
        cout<<setw(8)<<info[i]<<"  ";
        if((i+1)%5==0)
            cout<<endl;
    }
    cout<<endl;
}

//修改景点信息
int Graph::changeinfo(string NAME,string newinformation)
{
    int n=name.FindIndex(NAME);
    if(n==-1) return -1;
    SightInfo[n]=newinformation;
    //SaveGraph();//保存
    return 1;
}

void Graph::PutsMap() const
{
    const string s = "        ";
    cout << s;printf("   |----|            |---------|                                                                       \n");
    cout << s;printf("   |北八|------------|北苑 餐厅|____                                                                   \n");
    cout << s;printf("   |----|            |---------|    \\______                                                           \n");
    cout << s;printf("         \\                 |                \\ |------|                                               \n");
    cout << s;printf("          \\                 |                 |警务亭|\\_____                                         \n");
    cout << s;printf("           \\                 |       _ /------|------|       \\____                                   \n");
    cout << s;printf("            \\             |------| _/             |               \\_____                             \n");
    cout << s;printf("             \\            |驾 校 |/               |                     |                             \n");
    cout << s;printf("              \\           |------|                |                     |                             \n");
    cout << s;printf("               \\         /                        |                     |                             \n");
    cout << s;printf("                \\       /                         |                 |------|                          \n");
    cout << s;printf("                 \\   /\\                           |-----------      |信息楼|                         \n");
    cout << s;printf("                   /小山\\                         |           \\     |------|                         \n");
    cout << s;printf("                 /--------\\                       |            \\        |    \\                      \n");
    cout << s;printf("                     |   |                        |    -----    \\       |      \\                     \n");
    cout << s;printf("                     |   |                        |  /       |   \\      |        \\                   \n");
    cout << s;printf("                     |    |                         |      --     \\     |           \\   |----|       \n");
    cout << s;printf("                     |     |                      /      /          |------|          \\ |----|        \n");
    cout << s;printf("                     |      |                     |明德楼| ---------|图书馆|----------  |东门|         \n");
    cout << s;printf("                     |       |                    \\     \\           |------|          / |----|        \n");
    cout << s;printf("                     |        |                   / |     --            |            /  |----|         \n");
    cout << s;printf("                     |         |                 /    \\      |          |           /                 \n");
    cout << s;printf("                     |          ||-------------------|  -----           |          /                  \n");
    cout << s;printf("                |--------|       |      弘毅楼       |       \\          |         /                   \n");
    cout << s;printf("       |--------|南苑餐厅|------/|-------------------|         \\        |        /                    \n");
    cout << s;printf("       |        |--------|     /         |                       \\      |       /                     \n");
    cout << s;printf("       |             |        /          |                         \\ |------|  /                      \n");
    cout << s;printf("   |-------|         |       /           |                          -|行政楼| /                        \n");
    cout << s;printf("   | 南 一 |         |      /            |              ----------/  |------|                          \n");
    cout << s;printf("   |-------|        -----  /          |------|         /                                               \n");
    cout << s;printf("       |          /       \\-----------|篮球场| -------                                                \n");
    cout << s;printf("       |----------| 操 场 |           |------|                                                         \n");
    cout << s;printf("                  |       |                                                                            \n");
    cout << s;printf("                  \\       /                                                                           \n");
    cout << s;printf("                    -----                                                                              \n");
}


//void Dijkstra (MGraph *G, int v, int path[], int dist[]) //最短路径-Di jkstra算法  //v表示原顶点
//{
//    int i,j,k,vset [MaxVertexNum];
//    int MinDist;
//
//    for(i=0;i<G->n;i++)//初始化
//    {
//        vset[i]=1;
//        dist[i]=G->edges[v][i];
//        path[i]=dist[i]<MAXCOST?v:-1;
//    }
//
//    vset [v]=0, path[v]=0;
//
//    for (i=1;i<G->n;i++)
//    {
//        MinDist=MAXCOST;
//        for (j=0;j<G->n;j++)//循环扩展n-1次
//            if (vset [j]&&dist[j]<MinDist)
//                k=j, MinDist=dist[j];
//        vset[k]=0;
//
//        for (j=0;j<G->n;j++)//寻找未被扩展的权值最小的顶点
//            if (vset [j]&&(dist[j]>dist[k]+G->edges[k] [j]))
//                dist[j]=dist[k]+G->edges[k][j], path[j]=k;
//    }
//}
//for(k=0;k<g.n;k++)   //更新dist数组的值和路径的值
//{
//    if(visited[k]==false&&g.matrix[u][k]>0&&min+g.matrix[u][k]<dist[k])
//    {
//        dist[k]=min+g.matrix[u][k];
//        path[k]=u;
//    }
//}
//
//
//int DispPath(MGraph *G, int path[], int dist [], int start, int end) //显示最短路径
//{
//    int i=-1,k;
//    Vertex vex [MaxVertexNum] ;//顶点信息
//    k=path[end];
//
//    while(k!=start)//取得起点到终点的信息
//    {
//        vex [++i]=G->vexs [k] ; //顶点信息
//        k=path[k];
//    }
//    vex [++i]=G->vexs [start] ;//补充起点信息
//
//    cout<<"最短路径：";
//
//    while (i!=-1)
//        cout<<vex[i--]. date. name<<"-->";
//    cout<<G->vexs[end]. date.name;//依次输出顶点信息，最后输出终点信息
//    cout<<endl;
//    cout<<"两个景点的最短距离是："<<dist[end]<<"米"<<endl ;
//
//    return dist [end];
//}
//}
