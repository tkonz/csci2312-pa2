//
//  Kmeans.cpp
//  pa2-ucd
//
//  Created by Tisha Konz on 10/9/15.
//  Copyright (c) 2015 Tisha Konz. All rights reserved.
///Create a cluster point_space with __release_points set to true
#include "Kmeans.h"
#include <float.h>

double MAX = DBL_MAX;

namespace Clustering
{
    double Kmeans::SCORE_DIFF_THRESHOLD = .75;
    
    //FIX logic here
    double Kmeans::computeClusteringScore()
    {
        double score;
        double inner;
        double outer = 0.0;
        
        for (int i = 0; i < m_k; i++)
        {
            std::cout << clusterVec[i].getClusterEdges() << endl;
            if (clusterVec[i].getClusterEdges() == 0)
                break;
            outer += clusterVec[i].intraClusterDistance() / clusterVec[i].getClusterEdges();
            for (int j = 1; j < m_k; j++)
            {
                inner += interClusterDistance(clusterVec[i], clusterVec[j]);
            }
        }
        score = inner / outer;
        
        return score;
    }
    
    
    // initializing ClusterVec with k clusters
    void Kmeans::initializeClusters()
    {
        //clusterVec = &point_space;
        clusterVec.push_back(point_space);
        for (int i = 1; i < m_k; i++)
            clusterVec.push_back(i);
        for (int i = 0; i < m_k; i++)
            std::cout << clusterVec[i] << endl;
    }
    
    
    void Kmeans::initializeCentroids()
    {
        initializeClusters();
        std::vector<Point> pointVec;
        point_space.pickPoints(m_k, pointVec);
        for (int i = 0; i < m_k; i++)
        {
            cout << pointVec[i] << endl;
        }
        
        clusterVec[0].set_centroid(pointVec[0]);
        for (int i = 1; i < m_k; i++)
        {
            clusterVec[i].set_centroid(pointVec[i]);
            //std::cout << clusterVec[i].get_centroid();
        }
    }
    
    Cluster* Kmeans::findNearestCentroid(Point &p)
    {
        Cluster *c = &clusterVec[0];
        double distance = 0;
        distance = p.distanceTo(clusterVec[0].get_centroid());
        for (int i = 1; i < m_k; i++)
        {
            if (p.distanceTo(clusterVec[i].get_centroid()) < distance)
            {
                distance = p.distanceTo(clusterVec[i].get_centroid());
                c = &clusterVec[i];
            }
        }
        return c;
    }
    
    void Kmeans::kMeansAlgorithm()
    {
        initializeCentroids();
        oldScore = 0;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;
        int i  = 0;
        
        //while loop until scoreDiff < SCORE_DIFF_THRESHOLD
        while (scoreDiff > SCORE_DIFF_THRESHOLD)
        {
            std::vector<Cluster>::iterator it = clusterVec.begin(); // cluster[i]
            // Loop through all clusters with outer for loop
            for (int counter = 0; counter < m_k; counter++)
            {
                std::forward_list<Point>::iterator list = (*it).m_Points.begin();
                
                while (list != (*it).m_Points.end()) // Loop through all points in this cluster with while
                {
                    Cluster *cluster = findNearestCentroid(*list);
                    if (cluster != &clusterVec[i])
                    {
                        // create a move object of point, with two clusters and perform move
                        
                        Cluster::Move m(&*list, &clusterVec[i], cluster);
                        m.perform();
                    }
                    //it = ++it;
                    list = ++list;
                }//end while loop
                it = ++it;
            }// end for loop
            for (int h = 0; h < m_k; h++)
            {
                if (clusterVec[h].get_centroid_valid() == false)
                {
                    clusterVec[h].compute_centroid(clusterVec[h]);
                    //clusterVec[h].set_centroid(cen);
                }
            }
            //compute new clustering score
            newScore = computeClusteringScore();
            //compute absolute difference and set scoreDiff
            scoreDiff = std::abs(oldScore - newScore);
            
        }//end while loop
        printClusters();
    }
    
    void Kmeans::printClusters()
    {
        for (int i = 0; i < m_k; i++)
        {
            cout << clusterVec[i] << endl;
        }
    }
    
}