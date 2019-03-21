///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains interface part of the bidirectional list structure template.
///
/// © Sergey Shershakov 2015–2017.
/// Pavel Pertsukhov: 2018, added iterators.
///
/// This code is for educational purposes of the course "Algorithms and Data 
/// Structures" provided by the School of Software Engineering of the Faculty 
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////


#ifndef XI_ENHLINKEDLIST_BIDILIST_H_
#define XI_ENHLINKEDLIST_BIDILIST_H_

// !!! uncomment this if you'd like to get the highest mark !!!
// раскомментируй эту строчку, если хочется получить оценочку повыше
#define IWANNAGET10POINTS

#include <cstddef>      // size_t


/** \brief Declares a generic purpose bidirectional list
 *
 *  Since there are reverse links presented, a list can be traversed both 
 *  in direct and reverse direction.
 *
 *  **Requirements to a `T`** are as follows:
 *  *   `T` should be default constructable
 *  *   `T` should be copyable
 */
template<typename T>
class BidiLinkedList
{
public:
    //-----<Consts>------
    /** \brief Determines a value for case when a size has not been still calculated */
    static const std::size_t NO_SIZE = (std::size_t) -1;
public:
    //-----<Types>-----


    /** \brief Embedded class for representation list's nodes 
     *  
     *  Note, we have a template parameter \a T implicitly available here.
     *
     *  One neet to note, a `typename` keyword is needed when declaring any object
     *  of this type outside of the class. This is because no implicit way to determine
     *  if Node should be treated as a type, for example:
     *
     *  *    `template <typename T> typename BidiList<T>::Node* BidiList<T>::getLastNode() const`
     */
    class Node
    {
        /** \brief Declare a Bidilist as a friend class to allow it to have access to 
         *  Node's private members. 
         */
        friend class BidiLinkedList;

    public:
        /** \brief Default constructor */
        Node() : _next(nullptr), _prev(nullptr) {}

        /** \brief Inititalization wit a node element */
        Node(const T &el) : _next(nullptr), _prev(nullptr), _val(el) {}


    public:
        /** \brief Returns a pointer to a previous element */
        Node *getPrev() const { return _prev; }

        /** \brief Returns a pointer to a next element */
        Node *getNext() const { return _next; }

        /** \brief Returns node's value */
        T &getValue() { return _val; }

        /** \brief const overloaded verson of getValue() */
        const T &getValue() const { return _val; }

        /** \brief Sets a new value carried by the node */
        void setValue(const T &newVal) { _val = newVal; }

    public:

        // UPD: unfortunately, can't proclaim this methos due to encapsulation reqs
        ///** \brief Sets a given node \a insNode as the next node ather this
        // *  \param insNode a new node ot be after this
        // *  \return inserted node
        // */
        //Node* insertAfter(Node* insNode);

    protected:

        /** \brief Internal implementation of insertAfter() w/o any checkings 
         *
         *  <b style='color:orange'>Must be implemented by students</b>
         */
        Node *insertAfterInternal(Node *insNode);

    protected:
        T _val;                 ///< Storage a value
        Node *_next;            ///< Next element. nullptr, if no one presented
        Node *_prev;            ///< Previous element. nullptr, if no one presented
    }; // class Node<T> 


// You can comment this to disable tests for iterators if you need.
// Attention!!! An iterator implementation is necessary for this task!
// If you comment this line, one test `notImplemented` will be always failed.
//
#define TEST_ITERATOR
#ifdef TEST_ITERATOR

    // TODO: Implement iterators

    class MyIterator // You can rename it and extend it from std::iterator if you need for some reason.
    {

    public:
        MyIterator(Node *n, bool b = false)
        {
            _point = n;
            _isItEnd = b;
        }

        MyIterator &operator++()
        {
            if (_point->_next == nullptr)
                _isItEnd = true;

            else
                _point = _point->_next;
            return *this;
        }

        MyIterator operator++(int)
        {
            MyIterator tmp(*this);
            ++*this;
            return tmp;
        }

        MyIterator operator--(int)
        {
            MyIterator tmp(*this);
            --*this;
            return tmp;
        }

        bool operator!=(const MyIterator &obj) const
        {
            if (obj._point != this->_point || obj._isItEnd != this->_isItEnd)
                return true;
            else
                return false;
        }

        bool operator==(const MyIterator &obj) const
        {
            if (obj._point == this->_point && obj._isItEnd == this->_isItEnd)
                return true;
            else
                return false;
        }

