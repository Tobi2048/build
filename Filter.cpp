#include"Filter.h"


pcl::PointCloud<pcl::PointXYZ>::Ptr vox(pcl::PointCloud<pcl::PointXYZ>::Ptr cl_vox_in, float fakt) {

    pcl::PointCloud<pcl::PointXYZ>::Ptr cl_vox_out(new pcl::PointCloud<pcl::PointXYZ>);

    std::cout << " erstelle vox \n";

    // voxel grid erstellen -> Punktdichte verringern
    pcl::VoxelGrid<pcl::PointXYZ> sor;
    sor.setInputCloud(cl_vox_in);
    sor.setLeafSize(fakt, fakt, fakt);
    sor.filter(*cl_vox_out);
    std::cout << "Vox-Grid erstell faktor: " << fakt << " " << fakt << "  " << fakt << std::endl;

    std::cerr << "anzahl der Punkte nach vox  :" << cl_vox_out->points.size() << std::endl;
    return cl_vox_out;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr flaechen_filter(pcl::PointCloud<pcl::PointXYZ>::Ptr cl_fl_in, float grenzw, std::string achse, float aufloesung) {

    pcl::PointCloud<pcl::PointXYZ>::Ptr cl_fl_out(new pcl::PointCloud<pcl::PointXYZ>);
    // Flächenfilter in der 
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud(cl_fl_in);
    pass.setFilterFieldName(achse);
    pass.setFilterLimits(grenzw, grenzw + aufloesung);//Schneidet alle punkte unterhalb und oberhalb ab--------------------------------<--<--<--
    //pass.setFilterLimitsNegative (true);
    pass.filter(*cl_fl_out);
    return(cl_fl_out);
}