#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>

using namespace dlib;
using namespace std;

// ----------------------------------------------------------------------------------------

// The next bit of code defines a ResNet network.  It's basically copied
// and pasted from the dnn_imagenet_ex.cpp example, except we replaced the loss
// layer with loss_metric and made the network somewhat smaller.  Go read the introductory
// dlib DNN examples to learn what all this stuff means.
//
// Also, the dnn_metric_learning_on_images_ex.cpp example shows how to train this network.
// The dlib_face_recognition_resnet_model_v1 model used by this example was trained using
// essentially the code shown in dnn_metric_learning_on_images_ex.cpp except the
// mini-batches were made larger (35x15 instead of 5x5), the iterations without progress
// was set to 10000, and the training dataset consisted of about 3 million images instead of
// 55.  Also, the input layer was locked to images of size 150.
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

int main(int argc, char** argv) try
{
    if (argc != 2)
    {
        cout << "Run this example by invoking it like this: " << endl;
        cout << "   ./FaceFeatureExtractionModule ../TestFrames/bald_guys.jpg" << endl;
        cout << endl;
        cout << "You will also need to get the face landmarking model file as well as " << endl;
        cout << "the face recognition model file.  Download and then decompress these files from: " << endl;
        cout << "http://dlib.net/files/shape_predictor_5_face_landmarks.dat.bz2" << endl;
        cout << "http://dlib.net/files/dlib_face_recognition_resnet_model_v1.dat.bz2" << endl;
        cout << endl;
        return 1;
    }

    frontal_face_detector detector = get_frontal_face_detector();
    shape_predictor sp;
    anet_type net;
    deserialize("../shape_predictor_5_face_landmarks.dat") >> sp;
    deserialize("../dlib_face_recognition_resnet_model_v1.dat") >> net;

    matrix<rgb_pixel> img;
    load_image(img, argv[1]);
    image_window win(img); 

    std::vector<matrix<rgb_pixel>> faces;
    for (auto face : detector(img))
    {
        auto shape = sp(img, face);
        matrix<rgb_pixel> face_chip;
        extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
        faces.push_back(move(face_chip));
        win.add_overlay(face);
    }

    if (faces.size() == 0)
    {
        cout << "No faces found in image!" << endl;
        return 1;
    }

    // This call asks the DNN to convert each face image in faces into a 128D vector.
    // In this 128D vector space, images from the same person will be close to each other
    // but vectors from different people will be far apart.  So we can use these vectors to
    // identify if a pair of images are from the same person or from different people.  
    std::vector<matrix<float,0,1>> face_descriptors = net(faces);

    // In particular, one simple thing we can do is face clustering.  This next bit of code
    // creates a graph of connected faces and then uses the Chinese whispers graph clustering
    // algorithm to identify how many people there are and which faces belong to whom.
    std::vector<sample_pair> edges;
    for (size_t i = 0; i < face_descriptors.size(); ++i)
    {
        for (size_t j = i; j < face_descriptors.size(); ++j)
        {
            // Faces are connected in the graph if they are close enough.  Here we check if
            // the distance between two face descriptors is less than 0.6, which is the
            // decision threshold the network was trained to use.  Although you can
            // certainly use any other threshold you find useful.
            if (length(face_descriptors[i]-face_descriptors[j]) < 0.6)
                edges.push_back(sample_pair(i,j));
        }
    }

    std::vector<unsigned long> labels;
    const auto num_clusters = chinese_whispers(edges, labels);
    // This will correctly indicate that there are 4 people in the image.
    cout << "Number of people found in the image: "<< num_clusters << endl;

    // Now let's display the face clustering results on the screen.  You will see that it
    // correctly grouped all the faces. 
    std::vector<image_window> win_clusters(num_clusters);
    for (size_t cluster_id = 0; cluster_id < num_clusters; ++cluster_id)
    {
        std::vector<matrix<rgb_pixel>> temp;
        for (size_t j = 0; j < labels.size(); ++j)
        {
            if (cluster_id == labels[j])
                temp.push_back(faces[j]);
        }
        win_clusters[cluster_id].set_title("Face cluster " + cast_to_string(cluster_id));
        win_clusters[cluster_id].set_image(tile_images(temp));
    }

    // Finally, let's print one of the face descriptors to the screen.  
    cout << "Face descriptor for one face: " << trans(face_descriptors[0]) << endl;
    cout << "Hit enter to terminate" << endl;
    cin.get();
}

catch (std::exception& e)
{
    cout << e.what() << endl;
}