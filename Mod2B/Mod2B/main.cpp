#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

struct TreeNode
{
    int64_t key;
    std::string str;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int64_t& key, std::string& V)
    {
        this->key = key;
        this->str = V;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
    ~TreeNode()
    {
        delete left;
        delete right;
    }
};

class SplayTree
{
    TreeNode* root;

    void zig(TreeNode*);
    void zig_zig(TreeNode*);
    void zig_zag(TreeNode*);
    void splay(TreeNode*);

public:
    SplayTree();
    SplayTree(TreeNode*);
    TreeNode* find(int64_t);
    TreeNode* findSet(int64_t, std::string);
    TreeNode* subtree_max(TreeNode*);
    TreeNode* subtree_min(TreeNode*);
    void _max();
    void _min();
    void insert(int64_t,std::string);
    void Delete(int64_t);
    TreeNode* Root();

    void Print(std::ostream* stream) {
        std::string TREE = "";
        if (root == nullptr) {
            std::cout << "_" << std::endl;
            return;
        }
        TREE += '[' + std::to_string(root->key) + ' ' + root->str + ']' + '\n';
        std::vector<TreeNode*> que;
        bool is_end = true;
        que.push_back(root->left);
        que.push_back(root->right);
        if (root->left != nullptr) is_end = false;
        if (root->right != nullptr) is_end = false;
        int level = 1;
        int it = 0;
        while (1)
        {
            if (is_end)
            {
                (*stream) << TREE;
                return;
            }
            is_end = true;
            for (int i = 0; i < level; i++)
            {
                if (que[it] != nullptr)
                {
                    TREE += '[' + std::to_string(que[it]->key) + ' ' + que[it]->str + ' ' + std::to_string(que[it]->parent->key)
                        + ']';
                    que.push_back(que[it]->left);
                    if (que[it]->left != nullptr) is_end = false;
                    que.push_back(que[it]->right);
                    if (que[it]->right != nullptr) is_end = false;
                    //que.pop();
                    it++;
                }
                else
                {
                    TREE += '_';
                    que.push_back(nullptr);
                    que.push_back(nullptr);
                    //que.pop();
                    it++;
                }
                TREE += ' ';
                if (que[it] != nullptr)
                {
                    TREE += '[' + std::to_string(que[it]->key) + ' ' + que[it]->str + ' ' + std::to_string(que[it]->parent->key)
                        + ']';
                    que.push_back(que[it]->left);
                    if (que[it]->left != nullptr) is_end = false;
                    que.push_back(que[it]->right);
                    if (que[it]->right != nullptr) is_end = false;
                    //que.pop();
                    it++;
                }
                else
                {
                    TREE += '_';
                    que.push_back(nullptr);
                    que.push_back(nullptr);
                    //que.pop();
                    it++;
                }
                if (i == level - 1)
                {
                    TREE += '\n';
                }
                else
                {
                    TREE += ' ';
                }
            }
            level = 2 * level;
        }
    }


    ~SplayTree()
    {
        delete root;
    }
};

TreeNode* SplayTree::Root()
{
    return root;
}

void SplayTree::zig(TreeNode* x)
{
    TreeNode* p = x->parent;
    if (p->left == x)
    {
        TreeNode* A = x->left;
        TreeNode* B = x->right;
        TreeNode* C = p->right;

        x->parent = nullptr;
        x->right = p;

        p->parent = x;
        p->left = B;

        if (B != nullptr) B->parent = p;
    }
    else
    {
        TreeNode* A = p->left;
        TreeNode* B = x->left;
        TreeNode* C = x->right;

        x->parent = nullptr;
        x->left = p;

        p->parent = x;
        p->right = B;

        if (B != nullptr) B->parent = p;
    }
}

