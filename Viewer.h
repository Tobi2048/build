#pragma once
#include <pcl/io/pcd_io.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>


void visual_app(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, std::string anw, unsigned long zeit);