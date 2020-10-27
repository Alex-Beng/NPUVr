// run like
// ./Pose/hand_demo /media/alex/Data/baseRelate/code/learnopencv/HandPose/hand/pose_deploy.prototxt /media/alex/Data/baseRelate/code/learnopencv/HandPose/hand/pose_iter_102000.caffemodel

#include "hand_pose.h"

string protoFile = "hand/pose_deploy.prototxt";
string weightsFile = "hand/pose_iter_102000.caffemodel";

int main(int argc, char **argv) {
    // arg parser
    cv::CommandLineParser parser(argc, argv,
        "{@arg1||}{@arg2||}");
    protoFile = samples::findFile(parser.get<std::string>(0));
    weightsFile = samples::findFile(parser.get<std::string>(1));


    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Unable to connect to camera" << endl;
        return 1;
    }

    HandPose hp(protoFile, weightsFile);

    Mat frame;
    Mat res_frame;
    double t=0;
    while(1) {
        double t = (double) cv::getTickCount();

        cap >> frame;
        std::vector<Point> res_points;
        hp.ImageProc(frame, res_points, res_frame);

        Mat frameCopy = frame.clone();

        for (auto pnt : res_points) {
            cv::circle(frameCopy, pnt, 8, cv::Scalar(0, 255, 255), -1);
        }

        imshow("Output-Keypoints", frameCopy);
        imshow("Output-Skeleton", res_frame);
        
        char key = waitKey(1);
        if (key==27)
            break;
    }
    cap.release();

    return 0;
}
