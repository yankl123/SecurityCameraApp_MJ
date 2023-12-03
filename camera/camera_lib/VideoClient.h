#pragma once

#include <grpcpp/grpcpp.h>
#include "video_service.grpc.pb.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using video::VideoService;
using video::Empty;
using video::Frame;

using namespace std;

class VideoClient {
public:
    VideoClient(const std::string& server_address );
    bool sendMat(const cv::Mat& mat);

private:
    std::unique_ptr<VideoService::Stub> stub_;
    cv::VideoCapture capture;
};
