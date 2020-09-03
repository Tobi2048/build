#include"Mathe.h"
#include"viewer.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/common/time.h>

float min_max(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, std::string anw, std::string rueck , std::string achse ) {
    //std::cout << cl_in->points.size() << std::endl;
    
    float min_x = cloud->points[0].x, min_y = cloud->points[0].y, min_z = cloud->points[5].z, max_x = cloud->points[0].x, max_y = cloud->points[0].y, max_z = cloud->points[0].z;
    size_t Index = 5;


    if (anw == "min") {

        if (achse == "x") {
            for (size_t i = 1; i < cloud->points.size(); ++i) {
                if (cloud->points[i].x <= min_x) {
                    min_x = cloud->points[i].x;
                    Index = i;
                }
            }
            if (rueck == "index")
                return Index;
            if (rueck == "elem")
                return min_x;
        }

        else if (achse == "y")
        {
            for (size_t i = 1; i < cloud->points.size(); ++i) {
                if (cloud->points[i].y <= min_y) {
                    min_y = cloud->points[i].y;
                    Index = i;
                }
            }
            if (rueck == "index")
                return Index;
            if (rueck == "elem")
                return min_y;
        }
        else if (achse == "z") {
            for (size_t i = 1; i < cloud->points.size(); ++i) {
                if (cloud->points[i].z <= min_z) {
                    min_z = cloud->points[i].z;
                    Index = i;
                }
            }
            if (rueck == "index")
                return Index;
            if (rueck == "elem")
                return min_z;
        }
        else
            std::cout << "der vierte Eingabewert muss x / y / z  sein " << std::endl;
    }
    else if (anw == "max") {
        if (achse == "x") {
            for (size_t i = 1; i < cloud->points.size(); ++i) {
                if (cloud->points[i].x >= max_x) {
                    max_x = cloud->points[i].x;
                    Index = i;
                }
            }
            if (rueck == "index")
                return Index;
            if (rueck == "elem")
                return max_x;
        }

        else if (achse == "y")
        {
            for (size_t i = 1; i < cloud->points.size(); ++i) {
                if (cloud->points[i].y >= max_y) {
                    max_y = cloud->points[i].y;
                    Index = i;
                }
            }
            if (rueck == "index")
                return Index;
            if (rueck == "elem")
                return max_y;
        }
        else if (achse == "z") {
            for (size_t i = 1; i < cloud->points.size(); ++i) {
                if (cloud->points[i].z >= max_z) {
                    max_z = cloud->points[i].z;
                    Index = i;
                }
            }
            if (rueck == "index")
                return Index;
            if (rueck == "elem")
                return max_z;
        }
        else
            std::cout << "der vierte Eingabewert muss x / y / z  sein " << std::endl;


    }
    else
        std::cout << " der 2 Eingabewert muss min oder max sein" << std::endl << std::endl;
    return -1;



    
}
float mittel_wert(std::vector<float>&vec) {
    double zw_wert=0;
    for (int i = 0; i < vec.size(); i++) {
       
            zw_wert = zw_wert + vec[i];
        
    }
    return(zw_wert / vec.size());
}

