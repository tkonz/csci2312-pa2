//
//  main.cpp
//  pa2-ucd
//
//  Created by Tisha Konz on 9/18/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
//

#include "point.h"
#include "Cluster.h"
#include <iostream>
#include <cstdlib>


using namespace std;
using namespace Clustering;

int main()
{
    Cluster cluster;
    Point p1(2), p2(2), p3(2), p4(2), p5(2);
    Point sum(2);
    
    for (int i = 0; i < 3; i++)
    {
        p1[i] = i * 2 + 6;
        p2[i] = i * 6 - 3;
        p3[i] = i * .3 + 1;
        p4[i] = i + 25 - 2*i;
        p5[i] = i * i;
    }
    Point p6 = p5;
    cout << "p1 = " << p1;
    cout << "p2 = " << p2;
    cout << "p3 = " << p3;
    cout << "p4 = " << p4;
    cout << "p5 = " << p5;
    cout << p1.distanceTo(p2) << endl;
    
    cout << "p1 + p2 = " << p1 + p2;
    cout << "p2 - p1 = " << p2 - p1;
    cout << (p1 * p2);
    cout << (p1 * p2) / -1;
    cout << ((p1 * p2) / -1 != (p1* p2)) << endl;
    cout << (p1 < p2) << endl;
    
    return 0;
    
}
