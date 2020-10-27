#include "hand_pose.h"

string protoFile = "hand/pose_deploy.prototxt";
string weightsFile = "hand/pose_iter_102000.caffemodel";

int main(int argc, char **argv) {

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
        
        // imshow("Output-Keypoints", frameCopy);
        imshow("Output-Skeleton", res_frame);
        
        char key = waitKey(1);
        if (key==27)
            break;
    }
    cap.release();

    return 0;
}
