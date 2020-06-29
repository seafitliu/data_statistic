
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
 * mysql ��װ����չ-����batch insert
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
	 * batch insert����
	 * @throw mysql_execfail ִ��insert����
	 * @param data ���ݼ�
	 * @param dupmethod 0-�ؼ����ظ�ʱ�׳��쳣 1-�ؼ��ظ�ʱ����
	 */
	size_t insert(const MySqlSynData& data,const unsigned dupmethod=0)throw(mysql_execfail); 

public:
	CBInsertMySql();
	/**
	 * batch insert����
	 * @param u mysql֧�ֵ�������,һ��Ϊ1023K
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
 * ͬ�����ݽṹ,����CBInsertMySql��insert
 * <p> Description: ��Ҫʹ��MySqlBasicData��org_name��Fields</p>
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
	 * ͨ��[]��λһ������
	 * @return MySqlSynRowData һ������
	 * @see MySqlSynRowData
	 */
	MySqlSynRowData& operator [](const size_t row);
	/**
	 * �������
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
 * MySqlSynData���ݼ����е�һ��,����ֱ�ӹ���,��MySqlSynData��[]����
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
	 * ͨ��["string"]��λ��һ������
	 * @throw mysql_slopover ���ݼ��в����ڸ��ֶ�
	 * @see MySqlSynData
	 */
	string& operator [](const string &s) throw(mysql_slopover);

protected:
	vector<string>* _data;
	map<string,int >* _s2n;
};


}

#endif //


