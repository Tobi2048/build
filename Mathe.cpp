#include"Mathe.h"
#include"viewer.h"
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/common/time.h>

float min_max(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, std::string anw, std::string rueck , std::string achse ) {
    //std::cout << cl_in->points.size() << std::endl;
    
    float min_x = cloud->points[0].x, min_y = cloud->points[0].y, min_z = cloud->points[0].z, max_x = cloud->points[0].x, max_y = cloud->points[0].y, max_z = cloud->points[0].z;
    size_t Index = 0;

    if (!cloud->empty()) {
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
        else {
            std::cout << " der 2 Eingabewert muss min oder max sein" << std::endl << std::endl;
            return -1;
        }
    }
    else {
        std::cout << " dleer" << std::endl << std::endl;
        return -1;
    }



    
}
float min_maxx(pcl::PointCloud<pcl::PointXYZ>::Ptr cl_in, std::string anw, std::string var, std::string achse) {
    //std::cout << cl_in->points.size() << std::endl;
    std::vector< float> point;//laden der gefilterten zange in vector 

    if (achse == "x") {
        for (double i = 0; i < cl_in->size(); ++i)
        {
            point.push_back(cl_in->points[i].x);
        }
    }
    else if (achse == "y") {
        for (double i = 0; i < cl_in->size(); ++i)
        {
            point.push_back(cl_in->points[i].y);
        }
    }
    else if (achse == "z") {
        for (double i = 0; i < cl_in->size(); ++i)
        {
            point.push_back(cl_in->points[i].z);
        }
    }
    else
        std::cout << "der vierte Eingabewert muss x / y / z  sein " << std::endl;



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

