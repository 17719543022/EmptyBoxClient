// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 LIBHTTP_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// LIBHTTP_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef WIN32
#ifdef LIBHTTP_EXPORTS
#define LIBHTTP_API __declspec(dllexport)
#else
#define LIBHTTP_API __declspec(dllimport)
#endif
#else
#define LIBHTTP_API
#endif

#include "json/value.h"

#define MAX_POSTID        100                 //post id 个数

//ERROR CODE
#define	LIBERROR_OK          0					 //成功
#define	LIBERROR_OTHER       2001                //内部错误
#define LIBERROR_PARAM       2002                //参数错误
#define	LIBERROR_RIGIST_URL            2003      //已注册url
#define LIBERROR_ID_FINISHED           2004      //ID用尽
#define LIBERROR_ID_NOTFIND            2005      //ID未找到
#define LIBERROR_JSON_EXCEPTION        2006      //json异常


#ifdef _WIN32 
#define HTTPCALLBACK __stdcall
#else
#define HTTPCALLBACK
#endif

/* 功能： POST异步回调
** 参数：
**       url,url地址
**       result,0成功,其他错误码
**       value, 返回json对象
**       userData,用户数据
** 返回值：
**       无
*/
typedef void (HTTPCALLBACK *ResponseCB)(const char* url, int result, const Json::Value& value, void* userData);

/* 功能： POST异步回调
** 参数：
**       url,url地址
**       result,0成功,其他错误码
**       json, 返回json字符串
**       jsonLen, 返回json字符串长度
**       userData,用户数据
** 返回值：
**       无
*/
typedef void (HTTPCALLBACK *ResponseCBEx)(const char* url, int result, const char* json, int jsonLen, void* userData);

#ifdef __cplusplus
extern "C"
{
#endif

	/* 功能：初始化
	** 参数：
	**      caPath ，CA证书路径，[IN]
	** 返回值：
	**      0,成功；其他，错误码
	*/
	LIBHTTP_API int LIBInit(const char* caPath);

	/* 功能：反初始化
	** 返回值：
	**      0,成功；其他，错误码
	*/
	LIBHTTP_API int LIBUnInit();

	/* 功能： 设置HTTP头
	** 参数：
	**       url,   url地址,   [IN]
	**       header,HTTP头字段,[IN]
	** 返回值：
	**       0，成功； 其他，错误码
	** 说明： 内部默认设置Content-Type 、apiId 、apiKey、timestamp、sign；如果需要请用对应名称重新设置，区分大小写。
	*/
	LIBHTTP_API int LIBSetHeader(const char* url, const Json::Value& header);

	/* 功能： 设置HTTP头
	** 参数：
	**       url,   url地址,   [IN]
	**       header,HTTP头字段json字符串,[IN]
	** 返回值：
	**       0，成功； 其他，错误码
	** 说明： 内部默认设置Content-Type 、apiId 、apiKey、timestamp、sign；如果需要请用对应名称重新设置，区分大小写。
	*/
	LIBHTTP_API int LIBSetHeaderEx(const char* url, const char* header);


	/* 功能： 移除HTTP头设置
	** 参数： 
	**      url,  url地址,   [IN]
	** 返回值：
	**      0，成功；其他，错误码
	*/
	LIBHTTP_API int LIBRemoveHeader(const char* url);

	/* 功能： 注册异步回调函数
	** 参数： 
	**      cb, 回调函数, [IN]
	**      userData, 用户数据， [IN]
	** 返回值：
	**      0，成功；其他，错误码
	*/
	LIBHTTP_API int LIBSetResponseCB(ResponseCB cb, void* userData);

	/* 功能： 注册异步回调函数
	** 参数： 
	**      cb, 回调函数, [IN]
	**      userData, 用户数据， [IN]
	** 返回值：
	**      0，成功；其他，错误码
	*/
	LIBHTTP_API int LIBSetResponseCBEx(ResponseCBEx cb, void* userData);

	/* 功能： POST异步
	** 参数： 
	**      ipAddr, ip地址, [IN]		   https://192.168.1.105:4433/security-server  
	**      apiAddr, 接口地址，[IN]	   /api/v1/face/security/manual-check
	**      body, 发送数据json对象， [IN]
	**      https, 是否使用https,[IN]
	** 返回值：
	**      0，成功；其他，错误码
	*/
	LIBHTTP_API int LIBPost(const char* ipAddr, const char* apiAddr, const Json::Value& body, bool https);

	/* 功能： POST异步
	** 参数： 
	**      ipAddr, ip地址, [IN]		   https://192.168.1.105:4433/security-server  
	**      apiAddr, 接口地址，[IN]	   /api/v1/face/security/manual-check
	**      body, 发送数据json字符串， [IN]
	**      https, 是否使用https,[IN]
	** 返回值：
	**      0，成功；其他，错误码
	*/
	LIBHTTP_API int LIBPostEx(const char* ipAddr, const char* apiAddr, const char* body, bool https);

	/* 功能： POST同步
	** 参数： 
	**      ipAddr, ip地址, [IN]		   https://192.168.1.105:4433/security-server  
	**      apiAddr, 接口地址，[IN]	   /api/v1/face/security/manual-check
	**      body, 发送数据json对象， [IN]
	**      response， 服务器返回json对象， [OUT]
	**      https, 是否使用https,[IN]
	** 返回值：
	**      0，成功；其他，错误码
	*/
	LIBHTTP_API int LIBPostSyn(const char* ipAddr, const char* apiAddr, const Json::Value& body, Json::Value& response, bool https);

	/* 功能： POST同步
	** 参数： 
	**		ipAddr, ip地址, [IN]		   https://192.168.1.105:4433/security-server  
	**      apiAddr, 接口地址，[IN]	   /api/v1/face/security/manual-check
	**      body, 发送数据json字符串， [IN]
	**      response， 服务器返回json字符串， [OUT]
	**      resLen, 服务器返回json字符串长度, [OUT]
	**      https, 是否使用https,[IN]
	** 返回值：
	**      0，成功；其他，错误码
	*/
	LIBHTTP_API int LIBPostSynEx(const char* ipAddr, const char* apiAddr, const char* body, char** response, int* resLen, bool https);

	/* 功能： MD5加密
	** 参数：
	**      src，源字符串，[IN]
	**      dst, 加密后字符串，[OUT]
	**      dstLen, 加密后字符串长度，[OUT]
	** 返回值：
	**      0，成功；其他，错误码
	*/
	LIBHTTP_API int LIBMD5Encode(const char* src, char** dst, int* dstLen);

	/* 功能：Base64编码
	** 参数：
	**      src, 源数据，[IN]
	**      len, 源数据长度,[IN]
	**      dst, base64字符串，[OUT]
	**      dstLen, 加密后字符串长度，[OUT]
	** 返回值：
	**      0，成功；其他，错误码
	*/
	LIBHTTP_API int LIBBase64Encode(const char* src, int len, char** dst, int* dstLen);

	/* 功能：Base64解码
	** 参数：
	**      src, base64数据，[IN]
	**      dst, 解码后数据,[OUT]
	**      len, 数据长度，[OUT]
	** 返回值：
	**      0，成功；其他，错误码
	*/
	LIBHTTP_API int LIBBase64Decode(const char* src, char** dst, int* len);


#ifdef __cplusplus
}
#endif