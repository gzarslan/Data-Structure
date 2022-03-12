/*******************************************************/
/*                                                     */
/*  Put your linked list code from A1/lab3/lab4 into   */
/*  this file                                          */
/*                                                     */
/*******************************************************/
#ifndef MY_LIST_H
#define MY_LIST_H

template <class T>
void Swap(T& t1, T& t2) {
    auto tmp = static_cast<T&&>(t1); // move without std::move
    t1 = static_cast<T&&>(t2);
    t2 = static_cast<T&&>(tmp);
}

template <typename T>
class Sentinel
{
    struct Node
    {
        T data_;
        Node* next_;
        Node* prev_;
        Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr)
        {
            data_ = data;
            next_ = next;
            prev_ = prev;
        }
    };
    Node* front_;
    Node* back_;

    // Deletes everything but front_ and next
    void clear() {
        auto pnode = front_->next_;
        while (pnode != back_)
        {
            auto const tmp = pnode;
            pnode = pnode->next_;
            delete tmp;
        }
        front_->next_ = back_;
        back_->prev_ = front_;
    }

    void copy(Sentinel const& other) {
        if (this == &other)
            return;

        clear();
        for (auto const& elm : other)
            push_back(elm);
    }

    void swap(Sentinel& other) {
        Swap(front_, other.front_);
        Swap(back_, other.back_);
    }

    void move(Sentinel&& goner) noexcept {
        swap(goner);
    }

    void push_back(Node* node) {
        node->next_ = back_;
        node->prev_ = back_->prev_;
        back_->prev_->next_ = node;
        back_->prev_ = node;
    }

public:
    Sentinel()
    {
        front_ = new Node();
        back_ = new Node();
        front_->next_ = back_;
        back_->prev_ = front_;
    }

    Sentinel(Sentinel const& other) : Sentinel()
    {
        *this = other;
    }

    Sentinel(Sentinel&& goner) : Sentinel()
    {
        *this = static_cast<Sentinel&&>(goner);
    }

    Sentinel& operator=(Sentinel const& other)
    {
        copy(other); // self assignment check is done inside copy 
        return *this;
    }

    Sentinel& operator=(Sentinel&& goner) {
        move(static_cast<Sentinel&&>(goner)); // self assignment check is not necessary
        return *this;
    }

    ~Sentinel();

    void push_back(const T& data);
    void pop_back();

    class const_iterator
    {
    private:
        Node* curr_ = nullptr;

        const_iterator(Node* curr)
            : curr_(curr)
        {
        }
        friend class Sentinel;

    public:
        const_iterator() = default;
        const_iterator& operator++()
        {
            if (curr_)
            {
                curr_ = curr_->next_;
            }
            return *this;
        }
        const_iterator operator++(int)
        {
            auto copy = *this;
            ++* this;
            return copy;
        }
        const_iterator& operator--()
        {
            if (curr_)
            {
                curr_ = curr_->prev_;
            }
            return *this;
        }
        const_iterator operator--(int)
        {
            auto copy = *this;
            --* this;
            return copy;
        }
        bool operator==(const_iterator const& rhs)
        {
            return curr_ == rhs.curr_;
        }
        bool operator!=(const_iterator const& rhs)
        {
            return !(*this == rhs);
        }

        const T& operator*() const
        {
            return curr_->data_;
        }

        T const* operator->() const
        {
            return &**this;
        }
    };
    class iterator : public const_iterator
    {
    public:
        using const_iterator::const_iterator; // inherit constructors;
        friend class Sentinel;

        iterator& operator++()
        {
            const_iterator::operator++();
            return *this;
        }
        iterator operator++(int)
        {
            auto copy = *this;
            ++* this;
            return copy;
        }
        iterator& operator--()
        {
            const_iterator::operator--();
            return *this;
        }
        iterator operator--(int)
        {
            auto copy = *this;
            --* this;
            return copy;
        }
        T& operator*() const
        {
            return const_cast<T&>(const_iterator::operator*());
        }

        T* operator->() const
        {
            return &**this;
        }
    };

    void splice_back(const_iterator it, Sentinel& other);
    void erase(const_iterator it);

    const_iterator cbegin() const
    {
        return const_iterator(front_->next_);
    }
    const_iterator begin() const { return cbegin(); }
    iterator begin()
    {
        return iterator(front_->next_);
    }
    const_iterator cend() const
    {
        return const_iterator(back_);
    }
    const_iterator end() const { return cend(); }
    iterator end()
    {
        return iterator(back_);
    }


private:
    Node* extract(const_iterator it) {
        auto const pnode = it.curr_;

        auto const prev = pnode->prev_;
        auto const next = pnode->next_;
        prev->next_ = next;
        next->prev_ = prev;

        pnode->prev_ = nullptr;
        pnode->next_ = nullptr;
        return pnode;
    }
};


template <typename T>
void Sentinel<T>::push_back(const T& data)
{
    push_back(new Node(data));
}

template <typename T>
void Sentinel<T>::pop_back()
{
    if (back_->prev_ != front_)
    {
        auto const rm = back_->prev_;
        auto const prm = rm->prev_;
        back_->prev_ = prm;
        prm->next_ = back_;
        delete rm;
    }
}

template<typename T>
void Sentinel<T>::erase(const_iterator it)
{
    auto const node = it.curr_;
    auto const prev = node->prev_; // not null
    auto const next = node->next_; // not null
    prev->next_ = next;
    next->prev_ = prev;
    delete node;
}

template <typename T>
Sentinel<T>::~Sentinel()
{
    while (front_)
    {
        auto cpy = front_;
        front_ = front_->next_;
        delete cpy;
    }
}

template <class T>
void Sentinel<T>::splice_back(const_iterator it, Sentinel& other)
{
    push_back(other.extract(it.curr_));
}


#endif // MY_LIST_H
