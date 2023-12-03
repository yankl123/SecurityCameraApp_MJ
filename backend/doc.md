# Project Overview

## Backend Process

- Responsible for object detection and data storage.
- Utilizes gRPC for receiving frames from the Camera process.
- Uses YOLOv5 with OpenCV's DNN module for object detection.
- Calculates average color values (R, G, B) within detected object bounding boxes.
- Stores results in an SQLite database with frame details and color averages.
- Runs on a separate thread to avoid blocking.

## Camera Process

- Captures video frames and sends them to the Backend for processing.
- Utilizes OpenCV for video capture and processing.
- Sends frames to the Backend using gRPC.
