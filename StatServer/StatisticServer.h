#ifndef _STATISTIC_SERVER_H_
#define _STATISTIC_SERVER_H_

#include <iostream>
#include "util/tc_http.h"
#include "util/tc_cgi.h"
#include "servant/Application.h"

using namespace tars;

class StatisticServer: public Application {
public:
	/**
	 * ��������
	 **/
	virtual ~StatisticServer() {};

	/**
	 * �����ʼ��
	 **/
	virtual void initialize();

	/**
	 * ��������
	 **/
	virtual void destroyApp();
};
////////////////////////////////////////////
#endif
