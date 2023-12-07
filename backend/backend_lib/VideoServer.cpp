#include "videoServer.h"
#include <iostream>
#include <queue>
#include "JQueue.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using video::VideoService;
using video::Empty;
using video::Frame;

class VideoServer::VideoServiceImpl final : public VideoService::Service {
    int receivedFrameCount = 0;

public:
    grpc::Status SendFrame(grpc::ServerContext* context, const Frame* frame, Empty* response) override {
        std::vector<uchar> buffer(frame->data().begin(), frame->data().end());
        cv::Mat img = cv::imdecode(buffer, cv::IMREAD_COLOR);
        JQueue::getInstance().push(img);
        receivedFrameCount++;
        std::cout << "Received frame #" << receivedFrameCount << std::endl;
        return grpc::Status::OK;
    }
};

VideoServer::VideoServer(const std::string& server_address)
    : server_address_(server_address) {
    service_ = new VideoServiceImpl;
}

void VideoServer::run() {
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
    builder.RegisterService(service_);
    server_ = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address_ << std::endl;
    server_->Wait();
}

void VideoServer::stop() {
    if (server_) {
        server_->Shutdown();
    }
}

// You can include the necessary headers for JQueue and OpenCV here.
