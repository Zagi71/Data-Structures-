#include "List.h"
#include <stdexcept>
#include <cassert>
#include <string>

#define CURSOR_ASSERT() \
    assert(beforeCursor != nullptr && \
           afterCursor != nullptr && \
           beforeCursor->next == afterCursor && \
           afterCursor->prev == beforeCursor)

List::Node::Node(ListElement x) : 
    data(x), next(nullptr), prev(nullptr) {}

List::List() : 
    pos_cursor(0), num_elements(0) {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
}

List::List(const List& L) : List() {
    for(Node *n = L.frontDummy->next; n != L.backDummy; n = n->next) {
        insertBefore(n->data);
    }
    moveFront();
}

List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

int List::length() const {
    return num_elements;
}

ListElement List::front() const {
    if (num_elements == 0 || frontDummy->next == backDummy) {
        throw std::length_error("List: front(): empty List");
    }
    return frontDummy->next->data;
}

ListElement List::back() const {
    if (num_elements == 0 || backDummy->prev == frontDummy) {
        throw std::length_error("List: back(): empty List");
    }
    return backDummy->prev->data;
}

int List::position() const {
    return pos_cursor;
}

ListElement List::peekNext() const {
    if (afterCursor == backDummy) {
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}

ListElement List::peekPrev() const {
    if (beforeCursor == frontDummy) {
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}

void List::clear() {
    moveFront();
    for(;afterCursor != backDummy;) {
        eraseAfter();
    }
}

void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

void List::moveBack() {
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
    pos_cursor = num_elements;
}

ListElement List::moveNext() {
    CURSOR_ASSERT();
    if (afterCursor == backDummy) {
        throw std::range_error("List: moveNext(): cursor at back");
    }
    afterCursor = afterCursor->next;
    beforeCursor = beforeCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

ListElement List::movePrev() {
    CURSOR_ASSERT();
    if (beforeCursor == frontDummy) {
        throw std::range_error("List: moveNext(): cursor at front");
    }
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
    CURSOR_ASSERT();
    Node *newnode = new Node(x);
    newnode->next = afterCursor;
    newnode->prev = beforeCursor;
    afterCursor->prev = newnode;
    beforeCursor->next = newnode;
    afterCursor = newnode;
    num_elements++;
}

void List::insertBefore(ListElement x) {
    CURSOR_ASSERT();
    Node *newnode = new Node(x);
    newnode->next = afterCursor;
    newnode->prev = beforeCursor;
    afterCursor->prev = newnode;
    beforeCursor->next = newnode;
    beforeCursor = newnode;
    num_elements++;
    pos_cursor++;
}

void List::setAfter(ListElement x) {
    CURSOR_ASSERT();
    if (afterCursor == backDummy) {
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
    CURSOR_ASSERT();
    if (beforeCursor == frontDummy) {
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;
}

void List::eraseAfter() {
    CURSOR_ASSERT();
    if (afterCursor == backDummy) {
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    delete afterCursor;
    afterCursor = beforeCursor->next;
    num_elements--;
}

void List::eraseBefore() {
    CURSOR_ASSERT();
    if (beforeCursor == frontDummy) {
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    delete beforeCursor;
    beforeCursor = afterCursor->prev;
    num_elements--;
    pos_cursor--;
}

int List::findNext(ListElement x) {
    for(Node *n = afterCursor; n != backDummy;) {
        if (n->data == x) { this->moveNext(); return pos_cursor; }
        this->moveNext();
        n = afterCursor;
    }
    return -1;
}

int List::findPrev(ListElement x) {
    for(Node *n = beforeCursor; n != frontDummy;) {
        if (n->data == x) { this->movePrev(); return pos_cursor; }
        this->movePrev();
        n = beforeCursor;
    }
    return -1;
}

void List::cleanup() {
    CURSOR_ASSERT();
    int pos = 1;
    for(Node *n = frontDummy->next; n != backDummy;) {
        int val = n->data;
        int p = pos;
        for(Node *r = n->next; r != backDummy;) {
            if (r->data == val) {
                r->prev->next = r->next;
                r->next->prev = r->prev;
                if (r == afterCursor) {
                    afterCursor = r->next;
                } else if (r == beforeCursor) {
                    beforeCursor = r->prev;
                }
                Node *old = r;
                r = r->next;
                delete old;
                num_elements--;
                if (p < pos_cursor) pos_cursor--;
                continue;
            }
            r = r->next;
            p++;
        }
        n = n->next;
        pos++;
    }
}

List List::concat(const List& L) const {
    List res = List();
    for(Node *n = frontDummy->next; n != backDummy; n = n->next) {
        res.insertBefore(n->data);
    }
    for(Node *n = L.frontDummy->next; n != L.backDummy; n = n -> next) {
        res.insertBefore(n->data);
    }
    res.moveFront();
    return res;
}

std::string List::to_string() const {
    std::string s = "(";
    for(Node *n = frontDummy->next; n != backDummy; n = n->next) {
        s += std::to_string(n->data);
        if (n->next != backDummy) s += ", ";
    }
    s += ")";
    return s;
}

bool List::equals(const List &R) const {
    Node *nr = R.frontDummy->next;
    for(Node *n = frontDummy->next; n != backDummy; n = n->next) {
        if (nr == R.backDummy) return false;
        if (nr->data != n->data) return false;
        nr = nr->next;
    }
    return (nr == R.backDummy);
}

std::ostream& operator<<(std::ostream& stream, const List& L) {
    return stream << L.to_string();
}

bool operator==(const List& A, const List& B) {
    return A.equals(B);
}

List& List::operator=(const List& L) {
    clear();
    for(Node *n = L.frontDummy->next; n != L.backDummy; n = n->next) {
        insertBefore(n->data);
    }
    moveFront();
    for(int i = 0; i < L.position(); i++) {
        moveNext();
    }
    return *this;
}
