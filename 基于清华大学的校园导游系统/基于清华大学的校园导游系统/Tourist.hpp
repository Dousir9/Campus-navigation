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

class Tourist {
 public:
    //获取图信息的操作
    void Travel(const Graph &G) const;
    void MinLength(const Graph &G) const; //最短路径
    void TSP(const Graph &G) const; //TSP旅行商问题
};

#endif /* Tourist_hpp */
