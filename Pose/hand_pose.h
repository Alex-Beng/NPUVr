#ifndef HAND_POSE_H
#define HAND_POSE_H

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace cv::dnn;
using namespace std;

// input: img, model 
// output: points, result_img
class HandPose {
public:
    HandPose(std::string, std::string);
    // 仅需点
    bool ImageProc(cv::Mat, std::vector<cv::Point>&);
    // 需点和结果图
    bool ImageProc(cv::Mat, std::vector<cv::Point>&, cv::Mat&);
public:

private:
    const int POSE_PAIRS[20][2] =
    {
        {0,1}, {1,2}, {2,3}, {3,4},         // thumb
        {0,5}, {5,6}, {6,7}, {7,8},         // index
        {0,9}, {9,10}, {10,11}, {11,12},    // middle
        {0,13}, {13,14}, {14,15}, {15,16},  // ring
        {0,17}, {17,18}, {18,19}, {19,20}   // small
    };
    const int N_POINTS = 22;
    const int N_PAIRS = 20;
    // caffe网络
    Net net;
};


#endif