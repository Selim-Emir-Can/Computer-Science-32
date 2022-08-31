#ifndef SEQUENCE_H
#define SEQUENCE_H

#include<iostream>
#include<string>

using ItemType = std::string;


class ItemTypeNode
{
public:
    ItemTypeNode();   // empty node
    ItemTypeNode(ItemType theData, ItemTypeNode* nextLink, ItemTypeNode* prevLink);

    ItemTypeNode* getnextLink() const;
    ItemTypeNode* getprevLink() const;
    ItemType getData() const;

    void setnextLink(ItemTypeNode* nextLink);
    void setprevLink(ItemTypeNode* prevLink);
    void setData(ItemType theData);

private:
    ItemType m_data;
    ItemTypeNode* m_next_link;
    ItemTypeNode* m_prev_link;

};








class Sequence
{
public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence& CopyMe);
    Sequence& operator =(const Sequence& AssignMe);

    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);

private:
    ItemTypeNode* m_head;
    int m_size;
};


int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);


#endif // !SEQUENCE_H