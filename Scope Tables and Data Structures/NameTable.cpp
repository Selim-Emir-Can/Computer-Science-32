// NameTable.cpp

// This is a correct but inefficient implementation of
// the NameTable functionality.

#include "NameTable.h"
#include <list>
#include<queue>
#include <string>
#include <vector>
#include <iostream>
#include<stack>
#include<functional>
using namespace std;

class variable
{
public:
    variable();
    variable(const variable& copy);
    variable(string ID, int LINE, int SCOPE);
    int line;
    int scope;
    string id;
};
variable::variable(const variable& copy)
    : id(copy.id), line(copy.line), scope(copy.scope)
{}
variable::variable()
    : line(-1), scope(-1), id("")
{}
variable::variable(string ID, int LINE, int SCOPE)
    : id(ID), line(LINE), scope(SCOPE)
{}

int checkPrime(int n)
{
    int i;
    if (n == 1 || n == 0)
    {
        return 0;
    }
    for (i = 2; i < n / 2; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
int getPrime(int n)
{
    if (n % 2 == 0)
    {
        n++;
    }
    while (!checkPrime(n))
    {
        n += 2;
    }
    return n;
}

class HashTable
{
public:
    HashTable();
    HashTable(int c);
    void insertItem(const variable& var);
    int findItemReturnLine(const string& id) const;
    int findItemReturnScope(const string& id) const;
    bool canIDeclare(const string& id, const int& scope) const;
    void deleteItem(const std::string& id, const int& scope);
    int hashFunction(int key) const;
    int hashFunction(int key, int cap) const;
    void displayHash();
private:
    int capacity;
    list<variable>* table;
};
int HashTable::hashFunction(int key) const
{
    if (key < 0)
    {
        return(-(key % capacity));
    }
    else
    {
        return(key % capacity);
    }
}
int HashTable::hashFunction(int key, int cap) const
{
    if (key < 0)
    {
        return(-(key % cap));
    }
    else
    {
        return(key % cap);
    }
}

HashTable::HashTable()
    : HashTable(19997)
{

}
HashTable::HashTable(int c)
{
    capacity = getPrime(c);
    table = new list<variable>[capacity];
}
int HashTable::findItemReturnLine(const string& id) const
{
    unsigned int key = hashFunction(std::hash<string>()(id));
    for (auto p = table[key].begin(); p != table[key].end(); p++)
    {
        if (p->id == id)
        {
            return(p->line);
        }
    }

    return(-1);
}
int HashTable::findItemReturnScope(const string& id) const
{
    unsigned int key = hashFunction(std::hash<string>()(id));
    for (auto p = table[key].begin(); p != table[key].end(); p++)
    {
        if (p->id == id)
        {
            return(p->scope);
        }
    }

    return(-1);
}

bool HashTable::canIDeclare(const string& id, const int& scope) const
{
    unsigned int key = hashFunction(std::hash<string>()(id));
    for (auto p = table[key].begin(); p != table[key].end(); p++)
    {
        if ((p->id == id))
        {
            if (p->scope <= scope)
            {
                return(true);
            }
            else
            {
                return(false);
            }
        }
    }
    return(false);
}
void HashTable::insertItem(const variable& var) // insert/update item
{
    unsigned int key = hashFunction(std::hash<string>()(var.id));
    table[key].push_front(var);
}
void HashTable::deleteItem(const std::string& id, const int& scope)
{
    unsigned int key = hashFunction(std::hash<string>()(id));
    for (auto p = table[key].begin(); p != table[key].end(); p++)
    {
        if ((p->id == id) && (p->scope == scope))
        {
            table[key].erase(p);
            return;
        }
    }
}
void HashTable::displayHash()
{
    for (int i = 0; i < capacity; i++)
    {
        cout << "table[" << i << "]";
        for (auto x = table[i].begin(); x != table[i].end(); x++)
        {
            if (x == table[i].begin())
            {
                cout << " --> " << x->id;
            }
            else
            {
                cout << " " << x->id;
            }
        }
        cout << endl;
    }
}



// This class does the real work of the implementation.

class NameTableImpl
{
public:
    void enterScope();
    bool exitScope();
    bool declare(const string& id, int lineNum);
    int find(const string& id) const;
private:
    HashTable m_find;
    stack<string> m_dec;
    int m_scope = 0;
};

void NameTableImpl::enterScope()
{
    m_dec.push("");
    m_scope++;
}

bool NameTableImpl::exitScope()
{
    if (m_scope != 0)
    {
        while (m_dec.top() != "")
        {
            m_find.deleteItem(m_dec.top(), m_scope);
            m_dec.pop();
        }
        m_dec.pop();
        m_scope--;
        return(true);
    }
    else
    {
        return(false);
    }
}

bool NameTableImpl::declare(const string& id, int lineNum)
{
    if (m_scope == m_find.findItemReturnScope(id))
    {
        return(false);
    }
    else
    {
        m_find.insertItem(variable(id, lineNum, m_scope));
        m_dec.push(id);
        return(true);
    }
}

int NameTableImpl::find(const string& id) const
{
    return(m_find.findItemReturnLine(id));
}


//*********** NameTable functions **************

// For the most part, these functions simply delegate to NameTableImpl's
// functions.

NameTable::NameTable()
{
    m_impl = new NameTableImpl;
}

NameTable::~NameTable()
{
    delete m_impl;
}

void NameTable::enterScope()
{
    m_impl->enterScope();
}

bool NameTable::exitScope()
{
    return m_impl->exitScope();
}

bool NameTable::declare(const string& id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int NameTable::find(const string& id) const
{
    return m_impl->find(id);
}
