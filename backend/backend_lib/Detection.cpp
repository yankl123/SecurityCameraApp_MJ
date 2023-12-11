#include "Detection.h"
#include "BackendGlobalDef.h"
// Constructor to initialize the YOLOv5 model and class names.
Detection::Detection()
{
    cout << "Initializing YOLOv5 model..." << endl;

    // Load the YOLOv5 model.
    net = readNet(YOLO_PATH);

    //cout << "Loading class names from 'coco.names'..." << endl;

    // Load class names from a file (e.g., "coco.names").
    ifstream ifs("coco.names");
    string line;
    while (getline(ifs, line))
    {
        class_list.push_back(line);
    }
}

// Function to preprocess an input image for object detection.
vector<Mat> Detection::pre_process(Mat& input_image)
{
    cout << "Preprocessing input image..." << endl;

    // Convert the input image to a blob for model input.
    Mat blob;
    blobFromImage(input_image, blob, 1. / 255., Size((int)INPUT_WIDTH, (int)INPUT_HEIGHT), Scalar(), true, false);

    // Set the input blob for the model.
    net.setInput(blob);

    // Forward propagate through the model.
    vector<Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());
    //cout << "Finished preprocessing input image." << endl;
    ////cout size
    //cout << "outputs size: " << outputs.size() << endl;

    return outputs;
}

// Function to process a single detection for cars.
bool Detection::processDetection(const float* detectionData, const cv::Mat& inputImage, std::vector<Rect>& resultRects)
{
 //   //for on detectionData
 //   //cout << "detectionData size: " << sizeof(detectionData) << endl;
 //   for (int i = 0; i < 85; i++)
 //   {
	//	cout << "detectionData[" << i << "]: " << detectionData[i] << endl;
	//}
 //   //sleep
 //   std::this_thread::sleep_for(std::chrono::milliseconds(100000));

    //
    float confidence = detectionData[4];
    float carScore = detectionData[5 + 2]; // Car score is the 2nd element after confidence.

    // Calculate resizing factors based on the input image and model input size.
    double x_factor = inputImage.cols / INPUT_WIDTH;
    double y_factor = inputImage.rows / INPUT_HEIGHT;

    // Discard low-confidence detections.
    if (confidence < CONFIDENCE_THRESHOLD || carScore <= SCORE_THRESHOLD)
    {
        //cout << "Discarding low-confidence detection..." << endl;
         return false;
    }
    //cout << "confidence: " << confidence << endl;
    // Calculate bounding box coordinates.
    float xCenter = detectionData[0];
    float yCenter = detectionData[1];
    float rectWidth = detectionData[2];
    float rectHeight = detectionData[3];

    // Calculate bounding box coordinates in the original image space.
    int left = int((xCenter - 0.5 * rectWidth) * x_factor);
    int top = int((yCenter - 0.5 * rectHeight) * y_factor);
    int width = int(rectWidth * x_factor);
    int height = int(rectHeight * y_factor);

    // Ensure the bounding box is within the image boundaries.
    left = max(left, 0);
    top = max(top, 0);
    width = min(width, inputImage.cols - left);
    height = min(height, inputImage.rows - top);

    // Create and store the bounding box in the resultRects vector.
    resultRects.push_back(Rect(left, top, width, height));

    //cout << "Processed a detection and added to resultRects..." << endl;

    return true;
}

// Function to extract bounding boxes from detection outputs.
std::vector<Rect> Detection::extractBoundingBoxes(const cv::Mat& inputImage, const std::vector<Mat>& outputs)
{
    //cout << "Extracting bounding boxes from detection outputs..." << endl;

    std::vector<Rect> resultRects;

    // Resizing factor.
    double xFactor = inputImage.cols / INPUT_WIDTH;
    double yFactor = inputImage.rows / INPUT_HEIGHT;

    const float* data = (float*)outputs[0].data;

    const int dimensions = 85;
    const int rows = 25200;

    // Iterate through detections and process each one.
    for (int i = 0; i < rows; ++i)
    {
        if (processDetection(data, inputImage, resultRects))
            //cout << "Processed a detection." << endl;
        data += dimensions;

  
    }

    cout << "Finished extracting bounding boxes." << endl;

    return resultRects;
}

// Main function to post-process and obtain bounding boxes for detected objects.
std::vector<Rect> Detection::post_process_to_rects(Mat& inputImage, vector<Mat>& outputs)
{
    cout << "Performing post-processing and obtaining bounding boxes..." << endl;

    std::vector<Rect> resultRects = extractBoundingBoxes(inputImage, outputs);

    //cout << "Number of detected objects: " << resultRects.size() << endl;

    return resultRects;
}
