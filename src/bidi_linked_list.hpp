///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains pseudo-implementation part of bidirectional list structure 
/// template declared in the file's h-counterpart
///
/// © Sergey Shershakov 2015–2017.
///
/// This code is for educational purposes of the course "Algorithms and Data 
/// Structures" provided by the School of Software Engineering of the Faculty 
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////

#include <stdexcept>



//==============================================================================
// class BidiList<T>::Node
//==============================================================================


template<typename T>
typename BidiLinkedList<T>::Node *
BidiLinkedList<T>::Node::insertAfterInternal(Node *insNode)
{
    if (insNode == nullptr || this == nullptr)
        return nullptr;

    Node *afterNode = this->_next;// an element, which was after node
    insNode->_prev = this;
    this->_next = insNode;

    if (afterNode == nullptr)
        return insNode;
    else
    {
        afterNode->_prev = insNode;
        insNode->_next = afterNode;
        return insNode;
    }
}

//==============================================================================
// class B  idiList<T>
//==============================================================================



template<typename T>
BidiLinkedList<T>::~BidiLinkedList()
{
    clear();
}


template<typename T>
void BidiLinkedList<T>::clear()
{
    Node *specialfordelite = _head;
    while (specialfordelite != nullptr)
    {
        Node *killhim = specialfordelite;
        specialfordelite = specialfordelite->_next;
        delete killhim;
    }

}

template<typename T>
size_t BidiLinkedList<T>::getSize()
{
    if (_size == NO_SIZE)
        calculateSize();
    return _size;
}


template<typename T>
void BidiLinkedList<T>::calculateSize()
{
    _size = 0;
    Node *node = _head;
    while (node != nullptr)
    {
        node = node->_next;
        _size++;
    }
}


template<typename T>
typename BidiLinkedList<T>::Node *
BidiLinkedList<T>::getLastNode() const
{
    return _tail;
}


template<typename T>
typename BidiLinkedList<T>::Node *
BidiLinkedList<T>::appendEl(const T &val)
{
    Node *newNode = new Node(val);
    insertNodeAfter(getLastNode(), newNode);
    _tail = newNode;
    return newNode;

}

// возможно, этот метод даже не надо изменять
template<typename T>
typename BidiLinkedList<T>::Node *
BidiLinkedList<T>::insertNodeAfter(Node *node, Node *insNode)
{
    if (insNode == nullptr || insNode->_next != nullptr || insNode->_prev != nullptr)
        throw std::invalid_argument("INA NP");

    if (node == nullptr)
        node = getLastNode();

    if (node == nullptr)
    {
        _head = insNode;
        _tail = insNode;
    } else
    {
        node->insertAfterInternal(insNode);
        if (insNode->_next == nullptr)
            _tail = insNode;
    }

    invalidateSize();
    return insNode;
}

template<typename T>
void
BidiLinkedList<T>::insertNodesAfter(BidiLinkedList::Node *node, BidiLinkedList::Node *beg, BidiLinkedList::Node *end)
{
    if (beg == nullptr || end == nullptr || beg->_prev != nullptr || end->_next != nullptr)
    {
        throw std::invalid_argument("INA");
    }

    if (node == nullptr)
        node = getLastNode();

    if (node == nullptr)
    {
        _head = beg;
        _tail = end;
    } else if (node->_next == nullptr)
    {
        node->_next = beg;
        beg->_prev = node;
        _tail = end;
    } else
    {
        end->_next = node->_next;
        beg->_prev = node;
        node->_next->_prev = end;
        node->_next = beg;
    }
}


// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS

template<typename T>
typename BidiLinkedList<T>::Node *BidiLinkedList<T>::insertNodeBefore(Node *node, Node *insNode)
{
    insertNodesBefore(node, insNode, insNode);
    return insNode;
}


template<typename T>
void BidiLinkedList<T>::insertNodesBefore(Node *node, Node *beg, Node *end)
{
    if (beg == nullptr || end == nullptr || beg->_prev != nullptr || end->_next != nullptr)
        throw std::invalid_argument("INB");

    if (node == nullptr)
        node = getHeadNode();

    if (node == nullptr)
    {
        _head = beg;
        _tail = end;
    } else if (node->_prev == nullptr)
    {
        node->_prev = end;
        end->_next = node;
        _head = beg;
    } else
    {
        end->_next = node;
        beg->_prev = node->_prev;
        node->_prev->_next = beg;
        node->_prev = end;
    }
    invalidateSize();
}


#endif // IWANNAGET10POINTS


template<typename T>
void BidiLinkedList<T>::cutNodes(Node *beg, Node *end)
{
    if (beg == nullptr || end == nullptr)
        throw std::invalid_argument("CNS");

    if (end->_next == nullptr && beg->_prev == nullptr)
    {
        _head = nullptr;
        _tail = nullptr;
    } else if (end->_next == nullptr)
    {
        _tail = beg->_prev;
        beg->_prev->_next = nullptr;
        beg->_prev = nullptr;
    } else if (beg->_prev == nullptr)
    {
        _head = end->_next;
        end->_next->_prev = nullptr;
        end->_next = nullptr;
    } else
    {
        beg->_prev->_next = end->_next;
        end->_next->_prev = beg->_prev;
        beg->_prev = nullptr;
        end->_next = nullptr;
    }
    invalidateSize();
}


template<typename T>
typename BidiLinkedList<T>::Node *
BidiLinkedList<T>::cutNode(Node *node)
{
    cutNodes(node, node);
    return node;
}


template<typename T>
typename BidiLinkedList<T>::Node *
BidiLinkedList<T>::findFirst(Node *startFrom, const T &val)
{
    if (startFrom == nullptr)
        return nullptr;
    Node *findfirst = startFrom;
    while (findfirst != nullptr)
    {
        if (findfirst->getValue() == val)
            return findfirst;

        findfirst = findfirst->_next;
    }

    return nullptr;
}


template<typename T>
typename BidiLinkedList<T>::Node **
BidiLinkedList<T>::findAll(Node *startFrom, const T &val, int &size)
{
    if (!startFrom)
        return nullptr;
    // try not to use any standard containers. create an array only when found a first occurence
    Node **res = nullptr;
    size = 0;
    Node *letsfind = startFrom;
    while (startFrom)
    {
        if (startFrom->getValue() == val)
            size++;

        startFrom = startFrom->_next;
    }

    if (size == 0)
        return nullptr;
    else
        res = new Node *[size];

    int i = 0;

    if (res)
    {
        while (letsfind)
        {
            if (letsfind->getValue() == val)
            {
                res[i] = letsfind;
                i++;
            }
            letsfind = letsfind->_next;
        }
    }

    return res;
}



// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS

template<typename T>
typename BidiLinkedList<T>::Node **
BidiLinkedList<T>::cutAll(Node *startFrom, const T &val, int &size)
{
    Node **letskillhim = findAll(startFrom, val, size);
    int i = 0;
    while (i < size)
    {
        cutNode(letskillhim[i]);
        i++;
    }
    return letskillhim;
}

#endif  //IWANNAGET10POINTS
