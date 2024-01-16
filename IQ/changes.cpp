#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;



int main() {

    Mat inimg,imgsrc,detectimgsrc,detectimgsrcP, detectimgsrcPgray;

    imgsrc= imread("/home/learn/Documents/cv/practice/projects/HoughP/0002.jpeg");

    cvtColor(imgsrc, imgsrc, COLOR_BGR2GRAY);

    //cout << inimg.type() << endl;
    //cout << inimg.channels() << endl;

    threshold(imgsrc,imgsrc,0,255,THRESH_BINARY|THRESH_OTSU);

   


    //cout << imgsrc << endl;

    //imgsrc.convertTo(imgsrc, CV_8UC3);

    

    //cout << detectimgsrcP.type() << endl;

    //blur( inimg, imgsrc, Size(1,1));

    imgsrc.copyTo(detectimgsrcP);

    // Probabilistic Line Transform
    Canny(imgsrc, detectimgsrcP, 110, 220, 3, true);

    imshow("Edge Detection P", detectimgsrcP);
    waitKey(0);
     //imwrite ("/home/learn/Documents/cv/practice/projects/HoughP/hpResult2_2_600_50_30_edge.png", detectimgsrcP);	


     //waitKey(0);

    //cout << detectimgsrcP.size() << endl;
    //cout << detectimgsrcP << endl;



    vector<Vec4i> linesP;         // will hold the results of the detection
    vector<Vec4i> linesPagain;
    vector<Vec4i> linesPagainagain;



    double t = (double)getTickCount();
    HoughLinesP(detectimgsrcP, linesP, 1, CV_PI / 180, 20 ,15, 7);
    t = ((double)getTickCount() - t)/getTickFrequency();

    imshow("After HoughP and before line drawing", detectimgsrcP);
    waitKey(0);

    //imwrite ("/home/learn/Documents/cv/practice/projects/HoughP/hpResult2_180_50_20_10_After HoughP and before line drawing.png", detectimgsrcP);	

    


    cout << t << endl;
    for (size_t i = 0; i < linesP.size(); i++)
    {
            cout << linesP[i] << endl;
    }

    cout << linesP[0] << endl;

    cout << linesP.size() << endl;

    cvtColor(detectimgsrcP, detectimgsrcP, COLOR_GRAY2BGR);

    //cout << detectimgsrcP.type() << endl;
    //cout << detectimgsrcP.channels() << endl;


    // Draw the lines
    for (size_t i = 0; i < linesP.size(); i++)
    {
        Vec4i l = linesP[i];
        line(detectimgsrcP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
    }

    cvtColor(detectimgsrcP, detectimgsrcP, COLOR_BGR2GRAY);

    //imshow("Line Detection P", detectimgsrcP);
    //imwrite ("/home/learn/Documents/cv/practice/projects/HoughP/hpResult1_180_20_10_5.png", detectimgsrcP);	

    HoughLinesP(detectimgsrcP, linesPagain, 1, CV_PI / 180, 20 ,15, 7); 

    cout << linesPagain.size() << endl;


    cvtColor(detectimgsrcP, detectimgsrcP, COLOR_GRAY2BGR);


    for (size_t i = 0; i < linesPagain.size(); i++)
    {
        Vec4i l = linesPagain[i];
        line(detectimgsrcP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
    }
    
    
    // imshow("Line Detection P", detectimgsrcP);
    // imwrite ("/home/learn/Documents/cv/practice/projects/HoughP/hpResult1_180_20_10_7.png", detectimgsrcP);	

    // HOUGH P FOR THE THIRD TIME

    cvtColor(detectimgsrcP, detectimgsrcP, COLOR_BGR2GRAY);

// //     //imshow("Line Detection P", detectimgsrcP);
    

    HoughLinesP(detectimgsrcP, linesPagainagain, 1, CV_PI / 180, 20 ,15, 7); 

    cout << linesPagainagain.size() << endl;

    cvtColor(detectimgsrcP, detectimgsrcP, COLOR_GRAY2BGR);

    for (size_t i = 0; i < linesPagainagain.size(); i++)
    {
        Vec4i l = linesPagainagain[i];
        line(detectimgsrcP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0,255), 1, LINE_AA);
    }
    
    //Mat kernel = getStructuringElement(MORPH_RECT,Size(5,5),Point(-1,-1));

    // int kernelSize = 15;

    // Mat kernel = Mat::ones( kernelSize, kernelSize, CV_32F )/ (float)(kernelSize*kernelSize);
    // Mat detectimgsrcPeroded;

    // erode(detectimgsrcP,detectimgsrcPeroded,kernel,Point(-1,-1),10,0,MORPH_ERODE);

    imshow("Line Detection P after morpholgicals ops", detectimgsrcP);

    imwrite ("/home/learn/Documents/cv/practice/projects/HoughP/hpResult1_180_20_10_5.png", detectimgsrcP);	

    // ERODING AND DILATION

    // cvtColor(detectimgsrcP, detectimgsrcPgray, COLOR_BGR2GRAY);

    // int kernelSize = 3;

    // Mat kernel = Mat::ones( kernelSize, kernelSize, CV_32F )/ (float)(kernelSize*kernelSize);

    // erode(detectimgsrcPgray, detectimgsrcPgray,kernel);
    // dilate(detectimgsrcPgray, detectimgsrcPgray, kernel);

    // //cvtColor(detectimgsrcPgray, detectimgsrcP, COLOR_GRAY2BGR);

    // imshow("Line Detection P gray", detectimgsrcPgray);
    // //imwrite ("/home/learn/Documents/cv/practice/projects/HoughP/hpResult1_180_20_10_5.png", detectimgsrcP);	









//    // imshow("Line Detection P after gray conversion", detectimgsrcPgray);

//    // SOME OPERATIONS TO FIGURE OUT STUFF

//     // erode(detectimgsrcPgray, detectimgsrcPgray,Mat());
//     // dilate(detectimgsrcPgray, detectimgsrcPgray, Mat());
// adaptiveThreshold(detectimgsrcPgray, detectimgsrcPgray, 255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY_INV, 3, 4);

//     // imshow("Line Detection P after gray conversion", detectimgsrcPgray);

//     // HoughLinesP(detectimgsrcPgray, linesPgray, 2, CV_PI / 180, 25 ,20, 10); 

//     // cvtColor(detectimgsrcPgray, detectimgsrcPgray, COLOR_GRAY2BGR);

//     // for (size_t i = 0; i < linesPgray.size(); i++)
//     // {
//     //     Vec4i l = linesP[i];
//     //     line(detectimgsrcPgray, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
//     // }

  
//     // imshow("Line Detection P after second houghp", detectimgsrcPgray);


    
//     //cout << detectimgsrcP.channels() << endl;
//     //cout << detectimgsrcPgray << endl;



//     //imwrite ("/home/learn/Documents/cv/practice/projects/HoughP/pResult.png", imgsrc);	
//     //imwrite ("/home/learn/Documents/cv/practice/projects/HoughP/hpResult1_180_27_15_7.png", detectimgsrcP);	

    waitKey(0);



}