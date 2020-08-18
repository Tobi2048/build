#include"Mathe.h"
#include"viewer.h"

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