#include "Dictionary.h"
#include <functional>
#include <stdexcept>

enum { BLACK = 0, RED };

Dictionary::Node::Node(keyType k, valType v) : 
    key(k), val(v), 
    parent(nullptr), left(nullptr), right(nullptr), 
    color(BLACK) {}

Dictionary::Dictionary() : num_pairs(0) {
    nil = new Node("", 0);
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;
    nil->color = BLACK;
    root = nil;
    current = nil;
}

Dictionary::Dictionary(const Dictionary& D) : Dictionary() {
    std::function<void(Node*)> _copy = [&](Node *n) {
        if (n == D.nil) return;
        setValue(n->key, n->val);
        _copy(n->left);
        _copy(n->right);
    };
    _copy(D.root);
}

Dictionary::~Dictionary() {
    clear();
    delete nil;
}

int Dictionary::size() const {
    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    return (search(root, k) != nil);
}

valType& Dictionary::getValue(keyType k) const {
    Node *n = search(root, k);
    if (n == nil) 
        throw std::logic_error("Dictionary: key does not exist\n");
    return n->val;
}

bool Dictionary::hasCurrent() const {
    return current != nil;
}

keyType Dictionary::currentKey() const {
    if (current == nil)
        throw std::logic_error("Dictionary: current not defined\n");
    return current->key;
}

valType& Dictionary::currentVal() const {
    if (current == nil)
        throw std::logic_error("Dictionary: current not defined\n");
    return current->val;
}

void Dictionary::clear() {
    current = nil;
    for(;root != nil;) remove(root->key);
}

void Dictionary::setValue(keyType k, valType v) {
    Node *p = nil;
    Node*& n = search_r(root, k, p);
    if (n == nil) {
        Node* nn = new Node(k, v);
        nn->left = nil;
        nn->right = nil;
        nn->parent = p;
        nn->color = RED;
        n = nn;
        num_pairs++;
        RB_InsertFixUp(nn);
    } else {
        n->val = v;
    }
}

void Dictionary::remove(keyType k) {
    Node* p = nil;
    Node*& n = search_r(root, k, p);
    Node* _n = n;
    if (n == nil) 
        throw std::logic_error("Dictionary: remove(): key does not exist");
    num_pairs--;
    if (n == current) current = nil;
    RB_Delete(n);
    delete _n;
    // Node* _n = n;
    // if (n->left == nil) {
    //     n = n->right; n->parent = p;
    //     delete _n; return;
    // }
    // if (n->right == nil) { 
    //     n = n->left; n->parent = p;
    //     delete _n; return;
    // }
    // Node*& y = findMin(n->right);
    // if (y == n->right) {
    //     y->left = n->left;
    //     y->left->parent = y;
    //     n = y;
    //     n->parent = p;
    //     delete _n;
    //     return;
    // } else {
    //     Node* _y = y;
    //     y = y->right;
    //     y->parent = _y->parent;
    //     _y->left = n->left;
    //     _y->left->parent = _y;
    //     _y->right = n->right;
    //     _y->right->parent = _y;
    //     n = _y;
    //     n->parent = p;
    //     delete _n;
    //     return;
    // }
}

void Dictionary::begin() {
    current = findMin(root);
}

void Dictionary::end() {
    current = findMax(root);
}

void Dictionary::next() {
    if (current == nil)
        throw std::logic_error("Dictionary: current not defined\n");
    if (current->right != nil) { 
        current = findMin(current->right);
        return;
    }
    Node* p = current->parent;
    Node* n = current;
    for(; p != nil && n == p->right; ) {
        n = p;
        p = p->parent;
    }
    current = p;
}

void Dictionary::prev() {
    if (current == nil)
        throw std::logic_error("Dictionary: current not defined\n");
    if (current->left != nil) { 
        current = findMax(current->left);
        return;
    }
    Node* p = current->parent;
    Node* n = current;
    for(; p != nil && n == p->left; ) {
        n = p;
        p = p->parent;
    }
    current = p;
}

