// ScreenCut.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <io.h> 
#include <direct.h> 
//#include "SV_Common.h"
//#include "SV_GenSur.h"
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#ifdef _DEBUG
#pragma comment(lib, "opencv_core2413d.lib")  
#pragma comment(lib, "opencv_highgui2413d.lib")  
#pragma comment(lib, "opencv_imgproc2413d.lib")  
#pragma comment(lib, "opencv_calib3d2413d.lib")  
#pragma comment(lib, "opencv_features2d2413d.lib")  
#pragma comment(lib, "opencv_ml2413d.lib")   
#pragma comment(lib, "opencv_video2413d.lib")  
#pragma comment(lib, "opencv_contrib2413d.lib") 
#pragma comment(lib, "opencv_legacy2413d.lib") 
#pragma comment(lib, "opencv_nonfree2413d.lib")
#pragma comment(lib, "opencv_objdetect2413d.lib")
#pragma comment(lib, "opencv_flann2413d.lib")
#else
#pragma comment(lib, "opencv_core2413.lib")  
#pragma comment(lib, "opencv_highgui2413.lib")  
#pragma comment(lib, "opencv_imgproc2413.lib")  
#pragma comment(lib, "opencv_calib3d2413.lib")  
#pragma comment(lib, "opencv_features2d2413.lib")  
#pragma comment(lib, "opencv_ml2413.lib")   
#pragma comment(lib, "opencv_video2413.lib")  
#pragma comment(lib, "opencv_contrib2413d.lib") 
#pragma comment(lib, "opencv_legacy2413d.lib") 
#pragma comment(lib, "opencv_nonfree2413.lib")
#pragma comment(lib, "opencv_objdetect2413.lib")
#pragma comment(lib, "opencv_flann2413.lib")
#endif


int _tmain(int argc, _TCHAR* argv[])
{
	int i, j, k;
	int nFrmNum = 0;
	int camflag = 0;
	char   path[256];
	_finddata_t c_file;
	//sprintf(path, "X:\\k\\cs-zheng\\监控视频\\temp");
	sprintf(path, "C:\\Users\\Administrator\\Desktop\\图像处理\\Video\\screentcut");
	_chdir(path);
	int	hFile = _findfirst("*.mp4", &c_file);
	CvCapture* pCapture = cvCaptureFromFile(c_file.name);
	char imgname[512];
	IplImage* src;
	int numFrames = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_COUNT);
	int tinttime = 1000;
	int intval = numFrames / tinttime;
	if (intval>100||intval<0)
	{
		intval = 25;
	}
	goto XXX;
	while (_findnext(hFile, &c_file) == 0)
	{
		if (pCapture)
		{
			cvReleaseCapture(&pCapture);
		}
		pCapture = cvCaptureFromFile(c_file.name);
		if (pCapture == NULL)
			continue;
		numFrames = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_COUNT);
		intval = numFrames / tinttime;
	XXX:
		while (src = cvQueryFrame(pCapture))
		{
			nFrmNum++;
			if (nFrmNum%intval == 0)
			{
				IplImage* image = cvCreateImage(cvSize(src->width, src->height), 8, 3);
				cvResize(src, image);
				sprintf(imgname, "e:\\HS\\%s_%d.jpg", c_file.name, nFrmNum + 1000000);
				cvSaveImage(imgname, image);
				//cvNamedWindow("", 0);
				 cvShowImage("", image);
				cvWaitKey(1);
				cvReleaseImage(&image);

			}
			char key = cvWaitKey(1);
			if (key == 27)
			{
				cvReleaseCapture(&pCapture);
				return 0;
			}
		}
		nFrmNum = 0;
		cvReleaseImage(&src);
		cvReleaseCapture(&pCapture);
	}
	//释放高斯模型参数占用内存   
	cvReleaseCapture(&pCapture);
	return 0;
}

