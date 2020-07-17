#include"Vergleicher_ist_soll.h"
#include"Filter.h"
#include"Viewer.h"
#include"Mathe.h"
#include<numeric>
#include<vector>

std::vector<float> Auswertung(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_mess, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_soll, float aufloesung)
{
    std::vector<float> ret(20) ;
    //--------------Berechnung der startwerte ------------------------------------------------------
  
    float grenzX = 0;
    float grenz_x_soll = ((cloud_soll->points[min_max(cloud_soll, "max", "index", "x")].x - cloud_soll->points[min_max(cloud_soll, "min", "index", "x")].x));
    float grenz_x = ((cloud_mess->points[min_max(cloud_mess, "max", "index", "x")].x - cloud_mess->points[min_max(cloud_mess, "min", "index", "x")].x));
    float start_mess = cloud_mess->points[min_max(cloud_mess, "min", "index", "x")].x;
    float start_soll = cloud_soll->points[min_max(cloud_soll, "min", "index", "x")].x;
    if (grenz_x > grenz_x_soll) 
        grenzX = grenz_x;
    if (grenz_x < grenz_x_soll)
        grenzX = grenz_x_soll;

  

  
    //---------------------------Berechnung h�he in scheiben von -xmin bis +xmax einteilung in gut schlecht ------------------------------------------------------
    //viewer initialisierung
    pcl::visualization::PCLVisualizer viewer1("Matrix einteilung gut schlecht");
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_cloud_color_handler(cloud_mess, 0.05, 0.05, 0.05);// We add the point cloud to the viewer and pass the color handler
    viewer1.addPointCloud(cloud_mess, source_cloud_color_handler, "original_cloud");
    viewer1.addCoordinateSystem(100.0, "cloud", 0);
    viewer1.setBackgroundColor(255, 255, 255, 0); // Setting background to a dark grey
    viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "original_cloud");
    viewer1.setSize(475, 475);
    viewer1.setPosition(2, 507);
    viewer1.setWindowName("Anzeige Auswertung L�nge des Steins");
   

    int gut = 6;
   
    int defect = 15;

    float counter = 0;
    float count_gut = 0;
    float count_mangel = 0;
    float count_defect = 0;
    float count = 1;
    float erg_mess = 0;
    float erg_soll = 0;
    float ergl_m = 0;
    float erg_abw = 0;
    for (int i = 0; i*aufloesung < grenzX ; i++)
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_a;
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl;
        if (i*aufloesung <= grenz_x) {
            
            cloud_fl = flaechen_filter(cloud_mess, (start_mess + aufloesung * (i)), "x", aufloesung);
            erg_mess = cloud_fl->points[min_max(cloud_fl, "max", "index", "y")].y - cloud_fl->points[min_max(cloud_fl, "min", "index", "y")].y;
           
        }else
        {
            erg_mess = 0.0001;
        }
        
        if (i*aufloesung <= grenz_x_soll) {
            
         cloud_fl_a = flaechen_filter(cloud_soll, (start_soll + aufloesung * (i)), "x", aufloesung);
        erg_soll = cloud_fl_a->points[min_max(cloud_fl_a, "max", "index", "y")].y - cloud_fl_a->points[min_max(cloud_fl_a, "min", "index", "y")].y;
        }else
        {
            erg_soll = 0.0001;
           
        }
       // std::cout<<counter<<"   "<< erg_mess << "=mess    soll= " << erg_soll << std::endl;
       
        ergl_m = ergl_m + erg_mess;
        erg_abw = erg_abw+(abs(erg_soll - erg_mess) / erg_soll) * 100;
 
        if (erg_soll > 0.0001) {
            if (abs(erg_mess - erg_soll) * 100 / erg_soll > defect)
            {
                pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_a, 230, 20, 20); // Red
                viewer1.addPointCloud(cloud_fl_a, transformed_cloud_color_, "transformed_cloudd" + std::to_string(count_defect));
                viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudd" + std::to_string(count_defect));
                count_defect++;
            }
            else if (abs(erg_mess - erg_soll) * 100 / erg_soll > gut)
            {
                pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_a, 255, 165, 79); // gelb
                viewer1.addPointCloud(cloud_fl_a, transformed_cloud_color_, "transformed_cloudm" + std::to_string(count_mangel));
                viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudm" + std::to_string(count_mangel));
                count_mangel++;
            }
            else if (abs(erg_mess - erg_soll) * 100 / erg_soll < gut)
            {
                pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_a, 0, 100, 0); // gr�n
                viewer1.addPointCloud(cloud_fl_a, transformed_cloud_color_, "transformed_cloudg" + std::to_string(count_gut));
                viewer1.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudg" + std::to_string(count_gut));
                count_gut++;
            }
            else {
                std::cout << "ups" << counter << std::endl;
            }
            counter++;
        }

        
        //std::cout << "  " << count_mangel << "  " << count_defect << "  " << count_gut<<std::endl;

        
    }
    
    
 
 

    std::cout << "es sind " << count_gut << "gute Rheien und" << std::endl
        << "es sind " << count_mangel << "mangelhafte Rheien und" << std::endl
        << "es sind " << count_defect << "defecte Rheien und" << std::endl;

   

    

    //---------------------------Berechnung breite in scheiben von -ymin bis +ymax einteilung in gut schlecht ------------------------------------------------------



    
    //--------------Berechnung der startwerte ------------------------------------------------------
               
    float grenzy = 0;
    float grenz_y_soll = ((cloud_soll->points[min_max(cloud_soll, "max", "index", "y")].y - cloud_soll->points[min_max(cloud_soll, "min", "index", "y")].y));
    float grenz_y = ((cloud_mess->points[min_max(cloud_mess, "max", "index", "y")].y - cloud_mess->points[min_max(cloud_mess, "min", "index", "y")].y));
    float start_messy = cloud_mess->points[min_max(cloud_mess, "min", "index", "y")].y;
    float start_solly = cloud_soll->points[min_max(cloud_soll, "min", "index", "y")].y;
   
    if (grenz_y > grenz_y_soll)
        grenzy = grenz_y;
    if (grenz_y < grenz_y_soll)
        grenzy = grenz_y_soll;
  

  
    //---------------------------Berechnung h�he in scheiben von -xmin bis +xmax einteilung in gut schlecht ------------------------------------------------------
    //viewer initialisierung
    pcl::visualization::PCLVisualizer viewer2("Matrix einteilung gut schlecht");
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_cloud_color_handler2(cloud_mess, 0.05, 0.05, 0.05);// We add the point cloud to the viewer and pass the color handler
    viewer2.addPointCloud(cloud_mess, source_cloud_color_handler2, "original_cloud");
    viewer2.addCoordinateSystem(100.0, "cloud", 0);
    viewer2.setBackgroundColor(255, 255, 255, 0); // Setting background to a dark grey
    viewer2.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "original_cloud");
    viewer2.setSize(475, 475);
    viewer2.setPosition(477, 507);
    viewer2.setWindowName("Anzeige Auswertung Breite des Steins");
     

    float countery = 0;
    float count_guty = 0;
    float count_mangely = 0;
    float count_defecty = 0;
    float county = 1;
    float erg_messy = 0;
    float erg_solly = 0;
    float ergb_m = 0;
    float ergb_abw = 0;
    for (int i = 0; i*aufloesung <= grenzy ; i++)
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl_a;
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_fl;
        if (i*aufloesung <= grenz_y) {
            cloud_fl = flaechen_filter(cloud_mess, (start_messy + aufloesung * (i)), "y", aufloesung);
             erg_messy = cloud_fl->points[min_max(cloud_fl, "max", "index", "x")].x - cloud_fl->points[min_max(cloud_fl, "min", "index", "x")].x;

        } else
        {
             erg_messy =0.0000001;
        }

            if (i*aufloesung <= grenz_y_soll) {
                cloud_fl_a = flaechen_filter(cloud_soll, (start_soll + aufloesung * (i)), "y", aufloesung);
                  erg_solly = cloud_fl_a->points[min_max(cloud_fl_a, "max", "index", "x")].x - cloud_fl_a->points[min_max(cloud_fl_a, "min", "index", "x")].x;
             }else {
                erg_solly = 0.0001;
            }


        //std::cout<<countery<<"   "<< erg_messy << "=mess    soll= " << erg_solly << std::endl;
            ergb_m = ergb_m + erg_messy;
            ergb_abw =ergb_abw+ (abs(erg_solly - erg_messy) / erg_solly) * 100;
 
        if (erg_solly > 0.001) {
            if (abs(erg_messy - erg_solly) * 100 / erg_solly > defect)
            {
                pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_a, 230, 20, 20); // Red
                viewer2.addPointCloud(cloud_fl_a, transformed_cloud_color_, "transformed_cloudd" + std::to_string(count_defecty));
                viewer2.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudd" + std::to_string(count_defecty));
                count_defecty++;
            }
            else if (abs(erg_messy - erg_solly) * 100 / erg_solly > gut)
            {
                pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_a, 255, 165, 79); // gelb
                viewer2.addPointCloud(cloud_fl_a, transformed_cloud_color_, "transformed_cloudm" + std::to_string(count_mangely));
                viewer2.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudm" + std::to_string(count_mangely));
                count_mangely++;
            }
            else if (abs(erg_messy - erg_solly) * 100 / erg_solly < gut)
            {
                pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_(cloud_fl_a, 0, 100, 0); // gr�n
                viewer2.addPointCloud(cloud_fl_a, transformed_cloud_color_, "transformed_cloudg" + std::to_string(count_guty));
                viewer2.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloudg" + std::to_string(count_guty));
                count_guty++;
            }
            else {
                std::cout << "ups" << countery << std::endl;
            }
            countery++;
        }

        
        //std::cout << "  " << count_mangel << "  " << count_defect << "  " << count_gut<<std::endl;

        //viewer.setPosition(800, 400); // Setting visualiser window position
    }
    
    ret[3] = ergl_m / (counter);
    ret[4] = ergb_m / (countery);
  //  ret[5]= ergh_m
    ret[6] = erg_abw / counter;//abw der 
    ret[7] = ergb_abw / countery;//abw der 
    //ret[8] 
    ret[11]= ((count_defect/counter))*100;
    ret[10] = ((count_mangel/counter)) *100;
    ret[9] = ((count_gut/counter))*100;

    ret[14] = ((count_defecty/countery))*100;
    ret[13] = ((count_mangely/countery))*100;
    ret[12] = ((count_guty/countery))*100;
 
    

    return(ret);
    while (!viewer1.wasStopped())
    { // Display the visualiser until 'q' key is pressed
        viewer1.spinOnce();
        // Sleep(1000);
         //viewer1.close();
    }
    while (!viewer2.wasStopped())
    { // Display the visualiser until 'q' key is pressed
        viewer2.spinOnce();
        // Sleep(1000);
         //viewer1.close();
    }
    
  
    
   
}