void SplayTree::zig_zig(TreeNode* x)
{
    TreeNode* p = x->parent;
    TreeNode* g = p->parent;
    if (p->left == x)
    {
        TreeNode* A = x->left;
        TreeNode* B = x->right;
        TreeNode* C = p->right;
        TreeNode* D = g->right;

        x->parent = g->parent;
        x->right = p;

        p->parent = x;
        p->left = B;
        p->right = g;

        g->parent = p;
        g->left = C;


        if (x->parent != nullptr)
        {
            if (x->parent->left == g) x->parent->left = x;
            else x->parent->right = x;
        }

        if (B != nullptr) B->parent = p;

        if (C != nullptr) C->parent = g;
    }
    else
    {
        TreeNode* A = g->left;
        TreeNode* B = p->left;
        TreeNode* C = x->left;
        TreeNode* D = x->right;

        x->parent = g->parent;
        x->left = p;

        p->parent = x;
        p->left = g;
        p->right = C;

        g->parent = p;
        g->right = B;

        if (x->parent != nullptr)
        {
            if (x->parent->left == g) x->parent->left = x;
            else x->parent->right = x;
        }

        if (B != nullptr) B->parent = g;

        if (C != nullptr) C->parent = p;
    }
}

void SplayTree::zig_zag(TreeNode* x)
{
    TreeNode* p = x->parent;
    TreeNode* g = p->parent;
    if (p->right == x)
    {
        TreeNode* A = p->left;
        TreeNode* B = x->left;
        TreeNode* C = x->right;
        TreeNode* D = g->right;

        x->parent = g->parent;
        x->left = p;
        x->right = g;

        p->parent = x;
        p->right = B;

        g->parent = x;
        g->left = C;

        if (x->parent != nullptr)
        {
            if (x->parent->left == g) x->parent->left = x;
            else x->parent->right = x;
        }

        if (B != nullptr) B->parent = p;

        if (C != nullptr) C->parent = g;
    }
    else
    {
        TreeNode* A = g->left;
        TreeNode* B = x->left;
        TreeNode* C = x->right;
        TreeNode* D = p->right;

        x->parent = g->parent;
        x->left = g;
        x->right = p;

        p->parent = x;
        p->left = C;

        g->parent = x;
        g->right = B;

        if (x->parent != nullptr)
        {
            if (x->parent->left == g) x->parent->left = x;
            else x->parent->right = x;
        }

        if (B != nullptr) B->parent = g;

        if (C != nullptr) C->parent = p;
    }
}

void SplayTree::splay(TreeNode* x)
{
    while (x->parent != nullptr)
    {
        TreeNode* p = x->parent;
        TreeNode* g = p->parent;
        if (g == nullptr) zig(x);
        else if (g->left == p && p->left == x) zig_zig(x);
        else if (g->right == p && p->right == x) zig_zig(x);
        else zig_zag(x);
    }
    this->root = x;
}

SplayTree::SplayTree()
{
    this->root = nullptr;
}

SplayTree::SplayTree(TreeNode* rt)
{
    this->root = rt;
}

TreeNode* SplayTree::find(int64_t x)
{
    TreeNode* ret = nullptr;
    TreeNode* curr = this->root;
    TreeNode* prev = nullptr;
    while (curr != nullptr)
    {
        prev = curr;
        if (x < curr->key) curr = curr->left;
        else if (x > curr->key) curr = curr->right;
        else
        {
            ret = curr;
            break;
        }
    }
    if (ret !=nullptr) splay(ret);
    else if (prev != nullptr) splay(prev);
    return ret;
}

TreeNode* SplayTree::findSet(int64_t x, std::string V)
{
    if (root == nullptr)
    {
        std::cout << "error" << std::endl;
        return nullptr;
    }
    TreeNode* ret = nullptr;
    TreeNode* curr = this->root;
    TreeNode* prev = nullptr;
    while (curr != nullptr)
    {
        prev = curr;
        if (x < curr->key) curr = curr->left;
        else if (x > curr->key) curr = curr->right;
        else
        {
            ret = curr;
            break;
        }
    }
    if (ret != nullptr)
    {
        splay(ret);
        ret->str = V;
    }
    else if (prev != nullptr)
    {
        std::cout << "error" << std::endl;
        splay(prev);
    }
    return ret;
}

void SplayTree::insert(int64_t K, std::string V)
{
    TreeNode* preInsertPlace = nullptr;
    TreeNode* insertPlace = root;

    while (insertPlace != nullptr) {
        preInsertPlace = insertPlace;

        if (insertPlace->key < K)
            insertPlace = insertPlace->right;
        else if (K < insertPlace->key)
            insertPlace = insertPlace->left;
        else if (K == insertPlace->key)
        {
            splay(insertPlace);
            std::cout << "error" << std::endl;
            return;
        }
    }

    TreeNode* insertElement = new TreeNode(K, V);
    insertElement->parent = preInsertPlace;

    if (preInsertPlace == nullptr)
        root = insertElement;
    else if (preInsertPlace->key < insertElement->key)
        preInsertPlace->right = insertElement;
    else if (insertElement->key < preInsertPlace->key)
        preInsertPlace->left = insertElement;

    splay(insertElement);
}

