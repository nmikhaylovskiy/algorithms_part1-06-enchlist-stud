///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Testing module for BidiList class.
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



#include <gtest/gtest.h>

#include "bidi_linked_list.h"

/** \brief Type alias for a list of integers */
typedef BidiLinkedList<int> IntBidiList;
typedef IntBidiList::Node IntBidiListNode;


TEST(BidiListInt, simpleCreate)
{
    // simply tests is a creation of a list works well
    IntBidiList lst;
    EXPECT_EQ(nullptr, lst.getHeadNode());
    EXPECT_EQ(nullptr, lst.getLastNode());
}

TEST(BidiListInt, emptySize)
{
    IntBidiList lst;
    
    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);
}


TEST(BidiListInt, append1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);
    EXPECT_EQ(nullptr, lst.getHeadNode());
    EXPECT_EQ(nullptr, lst.getLastNode());

    // append first element
    IntBidiListNode* nd1 = lst.appendEl(10);
    sz = lst.getSize();
    EXPECT_EQ(1, sz);
    EXPECT_NE(nullptr, lst.getHeadNode());
    EXPECT_NE(nullptr, lst.getLastNode());
    EXPECT_EQ(lst.getHeadNode(), lst.getLastNode());

    // append second
    IntBidiListNode* nd2 = lst.appendEl(20);
    sz = lst.getSize();
    EXPECT_EQ(2, sz);
    EXPECT_NE(lst.getHeadNode(), lst.getLastNode());

    // test sequence
    EXPECT_EQ(nd1->getNext(), nd2);
    EXPECT_EQ(nd2->getPrev(), nd1);
}

TEST(BidiListInt, insert1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);
    EXPECT_EQ(nullptr, lst.getHeadNode());
    EXPECT_EQ(nullptr, lst.getLastNode());


    // append first element
    IntBidiListNode* nd1 = lst.appendEl(10);
    IntBidiListNode* nd2 = lst.appendEl(20);

    EXPECT_EQ(nd1->getNext(), nd2);
    EXPECT_EQ(nd2->getPrev(), nd1);

    // insert middle element
    IntBidiListNode* nd3 = new IntBidiListNode(15);
    // nd1->insertAfter(nd3);                           // can't proclaim this methos due to encapsulation reqs
    lst.insertNodeAfter(nd1, nd3);
    EXPECT_EQ(nd1->getNext(), nd3);
    EXPECT_EQ(nd3->getNext(), nd2);
    EXPECT_EQ(nd2->getPrev(), nd3);
    EXPECT_EQ(nd3->getPrev(), nd1);

    // insert with a List method
    IntBidiListNode* nd4 = new IntBidiListNode(18);
    lst.insertNodeAfter(nd3, nd4);

    EXPECT_EQ(nd3->getNext(), nd4);
    EXPECT_EQ(nd4->getNext(), nd2);
    EXPECT_EQ(nd4->getPrev(), nd3);
    EXPECT_EQ(nd2->getPrev(), nd4);
}


TEST(BidiListInt, insertAfter1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    
    IntBidiListNode* nd1 = lst.insertNodeAfter(nullptr, new IntBidiListNode(10));
    sz = lst.getSize();
    EXPECT_EQ(1, sz);
    EXPECT_EQ(nd1, lst.getHeadNode());
    EXPECT_EQ(nd1, lst.getLastNode());

    IntBidiListNode* nd2 = lst.insertNodeAfter(nullptr, new IntBidiListNode(20));
    sz = lst.getSize();
    EXPECT_EQ(2, sz);
    EXPECT_EQ(nd1, lst.getHeadNode());
    EXPECT_EQ(nd2, lst.getLastNode());
    EXPECT_EQ(nd1->getNext(), nd2);

    IntBidiListNode* nd3 = lst.insertNodeAfter(nullptr, new IntBidiListNode(30));
    sz = lst.getSize();
    EXPECT_EQ(3, sz);
    EXPECT_EQ(nd1, lst.getHeadNode());
    EXPECT_EQ(nd3, lst.getLastNode());
    EXPECT_EQ(nd1->getNext(), nd2);
    EXPECT_EQ(nd2->getNext(), nd3);
    EXPECT_EQ(nd3->getPrev(), nd2);
    EXPECT_EQ(nd2->getPrev(), nd1);
}




/** \brief Helper function clears memory for given chain of nodes */
void clearNodes(IntBidiListNode* beg, IntBidiListNode* end)
{
    while (beg)
    {
        IntBidiListNode* nxt = beg->getNext();
        delete beg;
        beg = nxt;
    }
}




