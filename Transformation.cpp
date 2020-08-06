#include"Transformation.h"
#include"Mathe.h"

#include"Filter.h"



pcl::PointCloud<pcl::PointXYZ>::Ptr ausrichten_stein(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,float soll_breite)
{
    int count = 1;
    float theta = 0;
    
  // -----------------------------------------------------------------------Aufteilen der Punktwolke in obere und untere hälfte 
    int min_y = min_max(cloud, "min", "index", "y");
    int max_y = min_max(cloud, "max", "index", "y");
    int min_x = min_max(cloud, "min", "index", "x");
    int max_x = min_max(cloud, "max", "index", "x");




    Eigen::Affine3f transform_to_0_0 = Eigen::Affine3f::Identity();

    transform_to_0_0.translation() << -cloud->points[min_x].x, -cloud->points[min_y].y, 0;
    pcl::transformPointCloud(*cloud, *cloud, transform_to_0_0);






    float mitte = ((cloud->points[max_y].y - cloud->points[min_y].y) / 2);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_unten = flaechen_filter(cloud, cloud->points[min_y].y, "y", mitte);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_oben = flaechen_filter(cloud, cloud->points[min_y].y + mitte, "y", mitte);

    for (int i = 0; i < 3; i++) {
        //In beiden hälften den min x wert finden 

        int min_x_oben = min_max(cloud_fl_oben, "min", "index", "x");
        int min_x_unten = min_max(cloud_fl_unten, "min", "index", "x");
        float oben_min_x = cloud_fl_oben->points[min_x_oben].x;
        float unten_min_x = cloud_fl_unten->points[min_x_unten].x;



        while (bool abrfrage = oben_min_x != unten_min_x)
        {
            Eigen::Affine3f transform_dreh = Eigen::Affine3f::Identity();
            oben_min_x = cloud_fl_oben->points[min_x_oben].x;
            unten_min_x = cloud_fl_unten->points[min_x_unten].x;
            theta = 0;

            if (oben_min_x < unten_min_x) {// links
                theta = -((float)M_PI / (4 * count)); // The angle of rotation in radians
                transform_dreh.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
                pcl::transformPointCloud(*cloud, *cloud, transform_dreh);
                pcl::transformPointCloud(*cloud_fl_oben, *cloud_fl_oben, transform_dreh);
                pcl::transformPointCloud(*cloud_fl_unten, *cloud_fl_unten, transform_dreh);
            }
            if (oben_min_x > unten_min_x) {//rechts
                theta = +((float)M_PI / (4 * count)); // The angle of rotation in radians
                transform_dreh.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
                pcl::transformPointCloud(*cloud, *cloud, transform_dreh);
                pcl::transformPointCloud(*cloud_fl_oben, *cloud_fl_oben, transform_dreh);
                pcl::transformPointCloud(*cloud_fl_unten, *cloud_fl_unten, transform_dreh);
            }
            count++;
        }
        
    }
  
    int min_y_a = min_max(cloud, "min", "index", "y");
    int min_x_a = min_max(cloud, "min", "index", "x");
    if (cloud->points[min_y_a].y != 0 || cloud->points[min_x_a].x != 0) {

        Eigen::Affine3f transform_to_0 = Eigen::Affine3f::Identity();
        transform_to_0.translation() << -cloud->points[min_x_a].x, -cloud->points[min_y_a].y, 0;
        pcl::transformPointCloud(*cloud, *cloud, transform_to_0);
        //       pcl::transformPointCloud(*cloud_fl, *cloud_fl, transform_to_0);

    }
    return(cloud);
    


   

}





pcl::PointCloud<pcl::PointXYZ>::Ptr ausrichten_cloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess) {
    float z_start = 0;
    z_start = cloud_mess->points[min_max(cloud_mess, "min", "index", "z")].z;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl = flaechen_filter(cloud_mess, z_start, "z", 0.3);
    double z_w = 0;
    for (int i = 0; i < cloud_fl->points.size(); i++) {
        z_w = z_w +cloud_fl->points[i].z;

    }
   

    Eigen::Affine3f transform_to_0 = Eigen::Affine3f::Identity();
    transform_to_0.translation() << -cloud_mess->points[min_max(cloud_mess, "min", "index", "x")].x, -cloud_mess->points[min_max(cloud_mess, "min", "index", "y")].y,-( z_w / cloud_fl->points.size());
    pcl::transformPointCloud(*cloud_mess, *cloud_mess, transform_to_0);

    return(cloud_mess);

}