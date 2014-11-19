#include <node.h>

#include <v8.h>

using namespace v8; //使用命名空间v8,不用在代码中写v8::XXXX

void init(Handle<Object> target) { 
	HandleScope handle_scope;
	Persistent<Context> context=Context::New();
	//创建一个上下文对象
	Context::Scope context_scope(context);
	Handle<String> source=String::New("hello world");
	//Handle<Script> script=Script::Compile(source);
	//Handle<Value>result=script->Run();
	context.Dispose();
	//String::AsciiValue ascii(result);
	//printf("%s\n",*ascii);
	target->Set(String::NewSymbol("hello"),source); 
}
NODE_MODULE(string, init) //固定将文件名hello，和init初始化函数丢入NODE_MODULE