TEST(BidiListInt, cutNode1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* nd1 = lst.appendEl(10);
    IntBidiListNode* nd2 = lst.appendEl(20);
    IntBidiListNode* nd3 = lst.appendEl(10);
    sz = lst.getSize();
    EXPECT_EQ(3, sz);

    IntBidiListNode* cutNd = lst.cutNode(nd2);
    sz = lst.getSize();
    EXPECT_EQ(2, sz);
    EXPECT_EQ(cutNd, nd2);

    EXPECT_EQ(nd1->getNext(), nd3);
    EXPECT_EQ(nd3->getPrev(), nd1);


    delete cutNd;
}




TEST(BidiListInt, insNodesAfter2)
{
    IntBidiList lst1;

    size_t sz = lst1.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* ndBeg = lst1.appendEl(10);
    IntBidiListNode* nd1 = lst1.appendEl(20);
    IntBidiListNode* nd2 = lst1.appendEl(21);
    IntBidiListNode* nd3 = lst1.appendEl(22);
    IntBidiListNode* ndEnd = lst1.appendEl(30);

    sz = lst1.getSize();
    EXPECT_EQ(5, sz);

    // try to add some chains into another list
    IntBidiList lst2;
    ASSERT_THROW(lst2.insertNodesAfter(nullptr, nd1, nd3), std::invalid_argument);
    ASSERT_THROW(lst2.insertNodesAfter(nullptr, ndBeg, nd3), std::invalid_argument);
    ASSERT_THROW(lst2.insertNodesAfter(nullptr, nd1, ndEnd), std::invalid_argument);
    ASSERT_THROW(lst2.insertNodesAfter(nullptr, nd2, nd2), std::invalid_argument);

    // NOTE: uncheckable wrong operation:
    //ASSERT_THROW(lst2.insertNodesAfter(nullptr, ndBeg, ndEnd), std::invalid_argument);
}


TEST(BidiListInt, findFirst1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* nd1 = lst.appendEl(10);
    IntBidiListNode* nd2 = lst.appendEl(20);
    IntBidiListNode* nd3 = lst.appendEl(10);
    IntBidiListNode* nd4 = lst.appendEl(22);
    IntBidiListNode* nd5 = lst.appendEl(10);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    // search empty
    IntBidiListNode* fnd = lst.findFirst(nullptr, 10);
    EXPECT_EQ(nullptr, fnd);

    // search first
    fnd = lst.findFirst(10);
    EXPECT_EQ(nd1, fnd);

    // search second from the same node
    fnd = lst.findFirst(fnd, 10);
    EXPECT_EQ(nd1, fnd);

    // search second from the next node
    fnd = lst.findFirst(fnd->getNext(), 10);
    EXPECT_EQ(nd3, fnd);

    // search third from the next node
    fnd = lst.findFirst(fnd->getNext(), 10);
    EXPECT_EQ(nd5, fnd);

    // search non-existing fourth
    fnd = lst.findFirst(fnd->getNext(), 10);
    EXPECT_EQ(nullptr, fnd);
}

TEST(BidiListInt, findAll1)
{
    IntBidiList lst;

    IntBidiListNode* nd1;
    IntBidiListNode* nd2;
    IntBidiListNode* nd3;
    IntBidiListNode* nd4;
    IntBidiListNode* nd5;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);
    lst.insertNodeAfter(nullptr, nd1 = new IntBidiListNode(10));
    lst.insertNodeAfter(nullptr, nd2 = new IntBidiListNode(20));
    lst.insertNodeAfter(nullptr, nd3 = new IntBidiListNode(30));
    lst.insertNodeAfter(nullptr, nd4 = new IntBidiListNode(40));
    lst.insertNodeAfter(nullptr, nd5 = new IntBidiListNode(50));
    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    lst.cutNodes(nd3, nd5);
    sz = lst.getSize();
    EXPECT_EQ(2, sz);

}


TEST(BidiListInt, cutFirst1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* nd1 = lst.appendEl(10);
    IntBidiListNode* nd2 = lst.appendEl(20);
    IntBidiListNode* nd3 = lst.appendEl(10);
    IntBidiListNode* nd4 = lst.appendEl(22);
    IntBidiListNode* nd5 = lst.appendEl(10);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    IntBidiListNode* cutNd = lst.cutFirst(10);
    sz = lst.getSize();
    EXPECT_EQ(4, sz);
    EXPECT_EQ(cutNd, nd1);
    delete cutNd;


    cutNd = lst.cutFirst(nd4, 10);
    sz = lst.getSize();
    EXPECT_EQ(3, sz);
    EXPECT_EQ(cutNd, nd5);
    delete cutNd;

}




TEST(BidiListInt, cutNodes1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* ndBeg = lst.appendEl(10);
    IntBidiListNode* nd1 = lst.appendEl(20);
    lst.appendEl(21);
    IntBidiListNode* nd2 = lst.appendEl(22);
    IntBidiListNode* ndEnd = lst.appendEl(30);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    lst.cutNodes(nd1, nd2);
    sz = lst.getSize();
    EXPECT_EQ(2, sz);

    // clear memory
    clearNodes(nd1, nd2);
}

