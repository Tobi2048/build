#include"Viewer.h"



void visual_app_soll(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
    //--------------------------------------------------------------------------zeigt die punktwolke an -------------------------------
    pcl::visualization::PCLVisualizer viewer("Matrix transformation example");
    // Define R,G,B colors for the point cloud
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color_handler(cloud, 0.05, 0.05, 0.05);//farbe einstellen
    // We add the point cloud to the viewer and pass the color handler
    viewer.addPointCloud(cloud, cloud_color_handler, "original_cloud");
    viewer.setWindowName("Anzeige des Soll-Steins");
    viewer.addCoordinateSystem(1.0, "cloud", 0);
    viewer.setBackgroundColor(255, 255, 255, 0); // Setting background to a dark grey
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "original_cloud");
    viewer.setSize(475, 475);
    viewer.setPosition(2, 2); // Setting visualiser window position


    while (!viewer.wasStopped()) { // Display the visualiser until 'q' key is pressed
        viewer.spinOnce();
        
        

    }
}
void visual_app_mess(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{

    //--------------------------------------------------------------------------zeigt die punktwolke an -------------------------------
    pcl::visualization::PCLVisualizer viewer("Matrix transformation example");
    // Define R,G,B colors for the point cloud
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color_handler(cloud, 0.05, 0.05, 0.05);//farbe einstellen
    // We add the point cloud to the viewer and pass the color handler
    viewer.addPointCloud(cloud, cloud_color_handler, "original_cloud");
    viewer.setWindowName("Anzeige des Mess-Steins");
    viewer.addCoordinateSystem(1.0, "cloud", 0);
    viewer.setBackgroundColor(255, 255, 255, 0); // Setting background to a dark grey
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "original_cloud");
    viewer.setSize(475, 475);
    viewer.setPosition(477, 2); // Setting visualiser window position


    while (!viewer.wasStopped()) { // Display the visualiser until 'q' key is pressed
        viewer.spinOnce();

        

    }
    
    
}

