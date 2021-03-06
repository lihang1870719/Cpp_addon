#include <node.h>
using namespace v8;

Handle<Value> RunCallback(const Arguments&args){
	HandleScope scope;
	Local<Function> cb=Local<Function>::Cast(args[0]);
	const unsigned argc=1;
	Local<Value> argv[argc]={Local<Value>::New(String::New("hello world"))};
	cb->Call(Context::GetCurrent()->Global(),argc,argv);
	return scope.Close(Undefined());
}

void Init(Handle<Object> target){
	target->Set(String::NewSymbol("runCallback"),FunctionTemplate::New(RunCallback)->GetFunction());
}

NODE_MODULE(callback,Init);