#pragma once

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <vector>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/segmentation/region_growing.h>

pcl::PointCloud<pcl::PointXYZ>::Ptr oberflaechen_filter(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, int num, int showcloud);
pcl::PointCloud<pcl::PointXYZ>::Ptr flaechen_filter(pcl::PointCloud<pcl::PointXYZ>::Ptr cl_fl_in, float grenzw, std::string achse, float aufloesung);
pcl::PointCloud<pcl::PointXYZ>::Ptr vox(pcl::PointCloud<pcl::PointXYZ>::Ptr cl_vox_in, float fakt);