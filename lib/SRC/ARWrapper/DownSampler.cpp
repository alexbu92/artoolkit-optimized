#include <ARWrapper/DownSampler.hpp>

unsigned char* DownSampler::downSample(unsigned char* t_src, int t_height, int t_width, bool luma, int target_res_x, int target_res_y) {

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

int DownSampler::getDownX() {
	return this->downsampled_img.width;
}

int DownSampler::getDownY() {
	return this->downsampled_img.height;
}