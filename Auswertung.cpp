#include"Auswertung.h"
#include"Filter.h"
#include"Viewer.h"
#include"Mathe.h"
#include<numeric>
#include<vector>



std::vector<float> Auswertung(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_soll, double aufloesung,double gut)
{
    float defect = gut * 2;
    std::vector<float> ret(20) ;

    //-------------------------------------------------Berechnung der mittleren höhe und dessen Stand.abweichung
    float hoehe_m = 0;
    float erg_soll_h = cloud_soll->points[min_max(cloud_soll, "max", "index", "z")].z;
   
    float count_gut_h = 0;
    float count_mangel_h = 0;
    float count_defect_h = 0;
    int counter_h = 0;
    for (int i = 0; i <= cloud->points.size(); i++)
    {
        hoehe_m = hoehe_m + cloud->points[i].z;

        if ((abs(cloud->points[i].z - erg_soll_h) * 100) / erg_soll_h > defect)
        {
            count_defect_h++;
        }
        else if ((abs(cloud->points[i].z - erg_soll_h) * 100) / erg_soll_h > gut)
        {
            count_mangel_h++;
        }
        else if ((abs(cloud->points[i].z - erg_soll_h) * 100) / erg_soll_h < gut)
        {
            count_gut_h++;
        }
        counter_h++;
    }
    double hoehe_mittel = hoehe_m / cloud->points.size();
    float v = 0;
    for (int i = 0; i <= cloud->points.size(); i++) {
        v = v + ((cloud->points[i].z - hoehe_mittel) * (cloud->points[i].z - hoehe_mittel));
    }
    float stand_abw = sqrt(v / (cloud->points.size() - 1));


    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess = flaechen_filter(cloud, hoehe_mittel - ((hoehe_mittel * gut * 0.01) / 2), "z", hoehe_mittel * gut * 0.01);

    //------------------------------------------------Berechnung der Länge y und dessen Stand.abweichung
    float grenz_x_soll= cloud_soll->points[min_max(cloud_soll, "max", "index", "x")].x;
    float start_x_soll = cloud_soll->points[min_max(cloud_soll, "min", "index", "x")].x;

    float grenz_x_mess = cloud_mess->points[min_max(cloud_mess, "max", "index", "x")].x;
    float start_x_mess = cloud_mess->points[min_max(cloud_mess, "min", "index", "x")].x;
    float grenz_x_max = 0;

    if (grenz_x_mess > grenz_x_soll)
        grenz_x_max = grenz_x_mess;
    if (grenz_x_mess <= grenz_x_soll)
        grenz_x_max = grenz_x_soll;

    float counter_mess = 0;
    float count_gut = 0;
    float count_mangel = 0;
    float count_defect = 0;
    int counter=0;
    float erg_mess = 0;
    float erg_soll = 0;
    float erg_m_sum = 0;

    visual_app_soll(cloud_mess);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_soll(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_mess(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::visualization::PCLVisualizer viewer1("Matrix einteilung gut schlecht");
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_cloud_color_handler(cloud_mess, 0.05, 0.05, 0.05);// We add the point cloud to the viewer and pass the color handler
    viewer1.addCoordinateSystem(100.0, "cloud", 0);
    viewer1.setBackgroundColor(255, 255, 255, 0); // Setting background to a dark grey
    viewer1.setSize(475, 475);
    viewer1.setPosition(2, 507);
    viewer1.setWindowName("Anzeige Auswertung Länge des Steins");
   
    for (int i = 0; i * aufloesung < grenz_x_max; i++)
    {
        if (i * aufloesung <= grenz_x_mess-3) {
            cloud_fl_mess = flaechen_filter(cloud_mess, (start_x_mess + aufloesung * (i)), "x", aufloesung * 2);
            erg_mess = cloud_fl_mess->points[min_max(cloud_fl_mess, "max", "index", "y")].y - cloud_fl_mess->points[min_max(cloud_fl_mess, "min", "index", "y")].y;
        }
        else
            erg_mess = 0.0001;
        if (i * aufloesung <= grenz_x_soll) {

            cloud_fl_soll = flaechen_filter(cloud_soll, (start_x_soll + aufloesung * (i)), "x", aufloesung * 2);
            erg_soll = cloud_fl_soll->points[min_max(cloud_fl_soll, "max", "index", "y")].y - cloud_fl_soll->points[min_max(cloud_fl_soll, "min", "index", "y")].y;
        }
        else
            erg_soll = 0.0001;

        if ((abs(erg_mess - erg_soll) * 100) / erg_soll > defect)
        {
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_mess, 230, 20, 20); // Red
            viewer1.addPointCloud(cloud_fl_mess, transformed_cloud_color_, "transformed_cloudd" + std::to_string(count_defect));
            viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudd" + std::to_string(count_defect));
            count_defect++;
        }
        else if ((abs(erg_mess - erg_soll) * 100) / erg_soll > gut)
        {
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_mess, 255, 165, 79); // gelb
            viewer1.addPointCloud(cloud_fl_mess, transformed_cloud_color_, "transformed_cloudm" + std::to_string(count_mangel));
            viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudm" + std::to_string(count_mangel));
            count_mangel++;
        }
        else if ((abs(erg_mess - erg_soll) * 100) / erg_soll < gut)
        {
            pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_mess, 0, 100, 0); // grün
            viewer1.addPointCloud(cloud_fl_mess, transformed_cloud_color_, "transformed_cloudg" + std::to_string(count_gut));
            viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudg" + std::to_string(count_gut));
            count_gut++;
        }
        counter++;

        if (erg_mess > 0.0001) {
            erg_m_sum = erg_m_sum + erg_mess;
            counter_mess++;
        }
    }
    
    float erg_mess_mittel_x = erg_m_sum / counter_mess;
    float zw_er = 0;
    counter_mess=0;
    float erg_abw_x = 0;
    for (int i = 0; i * aufloesung < grenz_x_mess-3; i++) {
        cloud_fl_mess = flaechen_filter(cloud_mess, (start_x_mess + aufloesung * (i)), "x", aufloesung * 2);
        erg_mess = cloud_fl_mess->points[min_max(cloud_fl_mess, "max", "index", "y")].y - cloud_fl_mess->points[min_max(cloud_fl_mess, "min", "index", "y")].y;
        zw_er= zw_er+((erg_mess - erg_mess_mittel_x)*(erg_mess - erg_mess_mittel_x));
        counter_mess++;
    }
    erg_abw_x = sqrt(zw_er / (counter_mess - 1));


  
    ret[3] = erg_mess_mittel_x ;
    //ret[4] = ergb_m / (countery);
    ret[5] = hoehe_mittel;
    ret[6] = erg_abw_x ;//abw der 
   // ret[7] = ergb_abw / countery;//abw der 
    ret[8] = stand_abw;
    ret[11] = ((count_defect / counter) * 100) ;
    ret[10] = ((count_mangel / counter) * 100) ;
    ret[9] = ((count_gut / counter) * 100) ;

   // ret[14] = ((count_defecty / countery)) * 100;
   // ret[13] = ((count_mangely / countery)) * 100;
   // ret[12] = ((count_guty / countery)) * 100;

    ret[17] = ((count_defect_h / counter_h) * 100);
    ret[16] = ((count_mangel_h / counter_h) * 100);
    ret[15] = ((count_gut_h / counter_h) * 100);
    return(ret);


}