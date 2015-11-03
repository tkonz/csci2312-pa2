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
    double Kmeans::SCORE_DIFF_THRESHOLD = .1;
    
    double Kmeans::computeClusteringScore()
    {
        double score;
        double inner;
        double outer = 0.0;
        
        for (int i = 0; i < __k; i++)
        {
            
            outer = clusterVec[i].intraClusterDistance() / clusterVec[i].getClusterEdges();
            for (int j = 1; j < __k; j++)
            {
                
                inner += interClusterDistance(clusterVec[i], clusterVec[j]);
                
            }
        }
        score = outer / inner;
        
        return score;
    }
    
    
    // initializing ClusterVec with k clusters
    void Kmeans::initializeClusters()
    {
        //clusterVec = &point_space;
        clusterVec = new Cluster[__k];
        
        for (int i = 1; i < __k-1; i++)
        {
            clusterVec[i].setDimensionality(__dimensionality);
        }
        
    }
    
    void Kmeans::initializeCentroids()
    {
        initializeClusters();
        PointPtr *pointArray = new PointPtr[__k];
        std::cout << pointArray[0];
        
        
        point_space.pickPoints(__k, pointArray);
        for (int i = 0; i < __k; i++)
        {
            cout << *(pointArray[i]) << endl;
        }
        
        clusterVec[0].set_centroid(*pointArray[0]);
        for (int i = 1; i < __k; i++)
        {
            clusterVec[i].set_centroid(*pointArray[i]);
        }
    }
    
    void Kmeans::kMeansAlgorithm()
    {
        initializeCentroids();
        oldScore = MAX;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;
        
        //while loop until scoreDiff < SCORE_DIFF_THRESHOLD
        while (scoreDiff > SCORE_DIFF_THRESHOLD)
        {
            // Loop through all clusters with outer for
            for (int h = 0; h < __k; h++)
            {
                //std::cout << "Cluster: " << clusterVec[h];
                
                // Loop through all points in this cluster with inner for
                
                Cluster::iterator it = clusterVec[h].begin();
                
                for (int i = 1; i < clusterVec[h].getSize(); i++)
                {
                    while (it != nullptr) // while not at end of list of pointptrs
                    {
                        newScore = clusterVec[i].get_centroid().distanceTo(**it); // get distance from current cluster's
                        // centroid to current point
                        
                        if (newScore < oldScore) // if new distance is less than old distance,
                        {
                            Cluster::Move m(*it, &clusterVec[h], &clusterVec[i]); // create a move object of point, with two                    clusters
                            m.perform();                                  // and perfrom move
                        }
                        it = ++it;
                        //newScore = computeClusteringScore();
                    }
                }//end inner for loop of one cluster
            }//end outer for loop of another cluster
            
            //loop through all clusters
            //if centroid invalid
            //compute and set valid to true
            
            for (int h = 0; h < __k; h++)
            {
                if (clusterVec[h].get_centroid_valid() == false)
                {
                    clusterVec[h].set_centroid(clusterVec[h].compute_centroid(clusterVec[h]));
                }
            }
            //compute new clustering score
            newScore = computeClusteringScore(); // (ivogeorg)
            //compute absolute difference and set scoreDiff
            // (ivogeorg)
            scoreDiff = std::abs(oldScore - newScore);
            
        }//end while loop
        printClusters();
    }
    
    void Kmeans::printClusters()
    {
        for (int i = 0; i < __k; i++)
        {
            cout << clusterVec[i] << endl;
        }
    }
    
    
}

