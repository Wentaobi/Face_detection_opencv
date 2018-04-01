#include <iostream>
#include <stdio.h>
// opencv header
#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui>
#include <opencv2/imgproc.hpp>

// namespace
using namespace std;
using namespace cv;

int main(int argc, const char* argv[]) {
    // load model
    string facePath = "fullpath/haarcascades/haarcascade_frontface_alt.xml";
    CascadeClassifier faceCascade;
    if (!faceCascade.load(facePath)){
        cout << "load failed" << endl;
        return -1;
    }
    cout << "load successfully" << endl;

    // open camera
    VideoCapture capture;
    capture.open(0);

    // monitor camera, read frame
    Mat frame;

    namedWindow("face detection");
    while   (capture.read(frame)){
        if (frame.empty()) {
            break;
        }
        // RGB2GRAY
        Mat frame_gray;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

        // CHECK FACE
        // min size
        vector<Rect> faces;
        face.detectMultiScale(frame_gray,faces,1.1,3,0, Size(100,100));

        // mark face
        for (size_t i = 0; i < faces.size(); i++){
            //different figures
            Point center(faces[i].x + faces[i].width/2,
                         faces[i].y + faces[i].height/2);

            // radius
            ellipse(frame,
                    center,
                    Size(faces[i].width/2,faces[i].height/2),
                    0,
                    0,
                    360,
                    Scalar(0,0,255),
                    5);
        }
        //display
        imshow("face detection", frame);

        // wait update
        waitKey(5);
    }

    return 0;
}