// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: OpencvImage.proto

#include "OpencvImage.pb.h"
#include "OpencvImage.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace ImageTransfer {

static const char* reciveImage_method_names[] = {
  "/ImageTransfer.reciveImage/reciveImage",
};

std::unique_ptr< reciveImage::Stub> reciveImage::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< reciveImage::Stub> stub(new reciveImage::Stub(channel, options));
  return stub;
}

reciveImage::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_reciveImage_(reciveImage_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status reciveImage::Stub::reciveImage(::grpc::ClientContext* context, const ::ImageTransfer::ImageInfo& request, ::ImageTransfer::Response* response) {
  return ::grpc::internal::BlockingUnaryCall< ::ImageTransfer::ImageInfo, ::ImageTransfer::Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_reciveImage_, context, request, response);
}

void reciveImage::Stub::async::reciveImage(::grpc::ClientContext* context, const ::ImageTransfer::ImageInfo* request, ::ImageTransfer::Response* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::ImageTransfer::ImageInfo, ::ImageTransfer::Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_reciveImage_, context, request, response, std::move(f));
}

void reciveImage::Stub::async::reciveImage(::grpc::ClientContext* context, const ::ImageTransfer::ImageInfo* request, ::ImageTransfer::Response* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_reciveImage_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::ImageTransfer::Response>* reciveImage::Stub::PrepareAsyncreciveImageRaw(::grpc::ClientContext* context, const ::ImageTransfer::ImageInfo& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::ImageTransfer::Response, ::ImageTransfer::ImageInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_reciveImage_, context, request);
}

::grpc::ClientAsyncResponseReader< ::ImageTransfer::Response>* reciveImage::Stub::AsyncreciveImageRaw(::grpc::ClientContext* context, const ::ImageTransfer::ImageInfo& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncreciveImageRaw(context, request, cq);
  result->StartCall();
  return result;
}

reciveImage::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      reciveImage_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< reciveImage::Service, ::ImageTransfer::ImageInfo, ::ImageTransfer::Response, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](reciveImage::Service* service,
             ::grpc::ServerContext* ctx,
             const ::ImageTransfer::ImageInfo* req,
             ::ImageTransfer::Response* resp) {
               return service->reciveImage(ctx, req, resp);
             }, this)));
}

reciveImage::Service::~Service() {
}

::grpc::Status reciveImage::Service::reciveImage(::grpc::ServerContext* context, const ::ImageTransfer::ImageInfo* request, ::ImageTransfer::Response* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace ImageTransfer
