#include "videoServer.h"

VideoServer::VideoServer(const std::string& server_address)
    : server_address_(server_address) {
    service_ = new VideoServiceImpl;
}

void VideoServer::run() {
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
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

grpc::Status VideoServer::VideoServiceImpl::SendFrame(grpc::ServerContext* context, const video::Frame* frame, video::Empty* response) {
    std::vector<uchar> buffer(frame->data().begin(), frame->data().end());
    cv::Mat img = cv::imdecode(buffer, cv::IMREAD_COLOR);
    JQueue::getInstance().push(img);
    receivedFrameCount++;
    std::cout << "Received frame #" << receivedFrameCount << std::endl;
    return grpc::Status::OK;
}

