#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include "mynteye/api/api.h"

MYNTEYE_USE_NAMESPACE

int main(int argc, char **argv) {
auto &&api = API::Create(argc, argv);

// api->EnableStreamData(Stream::DISPARITY);
api->EnableStreamData(Stream::DISPARITY_NORMALIZED);
// api->EnableStreamData(Stream::DEPTH);


api->SetDisparityComputingMethodType(DisparityComputingMethod::SGBM);
api->SetOptionValue(Option::IR_CONTROL, 80);


api->Start(Source::VIDEO_STREAMING);

cv::namedWindow("frame");
// cv::namedWindow("disparity");
cv::namedWindow("disparity_normalized");

while (true) {
  api->WaitForStreams();

  auto &&left_data = api->GetStreamData(Stream::LEFT);
  auto &&right_data = api->GetStreamData(Stream::RIGHT);

  cv::Mat img;
  cv::hconcat(left_data.frame, right_data.frame, img);
  cv::imshow("frame", img);

//   auto &&disp_data = api->GetStreamData(Stream::DISPARITY);
//   if (!disp_data.frame.empty()) {
//     cv::imshow("disparity", disp_data.frame);
//   }

  auto &&disp_norm_data = api->GetStreamData(Stream::DISPARITY_NORMALIZED);
  // auto &&disp_norm_data = api->GetStreamData(Stream::DISPARITY);
  // auto &&disp_norm_data = api->GetStreamData(Stream::DEPTH);

  if (!disp_norm_data.frame.empty()) {
    // std::cout<<disp_norm_data.frame.type()<<std::endl;
    cv::imshow("disparity_normalized", disp_norm_data.frame);  // CV_8UC1
    double min, max;
    cv::minMaxLoc(disp_norm_data.frame, &min, &max);
    std::cout<<min<<' '<<max<<std::endl;
  }
  

  char key = static_cast<char>(cv::waitKey(1));
  if (key == 27 || key == 'q' || key == 'Q') {  // ESC/Q
    break;
  }
}

api->Stop(Source::VIDEO_STREAMING);
    return 0;
}
