# 连珠游戏客户端
基于cocos2d-x-3.17.2 c++实现。

## 1、包说明
* net: 网络封装，实现网络数据包的定义、网络数据的收发，奇偶检验、临时对象池、消息队列，路由等。  
* context: 客户端传输上下文的定义。  
* threadpool: 线程池的实现，根据任务优先级大小进行对任务的处理。

## 2、客户端网络使用示例

* protobuf协议：demo.proto

```
syntax="proto3";
option go_package = ".;demo"; //协议包名

enum ServiceID {
    demo = 0;
}

enum Event {
    Hello = 0;
}

message HelloRequest {
    string name = 1;
}

message HelloResponse {
    string ret = 1;
}
```

* main.cpp

```
#include "net/client.h"
#include "demo.pb.h"
#include "net/Connection.h"

// demo
class DemoHandle : public IRouter
{
public:
	DemoHandle() {}
	~DemoHandle() {}

	virtual void PreHandle(Response * resp) override{
		printf("PreHandle\n");
	}

	virtual void Handle(Response * resp) override{
		// 此处可以再进行对 Demo 服里面的 api 路由，实现对应 api 执行对应的逻辑处理。
		printf("Handle\n");
		string data = resp->GetContext()->data();
		HelloResponse h;
		if (!h.ParseFromString(data)) {
			printf("ParseFromString:%s error", data);
			return;
		}
		printf("Recv: %s\n", h.ret().c_str());
	}

	virtual void PostHandle(Response * resp) override{
		printf("PostHandle\n");
	} 
};

static unsigned __stdcall MainFunc(void * param) 
{
	while (1){
		string output;
		HelloRequest req;
		req.set_name("tony");
		req.SerializeToString(&output);
		Connection::Instance()->Send(demo, Hello, output.c_str());
		Sleep(2000);
	}
	
	return 0;
}

int main()
{
	Client * client = Client::Instance();
	client->RegistryRouter(demo, new(DemoHandle));// 注册消息处理路由
	client->Start("127.0.0.1", 9999, MainFunc);// 开始连接，启动服务
	client->Stop();
    return 0;
}
```

* 关于工程需要的:protobuf-1.12.3  
链接：https://pan.baidu.com/s/1DF3QUo1Y1AcjQ-zXyfajeA   
提取码：92wl   
之后分别在项目中包含其 lib 和 include 文件。  