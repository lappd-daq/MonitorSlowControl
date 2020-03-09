#include "Factory.h"

Tool* Factory(std::string tool){
Tool* ret=0;

// if (tool=="Type") tool=new Type;
if (tool=="DummyTool") ret=new DummyTool;

if (tool=="Poll") ret=new Poll;
if (tool=="Stream") ret=new Stream;
if (tool=="Set") ret=new Set;
if (tool=="StreamReceive") ret=new StreamReceive;
  if (tool=="SetSend") ret=new SetSend;
return ret;
}

