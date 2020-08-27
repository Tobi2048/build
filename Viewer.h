#pragma once
#include <pcl/io/pcd_io.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>


void view_soll(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
void view_mess(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);