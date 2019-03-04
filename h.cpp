#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;
Mat dst, cdst, cdstP;
int thresh;
const int thresh_max = 100;
double t;
 vector<Vec4i> linesP;

void on_trackbar( int, void* )

{
  t = thresh;
 
  HoughLinesP(dst, linesP, 1, CV_PI/180, t, 50, 10 );
  imshow( "Linear Blend", cdstP );
}


int main(int argc, char** argv){

  const char* file = argv[1];
  Mat src = imread(file, 0);
  if(src.empty())
  {
    cout << "Error reading image" << file<< endl;
    return -1;
  }


  Canny(src, dst, 50, 200, 3);
  cvtColor(dst, cdst, COLOR_GRAY2BGR); // Convert to BGR
  cdstP = cdst.clone();

   // will hold the results of the detection
  namedWindow("My Window", 1);

 
  for( size_t i = 0; i < linesP.size(); i++ )
    {
        Vec4i l = linesP[i];
        line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
    }

  thresh = 0;
  char TrackbarName[50];
  createTrackbar("Brightness", "My Window", &thresh,thresh_max,on_trackbar);

  on_trackbar(thresh,0);

  imshow("source", src);
  imshow("detected lines", cdstP);
  waitKey();
  return 0;

}