TEST(BidiListInt, cutNodes2)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* ndBeg = lst.appendEl(10);
    IntBidiListNode* nd1 = lst.appendEl(20);
    IntBidiListNode* nd2 = lst.appendEl(21);
    IntBidiListNode* nd3 = lst.appendEl(22);
    IntBidiListNode* ndEnd = lst.appendEl(30);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    lst.cutNodes(ndBeg, nd3);
    sz = lst.getSize();
    EXPECT_EQ(1, sz);

    EXPECT_EQ(ndEnd, lst.getHeadNode());
    EXPECT_EQ(nullptr, ndEnd->getPrev());
    EXPECT_EQ(nullptr, ndEnd->getNext());

    // clear memory
    clearNodes(ndBeg, nd3);
}

TEST(BidiListInt, cutNodes3)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* ndBeg = lst.appendEl(10);
    IntBidiListNode* nd1 = lst.appendEl(20);
    IntBidiListNode* nd2 = lst.appendEl(21);
    IntBidiListNode* nd3 = lst.appendEl(22);
    IntBidiListNode* ndEnd = lst.appendEl(30);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    lst.cutNodes(nd1, ndEnd);
    sz = lst.getSize();
    EXPECT_EQ(1, sz);

    EXPECT_EQ(ndBeg, lst.getHeadNode());
    EXPECT_EQ(nullptr, ndBeg->getPrev());
    EXPECT_EQ(nullptr, ndBeg->getNext());

    // clear memory
    clearNodes(nd1, ndEnd);
}

TEST(BidiListInt, cutNodes4)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* ndBeg = lst.appendEl(10);
    IntBidiListNode* nd1 = lst.appendEl(20);
    IntBidiListNode* nd2 = lst.appendEl(21);
    IntBidiListNode* nd3 = lst.appendEl(22);
    IntBidiListNode* ndEnd = lst.appendEl(30);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    lst.cutNodes(ndBeg, ndEnd);
    sz = lst.getSize();
    EXPECT_EQ(0, sz);

    EXPECT_EQ(nullptr, lst.getHeadNode());

    // clear memory
    clearNodes(ndBeg, ndEnd);
}

// this part of code is active only if you'd like to get the highest mark
#ifdef IWANNAGET10POINTS

TEST(TenPoints, insNodesBefore1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* ndBeg = lst.appendEl(10);
    IntBidiListNode* nd1 = lst.appendEl(20);
    IntBidiListNode* nd2 = lst.appendEl(21);
    IntBidiListNode* nd3 = lst.appendEl(22);
    IntBidiListNode* ndEnd = lst.appendEl(30);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    lst.cutNodes(nd1, nd3);
    sz = lst.getSize();
    EXPECT_EQ(2, sz);

    lst.insertNodesBefore(nullptr, nd1, nd3);
    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    EXPECT_EQ(ndBeg->getNext(), ndEnd);
    EXPECT_EQ(ndEnd->getPrev(), ndBeg);

    EXPECT_EQ(nd3->getNext(), ndBeg);
    EXPECT_EQ(ndBeg->getPrev(), nd3);

    EXPECT_EQ(ndEnd->getNext(), nullptr);
    EXPECT_EQ(ndEnd->getPrev(), ndBeg);


    // put it back
    lst.cutNodes(nd1, nd3);
    sz = lst.getSize();
    EXPECT_EQ(2, sz);

    lst.insertNodesBefore(ndEnd, nd1, nd3);
    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    EXPECT_EQ(ndBeg->getNext(), nd1);
    EXPECT_EQ(nd1->getPrev(), ndBeg);

    EXPECT_EQ(ndEnd->getPrev(), nd3);
    EXPECT_EQ(nd3->getNext(), ndEnd);
}





TEST(TenPoints, insertBefore1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);


    IntBidiListNode* nd1 = lst.insertNodeBefore(nullptr, new IntBidiListNode(30));
    sz = lst.getSize();
    EXPECT_EQ(1, sz);
    EXPECT_EQ(nd1, lst.getHeadNode());
    EXPECT_EQ(nd1, lst.getLastNode());

    IntBidiListNode* nd2 = lst.insertNodeBefore(nullptr, new IntBidiListNode(20));
    sz = lst.getSize();
    EXPECT_EQ(2, sz);
    EXPECT_EQ(nd2, lst.getHeadNode());
    EXPECT_EQ(nd1, lst.getLastNode());
    EXPECT_EQ(nd2->getNext(), nd1);

    IntBidiListNode* nd3 = lst.insertNodeBefore(nullptr, new IntBidiListNode(10));
    sz = lst.getSize();
    EXPECT_EQ(3, sz);
    EXPECT_EQ(nd3, lst.getHeadNode());
    EXPECT_EQ(nd1, lst.getLastNode());
    EXPECT_EQ(nd3->getNext(), nd2);
    EXPECT_EQ(nd2->getNext(), nd1);
    EXPECT_EQ(nd1->getPrev(), nd2);
    EXPECT_EQ(nd2->getPrev(), nd3);
}




