#include <opencv4/opencv2/highgui/highgui.hpp>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>

using namespace dlib;
using namespace std;

int main(int argc, char **argv)
{
    try
    {
        cv::VideoCapture cap(0, cv::CAP_V4L2);
        cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, 520);
        cap.set(cv::CAP_PROP_FPS, 30);
        cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));

        if (!cap.isOpened())
        {
            cerr << "Unable to connect to camera" << endl;
            return 1;
        }

        frontal_face_detector detector = get_frontal_face_detector();
        image_window win;

        while (!win.is_closed())
        {
            cv::Mat temp;
            if (!cap.read(temp))
                break;
            cv_image<bgr_pixel> cimg(temp);
            std::vector<rectangle> faces_detected = detector(cimg);
            win.clear_overlay();
            win.set_image(cimg);
            win.add_overlay(faces_detected, rgb_pixel(255, 0, 0));
        }
    }

    catch (exception &e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
}