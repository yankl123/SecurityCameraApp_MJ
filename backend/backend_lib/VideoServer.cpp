
#include <iostream>
#include <queue>
#include <thread>
#include "JQueue.h"
#include <grpcpp/grpcpp.h>
#include "video_service.pb.h"
#include "video_service.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using video::VideoService;
using video::Empty;
using video::Frame;

class VideoServiceImpl final : public VideoService::Service {
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

class VideoServer {
private:
    //BackendProcessor& backendProcessor;
    std::unique_ptr<grpc::Server> server_;
    std::string server_address_;
    VideoServiceImpl service;

public:
    VideoServer(const std::string& server_address )
        : server_address_(server_address) {}

    void run() {
        grpc::ServerBuilder builder;
        builder.AddListeningPort(server_address_, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        server_ = builder.BuildAndStart();
        std::cout << "Server listening on " << server_address_ << std::endl;

        server_->Wait();
     }

    void stop() {
        if (server_) {
            server_->Shutdown();
        }
    }
};