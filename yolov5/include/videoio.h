#include "im2d.h"
#include "RgaUtils.h"
#include "rga.h"

#include "main.h"
#include "opencv2/videoio/videoio_c.h"
using namespace std;

extern vector<cv::Mat> imagePool;
extern mutex mtxQueueInput;
extern queue<input_image> queueInput;  // input queue client
extern mutex mtxqueueDetOut;
extern queue<imageout_idx> queueDetOut;        // Det output queue
extern mutex mtxQueueOutput;
extern queue<Mat> queueOutput;  // 目标追踪输出队列

extern bool add_head;
extern bool bReading;      // flag of input
extern bool bDetecting;    // 目标检测进程状态
extern int idxInputImage;  // image index of input video

extern video_property video_probs; // 视频属性类

/*
	图像预处理 
	img——原图像      _img——缩放后的图像
	resize：  		缩放图像
	get_max_scale： 获取最大缩放比例
*/
class preprocess
{
public:
    preprocess();
    int input_height;
    int input_width;
    int input_channel;
    // init rga context
    rga_buffer_t src;
    rga_buffer_t dst;
    im_rect src_rect;
    im_rect dst_rect;

	void resize(cv::Mat &img, cv::Mat &_img);
};


void videoRead(const char* video_name, int cpuid);
void videoResize(int cpuid);
vector<float> get_max_scale(int input_width, int input_height, int net_width, int net_height);
void videoWrite(const char* save_path,int cpuid) ;
int draw_image(cv::Mat& img, detect_result_group_t detect_result_group);