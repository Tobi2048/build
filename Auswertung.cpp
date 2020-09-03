//#define ausw


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
   
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_soll = cloud_solll;
    float gut_l = üb_ab[0], gut_b = üb_ab[1], gut_h = üb_ab[2];
    std::vector<double> ret(24);


    float erg_soll_h = cloud_soll->points[min_max(cloud_soll, "max", "index", "z")].z;

    float count_gut_h = 0;
    float count_mangel_h = 0;
    float count_defect_h = 0;
    int counter_h = 0;
    std::vector<float> vec_h;
    std::vector<float> vec_h_mitt;
    float hoehe_mittel = 0;
    for (int i = 0; i < cloud->points.size(); i++)
    {

        if (erg_soll_h == 0) {
            erg_soll_h = 0.001;
        }


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
    

    hoehe_mittel = mittel_wert(vec_h_mitt);

    double v = 0;
    float mitt_abw_h = mittel_wert(vec_h);
    for (int i = 0; i < vec_h.size(); i++) {
        v = v + ((vec_h[i] - mitt_abw_h) * (vec_h[i] - mitt_abw_h));
    }
    float stand_abw_h = 2 * sqrt(v / (vec_h.size() - 1));
    // std::cout << " Soll =" << erg_soll_h << "  ´gemessener mittelwert =" << hoehe_mittel << "   die abweichung ist=" << mitt_abw_h << "   dessen stand.abw ist =" << stand_abw_h << std::endl;
    std::cout << " höhe fertig" << std::endl;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess = flaechen_filter(cloud, hoehe_mittel - (gut_h / 2), "z", gut_h * 1.2);
   
    //------------------------------------------------------------------------------------------------------------------------------------------auswertung der Breite _________________------------------------------------------
#ifdef DEBUG
    std::fstream file1;
    std::string ort = " ";
    ort = ("C:/Users/tobia/Desktop/Masterarbeit_Qualitätskontrolle_Passsteinautomat/Auswertung/scheibchen/stein_A_erg_b.txt");
    file1.open(ort.c_str(), std::ios::out | std::ifstream::app);
#endif
   
    float grenz_x_soll = cloud_soll->points[min_max(cloud_soll, "max", "index", "x")].x;
    float start_x_soll = cloud_soll->points[min_max(cloud_soll, "min", "index", "x")].x;
    float grenz_x_mess_alt = cloud_mess->points[min_max(cloud_mess, "max", "index", "x")].x;
    float grenz_x_mess = min_max_cloud(cloud_mess, "max", "x");
    float start_x_mess = min_max_cloud(cloud_mess, "min", "x");
    std::cout <<grenz_x_mess_alt<<"alt   neu" <<grenz_x_mess << "  mess grenzen soll " << grenz_x_soll << std::endl;
    std::cout <<start_x_mess << "  mess grenzen soll " << start_x_soll << std::endl;
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



    for (int i = 0; i <= grenz_x_mess / aufloesung; i++)
    {
        cloud_fl_mess = flaechen_filter(cloud_mess, (start_x_mess + aufloesung * (i)), "x", aufloesung * 2);
        if (!cloud_fl_mess->empty()) {
            erg_mess = min_max_cloud(cloud_fl_mess, "max", "y") - min_max_cloud(cloud_fl_mess, "min", "y");
        }
        else
            erg_mess = 0.0001;

        vec_mess_x.push_back(erg_mess);
    }
    float erg_mess_mittel_x = mittel_wert(vec_mess_x);

    for (int i = 0; i <= grenz_x_soll / aufloesung; i++)
    {
        cloud_fl_soll = flaechen_filter(cloud_soll, (start_x_soll + aufloesung * (i)), "x", aufloesung * 1.5);
        erg_soll = cloud_fl_soll->points[min_max(cloud_fl_soll, "max", "index", "y")].y - cloud_fl_soll->points[min_max(cloud_fl_soll, "min", "index", "y")].y;
        vec_soll_x.push_back(erg_soll);
    }

    std::cout << vec_mess_x.size() << "    " << vec_soll_x.size() << std::endl;
    int leg = 0;
    if (vec_soll_x.size() < vec_mess_x.size()) {
        leg = vec_mess_x.size() - vec_soll_x.size();

        for (int i = 0; i < leg; i++) {
            vec_soll_x.push_back(0.0001);
        }
    }
    if (vec_soll_x.size() > vec_mess_x.size()) {
        leg = vec_mess_x.size() - vec_soll_x.size();
        for (int i = 0; i < leg; i++) {
            vec_mess_x.push_back(0.0001);
        }
    }
    std::cout << vec_mess_x.size() << "    " << vec_soll_x.size() << std::endl;
    int cf = 0;
    for (int i = 0; i < vec_mess_x.size(); i++) {
        vec_abw_x.push_back(abs(vec_soll_x[i] - vec_mess_x[i]));

#ifdef DEBUG
        file1 << std::to_string(i * aufloesung) << "  " << std::to_string(vec_soll_x[i]) <<"  " << std::to_string(vec_mess_x[i]) << std::endl;
#endif
        if (abs(vec_soll_x[i] - vec_mess_x[i]) > gut_l * 2)
        {
#ifndef DEBUG
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_mess, 230, 20, 20); // Red
            viewer1.addPointCloud(cloud_fl_mess, transformed_cloud_color_, "transformed_cloudd" + std::to_string(count_defect));
            viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudd" + std::to_string(count_defect));
#endif
            count_defect++;
        }
        else if (abs(vec_soll_x[i] - vec_mess_x[i]) > gut_l)
        {
#ifndef DEBUG
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_mess, 255, 165, 79); // gelb
            viewer1.addPointCloud(cloud_fl_mess, transformed_cloud_color_, "transformed_cloudm" + std::to_string(count_mangel));
            viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudm" + std::to_string(count_mangel));
#endif
            count_mangel++;
        }
        else if (abs(vec_soll_x[i] - vec_mess_x[i]) < gut_l)
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
#ifdef DEBUG
    file1.close();
