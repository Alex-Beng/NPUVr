#include "hand_pose.h"

HandPose::HandPose(std::string proto_file, std::string weight_file) {
    net = readNetFromCaffe(proto_file, weight_file);
}

bool HandPose::ImageProc(cv::Mat src_frame, std::vector<cv::Point>& res_points) {
    cv::Mat void_mat;
    return this->ImageProc(src_frame, res_points, void_mat);
}

bool HandPose::ImageProc(cv::Mat src_frame, std::vector<cv::Point>& res_points, cv::Mat& res_frame) {
    res_frame = src_frame.clone();

    int frame_width = src_frame.cols;
    int frame_heigth = src_frame.rows;
    float frame_ratio = frame_width*1.0/frame_heigth;
    
    int in_height = 368;
    int in_width = int(frame_ratio*in_height);

    cv::Mat input_blob = blobFromImage(src_frame, 1.0/255, cv::Size(in_width, in_height), cv::Scalar(0,0,0), false, false);

    net.setInput(input_blob);
    cv::Mat net_output = net.forward();

    int H = net_output.size[2];
    int W = net_output.size[3];

    res_points.resize(N_POINTS);
    for (int n=0; n<N_POINTS; n++) {
        cv::Mat prob_map(H, W, CV_32F, net_output.ptr(0,n));
        cv::resize(prob_map, prob_map, cv::Size(frame_width, frame_heigth));

        cv::Point max_loc;
        double prob;
        minMaxLoc(prob_map, 0, &prob, 0, &max_loc);
        res_points[n] = max_loc;
    }

    for (int n=0; n<N_PAIRS; n++) {
        cv::Point2f part_1 = res_points[POSE_PAIRS[n][0]];
        cv::Point2f part_2 = res_points[POSE_PAIRS[n][1]];

        if (part_1.x<=0 || part_1.y<=0 || part_2.x<=0 || part_2.y<=0) {
            continue;
        }
        line(res_frame, part_1, part_2, Scalar(0,255,255), 8);
        circle(res_frame, part_1, 8, Scalar(0,0,255), -1);
        circle(res_frame, part_2, 8, Scalar(0,0,255), -1);
    }
}