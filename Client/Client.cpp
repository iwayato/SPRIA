#include <opencv4/opencv2/highgui/highgui.hpp>
#include <dlib/dnn.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>

using namespace dlib;
using namespace std;
using namespace cv;

// ----------------------------------------------------------------------------------------
template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N,BN,1,tag1<SUBNET>>>;

template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2,2,2,2,skip1<tag2<block<N,BN,2,tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET> 
using block  = BN<con<N,3,3,1,1,relu<BN<con<N,3,3,stride,stride,SUBNET>>>>>;

template <int N, typename SUBNET> using ares      = relu<residual<block,N,affine,SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block,N,affine,SUBNET>>;

template <typename SUBNET> using alevel0 = ares_down<256,SUBNET>;
template <typename SUBNET> using alevel1 = ares<256,ares<256,ares_down<256,SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<128,ares<128,ares_down<128,SUBNET>>>;
template <typename SUBNET> using alevel3 = ares<64,ares<64,ares<64,ares_down<64,SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<32,ares<32,ares<32,SUBNET>>>;

using anet_type = loss_metric<fc_no_bias<128,avg_pool_everything<
                            alevel0<
                            alevel1<
                            alevel2<
                            alevel3<
                            alevel4<
                            max_pool<3,3,2,2,relu<affine<con<32,7,7,2,2,
                            input_rgb_image_sized<150>
                            >>>>>>>>>>>>;
// ----------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
    try
    {
        // Load models: shape predictor, face detector and face feature extraction
        shape_predictor sp;
        anet_type net;
        frontal_face_detector detector = get_frontal_face_detector();
        deserialize("../Models/shape_predictor_5_face_landmarks.dat") >> sp;
        deserialize("../Models/dlib_face_recognition_resnet_model_v1.dat") >> net;

        VideoCapture cap(0, CAP_V4L2);

        // Resolution can be modified if needed
        cap.set(CAP_PROP_FRAME_WIDTH, 640);
        cap.set(CAP_PROP_FRAME_HEIGHT, 520);
        cap.set(CAP_PROP_FPS, 30);
        cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('M', 'J', 'P', 'G'));

        if (!cap.isOpened())
        {
            cerr << "Unable to connect to camera" << endl;
            return 1;
        }

        while (cap.isOpened())
        {
            Mat frame;
            if (!cap.read(frame))
                break;
            cv_image<bgr_pixel> cimg(frame);
            std::vector<rectangle> faces_detected = detector(cimg);
        }
    }
        
    catch (exception &e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
}