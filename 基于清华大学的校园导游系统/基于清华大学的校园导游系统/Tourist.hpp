//
//  Tourist.hpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#ifndef Tourist_hpp
#define Tourist_hpp

#include "Global.hpp"
#include "Graph.hpp"
#include "Trie.hpp"
#include "ACautomaton.hpp"

class Tourist {
 public:
    void ShowMap(const Graph &G) const; //查看地图
    void Recommend(const Graph &G) const; //路线推荐
    void HotSights(const Graph &G, Trie &T); //热门景点
    void HotSearch(Trie &T); //热门搜索
    void SearchTip(Trie &T); //搜索提示
    void MultiKeywordSearch(const Graph &G, Trie &T); //多关键词搜索
    void MinLength(const Graph &G) const; //景点间最短路径
    void TSP(const Graph &G) const; //TSP旅行商问题
};

#endif /* Tourist_hpp */
