
cmake_minimum_required(VERSION 3.8)

project(image_grpc C CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/common.cmake) 

# Proto file
get_filename_component(image_grpc "video_service.proto" ABSOLUTE)
get_filename_component(image_grpc_path "${image_grpc}" PATH)

# Generated sources
set(image_proto_srcs "${CMAKE_CURRENT_SOURCE_DIR}/video_service.pb.cc")
set(image_proto_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/video_service.pb.h")
set(image_grpc_srcs "${CMAKE_CURRENT_SOURCE_DIR}/video_service.grpc.pb.cc")
set(image_grpc_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/video_service.grpc.pb.h")
add_custom_command(
      OUTPUT "${image_proto_srcs}" "${image_proto_hdrs}" "${image_grpc_srcs}" "${image_grpc_hdrs}" 
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_SOURCE_DIR}"
        --cpp_out "${CMAKE_CURRENT_SOURCE_DIR}"
        -I "${image_grpc_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${image_grpc}"
      DEPENDS "${image_grpc}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

set(SOURCES
  ${image_grpc_srcs}
  ${image_grpc_hdrs}
  ${image_proto_srcs}
  ${image_proto_hdrs}
)
# image_grpc_proto
add_library(image_grpc
  ${SOURCES}
 )

target_link_libraries(image_grpc PUBLIC
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF}
)
  