std::string Dictionary::to_string() const {
    std::function<std::string(Node*)> _to_str = 
        [&](Node* n) -> std::string {
        if (n == nil) return "";
        return 
            _to_str(n->left)
            + n->key + " : " + std::to_string(n->val) + '\n'
            + _to_str(n->right);
    };
    return _to_str(root);
    // return pretty_tree();
}

std::string Dictionary::pre_string() const {
    std::function<std::string(Node*)> _pre_str = 
        [&](Node* n) -> std::string {
        if (n == nil) return "";
        return 
            n->key + (n->color == RED? " (RED)" : "") + '\n' 
            + _pre_str(n->left) 
            + _pre_str(n->right);
    };
    return _pre_str(root);
}

bool Dictionary::equals(const Dictionary& D) const {
    std::function<bool(Node*)> _subset = 
        [&](Node *n) -> bool {
        if (n == nil) return true;
        if (!(D.contains(n->key) && (D.getValue(n->key) == n->val)))
            return false;
        return _subset(n->right) && _subset(n->left);
    };
    return (num_pairs == D.num_pairs) && _subset(root);
}

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return stream << D.to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    std::function<void(Node*)> _copy = [&](Node *n) {
        if (n == D.nil) return;
        setValue(n->key, n->val);
        _copy(n->left);
        _copy(n->right);
    };
    clear();
    _copy(D.root);
    return *this;
}

void Dictionary::tree_copy(Node *R) {
    if (R == nil) return;
    setValue(R->key, R->val);
    tree_copy(R->left);
    tree_copy(R->right);
}

Dictionary::Node*& Dictionary::search_r(Node*& R, 
                                        keyType k,
                                        Node*& P) const {
    if (R == nil) { return R; }
    if (R->key == k) { P = R->parent; return R; }
    if (k > R->key) { P = R; return search_r(R->right, k, P); }
    else { P = R; return search_r(R->left, k, P); }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil) return R;
    if (R->key == k) return R;
    return (k > R->key) ? search(R->right, k) 
                        : search(R->left, k);
}
Dictionary::Node*& Dictionary::findMin(Node*& R) const {
    if (R == nil) return R;
    if (R->left == nil) return R;
    return findMin(R->left);
}

Dictionary::Node*& Dictionary::findMax(Node*& R) const {
    if (R == nil) return R;
    if (R->right == nil) return R;
    return findMax(R->right);
}

void Dictionary::LeftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nil) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nil) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void Dictionary::RightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != nil) x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == nil) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void Dictionary::RB_InsertFixUp(Node* z) {
    for(; z->parent->color == RED;) {
        if (z->parent == z->parent->parent->left){
            Node* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } 
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RightRotate(z->parent->parent);
            }
        }
        else {
            Node* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } 
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* x) {
    for(; x != root && x->color == BLACK;) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(x->parent);
                x = root;
            }
        }
        else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void Dictionary::RB_Delete(Node* z) {
    Node* y = z;
    Node* x;
    int y_orig_color = y->color;
    if (z->left == nil) {
        x = z->right;
        RB_Transplant(z, z->right);
    }
    else if (z->right == nil) {
        x = z->left;
        RB_Transplant(z, z->left);
    }
    else {
        y = findMin(z->right);
        y_orig_color = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_orig_color == BLACK) RB_DeleteFixUp(x);
}

// std::string Dictionary::pretty_tree() const {
//     const std::string p = "+--------";
//     const std::string sp = "|        ";
//     const std::string b = "black";
//     const std::string r = "red";
//     std::function<std::string(Node*,int)> _pretty_tree = 
//         [&](Node *n, int d) -> std::string {
//         if (n == nil) return "(nil)";
//         std::string s;
//         if (d > 0) {
//             for(int i = d; i > 1; i--) s += sp;
//             s += p;
//         }
//         s += '(' + n->key + ',' + std::to_string(n->val) + ')' 
//                 + "<-" + n->parent->key + "~"
//                 + (n->color == RED? r : b) + '\n';
//         if (n->right != nil) {
//             s += _pretty_tree(n->right, d+1);
//         }
//         if (n->left != nil) {
//             s += _pretty_tree(n->left, d+1);    
//         }
//         return s;
//     };
//     return _pretty_tree(root, 0);
// }

