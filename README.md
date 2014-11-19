Cpp_addon
=========

1. hello.cc与hello.js用来输出一个简单的字符串
    主要是利用了一个函数来传递,再hello.cc中写的是一个C++的函数,但是通过FunctionTemplate重新指向那个C++函数,在node中可以来调用.
    /*void Initialize (Handle<Object> target);
    /*NODE_MODULE(module_name, Initialize)
    所有的node插件都必须输出一个格式化的函数,也就是上述的代码都是必须的.其中module_name与最后生成的文件是相同的名称,在node中require时就是这个名称.

 2. add.cc与add.js
     用来使用add方法实现两个整数相加
     String::New("Wrong arguments")
     表示将一个C++字符串转换成一个js字符串对象
     args[0]->NumberValue()
     表示将js传递过来的Number类型编程C++可用的double型
     V8接口的Local<xxx>这种类型是用来将C++的数据传递给js的
     V8下的Value类下的一些比如String等都可以用来讲C++的数据转换给js用

     模块的工作流程:接受node传来的数据,需要运算就变成C++类型,然后计算完成后变成js类型,传回来.

3.返回一个函数 returnfunction.js与returnfunction.cc
   函数的返回值是一个函数
   FunctionTemplate是用来创建函数的，在一个上下文中仅能创建一个FunctionTemplate创建的函数的声明周期等于这个上下文存在的声明周期
   FunctionTemplate可以拥有属性，当你创建它后，这些属性可以加给他.
   具体我们如何利用c++函数给node用我们了解了，大致的思路是：
   先写C++函数，然后利用函数模版转化成js模版函数，接着为这个函数模版做一些属性设置，比如设置原形链或者静态属性等，最后调用这个函数模版指针的GetFunction方法，转化成local<function>类型，供node使用.

4.回调函数 callback.js与callback.cc
   Local<Function> cb = Local<Function>::Cast(args[0]); 将参数第一个也就是js传递过来的回调函数转化成c++的function
   cb->Call(xxx)
   即js的回调

5.C++创建一个js对象creatobject.cc与createobject.js
    函数返回值就是一个用C++创建的js数组

6.wrapclass.js wrapclass.cc myobject.h 是一个将C++类输出给js,然后js通过new来获取

7.wrapcreateobject.cc wrapcreateobject.js mycreateobject.h也是将一个C++类输出给js,但是区别在于js是用过createobject来获取

将一个C++的类输出给js大致的步骤:
在mycreateobject.h中
1.定义Init函数，用来初始化，在Init函数中执行Myobject的静态方法Init、
2.Init函数第二行定义一个对外的方法createobject
3.定义createobject方法，执行Myobject类的静态方法NewInstance，然后将其值返回。

在myobject.h
1.定义Myobject类，继承自node命名空间下的ObjectWrap基类

2.声明2个public的静态方法init和NewInstance

3.声明private的属性和方法，声明构造和析构函数，静态属性 constructor，静态方法new和plusone

4.定义构造和析构函数

5.定义Init函数的步骤
5-1.定义一个函数模版，模版来源是c++的myobject类的静态方法new
5-2.设置模版函数tpl的class名，为Myobject
5-3.设置这个class名为myobject的构造函数（js中叫这个吧，不是基类）的原形链上的方法plusone，并且把c++中myobject类的静态私有方法plusone作为函数模版赋值给它
5-4.最后将constructor变量指向tpl转化为的Persistent<Function>类型的js函数对象。

6.定义new函数
6-1.创建一个指向Myobject类的实例的指针变量 obj
6-2.将这个实例的counter_属性初始赋值为0或者参数
6-3.将local<object>对象wrap包装
6-4.返回local<object>，其实这里就是js实例的对象，就是js的createobject()方法的返回值

7定义NewInstance方法
7-1.生成参数，然后调用
注意Local<Object> instance = constructor->NewInstance(argc, argv);
上面这段其实就是生成tpl函数模版的实例，同时将参数传进去，就相当于执行了Myobject::new的方法
7-2.最后将生成的实例通过scope.Close返回给客户端

8.定义PlusOne方法，将js的实例对象转化为C++对应的实例对象指针，然后执行属性counter_加1，最后返回数据


