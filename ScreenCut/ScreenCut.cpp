// ScreenCut.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <io.h> 
#include <direct.h> 
#include <iostream>
#include <fstream>
//#include "SV_Common.h"
//#include "SV_GenSur.h"
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include "opencv2/videoio/videoio.hpp"
//#ifdef _DEBUG
//#pragma comment(lib, "opencv_core2413d.lib")  
//#pragma comment(lib, "opencv_highgui2413d.lib")  
//#pragma comment(lib, "opencv_imgproc2413d.lib")  
//#pragma comment(lib, "opencv_calib3d2413d.lib")  
//#pragma comment(lib, "opencv_features2d2413d.lib")  
//#pragma comment(lib, "opencv_ml2413d.lib")   
//#pragma comment(lib, "opencv_video2413d.lib")  
//#pragma comment(lib, "opencv_contrib2413d.lib") 
//#pragma comment(lib, "opencv_legacy2413d.lib") 
//#pragma comment(lib, "opencv_nonfree2413d.lib")
//#pragma comment(lib, "opencv_objdetect2413d.lib")
//#pragma comment(lib, "opencv_flann2413d.lib")
//#else
//#pragma comment(lib, "opencv_core2413.lib")  
//#pragma comment(lib, "opencv_highgui2413.lib")  
//#pragma comment(lib, "opencv_imgproc2413.lib")  
//#pragma comment(lib, "opencv_calib3d2413.lib")  
//#pragma comment(lib, "opencv_features2d2413.lib")  
//#pragma comment(lib, "opencv_ml2413.lib")   
//#pragma comment(lib, "opencv_video2413.lib")  
//#pragma comment(lib, "opencv_contrib2413d.lib") 
//#pragma comment(lib, "opencv_legacy2413d.lib") 
//#pragma comment(lib, "opencv_nonfree2413.lib")
//#pragma comment(lib, "opencv_objdetect2413.lib")
//#pragma comment(lib, "opencv_flann2413.lib")
//#endif


int main(int argc, const char * argv[])
{
	int i, j, k;
	int nFrmNum = 0;
	int camflag = 0;
	char   path[256];
	std::string filename;
	_finddata_t c_file;
	//sprintf(path, "X:\\k\\cs-zheng\\监控视频\\temp");
	sprintf(path, "G:\\video\\20181014\\65hongwai");
	_chdir(path);
	int	hFile = _findfirst("*.mp4", &c_file);
	cv::Mat  cur_frame;
	//CvCapture* pCapture = cvCaptureFromFile(c_file.name);
	//filename = argv[1];
	if (argc != 3)
	{
		return 0;
	}
	//sprintf(filename, (char*)argv[1]);
	std::cout << argv[1] << std::endl;
	
	filename = argv[1];
	cv::VideoCapture cap;
	cap.open(filename);
	cap >> cur_frame;
	char imgname[512];
	//IplImage* src;
	int numFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
	int tinttime = 1000;
	int intval = numFrames / tinttime;
	if (intval>100||intval<0)
	{
		intval = 25;
	}
//	goto XXX;
//	while (_findnext(hFile, &c_file) == 0)
//	{
//// 		if (pCapture)
//// 		{
//// 			cvReleaseCapture(&pCapture);
//// 		}
//		cap.open(c_file.name);
//		cap >> cur_frame;
//		//pCapture = cvCaptureFromFile(c_file.name);
//		if (cur_frame.empty())
//			continue;
//		numFrames = cap.get(CV_CAP_PROP_FRAME_COUNT); //(int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_COUNT);
//		intval = numFrames / tinttime;
//	XXX:
		while (!cur_frame.empty())
		{
			nFrmNum++;
			if (nFrmNum%intval == 0)
			{
				
				//IplImage* image =(IplImage*) &cur_frame;// cvCreateImage(cvSize(cur_frame.cols, cur_frame.rows), 8, 3);
				if (cur_frame.data == NULL)
				{
					continue;
				}
				//IplImage *image = (IplImage *)&IplImage(cur_frame);
				IplImage *image = &(IplImage)(cur_frame);
				//cvConvert(&cur_frame image);
				IplImage* src = cvCreateImage(cvSize(image->width, image->height), 8, 3);
				cvResize(image, src);

				sprintf(imgname, "%s\\%d.jpg",argv[2],  nFrmNum + 1000000);
				char cmd[256];
				sprintf(cmd, "mkdir %s", argv[2]);
				if (_access(argv[2], 0) == -1)
				{
					system(cmd);
				}
				
				
				//cv::imwrite(imgname, image);
				cvSaveImage(imgname, src);
				//cvNamedWindow("", 0);
				 cvShowImage("", src);
				cvWaitKey(1);
				//cvReleaseImage(&image);

			}
			cap >> cur_frame;
			char key = cvWaitKey(1);
			if (key == 27)
			{
				//cvReleaseCapture(&pCapture);
				return 0;
			}
		}
		nFrmNum = 0;
		//cvReleaseImage(&src);
		//cvReleaseCapture(&pCapture);
	//}
	//释放高斯模型参数占用内存   
	//cvReleaseCapture(&pCapture);
	return 0;
}

