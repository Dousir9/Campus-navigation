//
//  ACautomaton.cpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/4/6.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "ACautomaton.hpp"

//构造函数
ACautomaton::ACautomaton() {
    pos = 1;
    tr.push_back(Root());
    trr.push_back(Root());
}

//判断是不是中文字符
inline int IsNotCN(const string &str, int i) {
    if (str[i] >= ' ' && str[i] <= '~')
        return 1;
    return 0;
}

//外部接口：插入记录
void ACautomaton::Insert(string &str) {
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
        dif.push_back(s);
        if (tr[p].next[s] == 0) {
            tr[p].next[s] = pos;
            tr.push_back(Root());
            tr[pos].next.clear();
            
            trr[p].next[s] = pos;
            trr.push_back(Root());
            trr[pos].next.clear();
            
            pos++;
        }
        p = tr[p].next[s];
    }
    val.resize(pos);
    val[p]++;
}

void ACautomaton::GetFail() {
    fail.resize(pos);
    fail.assign(pos, 0);
    sort(dif.begin(), dif.end());
    int s = (int) (unique(dif.begin(), dif.end()) - dif.begin());
    queue<int> q;
    for (auto it = tr[0].next.begin(); it != tr[0].next.end(); ++it) {
        q.push(it->second);
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < s; i++) {
            int c = tr[x].next[dif[i]];
            if (c != 0) {
                fail[c] = tr[fail[x]].next[dif[i]];
                q.push(c);
            } else {
                tr[x].next[dif[i]] = tr[fail[x]].next[dif[i]];
            }
        }
    }
}

//匹配函数
int ACautomaton::Query(const string &str) {
    int p = 0, res = 0;
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
        p = tr[p].next[s];
        for (int j = p; j; j = fail[j]) {
            res += val[j];
        }
    }
    return res;
}

//记录搜索,str是待记录的字符串
void ACautomaton::RecordSearch(const string &str) {
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
        p = tr[p].next[s];
        for (int j = p; j; j = fail[j]) {
            if (val[j]) {
                val[j]++;
            }
        }
    }
}

//str为""时，返回AC自动机的内容
pair<int, vector<SearchInfo>> ACautomaton::Find(string &str) {
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
        if (trr[p].next[s] == 0) {
            return make_pair(-1, end);
        } else {
            pre += s;
        }
        p = trr[p].next[s];
    }
    if (trr[p].next.size() == 0) {
        return make_pair(-1, end);
    }
    //当str为空，p在这等于0，是查看所有记录
    StoreInfo(p, pre, end, 1);
    return make_pair(1, end);
}

//将Find到的信息存到vector中
void ACautomaton::StoreInfo(int p, string s, vector<SearchInfo> &end, int flag) {
    int x;
    for (auto it = trr[p].next.begin(); it != trr[p].next.end(); ++it) {
        x = it->second;
        if (val[x] != 0) {
            end.push_back({s + it->first, val[x]});
        }
        if (x == 0) //可能有bug造成循环
            return;
        StoreInfo(x, s + it->first, end, flag + 1);
    }
}
