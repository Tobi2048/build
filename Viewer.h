#pragma once
#include <pcl/io/pcd_io.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>


void visual_app_soll(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
void visual_app_mess(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);