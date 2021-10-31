#pragma once

class Contact{
    public:
        Contact (const char *Aname,const char *Aaddress, const char *Atel);

        ~Contact (void);
        
        const char* Name (void) const {return name;}

        const char* Address (void) const {return address;}

        const char* Tel (void) const {return tel;}

        friend std::ostream& operator << (std::ostream&, Contact&);
    private:

        char *name;         // contact name

        char *address;      // contact address

        char *tel;          // contact telephone number
};


class ContactDir {

    public:

        ContactDir (const int AmaxSize);

        ~ContactDir(void);

        void Insert (const Contact&);

        void Delete (const char *Aname);

        Contact* Find (const char *name);

        friend std::ostream& operator << (std::ostream&, ContactDir&);

    private:

        int Lookup (const char *Aname);     // returns index i such that contacts[i]->Name equals name

        Contact **contacts;                 // list of contacts

        int dirSize;                        // current directory size

        int maxSize;                        // max directory size

};


class SmartDir : public ContactDir {

    public:

        SmartDir(const int max) : ContactDir(max) {recent = nullptr;}

        Contact* Recent (void);

        Contact* Find (const char *name);

    private:

        char *recent;             // the most recently looked-up name

};