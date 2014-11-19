/*#include <node.h>
class MyObject:public node::ObjectWrap{
	//MyObject继承node命名空间的ObjectWrap基类
public:
	static void Init(v8::Handle<v8::Object> target);
	//声明静态方法Init
private:
	MyObject();
	~MyObject();
	static v8::Handle<v8::Value> New(const v8::Arguments&args);
	//声明New方法
	static v8::Handle<v8::Value> PlusOne(const v8::Arguments&args);
	//声明PlusOne方法
	static v8::Persistent<v8::Function> constructor;
	double counter_;
};*/

#define BUILDING_NODE_EXTENSION_ONE
#include <node.h>
using namespace v8;

class MyObject:public node::ObjectWrap{
	//MyObject继承node命名空间的ObjectWrap基类
public:
	static void Init(v8::Handle<v8::Object> target);
	//声明静态方法Init
private:
	MyObject();
	~MyObject();
	static v8::Handle<v8::Value> New(const v8::Arguments&args);
	//声明New方法
	static v8::Handle<v8::Value> PlusOne(const v8::Arguments&args);
	//声明PlusOne方法
	static v8::Persistent<v8::Function> constructor;
	double counter_;
};

Persistent<Function> MyObject::constructor;

MyObject::MyObject(){	
}
MyObject::~MyObject() {
}

void MyObject::Init(Handle<Object> target) {
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	//定义一个函数模版tpl
	tpl->SetClassName(String::NewSymbol("MyObject")); 
	//设置函数模版的类名 MyObject
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	//设置这个对象模版内部字段的数量
	//InstanceTemplate方法用来获取tpl模板的实例的模板,返回Local<ObjectTemplate>
	//SetInternalFieldCount方法用来对这个对买你模板设置内部之段的数量,这里设置为1
	// Prototype
	tpl->PrototypeTemplate()->Set(String::NewSymbol("plusOne"),
	FunctionTemplate::New(PlusOne)->GetFunction());
	//设置tpl的原形链上的方法，名叫plusOne
	constructor = Persistent<Function>::New(tpl->GetFunction());
	 //获得构造函数
	//Persistent类表示需要明确的调用Persistent::Dispose才回去GC
	target->Set(String::NewSymbol("MyObject"), constructor); 
	//设置Myobject为构造函数
}

Handle<Value> MyObject::New(const Arguments& args) { 
	//对外的new函数
  	HandleScope scope;
  	MyObject* obj = new MyObject();
  	//实例化一个Myobject对象，用obj指针指向
  	obj->counter_ = args[0]->IsUndefined() ? 0 : args[0]->NumberValue(); 
  	//私有属性counter_初始化
  	obj->Wrap(args.This());
  	//包裹 args对象
  	return args.This();
}

Handle<Value> MyObject::PlusOne(const Arguments& args) {
	HandleScope scope;
	MyObject* obj = ObjectWrap::Unwrap<MyObject>(args.This());
	//指针变量指向arg对象
	obj->counter_ += 1; 
	//obj对象的属性counter_加上了1
	return scope.Close(Number::New(obj->counter_));
	//函数返回obj的counter属性
  }
