#include"Viewer.h"



void visual_app(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, std::string anw, unsigned long zeit)
{
    //--------------------------------------------------------------------------zeigt die punktwolke an -------------------------------
    pcl::visualization::PCLVisualizer viewer("Matrix transformation example");
    // Define R,G,B colors for the point cloud
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color_handler(cloud,0.1, 0.1, 0.1);//farbe einstellen
    // We add the point cloud to the viewer and pass the color handler
    viewer.addPointCloud(cloud, cloud_color_handler, "original_cloud");
    viewer.addCoordinateSystem(100.0, "cloud", 0);
    viewer.setBackgroundColor(255, 255, 255, 0); // Setting background Wei�
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "original_cloud");
    
    viewer.setWindowName("cloud");
    viewer.setPosition(2, 2); // Setting visualiser window position


    while (!viewer.wasStopped()) { // Display the visualiser until 'q' key is pressed
        viewer.spinOnce();
        if (anw == "auto_close")
        {
            Sleep(zeit);
            viewer.close();
        }


    }
}