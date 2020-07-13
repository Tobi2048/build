#include"Transformation.h"
#include"Mathe.h"

#include"Filter.h"



pcl::PointCloud<pcl::PointXYZ>::Ptr Ausrichten(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess,float soll_breite)
{
    int gut = 5;
    int mangel = 5;
    int defect = 20;


    //--------------Berechnung der Eckpunkte für die drehung ------------------------------------------------------
                //berechnung des eckpunktes mit dem kleinsten x wert
    int count = 1;
    float theta = 0;

    //------------------------schauen ob stein gerade ist--------------------------------------
    int minElementIndex_x = min_max(cloud_mess, "min", "index", "x");
    int minElementIndex_y = min_max(cloud_mess, "min", "index", "y");
    int minElementIndex_z = min_max(cloud_mess, "min", "index", "z");
    float start = cloud_mess->points[minElementIndex_y].y;
   
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl = flaechen_filter(cloud_mess, start, "y", 0.4);//y min filtern um davon min max zu finden
    
  
    int maxIndex_x = min_max(cloud_fl,"max","index","x");
    int minIndex_x = min_max(cloud_fl,"min","index","x");

    if (cloud_fl->points[minIndex_x].x != 0 || cloud_fl->points[minIndex_x].y != 0||cloud_mess->points[minElementIndex_z].z!=0)
    {
        Eigen::Affine3f transform_to_0 = Eigen::Affine3f::Identity();
        transform_to_0.translation() << -cloud_fl->points[minIndex_x].x, -cloud_fl->points[minIndex_x].y, -cloud_mess->points[minElementIndex_z].z;
        pcl::transformPointCloud(*cloud_mess, *cloud_mess,transform_to_0);
        pcl::transformPointCloud(*cloud_fl, *cloud_fl, transform_to_0);
        std::cout<<"ruecke linke ecke zu 0,0" << cloud_mess->points[minElementIndex_x] << std::endl;
    }
    std::cout << "linke ecke " << cloud_mess->points[minElementIndex_x] << std::endl;
    std::cout << (cloud_fl->points[maxIndex_x].x - cloud_fl->points[minIndex_x].x) << std::endl;// gibt die breite der gefilterten fläche
        

    if ((cloud_fl->points[maxIndex_x].x - cloud_fl->points[minIndex_x].x) < soll_breite*0.8)//wenn gefilterte Fläche kleiner als 0.8 mal solllbreite ist 
    {
        // ----------------wenn der stein schreg liegt dreh ihn gerade
        if (cloud_mess->points[min_max(cloud_mess, "min", "index", "x")].y - cloud_mess->points[min_max(cloud_mess, "min", "index", "y")].y >soll_breite * 0.8)//defi wirum der stein liegt
        {
            std::cout << "bin linksrum\n";
            while (bool abfrage = cloud_mess->points[minElementIndex_y].x != cloud_mess->points[minElementIndex_x].x)
            {


                Eigen::Affine3f transform_1 = Eigen::Affine3f::Identity();

                if (cloud_mess->points[minElementIndex_y].x > cloud_mess->points[minElementIndex_x].x)//wenn linksrum richte zur x achse aus  min_y.x==min_x.x
                {
                    theta = -(float)M_PI / (2 * count); // The angle of rotation in radians
                }
                else if (cloud_mess->points[minElementIndex_y].x < cloud_mess->points[minElementIndex_x].x)
                {
                    theta = (float)M_PI / (2 * count); // The angle of rotation in radians
                }
                else
                {
                    std::cout << "bin im break" << std::endl;
                    break;
                }
                transform_1.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
                pcl::transformPointCloud(*cloud_mess, *cloud_mess, transform_1);
                count++;
              // std::cout << " " << cloud_mess->points[minElementIndex_y].x << " soll gleich  " << cloud_mess->points[minElementIndex_x].x << std::endl;
            }
           
        }
        else if (cloud_mess->points[min_max(cloud_mess, "min", "index", "x")].y - cloud_mess->points[min_max(cloud_mess, "min", "index", "y")].y < soll_breite * 0.8)//defi wirum der stein liegt
        {
            std::cout << "bin rechtsrum\n";
            while (bool abfrage = cloud_mess->points[minElementIndex_y].y != cloud_mess->points[minElementIndex_x].y)//wenn Rechtsrum richte zur y achse aus  min_y.y==min_x.y
            {

                Eigen::Affine3f transform_1 = Eigen::Affine3f::Identity();

                if (cloud_mess->points[minElementIndex_y].y > cloud_mess->points[minElementIndex_x].y)
                {
                    theta = -(float)M_PI / (2 * count); // The angle of rotation in radians

                }
                else if (cloud_mess->points[minElementIndex_y].y < cloud_mess->points[minElementIndex_x].y)
                {
                    theta = (float)M_PI / (2 * count); // The angle of rotation in radians
                }
                else
                {
                    std::cout << "bin im break" << std::endl;
                    break;
                }
                transform_1.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
                pcl::transformPointCloud(*cloud_mess, *cloud_mess, transform_1);
                count++;
                
                //std::cout << " " << cloud_mess->points[minElementIndex_y].y << " soll gleich  " << cloud_mess->points[minElementIndex_x].y << std::endl;
            }
            
            
        }
        else
            std::cout << "drehung fehler" << std::endl;


    }
    else
    {
        std::cout << "cloud ist gerade\n";
        return(cloud_mess);
    }
   
    return(cloud_mess);
   
}
