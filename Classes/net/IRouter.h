#ifndef __ROUTER_H__
#define __ROUTER_H__

#include "Response.h"

/*
 * ·�ɻ��࣬·�ɵ�ʵ�־���Ҫʵ�ָû���
 */
class IRouter
{
public:
	/*
	 * ��ҵ����֮ǰ���е��ã�������Ƿ�ʵ�֣�
	 */
	virtual void PreHandle(Response * resp) = 0;

	/*
	 * ��������ҵ��ķ���
	 */
	virtual void Handle(Response * resp) = 0;

	/*
	 * ��ҵ����֮����е��ã������ʵ�֣�
	 */
	virtual void PostHandle(Response * resp) = 0;
};

#endif //! __ROUTER_H__
