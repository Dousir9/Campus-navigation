//
//  main.cpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "Menu.hpp"
#include "Graph.hpp"
#include "RBTree.hpp"

int main(int argc, const char * argv[]) {
    Graph G;
    G.InitGraph(); //只创建一次地图
    Menu M;
    M.MenuRun(G);
    return 0;
}
