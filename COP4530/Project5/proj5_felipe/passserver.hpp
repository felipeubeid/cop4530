#ifndef PASSSERVER_HPP
#define PASSSERVER_HPP

#include "passserver.h"
#include <unistd.h>
#include <crypt.h>
#include <utility>
#include <fstream>
#include <sstream>

PassServer::PassServer(size_t size) : table(size) 
{ }

PassServer::~PassServer() 
{ table.clear(); }

bool PassServer::load(const char *filename)
{ return table.load(filename); }

bool PassServer::addUser(std::pair<std::string, std::string> &kv)
{ 
    if (table.contains(kv.first))
        return false;
    kv.second = encrypt(kv.second);
    return table.insert(kv);
}

bool PassServer::addUser(std::pair<std::string, std::string> &&kv)
{
    if (table.contains(kv.first))
        return false;
    kv.second = encrypt(kv.second);
    return table.insert(std::move(kv));
}

bool PassServer::removeUser(const std::string &k)
{ return table.remove(k); }

bool PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string &newpassword)
{ 
    if (!table.contains(p.first))
        return false;
    std::string oldEncrypt = encrypt(p.second);
    if (!table.match(std::make_pair(p.first, oldEncrypt)))
        return false;
    if (newpassword == p.second)
        return false;
    std::string newEncrypt = encrypt(newpassword);
    return table.insert((std::make_pair(p.first, newEncrypt)));
}

bool PassServer::find(const std::string &user) const
{ return table.contains(user); }

void PassServer::dump()
{ table.dump(); }

size_t PassServer::size() const
{ return table.size(); }

bool PassServer::write_to_file(const char *filename) const
{ return table.write_to_file(filename); }

std::string PassServer::encrypt(const std::string &str)
{ 
    const char salt[] = "$1$########";
    char *encryptP = crypt(str.c_str(), salt);
    std::string encryptPS(encryptP);
    size_t pos = encryptPS.find_last_of('$');

    return encryptPS.substr(pos + 1);
}

#endif