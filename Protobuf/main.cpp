#include <QCoreApplication>
#include <iostream>
#include "addressbook.pb.h"
int main(int /*argc*/, char */*argv*/[])
{
    tutorial::AddressBook src_book;
    {
        tutorial::Person * person = src_book.add_person();
        person->set_name("M. K.");
        person->set_id(0);
        person->set_email("doommp2@gmail.com");
        {
            tutorial::Person_PhoneNumber * pn = person->add_phone();
            pn->set_number("380 69 85 97 955");
            pn->set_type(tutorial::Person_PhoneType_MOBILE);
        }
        {
            tutorial::Person_PhoneNumber * pn = person->add_phone();
            pn->set_number("380 67 84 98 667");
            pn->set_type(tutorial::Person_PhoneType_MOBILE);
        }
    }
    {
        tutorial::Person * person = src_book.add_person();
        person->set_name("M. G.");
        person->set_id(1);
        {
            tutorial::Person_PhoneNumber * pn = person->add_phone();
            pn->set_number("380 97 84 58 944");
            pn->set_type(tutorial::Person_PhoneType_HOME);

        }
    }
    std::string msg;
      src_book.SerializeToString(&msg);

      tutorial::AddressBook dst_book;
      dst_book.ParseFromString(msg);

      dst_book.PrintDebugString();

      return 0;
  }
