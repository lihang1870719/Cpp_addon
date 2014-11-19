#include <node.h>

#include <v8.h>

using namespace v8; //使用命名空间v8,不用在代码中写v8::XXXX

Handle<Value> Method(const Arguments& args) { //定义一个function，返回Handle<Value>类的值
HandleScope scope; //实例化scope，用来存放返回值
return scope.Close(String::New("world")); //将返回值丢入scope.close中
}

void init(Handle<Object> target) { //接受参数 Handle<Object>类型，注意，这里target是指针
target->Set(String::NewSymbol("hello"), //调用Set方法，对这个对象增加key和value
      FunctionTemplate::New(Method)->GetFunction()); //调用类FunctionTemplate的静态成员New方法，传入Handle<Value>类型的Method，然后调用GetFunction方法生成node函数，具体v8参考手册上有说明

}
NODE_MODULE(hello, init) //固定将文件名hello，和init初始化函数丢入NODE_MODULE