#include "Dictionary.h"
#include <functional>
#include <stdexcept>

Dictionary::Node::Node(keyType k, valType v) : 
    key(k), val(v), parent(nullptr), left(nullptr), right(nullptr) {}

Dictionary::Dictionary() : num_pairs(0) {
    nil = new Node("", 0);
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;
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
        n = nn;
        num_pairs++;
    } else {
        n->val = v;
    }
}

void Dictionary::remove(keyType k) {
    Node* p = nil;
    Node*& n = search_r(root, k, p);
    if (n == nil) 
        throw std::logic_error("Dictionary: remove(): key does not exist");
    num_pairs--;
    if (n == current) current = nil;
    Node* _n = n;
    if (n->left == nil) {
        n = n->right; n->parent = p;
        delete _n; return;
    }
    if (n->right == nil) { 
        n = n->left; n->parent = p;
        delete _n; return;
    }
    Node*& y = findMin(n->right);
    if (y == n->right) {
        y->left = n->left;
        y->left->parent = y;
        n = y;
        n->parent = p;
        delete _n;
        return;
    } else {
        Node* _y = y;
        y = y->right;
        y->parent = _y->parent;
        _y->left = n->left;
        _y->left->parent = _y;
        _y->right = n->right;
        _y->right->parent = _y;
        n = _y;
        n->parent = p;
        delete _n;
        return;
    }
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
}

std::string Dictionary::pre_string() const {
    std::function<std::string(Node*)> _pre_str = 
        [&](Node* n) -> std::string {
        if (n == nil) return "";
        return 
            n->key + '\n' 
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

// std::string Dictionary::pretty_tree() const {
//     const std::string p = "+--------";
//     const std::string sp = "|        ";
//     std::function<std::string(Node*,int)> _pretty_tree = 
//         [&](Node *n, int d) -> std::string {
//         if (n == nil) return "(nil)";
//         std::string s;
//         if (d > 0) {
//             for(int i = d; i > 1; i--) s += sp;
//             s += p;
//         }
//         s += '(' + n->key + ',' + std::to_string(n->val) + ')' 
//                 + "<-" + n->parent->key + '\n';
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

