#ifndef __ROUTER_H__
#define __ROUTER_H__

#include "Response.h"

/*
 * 路由基类，路由的实现均需要实现该基类
 */
class IRouter
{
public:
	/*
	 * 在业务处理之前进行调用（视情况是否实现）
	 */
	virtual void PreHandle(Response * resp) = 0;

	/*
	 * 真正处理业务的方法
	 */
	virtual void Handle(Response * resp) = 0;

	/*
	 * 在业务处理之后进行调用（视情况实现）
	 */
	virtual void PostHandle(Response * resp) = 0;
};

#endif //! __ROUTER_H__
