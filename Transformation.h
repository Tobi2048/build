#pragma once
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/transforms.h>


pcl::PointCloud<pcl::PointXYZ>::Ptr ausrichten_stein(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess);
pcl::PointCloud<pcl::PointXYZ>::Ptr ausrichten(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess);