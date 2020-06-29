
#ifndef __WIRELESS_BASE_LIBRARY_MYSQL_EXTEND_BATCH_INSERT_H__
#define __WIRELESS_BASE_LIBRARY_MYSQL_EXTEND_BATCH_INSERT_H__

#include "wbl_mysql.h"

namespace wbl {
struct MySqlSynRowData;
struct MySqlSynData;

/////////////////////////////////////////////////////////////////////////////////////////
// outside class 
// 
/**
 * mysql 封装类扩展-用于batch insert
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Create: 2004-11-15</p>
 * <p>LastModify: 2004-12-14</p>
 * @author  casper@tencent.com
 * @version  0.4
 * @since version 0.3
 */
class CBInsertMySql:public CMySql {
public:
	/**
	 * batch insert数据
	 * @throw mysql_execfail 执行insert错误
	 * @param data 数据集
	 * @param dupmethod 0-关键字重复时抛出异常 1-关键重复时忽略
	 */
	size_t insert(const MySqlSynData& data,const unsigned dupmethod=0)throw(mysql_execfail); 

public:
	CBInsertMySql();
	/**
	 * batch insert数据
	 * @param u mysql支持的最大包长,一般为1023K
	 */
	CBInsertMySql(unsigned u);
	/**
	 * no implementation
	 */
	CBInsertMySql(const CBInsertMySql&);// no implementation
	/**
	 * no implementation
	 */
	void operator = (const CBInsertMySql&); // no implementation
	~CBInsertMySql();
protected:
	unsigned _max_allowed_packet;
};

/**
 * 同步数据结构,用在CBInsertMySql的insert
 * <p> Description: 需要使用MySqlBasicData的org_name和Fields</p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Create: 2004-11-15</p>
 * <p>LastModify: 2004-12-14</p>
 * @author  casper@tencent.com
 * @version  0.4
 * @since version 0.3
 * @see #CBInsertMySql
 * @see #org_name
 * @see #Fields
 */
struct MySqlSynData:public MySqlBasicData {
	/**
	 * 通过[]定位一行数据
	 * @return MySqlSynRowData 一行数据
	 * @see MySqlSynRowData
	 */
	MySqlSynRowData& operator [](const size_t row);
	/**
	 * 清除数据
	 */
	void clear();

public:
	MySqlSynData();
	MySqlSynData(const MySqlSynData& right);
	void operator = (const MySqlSynData& right);
	~MySqlSynData();
protected:
	void gensynrows();
protected:
	vector <MySqlSynRowData> _synrows;
};

/////////////////////////////////////////////////////////////////////////////////////////
// inside class 
// 
/**
 * MySqlSynData数据集类中的一行,不能直接构造,由MySqlSynData的[]产生
 * @author  casper@tencent.com
 * @version  0.4
 * @since version 0.3
 */
struct MySqlSynRowData {
public:
	MySqlSynRowData(vector<string>& data,map<string,int >& s2n);
	MySqlSynRowData(const MySqlSynRowData& right);
	~MySqlSynRowData();
public:
	/**
	 * 通过["string"]定位到一列数据
	 * @throw mysql_slopover 数据集中不存在该字段
	 * @see MySqlSynData
	 */
	string& operator [](const string &s) throw(mysql_slopover);

protected:
	vector<string>* _data;
	map<string,int >* _s2n;
};


}

#endif //