        T &operator*() const
        {
            return _point->_val;
        }

        T *operator->() const
        {
            return &_point->_val;
        }

        MyIterator &operator--()
        {
            if (_isItEnd)
                _isItEnd = false;

            else
                _point = _point->_prev;
            return *this;
        }


    protected:
        Node *_point;
        bool _isItEnd;
    };


    class MyIteratorConst // You can rename it and extend it from std::iterator if you need for some reason.
    {
    public:
        MyIteratorConst(Node *n, bool b = false)
        {
            _point = n;
            _isItEnd = b;
        }

        const MyIteratorConst &operator++()
        {

            if (_point->_next == nullptr)
                _isItEnd = true;

            else
                _point = _point->_next;
            return *this;
        }

        const MyIteratorConst operator++(int)
        {
            MyIteratorConst tmp(*this);
            ++*this;
            return tmp;
        }

        const MyIteratorConst operator--(int)
        {

            MyIteratorConst tmp(*this);
            --*this;
            return tmp;
        }

        bool operator!=(const MyIteratorConst &obj) const
        {
            if (obj._point != this->_point || obj._isItEnd != this->_isItEnd)
                return true;
            else
                return false;
        }

        bool operator==(const MyIteratorConst &obj) const
        {
            if (obj._point == this->_point && obj._isItEnd == this->_isItEnd)
                return true;
            else
                return false;
        }

        const T &operator*() const
        {
            return _point->_val;
        }

        const T *operator->() const
        {
            return &_point->_val;
        }

        const MyIteratorConst &operator--()
        {
            if (_isItEnd)
                _isItEnd = false;

            else
                _point = _point->_prev;
            return *this;
        }


    protected:
        Node *_point;
        bool _isItEnd;
    };


    class MyIteratorReverse // You can rename it and extend it from std::iterator if you need for some reason.
    {
    public:
        MyIteratorReverse(Node *n, bool b = false)
        {
            _point = n;
            _isItEnd = b;
        }

        MyIteratorReverse &operator--()
        {

            if (_isItEnd)
                _isItEnd = false;

            else
                _point = _point->_next;
            return *this;
        }

        MyIteratorReverse operator++(int)
        {
            MyIteratorReverse tmp(*this);
            ++*this;
            return tmp;
        }

        MyIteratorReverse operator--(int)
        {
            MyIteratorReverse tmp(*this);
            --*this;
            return tmp;
        }

        bool operator!=(const MyIteratorReverse &obj) const
        {
            if (obj._point != this->_point || obj._isItEnd != this->_isItEnd)
                return true;
            else
                return false;
        }

        bool operator==(const MyIteratorReverse &obj) const
        {
            if (obj._point == this->_point && obj._isItEnd == this->_isItEnd)
                return true;
            else
                return false;
        }

        T &operator*() const
        {
            return _point->_val;
        }

        T *operator->() const
        {
            return &_point->_val;
        }

        MyIteratorReverse &operator++()
        {
            if (_point->_prev == nullptr)
                _isItEnd = true;

            else
                _point = _point->_prev;
            return *this;
        }


    protected:
        Node *_point;
        bool _isItEnd;
    };


    class MyIteratorReverseConst // You can rename it and extend it from std::iterator if you need for some reason.
    {
    public:
        MyIteratorReverseConst(Node *n, bool b = false)
        {
            _point = n;
            _isItEnd = b;
        }

        const MyIteratorReverseConst &operator--()
        {
            if (_isItEnd)
                _isItEnd = false;

            else
                _point = _point->_next;
            return *this;
        }

        const MyIteratorReverseConst operator++(int)
        {
            MyIteratorReverseConst tmp(*this);
            ++*this;
            return tmp;
        }

        const MyIteratorReverseConst operator--(int)
        {
            MyIteratorReverseConst tmp(*this);
            --*this;
            return tmp;
        }

        bool operator!=(const MyIteratorReverseConst &obj) const
        {
            if (obj._point != this->_point || obj._isItEnd != this->_isItEnd)
                return true;
            else
                return false;
        }

        bool operator==(const MyIteratorReverseConst &obj) const
        {
            if (obj._point == this->_point && obj._isItEnd == this->_isItEnd)
                return true;
            else
                return false;
        }

        const T &operator*() const
        {
            return _point->_val;
        }

        const T *operator->() const
        {
            return &_point->_val;
        }

        const MyIteratorReverseConst &operator++()
        {
            if (_point->_prev == nullptr)
                _isItEnd = true;

            else
                _point = _point->_prev;
            return *this;
        }


