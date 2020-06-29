
#ifndef __WIRELESS_BASE_LIBRARY_MYSQL_EXTEND_TRAVERSAL_SEARCH_H__
#define __WIRELESS_BASE_LIBRARY_MYSQL_EXTEND_TRAVERSAL_SEARCH_H__

#include "wbl_mysql.h"

namespace wbl {

/////////////////////////////////////////////////////////////////////////////////////////
// outside class 
// 
/**
 * mysql 封装类扩展-支持大表的遍历
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Create: 2004-11-15</p>
 * <p>LastModify: 2004-12-14</p>
 * @author  casper@tencent.com
 * @version  0.4
 * @since version 0.3
 */
class CTraversalMySql:public CMySql {
public:
	/**
	 * 执行查询语句,查询完之后必须使用havedata和data将数据取完,否则该对象无法执行下一次query
	 * @throw mysql_execfail when any error happened
	 * @param sql sql语句,只支持select
	 * @see havedata
	 * @see data
	 */
	void query(const string &sql) throw (mysql_execfail);
	/**
	 * 是否还有数据,query之后判断是否有数据
	 * @return bool 有数据,返回true,无数据返回false
	 * @see query
	 * @see data
	 */
	bool havedata() const {return _pstMySqlRes!=NULL;}
	/**
	 * 取数据,取完之后会自动更新数据状态
	 * @return MySqlData 取回的数据
	 * @see query
	 * @see havedata
	 */
	MySqlData data() throw(mysql_execfail);

public:
	/**
	 * @param max 一次data最多取回的数据量
	 */
	CTraversalMySql(unsigned max=1000);
	/**
	 * no implementation
	 */
	CTraversalMySql(const CTraversalMySql&);
	/**
	 * no implementation
	 */
	void operator = (const CTraversalMySql&); 
	~CTraversalMySql();
protected:
	void CheckSQL(const string& sql);
	unsigned _max_load_once;
	MYSQL_RES * _pstMySqlRes;
};

}

#endif //


