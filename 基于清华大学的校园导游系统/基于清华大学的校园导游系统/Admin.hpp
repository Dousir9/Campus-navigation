//
//  Admin.hpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#ifndef Admin_hpp
#define Admin_hpp

#include "Global.hpp"
#include "Graph.hpp"

class Admin {
 public:
    Admin() {}; //默认构造函数
    void Change(Graph &G); //修改景点信息
    void AddSight(Graph &G); //添加景点
    void DeleteSight(Graph &G); //删除景点
    void AddEdge(Graph &G); //添加路径
    void DeleteEdge(Graph &G); //删除路径
    void CheckInfo(Graph &G); //信息检查
};

#endif /* Admin_hpp */
