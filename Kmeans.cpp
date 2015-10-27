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
            
            outer = vec[i].intraClusterDistance() / vec[i].getClusterEdges();
            for (int j = 1; j < __k; j++)
            {
                
                inner += interClusterDistance(vec[i], vec[j]);
                
            }
        }
        score = outer / inner;
        
        return score;
    }
    void Kmeans::kMeansAlgorithm()
    {
        PointPtr array[5];
        vec[__k--];
        point_space.pickPoints(__k, array);
        
        // giving points to centroids of k clusters
        int i = 0;
        while (i < vec[i].getSize() && i < __k)
        {
            vec[i].set_centroid(*array[i]);
            i++;
        }
        
        oldScore = MAX;
        scoreDiff = SCORE_DIFF_THRESHOLD + 1;
        
        //while loop until scoreDiff < SCORE_DIFF_THRESHOLD
        while (scoreDiff > SCORE_DIFF_THRESHOLD)
        {
            // Loop through all clusters with outer for
            for (int h = 0; h < __k; h++)
            {
                std::cout << "Cluster: " << vec[h];
                
                // Loop through all points in this cluster with inner for
                
                LNodePtr cursor = vec[h].get_points();
                
                for (int i = 1; i < vec[h].getSize(); i++)
                {
                    
                    while (cursor) // while not at end of list of pointptrs
                    {
                        newScore = vec[i].get_centroid().distanceTo(*cursor->p); // get distance from current cluster's centroid
                        // to current point
                        
                        if (newScore < oldScore) // if new distance is less than old distance,
                        {
                            Cluster::Move m(cursor->p, &vec[h], &vec[i]); // create a move object of point, with two clusters
                            m.perform();                                  // and perfrom move
                        }
                        oldScore = newScore;
                        cursor = cursor->next;
                    }
                }//end inner for loop of one cluster
            }//end outer for loop of another cluster
        }//end while loop while
        //loop through all clusters
        //if centroid invalid
        //compute and set valid to true
        for (int h = 0; h < __k; h++)
        {
            if (vec[h].get_centroid_valid() == false)
            {
                vec[h].set_centroid(vec[h].compute_centroid(vec[h]));
            }
        }
        //compute new clustering score
        computeClusteringScore();
        //compute absolute difference and set scoreDiff
        std::abs(scoreDiff -= computeClusteringScore());
    }
    
    
    
}

//INITIALIZATION
/*Open data file and read in points into point_space
 Pick k points to serve as initial centroids
 Create k-1 empty clusters with __release_points set to false
 Set the centroids of the the k clusters to the k points that were picked
 Create double score, double scoreDiff
 Set scoreDiff = CHANGE_THRESHOLD + 1
 
 //MEAT OF KMEANS
 loop until scoreDiff < CHANGE_THRESHOLD
 loop through all clusters
 loop through all points
 
 find the min distance(point, centroid)
 if centroid not of current cluster
 perform move(point, current, other)
 if centroid invalid
 compute and set valid to true
 compute new clustering score
 compute absolute difference and set scoreDiff
 
 TEAR DOWN
 write out the clustering results to a file
 
 (OPTIONAL) move all points back to point_space by setting all other centroids to infinity
 delete all clusters
 */

