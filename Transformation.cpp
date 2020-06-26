#include"Transformation.h"
#include"Mathe.h"

#include"Filter.h"
#include"Viewer.h"

pcl::PointCloud<pcl::PointXYZ>::Ptr Ausrichten(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess,float soll_breite)
{
    int gut = 5;
    int mangel = 5;
    int defect = 20;


    //--------------Berechnung der Eckpunkte für die drehung ------------------------------------------------------
                //berechnung des eckpunktes mit dem kleinsten x wert
    int count = 1;
    float theta = 0;


    int minElementIndex_x = min_max(cloud_mess, "min", "index", "x");
    int minElementIndex_y = min_max(cloud_mess, "min", "index", "y");
    float start = cloud_mess->points[minElementIndex_x].x;
    visual_app(cloud_mess, "auto_close", 1000);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl = flaechen_filter(cloud_mess, start, "y", 0.5);
    visual_app(cloud_fl, "auto_clos", 6000);
    int maxIndex_x = min_max(cloud_fl, "max", "index", "x");
    int minIndex_x = min_max(cloud_fl, "min", "index", "x");
    std::cout << (cloud_fl->points[maxIndex_x].x - cloud_fl->points[minIndex_x].x) << std::endl;
        

    if ((cloud_fl->points[maxIndex_x].x - cloud_fl->points[minIndex_x].x) < soll_breite*0.7)
    {
        // ----------------wenn der stein schreg liegt dreh ihn gerade
        if (cloud_mess->points[min_max(cloud_mess, "min", "index", "x")].y - cloud_mess->points[min_max(cloud_mess, "min", "index", "y")].y >soll_breite * 0.9)//defi wirum der stein liegt
        {
            std::cout << "bin linksrum\n";
            while (bool abfrage = cloud_mess->points[minElementIndex_y].x != cloud_mess->points[minElementIndex_x].x)
            {


                Eigen::Affine3f transform_1 = Eigen::Affine3f::Identity();

                if (cloud_mess->points[minElementIndex_y].x > cloud_mess->points[minElementIndex_x].x)//wenn linksrum richte zur x achse aus  min_y.x==min_x.x
                {
                    theta = -(float)M_PI / (2 * count); // The angle of rotation in radians
                    transform_1.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
                    pcl::transformPointCloud(*cloud_mess, *cloud_mess, transform_1);

                }
                else if (cloud_mess->points[minElementIndex_y].x < cloud_mess->points[minElementIndex_x].x)
                {
                    theta = (float)M_PI / (2 * count); // The angle of rotation in radians
                    transform_1.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
                    pcl::transformPointCloud(*cloud_mess, *cloud_mess, transform_1);

                }
                else
                {
                    std::cout << "bin im break" << std::endl;
                    break;
                }

                count++;
              // std::cout << " " << cloud_mess->points[minElementIndex_y].x << " soll gleich  " << cloud_mess->points[minElementIndex_x].x << std::endl;
            }
            //-----------------------------------------------------------------bring y min zu 0_________________________
            std::cout << cloud_mess->points[minElementIndex_y] << std::endl;
            Eigen::Affine3f transform_to_0 = Eigen::Affine3f::Identity();
            transform_to_0.translation() << -cloud_mess->points[minElementIndex_y].x, -cloud_mess->points[minElementIndex_y].y, 0.0;
            pcl::transformPointCloud(*cloud_mess, *cloud_mess, transform_to_0);
            std::cout << cloud_mess->points[minElementIndex_y] << std::endl;
            return(cloud_mess);
            visual_app(cloud_mess, "auto_close", 1000);
        }
        else if (cloud_mess->points[min_max(cloud_mess, "min", "index", "x")].y - cloud_mess->points[min_max(cloud_mess, "min", "index", "y")].y < soll_breite * 0.9)//defi wirum der stein liegt
        {
            std::cout << "bin rechtsrum\n";
            while (bool abfrage = cloud_mess->points[minElementIndex_y].y != cloud_mess->points[minElementIndex_x].y)//wenn Rechtsrum richte zur y achse aus  min_y.y==min_x.y
            {

                Eigen::Affine3f transform_1 = Eigen::Affine3f::Identity();

                if (cloud_mess->points[minElementIndex_y].y > cloud_mess->points[minElementIndex_x].y)
                {
                    theta = -(float)M_PI / (2 * count); // The angle of rotation in radians
                    transform_1.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
                    pcl::transformPointCloud(*cloud_mess, *cloud_mess, transform_1);

                }
                else if (cloud_mess->points[minElementIndex_y].y < cloud_mess->points[minElementIndex_x].y)
                {
                    theta = (float)M_PI / (2 * count); // The angle of rotation in radians
                    transform_1.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
                    pcl::transformPointCloud(*cloud_mess, *cloud_mess, transform_1);

                }
                else
                {
                    std::cout << "bin im break" << std::endl;
                    break;
                }
                count++;
                
                //std::cout << " " << cloud_mess->points[minElementIndex_y].y << " soll gleich  " << cloud_mess->points[minElementIndex_x].y << std::endl;
            }
            //-----------------------------------------------------------------bring x min zu 0_________________________
            std::cout << cloud_mess->points[minElementIndex_x] << std::endl;
            Eigen::Affine3f transform_to_0 = Eigen::Affine3f::Identity();
            transform_to_0.translation() << -cloud_mess->points[minElementIndex_x].x, -cloud_mess->points[minElementIndex_x].y, 0.0;
            pcl::transformPointCloud(*cloud_mess, *cloud_mess, transform_to_0);
            std::cout << cloud_mess->points[minElementIndex_x] << std::endl;
            return(cloud_mess);
            visual_app(cloud_mess, "auto_close", 1000);
        }
        else
            std::cout << "drehung fehler" << std::endl;


    }
    else
    {
        std::cout << "cloud ist gerade\n";
        return(cloud_mess);
    }
    
}