#define ausw


#include"Auswertung.h"
#include"Transformation.h"
#include"Filter.h"
#include"Viewer.h"
#include"Mathe.h"
#include<numeric>
#include<vector>
#include <iostream>
#include<fstream>

#ifdef _DEBUG
#define DEBUG
#endif
#ifdef ausw
#define DEBUG
#endif


std::vector<double> auswerten(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_solll, double aufloesung, std::vector<float>& üb_ab)
{
    int zaheler = 0;
    std::cout << zaheler++ << std::endl;
   
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_soll = cloud_solll;
    float gut_l = üb_ab[0], gut_b = üb_ab[1], gut_h = üb_ab[2];
    std::vector<double> ret(24);


    float erg_soll_h = min_max(cloud_soll, "max", "elem", "z");

    float count_gut_h = 0;
    float count_mangel_h = 0;
    float count_defect_h = 0;
    int counter_h = 0;
    std::vector<float> vec_h;
    std::vector<float> vec_h_mitt;
    float hoehe_mittel = 0;
    for (int i = 0; i < cloud->size(); i++)
    {

        if (abs(cloud->points[i].z - erg_soll_h) > gut_h * 2)
        {
            count_defect_h++;
        }
        else if (abs(cloud->points[i].z - erg_soll_h) > gut_h)
        {
            count_mangel_h++;
        }
        else if (abs(cloud->points[i].z - erg_soll_h) < gut_h)
        {
            count_gut_h++;
        }
        vec_h.push_back(abs(erg_soll_h - cloud->points[i].z));
        vec_h_mitt.push_back(cloud->points[i].z);
        counter_h++;
    }
    std::cout << zaheler++ << std::endl;

    hoehe_mittel = mittel_wert(vec_h_mitt);

    double v = 0;
    float mitt_abw_h = mittel_wert(vec_h);
    for (int i = 0; i < vec_h_mitt.size(); i++) {
        v = v + ((vec_h_mitt[i] - hoehe_mittel) * (vec_h_mitt[i] - hoehe_mittel));
    }


    float stand_abw_h = 2 * sqrt(v /( vec_h_mitt.size() - 1));
    
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess = flaechen_filter(cloud, hoehe_mittel - (gut_h / 2), "z", gut_h * 1.4);
   
    //------------------------------------------------------------------------------------------------------------------------------------------auswertung der Breite _________________------------------------------------------
#ifndef DEBUG
    std::fstream file1;
    std::string ort = " ";
    ort = ("C:/Users/tobia/Desktop/Masterarbeit_Qualitätskontrolle_Passsteinautomat/Auswertung/scheibchen/stein_A_erg_b.txt");
    file1.open(ort.c_str(), std::ios::out | std::ifstream::app);
#endif
    std::cout << zaheler++ << std::endl;
    float grenz_x_soll = min_max(cloud_soll, "max", "elem", "x");
    float start_x_soll = min_max(cloud_soll, "min", "elem", "x");
    
    float grenz_x_mess = min_max(cloud_mess, "max", "elem", "x");
    float start_x_mess = min_max(cloud_mess, "min", "elem", "x");
    float grenz_x = grenz_x_mess;
    if (grenz_x_soll < grenz_x_mess)
        grenz_x = grenz_x_mess;
    if (grenz_x_soll > grenz_x_mess)
        grenz_x = grenz_x_soll;

    
    std::cout <<"alt   neu" <<grenz_x_mess << "  mess grenzen soll " << grenz_x_soll << std::endl;
   
    float counter_mess = 0;
    float count_gut = 0;
    float count_mangel = 0;
    float count_defect = 0;
    int counter = 0;
    float erg_mess = 0;
    float erg_soll = 0;

    std::vector<float> vec_mess_x;
    std::vector<float> vec_soll_x;
    std::vector<float> vec_abw_x;

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_soll(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_mess(new pcl::PointCloud<pcl::PointXYZ>);
#ifndef DEBUG
    pcl::visualization::PCLVisualizer viewer1("Matrix einteilung gut schlecht");
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_cloud_color_handler(cloud_mess, 0.05, 0.05, 0.05);// We add the point cloud to the viewer and pass the color handler
    viewer1.addCoordinateSystem(100.0, "cloud", 0);
    viewer1.setBackgroundColor(255, 255, 255, 0); // Setting background to a dark grey
    viewer1.setSize(475, 475);
    viewer1.setPosition(2, 507);
    viewer1.setWindowName("Anzeige Auswertung Länge des Steins");
#endif



    for (int i = 0; i < grenz_x / aufloesung; i++)
    {
        if (i < grenz_x_mess / aufloesung) {
            cloud_fl_mess = flaechen_filter(cloud_mess, (start_x_mess + aufloesung * (i)), "x", aufloesung * 2);
            
            if (!cloud_fl_mess->empty()) {
                erg_mess = min_max(cloud_fl_mess, "max", "elem", "y") - min_max(cloud_fl_mess, "min", "elem", "y");
            }
            else
                erg_mess = 0.0001;

            vec_mess_x.push_back(erg_mess);
        }else
            erg_mess = 0.0001;
        if (i == 188)
            std::cout << "bla";
    

        if (i < grenz_x_soll / aufloesung)
        {
            cloud_fl_soll = flaechen_filter(cloud_soll, (start_x_soll + aufloesung * (i)), "x", aufloesung * 1.5);
            erg_soll = min_max(cloud_fl_soll, "max", "elem", "y") - min_max(cloud_fl_soll, "min", "elem", "y");
            vec_soll_x.push_back(erg_soll);
        }
        else
            erg_soll= 0.0001;
        vec_abw_x.push_back(abs(erg_mess - erg_soll));

#ifndef DEBUG
        file1 << std::to_string(i * aufloesung) << "  " << std::to_string(erg_soll) <<"  " << std::to_string(erg_mess) << std::endl;
#endif
        if (abs(erg_soll - erg_mess) > gut_l * 2)
        {
#ifndef DEBUG
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_mess, 230, 20, 20); // Red
            viewer1.addPointCloud(cloud_fl_mess, transformed_cloud_color_, "transformed_cloudd" + std::to_string(count_defect));
            viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudd" + std::to_string(count_defect));
#endif
            count_defect++;
        }
        else if (abs(erg_soll - erg_mess) > gut_l)
        {
#ifndef DEBUG
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_mess, 255, 165, 79); // gelb
            viewer1.addPointCloud(cloud_fl_mess, transformed_cloud_color_, "transformed_cloudm" + std::to_string(count_mangel));
            viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudm" + std::to_string(count_mangel));
#endif
            count_mangel++;
        }
        else if (abs(erg_soll - erg_mess) < gut_l)
        {
#ifndef DEBUG
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_mess, 0, 100, 0); // grün
            viewer1.addPointCloud(cloud_fl_mess, transformed_cloud_color_, "transformed_cloudg" + std::to_string(count_gut));
            viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudg" + std::to_string(count_gut));
#endif
            count_gut++;
        }
        counter++;

    }
    std::cout << zaheler++ << std::endl;
