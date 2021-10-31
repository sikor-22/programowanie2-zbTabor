#include <iostream>
#include <cstring>
#include <cstdio>
#include "header.h"

Contact* SmartDir::Recent(){
    if(recent != nullptr){
        //this is extremely ugly hack but problem doesnt allow changing header,
        //so recent will get lost when calling parent find()
        char* tmp = new char[strlen(recent)];
        sprintf(tmp, "%s", recent);
        Contact* returnC =  Find(tmp);
        delete tmp;
        return returnC;
    }
    std::cerr<<"no recent element";
    return nullptr;
}

Contact* SmartDir::Find(const char* Aname){
    if(recent != nullptr)
        delete recent;
    recent = new char[strlen(Aname)];
    sprintf(recent, "%s", Aname);
    return ContactDir::Find(Aname);
}