
#ifndef __WIRELESS_BASE_LIBRARY_MYSQL_EXTEND_TRAVERSAL_SEARCH_H__
#define __WIRELESS_BASE_LIBRARY_MYSQL_EXTEND_TRAVERSAL_SEARCH_H__

#include "wbl_mysql.h"

namespace wbl {

/////////////////////////////////////////////////////////////////////////////////////////
// outside class 
// 
/**
 * mysql ��װ����չ-֧�ִ��ı���
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
	 * ִ�в�ѯ���,��ѯ��֮�����ʹ��havedata��data������ȡ��,����ö����޷�ִ����һ��query
	 * @throw mysql_execfail when any error happened
	 * @param sql sql���,ֻ֧��select
	 * @see havedata
	 * @see data
	 */
	void query(const string &sql) throw (mysql_execfail);
	/**
	 * �Ƿ�������,query֮���ж��Ƿ�������
	 * @return bool ������,����true,�����ݷ���false
	 * @see query
	 * @see data
	 */
	bool havedata() const {return _pstMySqlRes!=NULL;}
	/**
	 * ȡ����,ȡ��֮����Զ���������״̬
	 * @return MySqlData ȡ�ص�����
	 * @see query
	 * @see havedata
	 */
	MySqlData data() throw(mysql_execfail);

public:
	/**
	 * @param max һ��data���ȡ�ص�������
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


