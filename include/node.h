#ifndef __NODE_H__
#define __NODE_H__

template<class T>
class Node
{
public:
    Node() {}
    Node(const T& data)
    {
        this->_data = data;
    }

    Node(const T& data, Node* next)
    {
        this->_data = data;
        this->_next = next;
    }

    T& data() const
    {
        return _data;
    }
    
    Node<T>* next() const
    {
        return _next;
    }

    void next(Node* Node)
    {
        this->_next = Node;
    }

private:
    T _data;
    Node* _next;
};

#endif