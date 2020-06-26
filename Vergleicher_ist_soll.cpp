#include"Vergleicher_ist_soll.h"
#include"Filter.h"
#include"Viewer.h"
#include"Mathe.h"



int Auswertung(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_soll, float aufloesung)
{
    /*
    int gut = 5;
    int mangel = 5;
    int defect = 20;
    
    


    //--------------Berechnung der Eckpunkte für die drehung ------------------------------------------------------
                //berechnung des eckpunktes mit dem kleinsten x wert
    int minElementIndex_x = min_max(cloud_mess, "min", "index", "x");
    int minElementIndex_y = min_max(cloud_mess, "min", "index", "y");
    int count = 1;
    float theta = 0;
    float soll_breite = abs(cloud_soll->points[min_max(cloud_soll, "min", "index", "x")].y - cloud_soll->points[min_max(cloud_soll, "max", "index", "x")].y);
    std::cout << soll_breite << std::endl;
 // ----------------wenn der stein schreg liegt dreh ihn gerade
    if (cloud_mess->points[min_max(cloud_mess, "min", "index", "x")].y - cloud_mess->points[min_max(cloud_mess, "min", "index", "y")].y <soll_breite* 0.9)//defi wirum der stein liegt
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
            //std::cout << " " << cloud_mess->points[minElementIndex_y].x << " soll gleich  " << cloud_mess->points[minElementIndex_x].x << std::endl;
        }
        //-----------------------------------------------------------------bring y min zu 0_________________________
        std::cout << cloud_mess->points[minElementIndex_y] << std::endl;
        Eigen::Affine3f transform_to_0 = Eigen::Affine3f::Identity();
        transform_to_0.translation() << -cloud_mess->points[minElementIndex_y].x, -cloud_mess->points[minElementIndex_y].y, 0.0;
        pcl::transformPointCloud(*cloud_mess, *cloud_mess,transform_to_0);
        std::cout << cloud_mess->points[minElementIndex_y] << std::endl;
    }
    else if (cloud_mess->points[min_max(cloud_mess, "min", "index", "x")].y - cloud_mess->points[min_max(cloud_mess, "min", "index", "y")].y > soll_breite * 0.9)//defi wirum der stein liegt
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
    }
    else
        std::cout << "drehung fehler" << std::endl;

    

    visual_app(cloud_mess, "auto_close", 2000);
    //---------------------------Berechnung höhe in scheiben von -xmin bis +xmax einteilung in gut schlecht ------------------------------------------------------

    int counter = 1;
    int count_gut = 0;
    int count_mangel = 0;
    int count_defect = 0;

    pcl::visualization::PCLVisualizer viewer1("Matrix einteilung gut schlecht");
    // Define R,G,B colors for the point cloud
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_cloud_color_handler(cloud_mess, 255, 255, 255);
    // We add the point cloud to the viewer and pass the color handler
    viewer1.addPointCloud(cloud_mess, source_cloud_color_handler, "original_cloud");
    viewer1.addCoordinateSystem(1.0, "cloud", 0);
    viewer1.setBackgroundColor(0.05, 0.05, 0.05, 0); // Setting background to a dark grey
    viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "original_cloud");

    float erg_h_soll=0;
    float grenz_x = ((cloud_mess->points[min_max(cloud_mess, "max", "index", "x")].x - cloud_mess->points[min_max(cloud_mess, "min", "index", "x")].x) / aufloesung);
    float start = cloud_mess->points[minElementIndex_x].x;
    float start_soll = cloud_soll->points[minElementIndex_x].x;
    for (int i = 0; i <= grenz_x; i++)
    {
        
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl = flaechen_filter(cloud_mess,( start + aufloesung * (i)), "x", aufloesung);
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_soll = flaechen_filter(cloud_soll, (start_soll + aufloesung * (i)), "x", aufloesung);
        if (cloud_fl_soll->points.size() != 0)
        {
            float erg_h = cloud_fl->points[min_max(cloud_fl, "max", "index", "y")].y - cloud_fl->points[min_max(cloud_fl, "min", "index", "y")].y;

            erg_h_soll = cloud_fl_soll->points[min_max(cloud_fl_soll, "max", "index", "y")].y - cloud_fl_soll->points[min_max(cloud_fl_soll, "min", "index", "y")].y;





            std::cout << erg_h << "   " << "   " << abs(erg_h_soll - erg_h) * 100 / erg_h_soll << "prozentuale  abweichung der höhe a" << std::endl;

            if (abs(erg_h_soll - erg_h) * 100 / erg_h_soll > defect)
            {
                pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl, 230, 20, 20); // Red
                viewer1.addPointCloud(cloud_fl, transformed_cloud_color_, "transformed_cloudd" + std::to_string(count_defect));
                viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudd" + std::to_string(count_defect));
                count_defect++;
            }
            else if (abs(erg_h_soll - erg_h) * 100 / erg_h_soll > mangel)
            {
                pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl, 255, 165, 79); // gelb
                viewer1.addPointCloud(cloud_fl, transformed_cloud_color_, "transformed_cloudm" + std::to_string(count_mangel));
                viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudm" + std::to_string(count_mangel));
                count_mangel++;
            }
            else if (abs(erg_h_soll - erg_h) * 100 / erg_h_soll < gut)
            {
                pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl, 0, 100, 0); // grün
                viewer1.addPointCloud(cloud_fl, transformed_cloud_color_, "transformed_cloudg" + std::to_string(count_gut));
                viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudg" + std::to_string(count_gut));
                count_gut++;
            }
            else {
                std::cout << "ups" << counter << std::endl;
            }
        }
        else
        {
            std::cout << "bin leehr" << counter << std::endl;
            erg_h_soll = 100;
        }

        counter++;
        std::cout << "  " << count_mangel << "  " << count_defect << "  " << count_gut<<std::endl;
        


        //viewer.setPosition(800, 400); // Setting visualiser window position







    }
    
    std::cout << "hilfe\n";
    
    while (!viewer1.wasStopped())
    { // Display the visualiser until 'q' key is pressed
        viewer1.spinOnce();
    }





    std::cout << "es sind " << count_gut << "gute Rheien und" << std::endl
        << "es sind " << count_mangel << "mangelhafte Rheien und" << std::endl
        << "es sind " << count_defect << "defecte Rheien und" << std::endl;

   



    //---------------------------Berechnung breite in scheiben von -ymin bis +ymax einteilung in gut schlecht ------------------------------------------------------



    
    int counter_y = 1;
    int count_gut_y = 0;
    int count_mangel_y = 0;
    int count_defect_y = 0;
    float auf_y = 1.2;

    pcl::visualization::PCLVisualizer viewer2("Matrix einteilung gut schlecht");
    // Define R,G,B colors for the point cloud
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_cloud_color_handler_y(cloud_mess, 255, 255, 255);
    // We add the point cloud to the viewer and pass the color handler
    viewer2.addPointCloud(cloud_mess, source_cloud_color_handler_y, "original_cloud_y");
    viewer2.addCoordinateSystem(1.0, "cloud_y", 0);
    viewer2.setBackgroundColor(0.05, 0.05, 0.05, 0); // Setting background to a dark grey
    viewer2.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "original_cloud_y");

    float grenz_y = (cloud_mess->points[min_max(cloud_mess, "max", "index", "y")].y - cloud_mess->points[min_max(cloud_mess, "min", "index", "y")].y) / auf_y + auf_y;
    float erg_mitt_b = 0;//aufsummiren für mittelwert
    for (int i = 0; i <= grenz_y; i++)
    {



        float start_x = cloud_mess->points[minElementIndex_y].y;
        //std::cout << "start ist " << start + aufloesung * (i - 1) << std::endl;
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl = flaechen_filter(cloud_mess, start_x + auf_y * (i - 1), "y", auf_y);
        //visual_app(cloud_fl_x,"auto_close",100);
        float erg_b = cloud_fl->points[min_max(cloud_fl, "max", "index", "x")].x - cloud_fl->points[min_max(cloud_fl, "min", "index", "x")].x;

        erg_mitt_b = erg_mitt_b + (soll_b - erg_b);//aufsummiren für mittelwert

        std::cout << erg_b << "   " << abs(soll_b - erg_b) * 100 / soll_b << "prozentuale  abweichung der breite a" << std::endl;
        if (abs(soll_b - erg_b) * 100 / soll_b > defect)
        {
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl, 230, 20, 20); // Red
            viewer2.addPointCloud(cloud_fl, transformed_cloud_color_, "transformed_cloudd" + std::to_string(count_defect_y));
            viewer2.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "transformed_cloudd" + std::to_string(count_defect_y));
            count_defect_y++;
        }
        else if (abs(soll_b - erg_b) * 100 / soll_h > mangel)
        {
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl, 255, 165, 79); // Red
            viewer2.addPointCloud(cloud_fl, transformed_cloud_color_, "transformed_cloudm" + std::to_string(count_mangel_y));
            viewer2.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "transformed_cloudm" + std::to_string(count_mangel_y));
            count_mangel_y++;
        }
        else if (abs(soll_b - erg_b) * 100 / soll_b < gut)
        {
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl, 0, 100, 0); // Red
            viewer2.addPointCloud(cloud_fl, transformed_cloud_color_, "transformed_cloudg" + std::to_string(count_gut_y));
            viewer2.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "transformed_cloudg" + std::to_string(count_gut_y));
            count_gut_y++;
        }
        else {
            std::cout << "ups";
        }
        counter_y++;
    }
    float erg_h_mittel_b = erg_mitt_b / (counter);
    std::cout << " durschnittliche breitenabweichung  " << erg_h_mittel_b << std::endl;
    while (!viewer2.wasStopped()) { // Display the visualiser until 'q' key is pressed
        viewer2.spinOnce();
    }
    


    

    */
return(0);
}