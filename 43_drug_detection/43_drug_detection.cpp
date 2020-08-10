// 43_drug_detection.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()  //��ֵ�˲�
{
	cv::Mat frame = imread("C:/Users/lenovo/Desktop/��ͼͼƬ/002.jpg");
	cv::Mat rFrame = imread("C:/Users/lenovo/Desktop/��ͼͼƬ/002.jpg",0);

		cv::Mat hsvMat;
		cv::Mat edgeX_Mat;
		cv::Mat edgeY_Mat;
		cv::Mat edgeX_Mat_out;
		cv::Mat edgeY_Mat_out;
		cv::Mat edgeX_Y_Mat;
		cv::Mat edgeX_Y_Mat_out;
		cv::Mat g_edgeX_Y_Mat_out;
		cv::Mat close;

//		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);
		//��Ե���
		Sobel(rFrame, edgeX_Mat, CV_16SC1, 1, 0, 3);
//		convertScaleAbs(edgeX_Mat, edgeX_Mat_out);
		Sobel(rFrame, edgeY_Mat, CV_16SC1, 0, 1, 3);
//		convertScaleAbs(edgeY_Mat, edgeY_Mat_out);
		edgeX_Y_Mat = edgeX_Mat + edgeY_Mat;
		//ͼ����ǿ
		convertScaleAbs(edgeX_Y_Mat, edgeX_Y_Mat_out);
		//��ֵ��
		threshold(edgeX_Y_Mat_out, g_edgeX_Y_Mat_out, 160, 255, THRESH_BINARY);
		//������
		Mat element = getStructuringElement(MORPH_RECT, Size(20, 20), Point(-1, -1));
		morphologyEx(g_edgeX_Y_Mat_out, close, 3, element, Point(-1, -1));
		//��ͨ����
		Mat labels, stats, centroids;
		int num = cv::connectedComponentsWithStats(close, labels, stats, centroids);
		//������
		int max_i = 1;
		int32_t max_area = stats.at<int>(1, 4);	
		int i_num = num - 1;
		for (int i = 2; i <= i_num; i++)
		{
			if (stats.at<int>(i, 4) > max_area)
			{
				max_area = stats.at<int>(i, 4);
				max_i = i;
			}
		}
		//����
			cv::Rect rect;
			rect.x = stats.at<int>(max_i, 0);
			rect.y = stats.at<int>(max_i, 1);
			rect.width = stats.at<int>(max_i, 2);
			rect.height = stats.at<int>(max_i, 3);
			rectangle(frame, rect, CV_RGB(255, 0, 0), 1, 8, 0);

		cv::imshow("edgeX_Y_Mat", edgeX_Y_Mat_out);
		cv::imshow("g_edgeX_Y_Mat", g_edgeX_Y_Mat_out);
		cv::imshow("close", close);
//		cv::imshow("edgeX_Mat", edgeX_Mat_out);
//		cv::imshow("edgeY_Mat", edgeY_Mat_out);
		cv::imshow("rFrame", rFrame);
		cv::imshow("frame", frame);

		waitKey(0);

}
