
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <opencv/cv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <ARWrapper/HMRPolygon.hpp>
#include <chrono>


using namespace std;
using namespace cv;
using namespace chrono;

struct DownSampled_img {
	unsigned char* img_buff;
	unsigned char* img_luma;
	int width;
	int height;
};

class HMRAlphaMasking {
    
    private:
		Mat downsampledMat_buff;
		Mat downsampledMat_buffLuma;
		Mat imageDest;
		Mat mask;
		Mat image;
		DownSampled_img downsampled_img;
        vector<HMRPolygon> polygons;
        int height;
        int width;
		int frameCount;
		
    public:
        HMRAlphaMasking(int t_width, int t_height);
        void run(unsigned char* srcImage, vector<HMRPolygon> polygons);
		int getFrameCount();
		unsigned char* downSample(unsigned char* t_src, int t_height, int t_width, bool luma, int target_res_x, int target_res_y);
		int getDownX();
		int getDownY();
		unsigned char* getRGBTextureP();
		unsigned char* getAlphaTextureP();
};