#endif
    float abw_mitt_x = mittel_wert(vec_abw_x);

    double zw_er = 0;
    int step = 0;
    float erg_sabw_x = 0;
    for (int i = 0; i < vec_abw_x.size(); i++) {
        if (abs(vec_abw_x[i] - abw_mitt_x) < 0.7 * erg_mess_mittel_x) {
            zw_er = zw_er + ((abs(vec_abw_x[i] - abw_mitt_x)) * (abs(vec_abw_x[i] - abw_mitt_x)));
            step++;
            //std::cout << "zw_er=" << zw_er << std::endl;
        }
    }
    erg_sabw_x = 2 * sqrt(zw_er / (step - 1));

  //--------------------------------------------------------------------------------------------------breite---------------------------------------------------------------------------
#ifdef DEBUG
    
     ort = " ";
    ort = ("C:/Users/tobia/Desktop/Masterarbeit_Qualitätskontrolle_Passsteinautomat/Auswertung/scheibchen/stein_A_erg_l.txt");
    file1.open(ort.c_str(), std::ios::out | std::ifstream::app);
#endif
    float grenz_y_soll = cloud_soll->points[min_max(cloud_soll, "max", "index", "y")].y;
    float start_y_soll = cloud_soll->points[min_max(cloud_soll, "min", "index", "y")].y;

    float grenz_y_mess = min_max_cloud(cloud_mess, "max", "y");
    float start_y_mess = min_max_cloud(cloud_mess, "min", "y");
    std::cout << grenz_y_mess << "  mess grenzen soll " << grenz_y_soll << std::endl;
    std::cout << start_y_mess << "  mess grenzen soll " << start_y_soll << std::endl;
    float counter_mess_y = 0;
    float count_gut_y = 0;
    float count_mangel_y = 0;
    float count_defect_y = 0;
    int counter_y = 0;
    float erg_mess_y = 0;
    float erg_soll_y = 0;

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
    float erg_messy = 0;
    float erg_solly = 0;

    for (int i = 0; i <= grenz_y_mess / aufloesung; i++)
    {
        cloud_fl_mess = flaechen_filter(cloud_mess, (start_y_mess + aufloesung * (i)), "y", aufloesung * 2);
        if (!cloud_fl_mess->empty()) {
            erg_messy = min_max_cloud(cloud_fl_mess, "max", "x") - min_max_cloud(cloud_fl_mess, "min", "x");
        }
        else
            erg_messy = 0.0001;

        vec_mess_y.push_back(erg_messy);
    }
    float erg_mess_mittel_y = mittel_wert(vec_mess_y);

    for (int i = 0; i <= grenz_y_soll / aufloesung; i++)
    {
        cloud_fl_soll = flaechen_filter(cloud_soll, (start_y_soll + aufloesung * (i)), "y", aufloesung * 1.5);
        erg_solly = cloud_fl_soll->points[min_max(cloud_fl_soll, "max", "index", "x")].x - cloud_fl_soll->points[min_max(cloud_fl_soll, "min", "index", "x")].x;
        vec_soll_y.push_back(erg_solly);
    }

    std::cout << vec_mess_y.size() << "    " << vec_soll_y.size() << std::endl;
    int legy = 0;
    if (vec_soll_y.size() < vec_mess_y.size()) {
        legy = vec_mess_y.size() - vec_soll_y.size();

        for (int i = 0; i < legy; i++) {
            vec_soll_y.push_back(0.0001);
        }
    }
    if (vec_soll_y.size() > vec_mess_y.size()) {
        legy = vec_mess_y.size() - vec_soll_y.size();
        for (int i = 0; i < legy; i++) {
            vec_mess_y.push_back(0.0001);
        }
    }
    std::cout << vec_mess_y.size() << "    " << vec_soll_y.size() << std::endl;
   
    for (int i = 0; i < vec_mess_y.size(); i++) {
        vec_abw_y.push_back(abs(vec_soll_y[i] - vec_mess_y[i]));

#ifdef DEBUG
        file1 << std::to_string(i * aufloesung) << "  " << std::to_string(vec_soll_y[i]) << "  " << std::to_string(vec_mess_y[i]) << std::endl;
#endif
        if (abs(vec_soll_y[i] - vec_mess_y[i]) > gut_b * 2)
        {
#ifndef DEBUG
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_mess, 230, 20, 20); // Red
            viewer1.addPointCloud(cloud_fl_mess, transformed_cloud_color_, "transformed_cloudd" + std::to_string(count_defect));
            viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudd" + std::to_string(count_defect));
#endif
            count_defect_y++;
        }
        else if (abs(vec_soll_y[i] - vec_mess_y[i]) > gut_b)
        {
#ifndef DEBUG
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_mess, 255, 165, 79); // gelb
            viewer1.addPointCloud(cloud_fl_mess, transformed_cloud_color_, "transformed_cloudm" + std::to_string(count_mangel));
            viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudm" + std::to_string(count_mangel));
