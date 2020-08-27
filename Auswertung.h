#pragma once
#include <thread>

#include <pcl/filters/statistical_outlier_removal.h>

#include <string>
#include<algorithm>//min max
#include<vector>   //vector
#include <numeric> //mittelwert
#include <iostream>
#include<fstream>
#include <string>
#include <vector>


#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/console/parse.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/common/transforms.h>




std::vector<double> auswerten(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_soll, double aufloesung, std::vector<float> &);

void stein_position(pcl::PointCloud<pcl::PointXYZ>::Ptr , std::string );
