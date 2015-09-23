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
    
    Point p(3);
    for (int i = 0; i < 10; i++)
    {
        p[i] = i+2*3;
    }
    
    
        return 0;
}
