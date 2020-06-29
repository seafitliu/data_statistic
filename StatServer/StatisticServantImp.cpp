#include "StatisticServantImp.h"
#include "wbl_mysql.h"
#include "wbl/string_utility.h"
#include "json/json.h"
#include "yaml-cpp/yaml.h"
#include "utils/common_log.h"





using namespace tars;
using namespace wbl;
namespace {
const std::string IMP_STATISTIC_CONF =  "statistic.yaml";

}


StatisticServantImp::StatisticServantImp() { 
}

int StatisticServantImp::doRequest(tars::TarsCurrentPtr current, vector<char>& response) {

	map<string, string> url_params_map;

	const vector<char> &request = current->getRequestBuffer();

	TC_HttpRequest httpRequest;
	httpRequest.decode(&request[0], request.size());

	string sUrl = httpRequest.getRequestUrl();

	if(sUrl == "/monitor/status") {
		TC_HttpResponse response;
		response.setContent("I am ok!", true);
		response.setHeader("Content-Range", "8");
		response.setStatus(200);
		response.setAbout("OK");
		response.setConnection("close");
		string strTmpBuf = response.encode();

		current->sendResponse(strTmpBuf.c_str(), strTmpBuf.size());
		current->close();

		return 0;
	}

	string output_json;
	if(sUrl == "/dataset.stat") {
		get_url_param_map(httpRequest.getRequestParam(), url_params_map);

		string dateset_name = "";
		map<string, string>::iterator it_dateset_name = url_params_map.find("dataset");
		if(it_dateset_name == url_params_map.end()) {
			output_json="dataset not input";
			goto response_point;
		}
		dateset_name = it_dateset_name->second;
		

		string display_count = "";
		map<string, string>::iterator it_display_count = url_params_map.find("display_count");
		if(it_display_count != url_params_map.end()) {
			display_count = it_display_count->second;
		}

		
		vector<string> dateset_list = TC_Common::sepstr<string>(dateset_name, ",");

		TROLLLOG << "|" << dateset_name << endl;
		get_dataset_stat_data(TC_Common::strto<int>(display_count),dateset_list, output_json);
	}else if(sUrl == "/category.list") {

		string display_count = "";
		map<string, string>::iterator it_display_count = url_params_map.find("display_count");
		if(it_display_count != url_params_map.end()) {
			display_count = it_display_count->second;
		}
		
		get_category_list_data(TC_Common::strto<int>(display_count), output_json);
	} else if(sUrl == "/dataset.list") {
		get_url_param_map(httpRequest.getRequestParam(), url_params_map);

		string item_category = "";
		map<string, string>::iterator it_category = url_params_map.find("category");
		if(it_category == url_params_map.end()) {
			output_json="category not input";
			goto response_point;
		}
		item_category = it_category->second;

		string display_count = "";
		map<string, string>::iterator it_display_count = url_params_map.find("display_count");
		if(it_display_count != url_params_map.end()) {
			display_count = it_display_count->second;
		}

		get_dateset_list_data_by_category(TC_Common::strto<int>(display_count),item_category, output_json);
	} else {
		output_json = "not valid request!";
	}

response_point:


	TC_HttpResponse http_response;
	http_response.setContent(output_json, true);
	http_response.setHeader("Content-Range", TC_Common::tostr(output_json.length()));
	http_response.setHeader("Access-Control-Allow-Origin", "*");
	http_response.setStatus(200);
	http_response.setAbout("OK");
	http_response.setConnection("close");
	string strTmpBuf = http_response.encode();

	current->sendResponse(strTmpBuf.c_str(), strTmpBuf.size());
	current->close();
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
void StatisticServantImp::initialize() {
	try{
		std::string conf_path = ServerConfig::BasePath + IMP_STATISTIC_CONF;
		YAML::Node conf = YAML::LoadFile(conf_path.c_str());

		_db_info.host = conf["data_db"]["db_host"].as<std::string>();

		_db_info.port = conf["data_db"]["db_port"].as<int32_t>();

		_db_info.db_name = conf["data_db"]["db_name"].as<std::string>();

		_db_info.user = conf["data_db"]["db_user"].as<std::string>();

		_db_info.password = conf["data_db"]["db_pass"].as<std::string>();
	} catch(exception& e) {
        ERRLOG << "got std::exception:" << e.what() << endl;
    } catch(...) {
        ERRLOG << "got unknown exception." << endl;
    }
}

void StatisticServantImp::destroy() {
	
}

void StatisticServantImp::get_url_param_map(const string &str_url_param, map<string, string> &url_params_map)
{
	url_params_map.clear();

	vector<string> v_param;
	wbl::Split(str_url_param, "&", v_param);

	for (size_t i = 0; i < v_param.size(); i++)
	{
		string::size_type index = v_param[i].find("=");
		if (index != string::npos)
		{
			string key = TC_Common::trim(v_param[i].substr(0, index), " ");
			string value = TC_Common::trim(v_param[i].substr(index + 1), " ");

			url_params_map.insert(map<string, string>::value_type(key, value));
		}
	}
}


int StatisticServantImp::get_dataset_stat_data(int duration,const vector<string> &dataset_list, string& output_json)
{
	try {

		Json::Value	root;
	
		wbl::CMySql mySQL;
	    mySQL.Init(_db_info.host, _db_info.user, _db_info.password, _db_info.port);
	    mySQL.use(_db_info.db_name);

		string dataset_name_str = "";
		for(size_t i=0;i<dataset_list.size();++i) {
			const string& dataset_name = dataset_list.at(i);
			if(dataset_name.empty()) {
				continue;
			}
			if(i > 0) {
				dataset_name_str +=",";
			}
			dataset_name_str +="'";
			dataset_name_str +=dataset_name;
			dataset_name_str +="'";
			Json::Value item_node;
			root[dataset_name] = item_node;
		}

		string sql="select axis_x,axis_y,dataset_name,category,sub_category from tb_statistic where dataset_name in(" + dataset_name_str + ");";
		wbl::MySqlData data = mySQL.query(sql);
	   
	    CACHELOG << "|sql|" << sql << "|result_size|" << data.num_rows() << endl;
		
	    if(data.num_rows() > 0) {
	        for(size_t i = 0; i < data.num_rows(); i++) {
				root[data[i]["dataset_name"]][data[i]["axis_x"]] = data[i]["axis_y"];
	        }
	    }
		
		Json::FastWriter writer;
		output_json = writer.write(root);
		return 0;
	} catch(exception& e) {
        ERRLOG << "got std::exception:" << e.what() << endl;
		output_json = "got std::exception:";
		output_json += e.what();
    } catch(...) {
        ERRLOG << "got unknown exception." << endl;
		output_json = "got unknown exception.";
    }
	return -1;
	
}

int StatisticServantImp::get_category_list_data(int duration, string& output_json)
{
	try {

		Json::Value	root;
	
		wbl::CMySql mySQL;
	    mySQL.Init(_db_info.host, _db_info.user, _db_info.password, _db_info.port);
	    mySQL.use(_db_info.db_name);

		string sql="select category from tb_statistic group by category;";
		wbl::MySqlData data = mySQL.query(sql);
	   
	    CACHELOG << "|sql|" << sql << "|result_size|" << data.num_rows() << endl;
		
	    if(data.num_rows() > 0) {
	        for(size_t i = 0; i < data.num_rows(); i++) {
				root[data[i]["category"]] = data[i]["category"];
	        }
	    }
		
		Json::FastWriter writer;
		output_json = writer.write(root);
		return 0;
	} catch(exception& e) {
        ERRLOG << "got std::exception:" << e.what() << endl;
		output_json = "got std::exception:";
		output_json += e.what();
    } catch(...) {
        ERRLOG << "got unknown exception." << endl;
		output_json = "got unknown exception.";
    }
	return -1;
}

int StatisticServantImp::get_dateset_list_data_by_category(int duration,const string & category, string& output_json)
{
	try {

		Json::Value	root;
	
		wbl::CMySql mySQL;
	    mySQL.Init(_db_info.host, _db_info.user, _db_info.password, _db_info.port);
	    mySQL.use(_db_info.db_name);

		string sql="select dataset_name from tb_statistic where category='"+category+"' group by dataset_name;";
		wbl::MySqlData data = mySQL.query(sql);
	   
	    CACHELOG << "|sql|" << sql << "|result_size|" << data.num_rows() << endl;
		
	    if(data.num_rows() > 0) {
	        for(size_t i = 0; i < data.num_rows(); i++) {
				root[data[i]["dataset_name"]] = data[i]["dataset_name"];
	        }
	    }
		
		Json::FastWriter writer;
		output_json = writer.write(root);
		return 0;
	} catch(exception& e) {
        ERRLOG << "got std::exception:" << e.what() << endl;
		output_json = "got std::exception:";
		output_json += e.what();
    } catch(...) {
        ERRLOG << "got unknown exception." << endl;
		output_json = "got unknown exception.";
    }
	return -1;
	
}


