#pragma once
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/transforms.h>


pcl::PointCloud<pcl::PointXYZ>::Ptr ausrichten_stein(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess,  float soll_breite);
pcl::PointCloud<pcl::PointXYZ>::Ptr ausrichten_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess);