#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <nlohmann/json.hpp>
#include<fstream>

using namespace std;
using namespace cv;
using json = nlohmann::json;

int main(int argc, char** argv) {

    Mat inimg,imgsrc,detectimgsrc,detectimgsrcP, detectimgsrcPgray;

    imgsrc= imread(argv[1]); // first command line argument containing full path of target image

    cvtColor(imgsrc, imgsrc, COLOR_BGR2GRAY);

    threshold(imgsrc,imgsrc,0,255,THRESH_BINARY|THRESH_OTSU); // pre-processing step using otsu thresholding

    imgsrc.copyTo(detectimgsrcP);

    ifstream fJson(argv[2]); // second command line argument which is full path of json file
    stringstream buffer;
    buffer << fJson.rdbuf();
    auto jsonfile = nlohmann::json::parse(buffer.str());

    auto minCannythresh = jsonfile["houghParameters"]["minCannythresh"];
    auto maxCannythresh = jsonfile["houghParameters"]["maxCannythresh"];
    auto cannyKernelsize = jsonfile["houghParameters"]["cannyKernelsize"];
    
    auto angleResolution1 = jsonfile["houghParameters"]["angleResolution1"];
    auto accmThreshold1 = jsonfile["houghParameters"]["accmThreshold1"];
    auto minLinelen1 = jsonfile["houghParameters"]["minLinelen1"];
    auto maxPointdist1 = jsonfile["houghParameters"]["maxPointdist1"];

    auto angleResolution2 = jsonfile["houghParameters"]["angleResolution2"];
    auto accmThreshold2 = jsonfile["houghParameters"]["accmThreshold2"];
    auto minLinelen2 = jsonfile["houghParameters"]["minLinelen2"];
    auto maxPointdist2 = jsonfile["houghParameters"]["maxPointdist2"];

    auto angleResolution3 = jsonfile["houghParameters"]["angleResolution3"];
    auto accmThreshold3 = jsonfile["houghParameters"]["accmThreshold3"];
    auto minLinelen3 = jsonfile["houghParameters"]["minLinelen3"];
    auto maxPointdist3 = jsonfile["houghParameters"]["maxPointdist3"];

    Canny(imgsrc, detectimgsrcP, minCannythresh, maxCannythresh, cannyKernelsize, true); // canny edge detection

    imshow("Edge Detection P", detectimgsrcP);
    waitKey(0);
     
    vector<Vec4i> linesP;         // will hold the results of the detection
    vector<Vec4i> linesPagain;
    vector<Vec4i> linesPagainagain;

    double t = (double)getTickCount();
    HoughLinesP(detectimgsrcP, linesP, 1, angleResolution1, accmThreshold1 ,minLinelen1, maxPointdist1); // parameters need to be calibrated for different kinds of images
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << t << endl; // time in seconds taken for HoughP to run

    for (size_t i = 0; i < linesP.size(); i++)
    {
            cout << linesP[i] << endl;
    }
    cout << linesP.size() << endl;

    cvtColor(detectimgsrcP, detectimgsrcP, COLOR_GRAY2BGR);

    // Draw the lines
    for (size_t i = 0; i < linesP.size(); i++)
    {
        Vec4i l = linesP[i];
        line(detectimgsrcP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
    }

    cvtColor(detectimgsrcP, detectimgsrcP, COLOR_BGR2GRAY);

    HoughLinesP(detectimgsrcP, linesPagain, 1, angleResolution2, accmThreshold2 ,minLinelen2, maxPointdist2); 

    cout << linesPagain.size() << endl;

    cvtColor(detectimgsrcP, detectimgsrcP, COLOR_GRAY2BGR);

    for (size_t i = 0; i < linesPagain.size(); i++)
    {
        Vec4i l = linesPagain[i];
        line(detectimgsrcP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
    }
    
    cvtColor(detectimgsrcP, detectimgsrcP, COLOR_BGR2GRAY);

    HoughLinesP(detectimgsrcP, linesPagainagain, 1, angleResolution3, accmThreshold3 ,minLinelen3, maxPointdist3); 

    cout << linesPagainagain.size() << endl;

    cvtColor(detectimgsrcP, detectimgsrcP, COLOR_GRAY2BGR);

    for (size_t i = 0; i < linesPagainagain.size(); i++)
    {
        Vec4i l = linesPagainagain[i];
        line(detectimgsrcP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, LINE_AA);
    }
    
    imshow("Final Line Detection", detectimgsrcP);
    imwrite ("otsu.png", detectimgsrcP);

    waitKey(0);	

}