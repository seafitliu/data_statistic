
#ifndef __WIRELESS_BASE_LIBRARY_MYSQL_H__
#define __WIRELESS_BASE_LIBRARY_MYSQL_H__

#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include <mysql/mysql.h>

using namespace std;

namespace wbl {
struct MySqlRowData;
struct MySqlBasicData;
struct MySqlData;

/////////////////////////////////////////////////////////////////////////////////////////
// outside class 
// 
struct mysql_slopover: public logic_error { mysql_slopover(const string& s);};
struct mysql_execfail: public runtime_error { mysql_execfail(const string& s);};

/**
 * mysql ��װ��
 * ��ʹ��,�ṩ[]��ʽ��ʽ,�Զ��ͷ���Դ
 * Copyright: Copyright (c) 2004
 * Create: 2004-11-15
 * LastModify: 2004-12-14
 * @author  casper@tencent.com
 * @version  0.4
 * @since version 0.3
 */
class CMySql {
public:
	/**
	 * @throw mysql_execfail when any error happened
	 * @param host dbhost
	 * @param user �û���
	 * @param pass ����
     * @param port �˿�
     �� @param charSet �ַ���, ���Ϊ""���ʾʹ��Ĭ�ϻ�setCharSet���õ��ַ���
	 */
	void Init(const string &host,const string &user,const string &pass, unsigned short port = 3306, const string& charSet="") 
		throw(mysql_execfail);
	/**
	 * @param db ��ͬ��sql: use db
	 */
	void use(const string &db);
	/**
	 * ִ�в�ѯ���
	 * @throw mysql_execfail when any error happened
	 * @param sql sql���
	 * @return MySqlData�ṹ
	 * @see MySqlData
	 */
	MySqlData query(const string &sql) 
		throw(mysql_execfail);
	MYSQL* mysql(){return _Mysql;}
	void setCharSet(const string& cs) throw(mysql_execfail);

	std::string escape_string(const char * s, size_t length);
	std::string escape_string(const char *s) { return escape_string(s, strlen(s)); }
	std::string escape_string(const std::string& s) { return escape_string(s.data(), s.size()); }
public:
	CMySql();
	/**
	 * no implementation
	 */
	CMySql(const CMySql&);
	/**
	 * no implementation
	 */
	void operator = (const CMySql&); 
	~CMySql();

protected:
	void Connect();
	void Close();
	void Select();
protected:
	MYSQL * _Mysql;

	bool _bIsConn;
	string _dbname;
	string _host;
	string _user;
	string _pass;
    unsigned short _port;
	string _charSet;
};

/**
 * CMySql���ص����ݼ���<br>
 * @author  casper@tencent.com
 * @version  0.4
 * @since version 0.3
 */
struct MySqlData {
	/**
	 * @return update/delete/insert��Ӱ�������
	 */
	size_t affected_rows() const;
	/**
	 * @return ���ݼ�������
	 */
	size_t num_rows() const;
	/**
	 * @return ���ݼ����ֶ���
	 */
	size_t num_fields() const;
	/**
	 * @return ���ݼ��ı���(2007-01-24,��mysql�汾����,����֧�ִ˽ӿ�)
	 */
	string org_name() const;
	/**
	 * @return ���ݼ����ֶ�
	 */
	const vector<string>& Fields() const;
	/**
	 * ͨ��[]��λһ������
	 * @throw mysql_slopover row��������
	 * @return MySqlRowData һ������
	 * @see MySqlRowData
	 */
	const MySqlRowData& operator [](const size_t row) const 
		throw(mysql_slopover);

public:
	/**
	 * no implementation,����ֱ�ӹ���
	 */
	MySqlData(); 
	MySqlData(MySqlBasicData* data);
	MySqlData(const MySqlData& right);
	void operator = (const MySqlData& right);
	~MySqlData();

protected:
	MySqlBasicData* _data;
};

/////////////////////////////////////////////////////////////////////////////////////////
// inside class 
// 
/**
 * CMySql���ص����ݼ����е�һ��<br>
 * @author  casper@tencent.com
 * @version  0.4
 * @since version 0.3
 */
struct MySqlRowData {
public:
	~MySqlRowData(){}
public:
	/**
	 * ͨ��["string"]��λ��һ������
	 * @throw mysql_slopover ���ݼ��в����ڸ��ֶ�
	 * @return string ����ֵ,���ΪNULL������string("NULL")
	 * @see MySqlData
	 */
	const string& operator [](const string &s) const 
		throw(mysql_slopover);

public:
	MySqlRowData(const MySqlRowData& right);
	MySqlRowData(const vector<string>& data,map<string,int >& s2n);
	void operator=(const MySqlRowData& right);
	/**
	 * no implementation,����ֱ�ӹ���
	 */
	MySqlRowData(); 

protected:
	const vector<string>* _data;
	map<string,int >* _s2n;
};

/**
 * �ڲ�ʹ�õĽṹ,����ֱ�Ӳ���
 */
struct MySqlBasicData {
public: //don't modify these
	vector<vector<string > > _data;
	vector<string > _col;
	map<string,int > _s2n;// fields - indx
	string _org_name;
	size_t _affected_rows;

protected:
friend class MySqlData;
	vector <MySqlRowData> _rows;
	size_t _nRefCount;
	void RefAdd();
	void RefSub();

public:
	MySqlBasicData();
	MySqlBasicData(const MySqlBasicData&);// no implementation
	~MySqlBasicData(){}//{cerr << "delete " << this << endl;}

	/**
	 * ����Ӱ�������
	 */
	size_t affected_rows() const
		{return _affected_rows;}
	/**
	 * ���ؽ��������
	 */
	size_t num_rows() const 
		{return _data.size();}
	/**
	 * �����ֶ���
	 */
	size_t num_fields() const
		{return _col.size();}
	/**
	 * ���ر���
	 */
	string org_name() const
		{return _org_name;}
	/**
	 * �����ֶ�
	 */
	const vector<string>& Fields() const
		{return _col;}

	/**
	 * ���ñ���
	 */
	void org_name(const string& s) 
		{_org_name = s;}
	/**
	 * ����Ӱ������
	 */
	void affected_rows(const size_t i) 
		{_affected_rows = i;}
	/**
	 * �����ֶ�
	 * @throw mysql_slopover �ֶ����ظ�
	 */
	void Fields(const vector<string>& v) 
		throw(mysql_slopover);
	/**
	 * �������
	 */
	void clear() {_data.clear();}
	void push_back(vector<string>& v) 
		throw(mysql_slopover);
	void genrows();
};


}

#endif //

