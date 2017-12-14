#define USE_OPENCV_3
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/ml.hpp>
#include <string>
#include <dirent.h>

#include <cgal.h>
#include <off_screen_renderer.h>

#include <scorer.h>

#define TRAIN_RATIO 0.9
#define MODEL_1 "model1.yml"
#define MODEL_2 "model2.yml"
#define MODEL_3 "model3.yml"

using namespace cv::ml;
using namespace cv;
using namespace std;



void calculateKMeans(vector<Mat> view){
	

	vector<vector<float>> &hogSamples;
	getHog(vector<vector<float>> &hogSamples, vector<Mat> &view);


	Mat samples;
	ConvertVectortoMatrix(hogSamples,samples);


	int clusterCOunt = 5;

	Mat labels;
  	int attempts = 5;
  	Mat centers;

  	kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers );

}




void ConvertVectortoMatrix (vector<vector<float>> &hogSamples,  Mat &samples) {
	int descriptor_size = hogSamples[0].size();

	for (int i = 0; i < hogSamples.size(); i++) {
		for (int j = 0; j < descriptor_size; j++){
			samples.at<float>(i, j) = hogSamples[i][j]; 
		}
	}

}