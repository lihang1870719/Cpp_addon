#include <node.h>

using namespace v8;

Handle<Value> CreateObject(const Arguments& args) {
	HandleScope scope;
	Handle<Value> k = args[0]->ToString();
	 //将传递的第一个参数转化为String类型
	Local<Object> obj = Object::New();
	//创建一个js的空对象
	if(args[1]->IsBoolean()){ 
	//如果第二个参数是布尔值，则转化为布尔型
		obj->Set(k, args[1]->ToBoolean());
	}
	else if(args[1]->IsNumber()){ 
	//如果第二个参数是数值，则转化为整形
		obj->Set(k, args[1]->ToNumber());
	}
	else obj->Set(k, args[1]->ToString()); 
	//否则转化为字符串
	int n = args[2]->NumberValue(); 
	//将第三个参数转化为double
	Handle<Array> ary = Array::New(n); 
	//构建js数组，长度为n
	for(int i=0;i<n;i++){
		ary->Set(Integer::New(i), obj); 
		//循环的往js数组内插入obj对象
	}
	return scope.Close(ary); 
	//将数组输出给node端
}

void Init(Handle<Object> target) {
	target->Set(String::NewSymbol("createObject"),FunctionTemplate::New(CreateObject)->GetFunction());
}

NODE_MODULE(object, Init)