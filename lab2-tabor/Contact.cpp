#include <iostream>
#include <cstring>
#include <cstdio>
#include "header.h"


Contact::Contact(const char *Aname,const char *Aaddress, const char *Atel){
    name = new char[strlen(Aname)];
    address = new char[strlen(Aaddress)];
    tel = new char[strlen(Atel)];
    sprintf(name, "%s", Aname);
    sprintf(address, "%s", Aaddress);
    sprintf(tel, "%s", Atel);
}

Contact::~Contact(){
    delete name;
    delete address;
    delete tel;
}

std::ostream& operator<<(std::ostream& out, Contact& that){
    out<<that.Address()<<" "<<that.Name()<<" "<<that.Tel();
    return out;
}