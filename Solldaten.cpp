

#include"Solldaten.h"


pcl::PointCloud<pcl::PointXYZ>::Ptr sollstein_erstellen(float aufloesung ,std::string dat)
{//------------------------------------------------------------------------------------------solldaten eckpunkte laden---------------------------------------
	pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud(new pcl::PointCloud<pcl::PointXYZ>);

	int number_Txt;
	FILE* fp_txt;
	points_txt_soll TxtPoint;
	std::vector<points_txt_soll> vec_TxtPoints;
	std::string pfad = ("C:/Users/tobia/Desktop/Masterarbeit_Qualit�tskontrolle_Passsteinautomat/Point_Clouds/Soll_Daten/"+dat+".txt");

	fp_txt = fopen(pfad.c_str(), "r");// hier die txt datei eintragen<--------------------------------<-<-<-<-<-<-<-<-<

	if (fp_txt)//If File open, push points in Vector 
	{
		while (fscanf(fp_txt, "%lf %lf %lf", &TxtPoint.x, &TxtPoint.y, &TxtPoint.z) != EOF)
		{
			vec_TxtPoints.push_back(TxtPoint);
		}
	}
	else//wenn Datei nicht ge�ffnet wurde
		std::cout << "could not open" << std::endl;


	number_Txt = vec_TxtPoints.size();// Anzahl der xyz Punkte 

	//pcl::PointCloud<pcl::PointXYZ> cloud;// Pointcloud Datenformat  in "cloud"
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);


	// Fill in the cloud data
	float my = ((vec_TxtPoints[3].y - vec_TxtPoints[2].y) / (vec_TxtPoints[3].x - vec_TxtPoints[2].x));
	

		for (float z = vec_TxtPoints[0].z; z <= vec_TxtPoints[5].z - vec_TxtPoints[0].z; z += vec_TxtPoints[5].z - vec_TxtPoints[0].z)
		{
			for (float x = vec_TxtPoints[0].x; x <= vec_TxtPoints[1].x - vec_TxtPoints[0].x; x += aufloesung)//aufl�sung
			{
				for (float y = vec_TxtPoints[0].y; y <= (vec_TxtPoints[2].y - vec_TxtPoints[0].y)+my*x; y += aufloesung)
				{
					pcl::PointXYZ point;
					point.x = x;  point.y = y;  point.z = z;
					point_cloud->points.push_back(point);
				}
			}
			point_cloud->width = (int)point_cloud->points.size();  point_cloud->height = 1;
		}
		
		return point_cloud;

}
std::vector<float> soll_breite_txt(std::string dat)
{//------------------------------------------------------------------------------------------solldaten eckpunkte laden---------------------------------------
	pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud(new pcl::PointCloud<pcl::PointXYZ>);
	std::vector<float> soll_w(3);
	int number_Txt;
	FILE* fp_txt;
	points_txt_solll TxtPoint;
	std::vector<points_txt_solll> vec_TxtPoints;
	std::string pfad = ("C:/Users/tobia/Desktop/Masterarbeit_Qualit�tskontrolle_Passsteinautomat/Point_Clouds/Soll_Daten/" + dat + ".txt");

	fp_txt = fopen(pfad.c_str(), "r");// hier die txt datei eintragen<--------------------------------<-<-<-<-<-<-<-<-<

	if (fp_txt)//If File open, push points in Vector 
	{
		while (fscanf(fp_txt, "%lf %lf %lf", &TxtPoint.x, &TxtPoint.y, &TxtPoint.z) != EOF)
		{
			vec_TxtPoints.push_back(TxtPoint);
		}
	}
	else//wenn Datei nicht ge�ffnet wurde
		std::cout << "could not open" << std::endl;
	soll_w[0] =(( vec_TxtPoints[2].y - vec_TxtPoints[0].y)+ (vec_TxtPoints[3].y - vec_TxtPoints[1].y))/2;//l�nge links
	soll_w[3]= vec_TxtPoints[3].y - vec_TxtPoints[1].y;//l�nge rechts
	soll_w[1]= vec_TxtPoints[1].x - vec_TxtPoints[0].x;//breite
	soll_w[2]=vec_TxtPoints[4].z - vec_TxtPoints[0].z;//h�he

	return (soll_w);
}