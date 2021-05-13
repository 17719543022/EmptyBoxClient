#ifndef ISEmpty_H
#define ISEmpty_H



#if defined (__cplusplus)
extern "C" {
#endif


	///@brief
	///创建空框检测通道，以后相关操作作为参数传入
	///@param
	///@return
	///-1 失败，0...N 成功
 int ISCreateEmptyChannel();

///@brief
///创建空框检测通道，以后相关操作作为参数传入
///@param
///@return
///-1 失败，0...N 成功
 int ISDestroyEmptyChannel(int channel);

	///@brief
	///空框判读模板设置
	///@param
	/*input*/
	///channel-创建的通道号
	///rfid-空框的rfid
	///imgData-对应框图像的data数据
	///imgWidth-对应框图像的宽度
	///imgHeight-对应框图像的高度
	///imgChannel-对应框图像的通道数
 int ISSetBoxParam(int channel, char *rfid, char *img_template, int imgWidth, int imgHeight, int imgChannel);

	///@brief
	///空框判断
	///@param
	/*input*/
	///channel-创建的通道号
	///imgData-图像的data数据
	///imgWidth-图像的宽度
	///imgHeight-图像的高度
	///imgChannel-图像的通道数
	///rfid-当前图像的rfid
	/*output*/
	///result-1代表是空框 -1代表非空框 0代表分析失败或者无法判断
	///@return
	///0 成功，其他 失败
 int ISAnaEmptyBoxRgb(int channel, char *imgData, int imgWidth, int imgHeight, int imgChannel, char *rfid, int *result);

	///@brief
	///返回当前SDK能够创建的空框检测器最大通道数
 int ISGetMaxEmptyChannel();

	///@brief
	///返回当前SDK  空框检测器信息
 const char* ISGetEmptyVersionInfo();


#if defined (__cplusplus)
}
#endif


#endif


