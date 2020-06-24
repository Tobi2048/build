#pragma once

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>

pcl::PointCloud<pcl::PointXYZ>::Ptr vox(pcl::PointCloud<pcl::PointXYZ>::Ptr cl_vox_in, float fakt);