    protected:
        Node *_point;
        bool _isItEnd;
    };


    // If you call iterator classes with different names or use adapters, you can use typedefs:
    typedef MyIterator iterator;
    typedef MyIteratorConst const_iterator;
    typedef MyIteratorReverse reverse_iterator;
    typedef MyIteratorReverseConst const_reverse_iterator;



    // For iterator
public:


    /** \brief Returns an iterator to the first element of the list
     *  If the list is empty - returns an iterator to the non existing element. (Like end() does.)
     */
    iterator begin()
    {
        return MyIterator(_head, false);
    }

    /** \brief Returns an iterator to the non existing element after the end of the list.
    *  If we decrement the end() iterator, it points to the last element of the list. (If it exists.)
    */
    iterator end()
    {
        return MyIterator(_tail, true);
    }

    // Similary you should define rbegin() rend() and their const combinations for reversed iterators:

    const_iterator cbegin()
    {
        return MyIteratorConst(_head, false);
    }

    const_iterator cend()
    {
        return MyIteratorConst(_tail, true);
    }

    reverse_iterator rbegin()
    {
        return MyIteratorReverse(_tail, false);
    }

    reverse_iterator rend()
    {
        return MyIteratorReverse(_head, true);
    }

    const_reverse_iterator crbegin()
    {
        return MyIteratorReverseConst(_tail, false);
    }

    const_reverse_iterator crend()
    {
        return MyIteratorReverseConst(_head, true);
    }

protected:


#endif // TEST_ITERATOR

public:
    /** \brief Default constructor */
    BidiLinkedList() : _head(nullptr), _tail(nullptr), _size(NO_SIZE) {};

    /** \brief Destructor
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    ~BidiLinkedList();

    // TODO don't forget about big three. You can either implement it or just declare private.
public:

    /** \brief Clears the list (deletes all elements and frees memory) 
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    void clear();

    /** \brief Appends a given element (to the end) and returns a pointer to a new Node
     *  \param val const ref to a value of a appended element
     *  \return a pointer to a newly created node containing appended element
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    Node *appendEl(const T &val);

    /** \brief Inserts a given new (free) node \a insNode after node \a node
     *  \param node a node after which \a insNode is inserted
     *  \param insNode inserted node
     *  \return inserted node
     *
     *  if \a node is nullptr, inserts \a insNode at the very end
     *  If \a insNode is nullptr, an expection is raised.
     *  If \a insNode has a previous or next sibling, an exception is thrown.
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    Node *insertNodeAfter(Node *node, Node *insNode);


    /** \brief Inserts a free chain given by its begin and end node after the given node.
     *  \param beg begin node of the inserted chain
     *  \param end end node of the inserted chain
     *  \param node a node, after which the chain is inserted
     *  
     *  If either \a beg or \a end is nullptr, an expection is thrown
     *
     *  If inserted nodes \a beg and \a end  has a previous or next sibling respectively, 
     *  an exception is thrown. Since it is impossible to check whether [beg,end] belongs
     *  to another list, using such an forbidden operation can lead to a run-time error.
     *
     *  If \a node is nullptr, the chain is inserted in the very end of the list
     */
    void insertNodesAfter(Node *node, Node *beg, Node *end);

    // this part of code is active only if you'd like to get the highest mark
#ifdef IWANNAGET10POINTS

    /** \brief Inserts a given new node \a insNode before node \a node
     *  \param node a node before which \a insNode is inserted
     *  \param insNode inserted node
     *  \return inserted node
     *
     *
     *  if \a node is nullptr, inserts \a insNode in the very begin (as the head)
     *  If \a insNode is nullptr, an expection is raised
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    Node *insertNodeBefore(Node *node, Node *insNode);

    /** \brief Inserts a free chain given by its begin and end node before the given node.
     *  \param beg begin node of the inserted chain
     *  \param end end node of the inserted chain
     *  \param node a node, before which the chain is inserted
     *
     *  If either \a beg or \a end is nullptr, an expection is thrown
     *
     *  If inserted nodes \a beg and \a end  has a previous or next sibling respectively, 
     *  an exception is thrown. Since it is impossible to check whether [beg,end] belongs
     *  to another list, using such an forbidden operation can lead to a run-time error.
     *
     *  If \a node is nullptr, the chain is inserted in the very begin of the list
     *  If \a insNode has a previous or next sibling, an exception is thrown.
     */
    void insertNodesBefore(Node *node, Node *beg, Node *end);

#endif // IWANNAGET10POINTS

