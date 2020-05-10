//
//  Trie.cpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/4/5.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "Trie.hpp"

//构造函数
Trie::Trie() {
    pos = 1;
    tr.push_back(Root());
}

//判断是不是中文字符
inline int IsNotCN(const string &str, int i) {
    if (str[i] >= ' ' && str[i] <= '~')
        return 1;
    return 0;
}


//外部接口：插入记录
void Trie::Insert(string &str) {
    int p = 0;
    int len = (int) str.size();
    string s;
    for (int i = 0; i < len; i++) {
        if (IsNotCN(str, i)) {
            int j = i;
            int cnt = 0;
            while (IsNotCN(str, j)) {
                j++;
                cnt++;
            }
            s = str.substr(i, cnt);
            i = j - 1;
        } else {
            s = str.substr(i, CN_SIZE);
            i += CN_SIZE - 1;
        }
        if (tr[p].next[s] == 0) {
            tr[p].next[s] = pos;
            tr.push_back(Root());
            tr[pos].next.clear();
            pos++;
        }
        p = tr[p].next[s];
    }
    val.resize(pos);
    val[p]++;
}

//读取文件的插入,cnt是次数
void Trie::InFileInsert(string &str, int cnt) {
    int p = 0;
    int len = (int) str.size();
    string s;
    for (int i = 0; i < len; i++) {
        if (IsNotCN(str, i)) {
            int j = i;
            int cnt = 0;
            while (IsNotCN(str, j)) {
                j++;
                cnt++;
            }
            s = str.substr(i, cnt);
            i = j - 1;
        } else {
            s = str.substr(i, CN_SIZE);
            i += CN_SIZE - 1;
        }
        if (tr[p].next[s] == 0) {
            tr[p].next[s] = pos;
            tr.push_back(Root());
            tr[pos].next.clear();
            pos++;
        }
        p = tr[p].next[s];
    }
    val.resize(pos);
    val[p] += cnt;
}

//读取文件建立字典树
void Trie::InitTrie() {
    ifstream OutFile;
    OutFile.open(SEARCH_INFO_FILE_NAME);
    string str;
    int cnt;
    while (!OutFile.eof()) {
        OutFile >> str >> cnt;
        InFileInsert(str, cnt);
    }
    OutFile.close();
}

//搜索提示
pair<int, vector<SearchInfo>> Trie::Find(string &str) {
    int p = 0;
    int len = (int) str.size();
    string pre = "";
    string s;
    vector<SearchInfo> end;
    for (int i = 0; i < len; i++) {
        if (IsNotCN(str, i)) {
            int j = i;
            int cnt = 0;
            while (IsNotCN(str, j)) {
                cnt++;
                j++;
            }
            s = str.substr(i, cnt);
            i = j - 1;
        } else {
            s = str.substr(i, CN_SIZE);
            i += CN_SIZE - 1;
        }
        if (tr[p].next[s] == 0) {
            return make_pair(-1, end);
        } else {
            pre += s;
        }
        p = tr[p].next[s];
    }
    if (tr[p].next.size() == 0) {
        return make_pair(-1, end);
    }
    //当str为空，p在这等于0，是查看所有记录
    StoreInfo(p, pre, end);
    return make_pair(1, end);
}

void Trie::StoreInfo(int p, string s, vector<SearchInfo> &end) {
    int x;
    for (auto it = tr[p].next.begin(); it != tr[p].next.end(); ++it) {
        x = it->second;
        if (val[x] != 0) {
            end.push_back({s + it->first, val[x]});
        }
        if (x == 0) //可能有bug造成循环
            return;
        StoreInfo(x, s + it->first, end);
    }
}

void Trie::SaveTrie() {
    ofstream InFile;
    InFile.open(SEARCH_INFO_FILE_NAME);
    string str = "";
    pair<int, vector<SearchInfo>> p = Find(str);
    for (int i = 0, s = (int) p.second.size(); i < s; i++) {
        InFile << p.second[i].info << " " << p.second[i].val;
        if (i != s - 1)
            InFile << '\n';
    }
}
