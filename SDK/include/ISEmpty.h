#ifndef ISEmpty_H
#define ISEmpty_H

#define IS_API  __declspec(dllexport)


#if defined (__cplusplus)
extern "C" {
#endif


	///@brief
	///�����տ���ͨ�����Ժ���ز�����Ϊ��������
	///@param
	///@return
	///-1 ʧ�ܣ�0...N �ɹ�
IS_API int ISCreateEmptyChannel();

///@brief
///�����տ���ͨ�����Ժ���ز�����Ϊ��������
///@param
///@return
///-1 ʧ�ܣ�0...N �ɹ�
IS_API int ISDestroyEmptyChannel(int channel);

	///@brief
	///�տ��ж�ģ������
	///@param
	/*input*/
	///channel-������ͨ����
	///rfid-�տ��rfid
	///imgData-��Ӧ��ͼ���data����
	///imgWidth-��Ӧ��ͼ��Ŀ��
	///imgHeight-��Ӧ��ͼ��ĸ߶�
	///imgChannel-��Ӧ��ͼ���ͨ����
IS_API int ISSetBoxParam(int channel, char *rfid, char *img_template, int imgWidth, int imgHeight, int imgChannel);

	///@brief
	///�տ��ж�
	///@param
	/*input*/
	///channel-������ͨ����
	///imgData-ͼ���data����
	///imgWidth-ͼ��Ŀ��
	///imgHeight-ͼ��ĸ߶�
	///imgChannel-ͼ���ͨ����
	///rfid-��ǰͼ���rfid
	/*output*/
	///result-1�����ǿտ� -1����ǿտ� 0�������ʧ�ܻ����޷��ж�
	///@return
	///0 �ɹ������� ʧ��
IS_API int ISAnaEmptyBoxRgb(int channel, char *imgData, int imgWidth, int imgHeight, int imgChannel, char *rfid, int *result);

	///@brief
	///���ص�ǰSDK�ܹ������Ŀտ��������ͨ����
IS_API int ISGetMaxEmptyChannel();

	///@brief
	///���ص�ǰSDK  �տ�������Ϣ
IS_API const char* ISGetEmptyVersionInfo();


#if defined (__cplusplus)
}
#endif


#endif