    /** \brief Cuts a chain of nodes determined by its begin and end node from the list
     *  \param beg begin node of the chain
     *  \param end end node of the chain
     *
     *  If either \a beg or \a end is nullptr, an expection is thrown
     *  A cutted chain should be a part of the list, otherwise unpredictable behavior
     *  is expected
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    void cutNodes(Node *beg, Node *end);


    /** \brief Cuts a given node from the list
     *  \param node  node to be cut
     *  \returns cutted node
     *
     *  If \a node is nullptr, an expection is thrown
     *  A cutted node should be a part of the list, otherwise unpredictable behavior
     *  is expected
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    Node *cutNode(Node *node);

public:

    /** \brief Finds first node carrying a given value \a val and returns it
     *  \param val value to search for
     *  \return a pointer to a node with found value; if no appropriate node is found, 
     *  returns nullptr
     *  
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    Node *findFirst(const T &val) { return findFirst(_head, val); };

    /** \brief Finds first node carrying a given value \a val, starting from a given 
     *  node \a startFrom, and returns it
     *  \param startFrom first node in a chain of all nodes algorithm starts searching from
     *  \param val value to search for
     *  \return a pointer to a node with found value; if no appropriate node is found, 
     *  returns nullptr
     *  
     *  Node \a startFrom is also tested for suitability of the search condition.
     *  If the given \a startFrom node is nullptr, returns nullptr immediately
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    Node *findFirst(Node *startFrom, const T &val);

    /** \brief Find all occurences of a value \a val and returns a C-style array with
     *  non-free pointers to a nodes of **this list**.
     *  \param size *out* determines a size of returning array if the latter is not nullptr
     *  \return a newly created array of Node* pointers with nodes with value \a val
     *
     *  Input parameters are the same as in findFirst() method.
     *  Returned array should be freed by caller!
     *  If no matches are found, returns a nullptr
     *  If the given \a startFrom node is nullptr, returns nullptr immediately
     *
     *  Try not to use std:: containers while implementing the method!  
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    Node **findAll(Node *startFrom, const T &val, int &size);

    /** \brief Overloaded version of findAll(): searching in the entire list */
    Node **findAll(const T &val, int &size) { return findAll(_head, val, size); };

    /** \brief Looking for a node with value \a val and cuts it from the list. 
     *  \param cutted node if found, nullptr otherwise
     */
    Node *cutFirst(Node *startFrom, const T &val)
    {
        Node *res = findFirst(startFrom, val);
        if (res)
            return cutNode(res);

        return nullptr;
    }

    /** \brief Cuts first node with the given value \a val */
    Node *cutFirst(const T &val) { return cutFirst(_head, val); }

    // this part of code is active only if you'd like to get the highest mark
#ifdef IWANNAGET10POINTS

    /** \brief Cuts all nodes with value that is equal to \a val and returns an
     *  array of cutted nodes.
     *
     *  For parameters, return value and special behavior description, see findAll()
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    Node **cutAll(Node *startFrom, const T &val, int &size);

    /** \brief Overloaded version of cutAll(): searching in the entire list */
    Node **cutAll(const T &val, int &size) { return cutAll(_head, val, size); };

#endif // IWANNAGET10POINTS

public:
    /** \brief Returns a lists's head */
    Node *getHeadNode() const { return _head; }

    /** \brief Returns a pointer to a last node
     *
     *  If the list is empty, returns nullptr
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    Node *getLastNode() const;

    /** \brief Returns a size of a list that is equal to a number of storing elements */
    std::size_t getSize();

protected:
    /** \brief Method invalidate size cache value until it is calculated again. 
     *  Should be invoked every time a structure of the list is changed
     */
    void invalidateSize() { _size = NO_SIZE; }

    /** \brief (Re)calculate size of the list 
     *
     *  <b style='color:orange'>Must be implemented by students</b>
     */
    void calculateSize();

protected:
    /** \brief Pointer to a first element of a list
     *
     *  Since we have both direct and reverse links, we need no more to store inconvenient prehead
     */
    Node *_head;

    /** \brief Pointer to the last element of the list
     *
     *  If the list is empty it holds nullptr.
     */
    Node *_tail;

    /** \brief Caches a size of a list. If no size has been calculated, stores NO_SIZE value */
    std::size_t _size;

}; // class BidiList 



// declaration of template class template methods
#include "bidi_linked_list.hpp"


#endif // XI_ENHLINKEDLIST_BIDILIST_H_


