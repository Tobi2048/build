#pragma once
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/transforms.h>


pcl::PointCloud<pcl::PointXYZ>::Ptr Ausrichten(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess,  float soll_breite);
pcl::PointCloud<pcl::PointXYZ>::Ptr Ausrichten_pos(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess);