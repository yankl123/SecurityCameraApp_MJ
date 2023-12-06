#include "VideoClient.h"
 
#include <iostream>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using video::VideoService;
using video::Empty;
using video::Frame;

 using namespace std;


 VideoClient:: VideoClient(const std::string& server_address  ) {
        std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
        stub_ = VideoService::NewStub(channel);

   
    }

    bool VideoClient::sendMat(const cv::Mat& mat) {
        Frame frame;
        std::vector<uchar> buffer;
        cv::imencode(".jpg", mat, buffer);
        frame.set_data(buffer.data(), buffer.size());

        Empty response;
        grpc::ClientContext context;
        grpc::Status status = stub_->SendFrame(&context, frame, &response);
        if (!status.ok()) {
            std::cerr << "Failed to send frame: " << status.error_message() << std::endl;
            return false;
        }
        return true;
    }


 
 

 

 
