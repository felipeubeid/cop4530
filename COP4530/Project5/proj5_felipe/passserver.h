#ifndef PASSSERVER_H
#define PASSSERVER_H

#include <string>
#include <utility>
#include <unistd.h>
#include <crypt.h>
#include "hashtable.hpp"

namespace cop4530
{
    class PassServer
    {
        public:
            PassServer(size_t size = 101); // constructor, create a hash table of the specified size
            ~PassServer(); // destructor
            bool load(const char *filename); // load a password file into the HashTable object
            bool addUser(std::pair<std::string, std::string> & kv); // add a new username and password
            bool addUser(std::pair<std::string, std::string> && kv); // move version of addUser
            bool removeUser(const std::string & k); // delete an existing user with username k
            bool changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword); // change an existing user's password
            bool find(const std::string & user) const; // check if a user exists
            void dump(); // show the structure and contents of the HashTable object to the screen
            size_t size() const; // return the size of the HashTable (the number of username/password pairs in the table)
            bool write_to_file(const char *filename) const; // save the username and password combination into a file

        private:
            std::string encrypt(const std::string & str); // encrypt the parameter str and return the encrypted string
            HashTable<std::string, std::string> table;
    };

    #include "passserver.hpp"
}

#endif