TreeNode* SplayTree::subtree_max(TreeNode* subRoot)
{
    TreeNode* curr = subRoot;

    while (curr->right != nullptr) curr = curr->right;

    return curr;
}

TreeNode* SplayTree::subtree_min(TreeNode* subRoot)
{
    TreeNode* curr = subRoot;
    while (curr->left != nullptr) curr = curr->left;
    return curr;
}

void SplayTree::_max()
{
    if (root == nullptr)
    {
        std::cout << "error" << std::endl;
    }
    else
    {
        TreeNode* curr = root;

        while (curr->right != nullptr) curr = curr->right;
        std::cout << curr->key << " " << curr->str << std::endl;
        splay(curr);
    }
}

void SplayTree::_min()
{
    if (root == nullptr)
    {
        std::cout << "error" << std::endl;
    }
    else
    {
        TreeNode* curr = root;
        while (curr->left != nullptr) curr = curr->left;
        std::cout << curr->key << " " << curr->str << std::endl;
        splay(curr);
    }
}

void SplayTree::Delete(int64_t x)
{
    TreeNode* del = find(x);
    if (del == nullptr)
    {
        std::cout << "error" << std::endl;
        return;
    }
    TreeNode* L = del->left;
    TreeNode* R = del->right;
    del->left = nullptr;
    del->right = nullptr;
    delete del;
    if(L != nullptr) L->parent = nullptr;
    if(R!= nullptr) R->parent = nullptr;
    if (L == nullptr && R == nullptr)
    {
        this->root = nullptr;
    }
    else if (L == nullptr)
    {
        root = R;
    }
    else if (R == nullptr)
    {
        root = L;
    }
    else
    {
        root = L;
        TreeNode* M = subtree_max(L);
        splay(M);
        M->right = R;
        R->parent = M;
    }
}

int main()
{
    std::string str; // строка, которую считываем
    SplayTree tree;
    int64_t Kint;
    std::string K = "";
    std::string V = "";
    int NumofVer = 0; // кол-во вершин
    while (getline(std::cin, str))
    {
        if (str.substr(0, 3) == "add")
        {
            int i = 4;
            V = "";
            K = "";
            while (str[i] != ' ')
            {
                K += str[i];
                i++;
            }
            i++;
            while (str[i] != '\0')
            {
                V += str[i];
                i++;
            }
            Kint = std::stoll(K);
            tree.insert(Kint, V);
            NumofVer++;
        }

        if (str.substr(0, 3) == "set")
        {
            int i = 4;
            K = "";
            V = "";
            while (str[i] != ' ')
            {
                K += str[i];
                i++;
            }
            i++;
            while (str[i] != '\0')
            {
                V += str[i];
                i++;
            }
            Kint = std::stoll(K);
            tree.findSet(Kint, V);
        }

        if (str.substr(0, 3) == "min")
        {
            tree._min();
        }

        if (str.substr(0, 3) == "max")
        {
            tree._max();
        }

        if (str.substr(0, 6) == "search")
        {
            int i = 7;
            K = "";
            V = "";
            while (str[i] != '\0')
            {
                K += str[i];
                i++;
            }
            Kint = std::stoll(K);
            std::string s = "";
            TreeNode* ptr = tree.find(Kint);
            if (ptr != nullptr)
            {
                std::cout << true << " " << ptr->str << std::endl;
            }
            else
            {
                std::cout << false << std::endl;
            }
        }

        if (str.substr(0, 6) == "delete")
        {
            int i = 7;
            K = "";
            while (str[i] != '\0')
            {
                K += str[i];
                i++;
            }
            Kint = std::stoll(K);
            tree.Delete(Kint);
            
        }

        if (str.substr(0, 5) == "print")
        {
            tree.Print(&std::cout);
        }
    }
    //delete tree;
    return 0;
}