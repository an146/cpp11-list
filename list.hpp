#ifndef OURSTL_LIST_H
#define OURSTL_LIST_H

#include <algorithm>
#include <iterator>

namespace ourstd
{
    struct list_node
    {
        list_node *prev, *next;

        inline void insert(list_node *p, list_node *n) throw()
        {
            this->prev = p;
            this->next = n;
            p->next = n->prev = this;
        }

        inline void insert_before(list_node *n) throw()
        {
            insert(n->prev, n);
        }

        inline void erase() throw()
        {
            this->prev->next = this->next;
            this->next->prev = this->prev;
        }

        inline void reset() throw()
        {
            this->prev = this->next = this;
        }

        inline void reverse() throw()
        {
            std::swap(this->prev, this->next);
        }
    };

    template <class T, class A = std::allocator<T> >
    class list
    {
        struct node
        {
            list_node _node;
            T _value;
            
            explicit node(const T &value) : _value(value) { }
        };

        list_node head;

    public:
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::const_reference const_reference;
        typedef typename A::pointer pointer;

        //TODO: basic_iterator<class NodePointer, ...>
        class iterator;
        class const_iterator;
        class iterator_identity
        {
            friend class iterator;
            friend class const_iterator;
            const list_node *_node;
            iterator_identity(const list_node *n) : _node(n) { }
        };

        class iterator
        {
            friend class const_iterator;
            friend class list;
            list_node *_node;
            iterator(list_node *n) : _node(n) { }
        protected:
            void destroy()
            {
                delete reinterpret_cast<node *>(_node);
            }
        public:
            typedef list::difference_type difference_type;
            typedef list::value_type value_type;
            typedef list::reference reference;
            typedef list::const_reference const_reference;
            typedef list::pointer pointer;
            typedef std::bidirectional_iterator_tag iterator_category;

            iterator() { }
            T &operator *() { return reinterpret_cast<node *>(_node)->_value; }
            T *operator ->() { return &**this; }
            iterator operator ++() { _node = _node->next; return *this; }
            iterator operator --() { _node = _node->prev; return *this; }
            operator iterator_identity() const { return _node; }
            bool operator ==(const iterator_identity &other) const { return _node == other._node; }
            bool operator !=(const iterator_identity &other) const { return _node != other._node; }
        };

        class const_iterator : public std::bidirectional_iterator_tag
        {
            //TODO: make sure about pointer/reference constness
            typedef list::difference_type difference_type;
            typedef list::value_type value_type;
            typedef list::reference reference;
            typedef list::const_reference const_reference;
            typedef list::pointer pointer;
            typedef std::bidirectional_iterator_tag iterator_category;

            friend class list;
            const list_node *_node;
            const_iterator(const list_node *n) : _node(n) { }
        public:
            const_iterator() { }
            const_iterator(iterator it) : _node(it._node) { }
            const T &operator *() { return reinterpret_cast<const node *>(_node)->_value; }
            const T *operator ->() { return &**this; }
            const_iterator operator ++() { _node = _node->next; return *this; }
            const_iterator operator --() { _node = _node->prev; return *this; }
            operator iterator_identity() const { return _node; }
            bool operator ==(const iterator_identity &other) const { return _node == other._node; }
            bool operator !=(const iterator_identity &other) const { return _node != other._node; }
        };

        list() { head.reset(); }
        ~list() { clear(); }
        iterator begin() { return head.next; }
        iterator end() { return &head; }
        const_iterator begin() const { return head.next; }
        const_iterator end() const { return &head; }
        bool empty() const { return begin() == end(); }
        void clear()
        {
            while (!empty())
                erase(begin());
        }
        iterator insert(iterator where, const T &value)
        {
            node *n = new node(value);
            n->_node.insert_before(where._node);
            return &n->_node;
        }
        iterator erase(iterator it)
        {
            iterator ret = it;
            ++ret;
            it._node->erase();
            it.destroy();
            return ret;
        }
        void push_front(const T &value) { insert(begin(), value); }
        void push_back(const T &value) { insert(end(), value); }

        void reverse()
        {
            iterator i = end();
            do {
                i._node->reverse();
            } while (--i != end());
        }
    };
}

#endif // OURSTL_LIST_H
