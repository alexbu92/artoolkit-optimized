#include <ARWrapper/HMRAlphaMasking.hpp>
#include <iostream>
#include <android/log.h>

#define  LOG_TAG    "someTag"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

HMRAlphaMasking::HMRAlphaMasking(int t_width, int t_height){
	this->height = t_height;
	this->width = t_width;
    this->mask = *new Mat(height, width, CV_8UC1);
	this->imageDest = *new Mat(height, width, CV_8UC4);
	this->frameCount = 0;
}

void HMRAlphaMasking::run(unsigned char* srcImage, vector<HMRPolygon> polygons){
	this->mask = cv::Scalar(0, 0, 0);
	this->polygons = polygons;
	this->image = *new Mat(height, width, CV_8UC4, srcImage);
	
    for(int pCount = 0; pCount < this->polygons.size(); pCount++){
        vector<Point> cvPolygon;
        vector<Point> cvVertices;
        for(int vCount = 0; vCount < this->polygons[pCount].getVertices().size(); vCount++){
            cvVertices.push_back(Point2f(float(this->polygons[pCount].getVertices()[vCount].getX()),float(this->polygons[pCount].getVertices()[vCount].getY())));
        }
        approxPolyDP(cvVertices, cvPolygon, 1, true);
        fillConvexPoly(this->mask, &cvPolygon[0] , cvPolygon.size(), 255, 8, 0);
    }
	this->imageDest = this->image;
	this->frameCount += 1;
}

int HMRAlphaMasking::getFrameCount() {
	return this->frameCount;
}

unsigned char* HMRAlphaMasking::downSample(unsigned char* t_src, int t_height, int t_width, bool luma, int target_res_x, int target_res_y) {
	
	Mat originalImg;
	Mat tmp;
	if (luma) {
		originalImg = Mat(t_height, t_width, CV_8UC1, t_src);
		resize(originalImg, downsampledMat_buffLuma, Size(target_res_x, target_res_y), 0, 0, INTER_NEAREST);
	}
	else {
		originalImg = Mat(t_height, t_width, CV_8UC4, t_src);
		resize(originalImg, downsampledMat_buff, Size(target_res_x, target_res_y), 0, 0, INTER_NEAREST);
	}
	this->downsampled_img.width = downsampledMat_buff.cols;
	this->downsampled_img.height = downsampledMat_buff.rows;
	if (luma) {
		this->downsampled_img.img_luma = downsampledMat_buffLuma.data;
		return downsampled_img.img_luma;
	}
	else {
		this->downsampled_img.img_buff = downsampledMat_buff.data;
		return downsampled_img.img_buff;
	}
}

int HMRAlphaMasking::getDownX() {
	return this->downsampled_img.width;
}

int HMRAlphaMasking::getDownY() {
	return this->downsampled_img.height;
}

unsigned char* HMRAlphaMasking::getRGBTextureP() {
	return this->imageDest.data;
}
unsigned char* HMRAlphaMasking::getAlphaTextureP() {
	return this->mask.data;
}

/*
Legacy area

//if (luma) {
//originalImg = Mat(t_height, t_width, CV_8UC1, t_src);
//resize(originalImg, downsampledMat_buffLuma, Size(target_res_x, target_res_y), 0, 0, INTER_NEAREST);
////downsampledMat_buffLuma = Mat(target_res_y, target_res_x, CV_8UC1);
////originalImg.copyTo(tmp);
////TODO: metti downsampled mat come pubblico e duplicalo uno per buff e uno buff luma. Questo per garantire che l'immagine resta in memoria almeno fino al ciclo dopo
////downsampledMat_buffLuma = tmp;
////Mat temp = Mat(t_height, t_width, CV_8UC4);
////cvtColor(originalImg, temp, CV_YUV2RGBA_NV21);
////originalImg = temp;
//}
//else {
//originalImg = Mat(t_height, t_width, CV_8UC4, t_src);
//resize(originalImg, downsampledMat_buff, Size(target_res_x, target_res_y), 0, 0, INTER_NEAREST);
////downsampledMat_buff = Mat(target_res_y, target_res_x, CV_8UC4);

////cvtColor(originalImg, originalImg, COLOR_BGR2RGB);

////originalImg.copyTo(tmp);

////TODO: metti downsampled mat come pubblico e duplicalo uno per buff e uno buff luma. Questo per garantire che l'immagine resta in memoria almeno fino al ciclo dopo
////downsampledMat_buff = tmp;
//	}


//if (luma) {
//		//do nothing
//			//downsampledMat_buffLuma = tmp;
//		//resize()
//			
//		//pyrdown()	
//			//pyrDown(tmp, downsampledMat_buffLuma, Size(tmp.cols / 2, tmp.rows / 2));
//			//tmp = downsampledMat_buffLuma;
//		}
//		else {
//		//do nothing
//			//downsampledMat_buff = tmp;
//		//resize()
//			
//		//pyrdown()
//			//pyrDown(tmp, downsampledMat_buff, Size(tmp.cols / 2, tmp.rows / 2));
//			//tmp = downsampledMat_buff;
//		}
*/