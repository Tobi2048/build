#include"Mathe.h"
#include"viewer.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/common/time.h>

int min_max(pcl::PointCloud<pcl::PointXYZ>::Ptr cl_in, std::string anw, std::string var , std::string achse ) {
    //std::cout << cl_in->points.size() << std::endl;
    
        std::vector< long long> point(cl_in->points.size());//laden der gefilterten zange in vector 
        for (int i = 0; i < point.size(); ++i)
        {
            if (achse == "x")
                point[i] = cl_in->points[i].x;
            else if (achse == "y")
                point[i] = cl_in->points[i].y;
            else if (achse == "z")
                point[i] = cl_in->points[i].z;
            else
                std::cout << "der vierte Eingabewert muss x / y / z  sein " << std::endl;

        }
       

        if (anw == "min") {
            int minElementIndex = std::min_element(point.begin(), point.end()) - point.begin();
            float minElement = *std::min_element(point.begin(), point.end());
            //std::cout << " xmin ecke punktindex " << minElementIndex << "      " << minElement << std::endl << std::endl;
            if (var == "elem")
                return(minElement);
            else if (var == "index")
                return(minElementIndex);
            else
                std::cout << " der dritte wert muss index oder elem sein" << std::endl;
        }
        else if (anw == "max") {

            int maxElementIndex = std::max_element(point.begin(), point.end()) - point.begin();
            float maxElement = *std::max_element(point.begin(), point.end());
            //std::cout << " xmax ecke punktindex " << maxElementIndex << "      " << maxElement << std::endl << std::endl;
            if (var == "elem")
                return(maxElement);
            else if (var == "index")
                return(maxElementIndex);
            else
                std::cout << " der dritte wert muss index oder elem sein" << std::endl;
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

float min_max_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, std::string anw, std::string achse) {
    float min_x = cloud->points[0].x, min_y = cloud->points[0].y, min_z = cloud->points[0].z, max_x = cloud->points[0].x, max_y = cloud->points[0].y, max_z = cloud->points[0].z;
    
    for (size_t i = 1; i < cloud->points.size(); ++i) {
        if (cloud->points[i].x <= min_x)
            min_x = cloud->points[i].x;
        else if (cloud->points[i].y <= min_y)
            min_y = cloud->points[i].y;
        else if (cloud->points[i].z <= min_z)
            min_z = cloud->points[i].z;
        else if (cloud->points[i].x >= max_x)
            max_x = cloud->points[i].x;
        else if (cloud->points[i].y >= max_y)
            max_y = cloud->points[i].y;
        else if (cloud->points[i].z >= max_z)
            max_z = cloud->points[i].z;
    }
    
    if (achse == "x") {
        if (anw == "min") {
            return (min_x);
        }
        if (anw == "max") {
            return (max_x);
        }
    }
    if (achse == "y") {
        if (anw == "min") {
            return (min_y);
        }
        if (anw == "max") {
            return (max_y);
        }
    }
    if (achse == "z") {
        if (anw == "min") {
            return (min_z);
        }
        if (anw == "max") {
            return (max_z);
        }
    }
}