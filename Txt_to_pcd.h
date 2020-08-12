#pragma once


#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
#include <pcl/filters/voxel_grid.h>


typedef struct points_txt
{
	double x;  //mm world coordinate x
	double y;  //mm world coordinate y
	double z;  //mm world coordinate z
	int rgb;


}POINT_WORLD;



pcl::PointCloud<pcl::PointXYZ>::Ptr Convert_txt_to_pcd(float fakt, std::string dat);