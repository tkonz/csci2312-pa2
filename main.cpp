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
#include <fstream>

#include <cstdlib>

void testDestructor();


using namespace std;
using std::stringstream;
using namespace Clustering;
void testDestructor(Point&);

int main()
{
    //    Cluster cluster1, cluster2;
    //    //new Cluster
    //
    //    //char c;
    //    Point p1(2), p2(2), p3(2), p4(2), p5(2), p7(2), p8(2), p9(2), p10(3), p11(3);
    //    Point sum(2);
    //    cluster1.add(&p1);
    //    cluster1.add(&p2);
    //    cluster1.add(&p3);
    //    cluster1.add(&p4);
    //    cluster1.add(&p5);
    //    cluster2.add(&p7);
    //    cluster2.add(&p8);
    //    cluster2.add(&p9);
    //    cluster2.add(&p1);
    //
    //
    //
    //
    //    for (int i = 0; i < 3; i++)
    //    {
    //        p1[i] = i * 2 + 6;
    //        p2[i] = i * 6 - 3;
    //        p3[i] = i * .3 + 1;
    //        p4[i] = i + 25 - 2 * i;
    //        p5[i] = i * i;
    //        p7[i] = i / 2 + 12;
    //        p8[i] = i + 12 * .2;
    //        p9[i] = i * i * 3.14;
    //    }
    //
    //    Point p6 = p5;
    //    cout << "p1 = " << p1;
    //    cout << "p2 = " << p2;
    //    cout << "p3 = " << p3;
    //    cout << "p4 = " << p4;
    //    cout << "p5 = " << p5;
    //    cout << "p6 = " << p6;
    //
    //    //cout << p1.distanceTo(p2) << endl;
    //
    //    cout << "p1 + p2 = " << p1 + p2;
    //    cout << "p2 - p1 = " << p2 - p1;
    //    p6 = p1 + p1;
    //    cout << "p6 = " << p6;
    //    cout << (p1 * p2);
    //    cout << (p1 * p2) / -1;
    //    cout << ((p1 * p2) / -1 != (p1* p2)) << endl;
    //    cout << (p1 < p2) << endl;
    //
    //    if (p6 == p5)
    //    {
    //        cout << "EQUAL\n";
    //    }
    //    else
    //        cout << "NOT EQUAL/n";
    //
    //    cout << "cluster1 = " << cluster1;
    //    cout << "cluster2 = " << cluster2;
    //    cout << "cluster1 + cluster2 = " << (cluster1 + cluster2);
    //    cout << "p1 = " << p1;
    //    cout << "p3 = " << p3;
    //    cout << "cluster1 = " << cluster1;
    //    cout << "cluster1 -= p3" << (cluster1 -= p3);
    //    cout << "cluster1 - p6(1, 4) = " << (cluster1 -= p6);
    //    cout << "cluster1 - p3(8) = " << (cluster1 -= p3);
    //    cout << "cluster1 - p1 = " << (cluster1 -= p1);
    //    //cin >> p1;
    //    cout << "cluster1 = " << cluster1;
    //
    //
    //    //cluster1.add(&p1);
    //    //cluster1.add(&p2);
    //    //cluster1.add(&p3);
    //    //cluster1.add(&p4);
    //    //cluster1.add(&p5);
    //
    //    int i = 0;
    //    if (i == 0)
    //    {
    //        Cluster c3;
    //        c3.add(&p1);
    //    }
    //
    //    cout << "cluster1 = " << cluster1;
    //    Cluster cluster3(cluster1);
    //    cout << "cluster3 = " << cluster3;
    //    //Cluster cluster4(cluster3);
    //    //cout << "cluster4 = " << cluster4;
    //
    //    //if (cluster4 == cluster3)
    //    //    cout << "Equal\n";
    //    //else
    //    cout << "Not equal.\n";
    //    Cluster c2;
    //    //c2.operator=(cluster1);
    //    c2 = cluster1;
    //    cout << "c2 = " << c2;
    //    cout << "cluster2 = " << cluster2;
    //    c2 = cluster2;
    //    cout << "c2 = " << c2;
    //    cout << "p3 = " << p3;
    //    cluster1.remove(&p3);
    //    cout << "cluster1 = " << cluster1 << "cluster2 = " << cluster3;
    //    cout << "p5 = " << p5;
    //    cout << "p6 = " << p6;
    //    cout << "p5 * p6 = " << (p5 * p6);
    //    cout << "p5 * 2 = " << (p5 *= 2.0);
    //    cout << "cluster1 - p5" << (cluster1 -= p5);
    //    // cout << "p5 = " << p5;
    //    cout << "cluster1 += p5" << (cluster1 += p5);
    //    cout << "cluster1 = " << cluster1;
    //    cluster1 = cluster2;
    //    cout << "cluster1 = " << cluster1;
    //    if (cluster1 == cluster2)
    //    {
    //        cout << "Equal\n";
    //    }
    //    else
    //        cout << "not equal\n";
    
    Cluster universe;
    
    ifstream csv("/Users/Tish/Desktop/pa3-2312/points.txt");
    //string line;
    while (csv.is_open() && !csv.eof())
    {
        csv >> universe;
        cout << "Point: " << universe << endl;
        
    }
    cout << "Point: " << universe << endl;
    csv.close();
    
    Cluster c;
    Cluster c2;
    
    cout << c;
    cout << c2;
    
    //cout << "Point: " << universe << endl;
    //cluster1.computeCentroid();
    
    //testDestructor(p5);
    
    //cin >> c;
    
    
    return 0;
    
}

void testDestructor(Point &p)
{
    Cluster x;
    
    x.add(&p);
}
