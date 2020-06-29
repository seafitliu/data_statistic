#ifndef _STATISTIC_SERVANT_IMP_H_
#define _STATISTIC_SERVANT_IMP_H_

#include <sys/syscall.h>
#include <unistd.h>
#include <map>
#include <string>
#include <vector>
#include "servant/Application.h"

using namespace std;
using namespace tars;


/*
 * Storage the info for how to connect a database.
 */
struct DatabaseInfo {
    std::string host;
    int32_t port;
    std::string user;
    std::string password;
    std::string db_name;
    std::string table_name;
};


/////////////////////////////////////////////////////////////////////////
class StatisticServantImp : public Servant {

public:
    /**
     * 构造函数
     */
    StatisticServantImp();

public:
    /**
     * 对象初始化
     */
    virtual void initialize();

	/**
     * 对象销毁
     */
    virtual void destroy();


    /**
     * 处理客户端的主动请求
     * @param current 
     * @param response 
     * @return int 
     */
    virtual int doRequest(TarsCurrentPtr current, vector<char>& response);

	/**
     * 解析url参数
     * @param str_url_param 
     * @param url_params_map 
     */
	void get_url_param_map(const string &str_url_param, map<string, string> &url_params_map);

	/**
     * 获取单项统计数据
     * @param duration,从现在往前多少天 
     * @param item_name要统计的项目
     */
	int get_dataset_stat_data(int duration,const vector<string> &dataset_list, string& output_json);

	/**
     * 获取单项统计数据
     * @param duration,从现在往前多少天 
     * @param item_name要统计的项目
     */
	int get_category_list_data(int duration, string& output_json);

	/**
     * 获取单项统计数据
     * @param duration,从现在往前多少天 
     * @param item_name要统计的项目
     */
	int get_dateset_list_data_by_category(int duration,const string & category, string& output_json);


private:
	DatabaseInfo	_db_info;

};

///////////////////////////////////////////////////////////////////////////////
#endif
