#include"Transformation.h"
#include"Mathe.h"
#include"Viewer.h"
#include"Filter.h"
#include<math.h>



pcl::PointCloud<pcl::PointXYZ>::Ptr ausrichten_stein(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
    int count = 1;
    float theta = 0;
    
  // -----------------------------------------------------------------------Aufteilen der Punktwolke in obere und untere hälfte 
    for (int i = 0; i < 20; i++) {

    float min_y = min_max(cloud, "min", "elem", "y");
    float max_y = min_max(cloud, "max", "elem", "y");
    float min_x = min_max(cloud, "min", "elem", "x");
    float max_x = min_max(cloud, "max", "elem", "x");





    float mitte = ((max_y -min_y) / 2);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_unten = flaechen_filter(cloud,min_y, "y", mitte);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_oben = flaechen_filter(cloud, min_y + mitte, "y", mitte);

    
        //In beiden hälften den min x wert finden 

        int min_x_oben = min_max(cloud_fl_oben, "min", "index", "x");
        int min_x_unten = min_max(cloud_fl_unten, "min", "index", "x");
        float oben_min_x = cloud_fl_oben->points[min_x_oben].x;
        float unten_min_x = cloud_fl_unten->points[min_x_unten].x;
        float oben_min_y = cloud_fl_oben->points[min_x_oben].y;
        float unten_min_y = cloud_fl_unten->points[min_x_unten].y;
       // std::cout << oben_min_x << " oben sooll gleich unten" << unten_min_x <<"und boden auf "<< min_max(cloud, "min", "elem", "y")<< std::endl;
        if (oben_min_x != unten_min_x) {
            theta = atan((oben_min_x - unten_min_x) / (oben_min_y - unten_min_y));

            Eigen::Affine3f transform_dreh = Eigen::Affine3f::Identity();

            transform_dreh.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
            pcl::transformPointCloud(*cloud, *cloud, transform_dreh);
            pcl::transformPointCloud(*cloud_fl_oben, *cloud_fl_oben, transform_dreh);
            pcl::transformPointCloud(*cloud_fl_unten, *cloud_fl_unten, transform_dreh);


            if (min_max(cloud, "min", "elem", "y") != 0) {

                Eigen::Affine3f transform_to_0 = Eigen::Affine3f::Identity();
                transform_to_0.translation() << 0, -min_max(cloud, "min", "elem", "y"), 0;
                pcl::transformPointCloud(*cloud, *cloud, transform_to_0);
                //       pcl::transformPointCloud(*cloud_fl, *cloud_fl, transform_to_0);

            }
            if (min_max(cloud, "min", "elem", "x") != 0) {

                Eigen::Affine3f transform_to_0 = Eigen::Affine3f::Identity();
                transform_to_0.translation() << -min_max(cloud, "min", "elem", "x"), 0, 0;
                pcl::transformPointCloud(*cloud, *cloud, transform_to_0);


            }

        }
       
        /*
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



        float min_y_a = min_max_cloud(cloud, "min", "y");
        float min_x_a = min_max_cloud(cloud, "min", "x");
        if (min_y_a != 0 ){

            Eigen::Affine3f transform_to_0 = Eigen::Affine3f::Identity();
            transform_to_0.translation() << 0, -min_y_a, 0;
            pcl::transformPointCloud(*cloud, *cloud, transform_to_0);
            //       pcl::transformPointCloud(*cloud_fl, *cloud_fl, transform_to_0);

        }
        if (min_x_a != 0) {

            Eigen::Affine3f transform_to_0 = Eigen::Affine3f::Identity();
            transform_to_0.translation() << -min_x_a, 0, 0;
            pcl::transformPointCloud(*cloud, *cloud, transform_to_0);
            //       pcl::transformPointCloud(*cloud_fl, *cloud_fl, transform_to_0);

        }
        min_y_a = min_max_cloud(cloud, "min", "y");
        min_x_a = min_max_cloud(cloud, "min", "x");
        std::cout << min_x_a << " x min und min y " << min_y_a << std::endl;
        */
    }
    return(cloud);
    


   

}





pcl::PointCloud<pcl::PointXYZ>::Ptr ausrichten(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess) {
    float z_start = 0;
    z_start = min_max(cloud_mess, "min", "elem", "z");
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl = flaechen_filter(cloud_mess, z_start, "z", 5);
    double z_w = 0;
    for (int i = 0; i < cloud_fl->points.size(); i++) {
        z_w = z_w +cloud_fl->points[i].z;

    }
   

    Eigen::Affine3f transform_to_0 = Eigen::Affine3f::Identity();
    
    transform_to_0.translation() << -min_max(cloud_mess, "min", "elem", "x"), -min_max(cloud_mess, "min", "elem", "y"),-( z_w / cloud_fl->points.size());
    pcl::transformPointCloud(*cloud_mess, *cloud_mess, transform_to_0);
   
    return(cloud_mess);

}