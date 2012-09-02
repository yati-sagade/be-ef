#include "bf.h"
using namespace std;

Tape::Tape() : m_position(0) 
{
    m_tape.push_back(0);
}

inline int Tape::get() const
{
    return m_tape[m_position];
}

inline void Tape::set(int c)
{
    m_tape[m_position] = c;
}

inline void Tape::inc()
{
    ++m_tape[m_position];
}

inline void Tape::dec()
{
    --m_tape[m_position];
}

inline void Tape::advance()
{
    ++m_position;
    if(m_position >= m_tape.size())
        m_tape.push_back(0);
}

inline void Tape::retreat()
{
    --m_position;
}


set<char> BFInterpreter::m_valid_chars;
// This line is a must, as the ctor for _initializer will never be called
// otherwise.
BFInterpreter::_init BFInterpreter::_initializer;

BFInterpreter::BFInterpreter() { }

void BFInterpreter::_parse(const string& code,
                           string& result,
                           map<tapesize_t, tapesize_t>& bracket_map)
{
    stringstream parsed;
    tapesize_t pc = 0;
    vector<tapesize_t> leftstack;
    for(char c : code)
    {
        if(m_valid_chars.find(c) != m_valid_chars.end())
        {
            parsed << c;
            switch(c)
            {
            case '[':
                leftstack.push_back(pc);
                break;
            case ']':
                tapesize_t left = leftstack.back();
                leftstack.pop_back();
                bracket_map[left] = pc;
                bracket_map[pc] = left;
                break;
            }
            ++pc;
        }
    }
    result = parsed.str();
}

void BFInterpreter::_run(const string& code, 
                         const map<tapesize_t, tapesize_t>& bracket_map)
{   
    Tape tape;
    tapesize_t pc = 0;
    const auto code_size = code.size();
    while(pc < code_size)
    {
        char c = code[pc];
        switch(c)
        {
        case '<':
            tape.retreat();
            break;
        case '>':
            tape.advance();
            break;
        case '[':
            if(!tape.get()) pc = bracket_map.find(pc)->second;
            break;
        case ']':
            if(tape.get()) pc = bracket_map.find(pc)->second;
            break;
        case '+':
            tape.inc(); 
            break;
        case '-':
            tape.dec();
            break;
        case '.':
            cout << (char)tape.get();
            break;
        case ',':
            int tmp;
            cin >> tmp;
            tape.set(tmp);
            cin.clear();
            break;
        default:
            stringstream err;
            err << "Invalid character at position " << pc
                << ": '" << c << "'";
            throw BFException(err.str());
        }
        ++pc;
    }
}

void BFInterpreter::run(const string& code)
{
    string program;
    map<tapesize_t, tapesize_t> bracket_map;
    _parse(code, program, bracket_map);
    _run(program, bracket_map);
}

int main(int argc, char* argv[])
{
    BFInterpreter interpreter;
    if (argc > 1)
    {
        fstream input(argv[1], fstream::in);
        if(input.fail())
        {
            cerr << argv[1] << ": No such file" << endl;
            return 1;
        }
        stringstream instream;
        instream << input.rdbuf();
        interpreter.run(instream.str());
    }
    else
    {
        string line;
        cout << "bf> ";
        while(getline(cin, line))
        {
            trim(line);
            if(!line.empty())
            {
                interpreter.run(line);
                cout << "bf> ";
            }
            cin.clear();
        }
    }
    return 0;
}

static inline string& ltrim(string& s) {
        s.erase(s.begin(), find_if(s.begin(), s.end(), 
                                   not1(ptr_fun<int, int>(isspace))));
        return s;
}

// trim from end
static inline string& rtrim(string& s) {
        s.erase(find_if(s.rbegin(), s.rend(), 
                        not1(ptr_fun<int, int>(isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline string& trim(string& s) {
        return ltrim(rtrim(s));
}