#endif
            count_mangel_y++;
        }
        else if (abs(vec_soll_y[i] - vec_mess_y[i]) < gut_b)
        {
#ifndef DEBUG
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_mess, 0, 100, 0); // grün
            viewer1.addPointCloud(cloud_fl_mess, transformed_cloud_color_, "transformed_cloudg" + std::to_string(count_gut));
            viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudg" + std::to_string(count_gut));
#endif
            count_gut_y++;
        }
        counter_y++;

    }
#ifdef DEBUG
    file1.close();
#endif
    float abw_mitt_y = mittel_wert(vec_abw_y);

    double zw_ery = 0;
    int stepy = 0;
    float erg_sabw_y = 0;
    for (int i = 0; i < vec_abw_y.size(); i++) {
        if (abs(vec_abw_y[i] - abw_mitt_y) < 0.7 * erg_mess_mittel_y) {
            zw_ery = zw_ery + ((abs(vec_abw_y[i] - abw_mitt_y)) * (abs(vec_abw_y[i] - abw_mitt_y)));
            stepy++;
            //std::cout << "zw_er=" << zw_er << std::endl;
        }
    }
    erg_sabw_y = 2 * sqrt(zw_ery / (stepy - 1));







    int grenz_ok = 94;


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


    ret[18] = stand_abw_h=2;
    ret[19] = erg_sabw_x=3;
    ret[20] = erg_sabw_y=1;
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