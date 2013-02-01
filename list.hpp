namespace ourstl
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

        inline void remove() throw()
        {
            this->prev->next = this->next;
            this->next->prev = this->prev;
        }

        inline void reset() throw()
        {
            this->prev = this->next = this;
        }
    };

    template <class T>
    class list
    {
        struct node
        {
            list_node _node;
            T _value;
            
            explicit node(const T &value) : _value(value) { }
        };

        class iterator
        {
            friend class list;
            list_node *_node;
        public:
            iterator(list_node *n) : _node(n) { }
            T &operator *() { return reinterpret_cast<node *>(_node)->_value; }
            T *operator ->() { return &**this; }
            iterator operator ++() { _node = _node->next; return *this; }
            iterator operator --() { _node = _node->prev; return *this; }
            bool operator ==(const iterator &other) const { return _node == other._node; }
            bool operator !=(const iterator &other) const { return _node != other._node; }
        };

        list_node head;
    public:
        list() { head.reset(); }
        iterator begin() { return head.next; }
        iterator end() { return &head; }
        iterator insert(iterator where, const T &value)
        {
            node *n = new node(value);
            n->_node.insert_before(where._node);
            return &n->_node;
        }
        void push_front(const T &value) { insert(begin(), value); }
        void push_back(const T &value) { insert(end(), value); }
    };
}
