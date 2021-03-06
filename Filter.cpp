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
    pass.setFilterLimits(grenzw, (grenzw + aufloesung));//Schneidet alle punkte unterhalb und oberhalb ab--------------------------------<--<--<--
    //pass.setFilterLimitsNegative (true);
    pass.filter(*cl_fl_out);
    if (cl_fl_out->points.size() > 0)
        return(cl_fl_out);
    else {
        cl_fl_out->points[0] = { 0,0,0 };
        std::cout << "lade 0 0 0\n";
        return(cl_fl_out);
    }
}


pcl::PointCloud<pcl::PointXYZ>::Ptr oberflaechen_filter(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, int num, int showcloud)
{


    pcl::search::Search<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    pcl::PointCloud <pcl::Normal>::Ptr normals(new pcl::PointCloud <pcl::Normal>);
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normal_estimator;
    normal_estimator.setSearchMethod(tree);
    normal_estimator.setInputCloud(cloud);
    normal_estimator.setKSearch(50);
    normal_estimator.compute(*normals);

    pcl::IndicesPtr indices(new std::vector <int>);
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud(cloud);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(0.0, 1.0);
    pass.filter(*indices);

    pcl::RegionGrowing<pcl::PointXYZ, pcl::Normal> reg;
    reg.setMinClusterSize(2000);
    reg.setMaxClusterSize(10000000);
    reg.setSearchMethod(tree);
    reg.setNumberOfNeighbours(40);
    reg.setInputCloud(cloud);
    //reg.setIndices (indices);
    reg.setInputNormals(normals);
    reg.setSmoothnessThreshold(5.0 / 180.0 * M_PI);
    reg.setCurvatureThreshold(2.0);

    std::vector <pcl::PointIndices> clusters;
    reg.extract(clusters);

    std::cout << "Number of clusters is equal to " << clusters.size() << std::endl;
    for (int i = 0; i < clusters.size(); i++)
    {

        std::cout << i << " cluster has " << clusters[i].indices.size() << " points." << std::endl;
        std::cout << "These are the indices of the points of the initial" <<
            std::endl << "cloud that belong to the first cluster:" << std::endl;


        std::cout << std::endl;
    }
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_stein(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PCDWriter writer;
    int j = 0;
    for (std::vector<pcl::PointIndices>::const_iterator it = clusters.begin(); it != clusters.end(); ++it)
    {

        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_cluster(new pcl::PointCloud<pcl::PointXYZ>);
        for (std::vector<int>::const_iterator pit = it->indices.begin(); pit != it->indices.end(); ++pit)
            cloud_cluster->points.push_back(cloud->points[*pit]); //*
        cloud_cluster->width = cloud_cluster->points.size();
        cloud_cluster->height = 1;
        cloud_cluster->is_dense = true;

        std::cout << "PointCloud representing the Cluster: " << cloud_cluster->points.size() << " data points." << std::endl;
        std::stringstream ss;
        ss << "cloud_cluster_" << j << ".pcd";
        writer.write<pcl::PointXYZ>("C:/Users/tobia/Desktop/Masterarbeit_Qualitätskontrolle_Passsteinautomat/Point_Clouds/"+ss.str(), *cloud_cluster, false); //*
        
        if (num == j)
            cloud_stein = cloud_cluster;
        j++;
    }

    if (showcloud == 1)
    {
        pcl::PointCloud <pcl::PointXYZRGB>::Ptr colored_cloud = reg.getColoredCloud();
        pcl::visualization::CloudViewer viewer("Cluster viewer");
        viewer.showCloud(colored_cloud);

        while (!viewer.wasStopped())
        {
        }
    }
    return (cloud_stein);
}