#ifndef DEBUG
    file1.close();
#endif
    float erg_mess_mittel_x = mittel_wert(vec_mess_x);
    float abw_mitt_x = mittel_wert(vec_abw_x);

    double zw_er = 0;
    int step = 0;
    float erg_sabw_x = 0;
    for (int i = 0; i < vec_mess_x.size(); i++) {
        if (abs(vec_mess_x[i] - erg_mess_mittel_x) < 0.7 * erg_mess_mittel_x) {
            zw_er = zw_er + ((abs(vec_mess_x[i] - erg_mess_mittel_x)) * (abs(vec_mess_x[i] - erg_mess_mittel_x)));
            step++;
          
        }
    }
    erg_sabw_x = 2 * sqrt(zw_er / (step - 1));
    std::cout << zaheler++ << std::endl;
  //--------------------------------------------------------------------------------------------------länge---------------------------------------------------------------------------
#ifndef DEBUG
    
     ort = " ";
    ort = ("C:/Users/tobia/Desktop/Masterarbeit_Qualitätskontrolle_Passsteinautomat/Auswertung/scheibchen/stein_A_erg_l.txt");
    file1.open(ort.c_str(), std::ios::out | std::ifstream::app);
#endif
    float grenz_y_soll = cloud_soll->points[min_max(cloud_soll, "max", "index", "y")].y;
    float start_y_soll = cloud_soll->points[min_max(cloud_soll, "min", "index", "y")].y;

    float grenz_y_mess = min_max(cloud_mess, "max","elem", "y");
    float start_y_mess = min_max(cloud_mess, "min","elem" ,"y");
    std::cout << grenz_y_mess << "  mess grenzen soll " << grenz_y_soll << std::endl;
   
    float counter_mess_y = 0;
    float count_gut_y = 0;
    float count_mangel_y = 0;
    float count_defect_y = 0;
    int counter_y = 0;
    float erg_mess_y = 0;
    float erg_soll_y = 0;
    float grenz_y = grenz_y_mess;
    if (grenz_y_soll < grenz_y_mess)
        grenz_y = grenz_y_mess;
    if (grenz_y_soll > grenz_y_mess)
        grenz_y = grenz_y_soll;

    std::vector<float> vec_mess_y;
    std::vector<float> vec_soll_y;
    std::vector<float> vec_abw_y;
