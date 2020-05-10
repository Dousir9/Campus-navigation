//
//  ACautomaton.hpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/4/6.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#ifndef ACautomaton_hpp
#define ACautomaton_hpp

#include "Global.hpp"
#include "Trie.hpp"

//AC自动机
class ACautomaton {
public:
    ACautomaton();
    void Insert(string &str); //外部接口：插入
    void GetFail(); //外部接口：获取Fail数组
    int Query(const string &str); //外部接口：匹配函数
    void RecordSearch(const string &str); //外部接口：记录搜索
    pair<int, vector<SearchInfo>> Find(string &str); //外部接口：str为""时，返回AC自动机的内容
private:
    void StoreInfo(int p, string s, vector<SearchInfo> &end, int flag); //内部接口：将Find到的信息存到vector中
    int pos;
    vector<Root> tr;
    vector<Root> trr;
    vector<int> val;
    vector<int> fail;
    vector<string> dif; //不同的字符
};

#endif /* ACautomaton_hpp */
