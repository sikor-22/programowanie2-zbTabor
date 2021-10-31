#include <iostream>
#include <cstring>
#include <cstdio>
#include "header.h"

ContactDir::ContactDir(const int AmaxSize){
    maxSize = AmaxSize;
    contacts = new Contact*[maxSize];
    dirSize = 0;
}

ContactDir::~ContactDir(){
    //assumes deleting contactdir deletes contacts included within
    for(int i = 0; i < dirSize; i++){
        delete contacts[i]; 
    }
    delete contacts;
}

void ContactDir::Insert(const Contact& Acontact){
    //always insert at the end
    if(dirSize == maxSize){
        std::cerr<<"contact directory full \n";
        return;
    }
    contacts[dirSize] = new Contact(Acontact.Name(), Acontact.Address(), Acontact.Tel());
    dirSize++;
    return;
}

void ContactDir::Delete(const char* Aname){
    int contact_to_delete = Lookup(Aname);
    if(contact_to_delete == dirSize){
        std::cerr<<"attempting to delete nonexisting contact\n";
        return;
    }
    delete contacts[contact_to_delete];
    dirSize--;
    //contacts not need to be sorted, swap last one in place of deleted one 
    contacts[contact_to_delete] = contacts[dirSize];
}

int ContactDir::Lookup(const char* Aname){
    for(int i = 0; i < dirSize; i++){
        if(strcmp(contacts[i]->Name(), Aname) == 0){
            return i;
        }   
    }
    return dirSize;
}

Contact* ContactDir::Find(const char* Aname){
    int found = Lookup(Aname);
    if(found != dirSize)
        return contacts[found];
    return nullptr;
}

std::ostream& operator<<(std::ostream& out, ContactDir& Acontact){
    for(int i = 0; i < Acontact.dirSize; i++){
        out<<i<<": "<<*(Acontact.contacts[i])<<"\n";
    }
    return out;
}