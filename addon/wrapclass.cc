#define BUILDING_NODE_EXTENSION_ONE
#include <node.h>
#include "myobject.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  MyObject::Init(exports);
}

NODE_MODULE(wrapclass, InitAll)