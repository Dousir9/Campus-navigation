//
//  Tourist.cpp
//  基于清华大学的校园导游系统
//
//  Created by Dousir9 on 2020/2/28.
//  Copyright © 2020 🍓XJK. All rights reserved.
//

#include "Tourist.hpp"

void Tourist::Travel(const Graph &G) const{
    cout << "是否遍历地图?(y/n)";
    char ch;
    cin >> ch;
    if (ch == 'y') {
        G.Input();
    }
    MY_PAUSE();
}
