#include <iostream>
#include <string>
#include <vector>

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

class BTree
{
    TreeNode* root;
public:

    BTree();
    BTree(TreeNode*);
    TreeNode* find(int64_t);
    bool findSet(int64_t, std::string);
    TreeNode* subtree_max(TreeNode*);
    TreeNode* subtree_min(TreeNode*);
    std::string _max();
    std::string _min();
    bool add(int64_t, std::string);
    TreeNode* tsuccessor(TreeNode*);
    bool Delete(int64_t);
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

    ~BTree()
    {
        delete root;
    }
};
    BTree::BTree()
    {
        this->root = nullptr;
    }

    BTree::BTree(TreeNode* rt)
    {
        this->root = rt;
    }

    TreeNode* BTree::Root()
    {
        return root;
    }

    bool BTree::add(int64_t K, std::string V)
    {
        TreeNode* preInsertPlace = nullptr;
        TreeNode* insertPlace = root;

        while (insertPlace != nullptr)
        {
            preInsertPlace = insertPlace;

            if (insertPlace->key < K)
                insertPlace = insertPlace->right;
            else 
                if (K < insertPlace->key)
                insertPlace = insertPlace->left;
            else 
            if (K == insertPlace->key)
            {
                return true;
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
        return false;
    }

    bool BTree::findSet(int64_t x, std::string V)
    {
        TreeNode* f_el = find(x);
        if (f_el == nullptr)
        {
            return true;
        }
        else f_el->str = V;
        return false;
    }

    TreeNode* BTree::find(int64_t x)
    {
        TreeNode* f_el = root;
        while (f_el != nullptr)
        {
            if (f_el->key < x)
            {
                f_el = f_el->right;
            }
            else if (f_el->key > x)
            {
                f_el = f_el->left;
            }
            else return f_el;
        }
        return nullptr;
    }

    std::string BTree::_max()
    {
        if (root == nullptr)
        {
            return "error";
        }
        else
        {
            TreeNode* curr = root;

            while (curr->right != nullptr)
            {
                curr = curr->right;
            }
            return std::to_string(curr->key) + " " + curr->str;
        }
    }

    std::string BTree::_min()
    {
        if (root == nullptr)
        {
            return "error";
        }
        else
        {
            TreeNode* curr = root;
            while (curr->left != nullptr) curr = curr->left;
            return std::to_string(curr->key) + " " + curr->str;
        }
    }

    TreeNode* BTree::subtree_max(TreeNode* subRoot)
    {
        TreeNode* curr = subRoot;

        while (curr->right != nullptr) curr = curr->right;

        return curr;
    }

    TreeNode* BTree::subtree_min(TreeNode* subRoot)
    {
        TreeNode* curr = subRoot;
        while (curr->left != nullptr) curr = curr->left;
        return curr;
    }

    TreeNode* BTree::tsuccessor(TreeNode* x)
    {
        if (x->right != nullptr) return subtree_min(x->right);
        TreeNode* y = x->parent;
        while (y != nullptr && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    bool BTree::Delete(int64_t key)
    {
        TreeNode* z = find(key);
        TreeNode* y;
        if (z == nullptr)
        {
            return true;
        }
        if (z->left == nullptr)
        {
            y = z;
        }
        else
        {
            y = subtree_max(z->left);
        }
        TreeNode* x;
        if (y->left != nullptr)
        {
            x = y->left;
        }
        else
        {
            x = y->right;
        }
        if (x != nullptr)
        {
            x->parent = y->parent;
        }
        if (y->parent == nullptr) root = x;
        else
        {
            if (y == y->parent->left) y->parent->left = x;
            else y->parent->right = x;
        }
        if (y != z)
        {
            z->key = y->key;
            z->str = y->str;
        }
        y->parent = nullptr;
        y->right = nullptr;
        y->left = nullptr;
        delete y;
        return false;
    }

int main()
{
    std::string str; // строка, которую считываем
    BTree tree;
    int64_t Kint;
    std::string K = "";
    std::string V = "";
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
            if (tree.add(Kint, V))
            {
                std::cout << "error" << std::endl;
            }
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
            if (tree.findSet(Kint, V))
            {
                std::cout << "error" << std::endl;
            }
        }

        if (str.substr(0, 3) == "min")
        {
            std::cout << tree._min() << std::endl;
        }

        if (str.substr(0, 3) == "max")
        {
            std::cout << tree._max() << std::endl;
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
            if (tree.Delete(Kint))
            {
                std::cout << "error" << std::endl;
            }
        }

        if (str.substr(0, 5) == "print")
        {
            tree.Print(&std::cout);
        }
        
        if (str.substr(0, 3) != "add" && str.substr(0, 3) != "set" && str.substr(0, 3) != "min" &&
            str.substr(0, 3) != "max" && str.substr(0, 6) != "search" && str.substr(0, 6) != "delete" && str.substr(0, 5) != "print"
             && !str.empty())
        {
            std::cout << "error" << std::endl;
        }

    }
    return 0;
}