TEST(TenPoints, cutAll1)
{
    IntBidiList lst;

    size_t sz = lst.getSize();
    EXPECT_EQ(0, sz);

    IntBidiListNode* nd1 = lst.appendEl(10);
    IntBidiListNode* nd2 = lst.appendEl(20);
    IntBidiListNode* nd3 = lst.appendEl(10);
    IntBidiListNode* nd4 = lst.appendEl(22);
    IntBidiListNode* nd5 = lst.appendEl(10);

    sz = lst.getSize();
    EXPECT_EQ(5, sz);

    // search empty
    int fndSize = 0;
    IntBidiListNode** fnd = lst.cutAll(nullptr, 10, fndSize);
    EXPECT_EQ(nullptr, fnd);

    // search first
    fnd = lst.cutAll(10, fndSize);

    sz = lst.getSize();
    EXPECT_EQ(2, sz);       // only two more elements should be left


    EXPECT_NE(nullptr, fnd);
    EXPECT_EQ(3, fndSize);
    EXPECT_EQ(nd1, fnd[0]);
    EXPECT_EQ(nd3, fnd[1]);
    EXPECT_EQ(nd5, fnd[2]);

    delete[] fnd;


}

#endif // IWANNAGET10POINTS


///////////////////////////// ITERATOR TESTS /////////////////////////////

#ifdef TEST_ITERATOR

TEST(Iterators, simple)
{
    IntBidiList lst;

    lst.appendEl(10);
    lst.appendEl(20);
    lst.appendEl(30);
    lst.appendEl(40);
    lst.appendEl(50);

    std::stringstream ss;

    for (int& it : lst)
        ss << it;
    
    EXPECT_EQ(ss.str(), "1020304050");
}

TEST(Iterators, simpleReverse)
{
    IntBidiList lst;

    lst.appendEl(1);
    lst.appendEl(2);
    lst.appendEl(3);
    lst.appendEl(4);
    lst.appendEl(5);

    std::stringstream ss;

    for (IntBidiList::reverse_iterator it = lst.rbegin(); it != lst.rend(); it++ )
        ss << *it;
    
    EXPECT_EQ(ss.str(), "54321");
}

//TEST(Iterators, simpleConst)
//{
//    IntBidiList lst;
//
//    lst.appendEl(1);
//    lst.appendEl(2);
//    lst.appendEl(3);
//    lst.appendEl(4);
//    lst.appendEl(5);
//
//    std::stringstream ss;
//
//    for (IntBidiList::const_iterator it = lst.cbegin(); it != lst.cend(); ++it )
//        ss << *it;
//
//    EXPECT_EQ(ss.str(), "12345");
//}

// this test is public, because it can cause some difficulties!
TEST(Iterators, arrowOperator)
{
    using namespace std;
    BidiLinkedList<string> lst;

    lst.appendEl("aaa");
    lst.appendEl("bb");
    lst.appendEl("c");
    lst.appendEl("");

    auto it = lst.begin();

    EXPECT_EQ(it->size(), 3);
    ++it;
    EXPECT_EQ(it->size(), 2);
}

// this test is public, because it can cause some difficulties!
TEST(Iterators, endBehavior)
{
    IntBidiList lst;

    lst.appendEl(10);
    lst.appendEl(20);
    lst.appendEl(30);
    
    // should work like in vector: (--end) - the last element of the list.
    EXPECT_EQ(*(--lst.end()), 30);
}

// this test is public, because it can cause some difficulties!
TEST(Iterators, combinedIncrements)
{
    IntBidiList lst;

    lst.appendEl(10);
    lst.appendEl(20);
    lst.appendEl(30);
    lst.appendEl(40);
    lst.appendEl(50);

    auto it = lst.begin();

    EXPECT_EQ(*it, 10);
    EXPECT_EQ(*(++(++it)), 30);
    EXPECT_EQ(*(--(--it)), 10);
}


TEST(Iterators, postfixEncDec)
{
    IntBidiList lst;
    lst.appendEl(1);
    lst.appendEl(12);
    lst.appendEl(3);
    lst.appendEl(4);

    auto iter = lst.begin();

    iter++;
    EXPECT_EQ(*iter, 12);
    iter--;
    EXPECT_EQ(*iter, 1);
}


#else // TEST_ITERATOR
TEST(Iterators, notImplemented)
{
    FAIL();
}
#endif // TEST_ITERATOR
