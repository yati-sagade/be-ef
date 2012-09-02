#ifndef __BF_H__
#define __BF_H__

#include <set>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <exception>
#include <algorithm>
#include <functional>
#include <cctype>

typedef std::vector<int>::size_type tapesize_t;

class Tape
{
private:
    std::vector<int> m_tape;
    tapesize_t m_position;
    
public:
    Tape();
    int get() const;
    void set(int c);
    void inc();
    void dec();
    void advance();
    void retreat();
};

class BFException : public std::exception
{
private:
    std::string m_message;
public:
    BFException(const std::string& message) : 
        exception(), m_message(message)
    { }
    const char* what() const throw()
    {
        return m_message.c_str();
    }
};

class BFInterpreter
{
private:
    static std::set<char> m_valid_chars;
    void _parse(const std::string& code,
                std::string& result, 
                std::map<tapesize_t, tapesize_t>& bracket_map);
    void _run(const std::string& code, 
              const std::map<tapesize_t, tapesize_t>& bracket_map);
    // This is a subobject hack for initializing the static member 
    // m_valid_chars. This is a static object and its ctor will be called
    // only once for the class, and we take advantage of that by keeping
    // all static init code inside this ctor.
    static class _init 
    {
    public:
        _init()
        {
            const std::string _valid("<>[]+-,.");
            for(auto it = _valid.begin(); it != _valid.end(); ++it)
                m_valid_chars.insert(*it);
        }
    }_initializer;
public:
    BFInterpreter();
    void run(const std::string& code);
};

static std::string& trim(std::string&);
static std::string& ltrim(std::string&);
static std::string& rtrim(std::string&);

#endif
