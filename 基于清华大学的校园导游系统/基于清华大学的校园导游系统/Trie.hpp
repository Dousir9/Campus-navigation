//
//  Trie.hpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/4/5.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#ifndef Trie_hpp
#define Trie_hpp

#include "Global.hpp"

struct Root {
    map<string, int> next;
    Root() {
        next.clear();
    }
};

struct SearchInfo {
    string info;
    int val; //次数
    bool operator < (const SearchInfo &other) const {
        if (val != other.val)
            return val > other.val;
        return info.size() < other.info.size();
    }
};

//字典树
class Trie {
 public:
    Trie();
    void Insert(string &str); //外部接口：插入
    pair<int, vector<SearchInfo>> Find(string &str); //外部接口：搜索提示，1代表搜索到信息，-1代表未搜索到信息
    void InitTrie(); //读取文件建立字典树
    void SaveTrie(); //写入文件保存字典树
 private:
    void InFileInsert(string &str, int cnt); //读取文件的插入插入
    void StoreInfo(int p, string s, vector<SearchInfo> &end); //将搜索的到信息存到vector中
    int pos;
    vector<Root> tr;
    vector<int> val;
};

#endif /* Trie_hpp */
