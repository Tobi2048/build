#pragma once
#include <string>
#include<algorithm>//min max
#include<vector>   //vector
#include <numeric> //mittelwert
#include <iostream>
#include<fstream>

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>

int min_max(pcl::PointCloud<pcl::PointXYZ>::Ptr cl_in, std::string anw, std::string var = " h", std::string achse = " h");
float mittel_wert(std::vector<float>& vec);