#ifndef DEBUG
    pcl::visualization::PCLVisualizer viewer1_y("Matrix einteilung gut schlecht");
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_cloud_color_handler_y(cloud_mess, 0.05, 0.05, 0.05);// We add the point cloud to the viewer and pass the color handler
    viewer1_y.addCoordinateSystem(100.0, "cloud", 0);
    viewer1_y.setBackgroundColor(255, 255, 255, 0); // Setting background to a dark grey
    viewer1_y.setSize(475, 475);
    viewer1_y.setPosition(478, 507);
    viewer1_y.setWindowName("Anzeige Auswertung Breite des Steins");
#endif
  
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_soll_y(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_mess_y(new pcl::PointCloud<pcl::PointXYZ>);

    for (int i = 0; i < grenz_y / aufloesung; i++)
    {
        if (i < grenz_y_mess / aufloesung) {
            cloud_fl_mess_y = flaechen_filter(cloud_mess, (start_y_mess + aufloesung * (i)), "y", aufloesung * 2);
            if (!cloud_fl_mess_y->empty()) {
                erg_mess_y = min_max(cloud_fl_mess_y, "max", "elem", "x") - min_max(cloud_fl_mess_y, "min", "elem", "x");
            }
            else
                erg_mess_y = 0.0001;

            vec_mess_y.push_back(erg_mess_y);
        }
        else
            erg_mess_y = 0.0001;



        if (i < grenz_y_soll / aufloesung)
        {
            cloud_fl_soll_y = flaechen_filter(cloud_soll, (start_y_soll + aufloesung * (i)), "y", aufloesung * 1.5);
            erg_soll_y = min_max(cloud_fl_soll_y, "max", "elem", "x") - min_max(cloud_fl_soll_y, "min", "elem", "x");
            vec_soll_y.push_back(erg_soll_y);
        }
        else
            erg_soll_y = 0.0001;
        vec_abw_y.push_back(abs(erg_mess_y - erg_soll_y));

#ifndef DEBUG
        file1 << std::to_string(i * aufloesung) << "  " << std::to_string(erg_soll_y) << "  " << std::to_string(erg_mess_y) << std::endl;
#endif

        if (abs(erg_soll_y - erg_mess_y) > gut_b * 2)
        {
#ifndef DEBUG

            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_y(cloud_fl_mess_y, 230, 20, 20); // Red
            viewer1_y.addPointCloud(cloud_fl_mess_y, transformed_cloud_color_y, "transformed_cloudd" + std::to_string(count_defect_y));
            viewer1_y.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudd" + std::to_string(count_defect_y));
#endif
            count_defect_y++;
        }
        else if (abs(erg_soll_y - erg_mess_y) > gut_b)
        {
#ifndef DEBUG
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_y(cloud_fl_mess_y, 255, 165, 79); // gelb
            viewer1_y.addPointCloud(cloud_fl_mess_y, transformed_cloud_color_y, "transformed_cloudm" + std::to_string(count_mangel_y));
            viewer1_y.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudm" + std::to_string(count_mangel_y));
#endif
            count_mangel_y++;
        }
        else if (abs(erg_soll_y - erg_mess_y) < gut_b)
        {
#ifndef DEBUG
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_y(cloud_fl_mess_y, 0, 100, 0); // grün
            viewer1_y.addPointCloud(cloud_fl_mess_y, transformed_cloud_color_y, "transformed_cloudg" + std::to_string(count_gut_y));
            viewer1_y.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudg" + std::to_string(count_gut_y));
#endif
            count_gut_y++;
        }
        counter_y++;

    }
    std::cout << zaheler++ << std::endl;
#ifndef DEBUG
    file1.close();
#endif
 
    float erg_mess_mittel_y = mittel_wert(vec_mess_y);
    float abw_mitt_y = mittel_wert(vec_abw_y);

    double zw_ery = 0;
    int stepy = 0;
    float erg_sabw_y = 0;
    for (int i = 0; i < vec_mess_y.size(); i++) {
        if (abs(vec_mess_y[i] - erg_mess_mittel_y) < 0.7 * erg_mess_mittel_y) {
            zw_ery = zw_ery + ((abs(vec_mess_y[i] - erg_mess_mittel_y)) * (abs(vec_mess_y[i] - erg_mess_mittel_y)));
            stepy++;
            
        }
    }
    erg_sabw_y = 2 * sqrt(zw_ery / (stepy - 1));
    std::cout << zaheler++ << std::endl;

#ifndef DEBUG

    while (!viewer1.wasStopped())
    { // Display the visualiser until 'q' key is pressed
        viewer1.spinOnce();
        //Sleep(1000);
         // viewer2.close();
    }
    while (!viewer1_y.wasStopped())
    { // Display the visualiser until 'q' key is pressed
        viewer1_y.spinOnce();
        //Sleep(1000);
         // viewer2.close();
    }
#endif




    int grenz_ok = 94;

    std::cout << erg_mess_mittel_x << "    " << erg_mess_mittel_y << "    " << hoehe_mittel  << "    "<<std::endl;
    ret[3] = erg_mess_mittel_x;
    ret[4] = erg_mess_mittel_y;
    ret[5] = hoehe_mittel;

    ret[6] = abw_mitt_x;
    ret[7] = abw_mitt_y;
    ret[8] = mitt_abw_h;

    ret[11] = ((count_defect / counter) * 100);
    ret[10] = ((count_mangel / counter) * 100);
    ret[9] = ((count_gut / counter) * 100);

    ret[14] = ((count_defect_y / counter_y)) * 100;
    ret[13] = ((count_mangel_y / counter_y)) * 100;
    ret[12] = ((count_gut_y / counter_y)) * 100;

    ret[17] = ((count_defect_h / counter_h) * 100);
    ret[16] = ((count_mangel_h / counter_h) * 100);
    ret[15] = ((count_gut_h / counter_h) * 100);


    ret[18] = stand_abw_h;
    ret[19] = erg_sabw_x;
    ret[20] = erg_sabw_y;
    ret[21] = 1;

    if (((count_gut / counter) * 100) < grenz_ok) {
        ret[21] = 0;
    }
    if (((count_gut_y / counter_y)) * 100 < grenz_ok) {
        ret[21] = 0;
    }
    if (((count_gut_h / counter_h) * 100) < grenz_ok) {
        ret[21] = 0;
    }
    if (((count_defect / counter) * 100) > 100 - grenz_ok) {
        ret[21] = 0;
    }
    if (((count_defect_y / counter_y) * 100) > 100 - grenz_ok) {
        ret[21] = 0;
    }
    if (((count_defect_h / counter_h) * 100) > 100 - grenz_ok) {
        ret[21] = 0;
    }

    

return(ret);
}
void stein_position(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, std::string dat) {


    typedef struct points_txt
    {
        float x;  //mm world coordinate x
        float y;  //mm world coordinate y
        float z;  //mm world coordinate z



    }POINT_WORLD;
    points_txt TxtPoint;
    std::vector<points_txt> vec_TxtPoints;


    float grenz_h = cloud->points[min_max(cloud, "max", "index", "z")].z;

    cloud = flaechen_filter(cloud, grenz_h / 2, "z", grenz_h);

    int min_y = min_max(cloud, "min", "index", "y");
    int max_y = min_max(cloud, "max", "index", "y");

    float mitte = ((cloud->points[max_y].y - cloud->points[min_y].y) / 2);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_unten = flaechen_filter(cloud, cloud->points[min_y].y, "y", mitte);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_oben = flaechen_filter(cloud, cloud->points[min_y].y + mitte, "y", mitte);

    float oben_min_x = cloud_fl_oben->points[min_max(cloud_fl_oben, "min", "index", "x")].x;
    float unten_min_x = cloud_fl_unten->points[min_max(cloud_fl_unten, "min", "index", "x")].x;
    int index = 0;
    if (oben_min_x < unten_min_x) {// links

        index = min_max(cloud, "min", "index", "y");
        TxtPoint.x = cloud->points[index].x; TxtPoint.y = cloud->points[index].y; TxtPoint.z = cloud->points[index].z;
        vec_TxtPoints.push_back(TxtPoint);
        index = min_max(cloud, "max", "index", "x");
        TxtPoint.x = cloud->points[index].x; TxtPoint.y = cloud->points[index].y; TxtPoint.z = cloud->points[index].z;
        vec_TxtPoints.push_back(TxtPoint);
        index = min_max(cloud, "min", "index", "x");
        TxtPoint.x = cloud->points[index].x; TxtPoint.y = cloud->points[index].y; TxtPoint.z = cloud->points[index].z;
        vec_TxtPoints.push_back(TxtPoint);
        index = min_max(cloud, "max", "index", "y");
        TxtPoint.x = cloud->points[index].x; TxtPoint.y = cloud->points[index].y; TxtPoint.z = cloud->points[index].z;
        vec_TxtPoints.push_back(TxtPoint);

    }
    if (oben_min_x > unten_min_x) {//rechts
        index = min_max(cloud, "min", "index", "x");
        TxtPoint.x = cloud->points[index].x; TxtPoint.y = cloud->points[index].y; TxtPoint.z = cloud->points[index].z;
        vec_TxtPoints.push_back(TxtPoint);
        index = min_max(cloud, "min", "index", "y");
        TxtPoint.x = cloud->points[index].x; TxtPoint.y = cloud->points[index].y; TxtPoint.z = cloud->points[index].z;
        vec_TxtPoints.push_back(TxtPoint);
        index = min_max(cloud, "max", "index", "y");
        TxtPoint.x = cloud->points[index].x; TxtPoint.y = cloud->points[index].y; TxtPoint.z = cloud->points[index].z;
        vec_TxtPoints.push_back(TxtPoint);
        index = min_max(cloud, "max", "index", "x");
        TxtPoint.x = cloud->points[index].x; TxtPoint.y = cloud->points[index].y; TxtPoint.z = cloud->points[index].z;
        vec_TxtPoints.push_back(TxtPoint);
    }



    std::string ort = ("C:/Users/tobia/Desktop/Masterarbeit_Qualitätskontrolle_Passsteinautomat/Point_Clouds/Positions_Daten/" + dat + "_position.txt");
    std::fstream file;
    file.open(ort.c_str(), std::ios::out);
    for (int i = 0; i < vec_TxtPoints.size(); i++) {

        file << vec_TxtPoints[i].x << "  " << vec_TxtPoints[i].y << "  " << vec_TxtPoints[i].z << std::endl;

    }
    file.close();
}