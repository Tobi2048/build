#pragma once

#include <pcl/common/common_headers.h>
#include <pcl/range_image/range_image.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/range_image_visualizer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/console/parse.h>

#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <pcl/point_types.h>



pcl::PointCloud<pcl::PointXYZ>::Ptr sollstein_erstellen(float aufloesung = 0.1, std::string dat="leer");
float soll_breite_txt();

typedef struct points_txt_soll
{
	double x;  //mm world coordinate x
	double y;  //mm world coordinate y
	double z;  //mm world coordinate z
};


typedef struct points_txt_solll
{
	double x;  //mm world coordinate x
	double y;  //mm world coordinate y
	double z;  //mm world coordinate z
};

