 

### MILESTONE #1:
This milestone focuses on basic video processing and object detection tasks on a single Windows machine. The tasks include reading frames from a video, skipping similar frames, running object detection with YOLO, and calculating average color values.

### MILESTONE #2:
In this milestone, you plan to improve your project's structure and tools. You aim to switch from using Visual Studio solutions to CMake, replace CSV with SQLite3 for data storage, use a proper logging library, and integrate a simple UI using the Qt library.

### MILESTONE #3:
Milestone #3 involves implementing multithreading to separate the camera and backend parts. You need to ensure thread safety for the queue used to exchange data between threads. You plan to create your own thread-safe queue class and implement circular queue behavior. Unit tests will help validate these changes.

### MILESTONE #4:
In this milestone, you consider using gRPC for communication between the camera and backend threads. Additionally, you switch from multithreading to multiprocessing, which means the camera process will send images to the backend process via a queue.

### MILESTONE #5:
Here, you plan to expand the project's reach by running the camera process on Windows Subsystem for Linux 2 (WSL2), creating a Docker image for the camera process, and running it on WSL2 on a different computer.

### MILESTONE #6:
This milestone involves running the camera process on a Raspberry Pi (RP). You also intend to integrate an ultrasonic distance sensor to detect proximity and trigger alerts via gRPC messages.
 
