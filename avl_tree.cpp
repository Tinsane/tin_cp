template<class T>
class AVLTree {
private:
    struct Node {
        Node *Left;
        Node *Right;
        T Key;
        size_t Height;

        Node(Node* left, Node* right, T key) {
            Left = left;
            Right = right;
            Key = key;
            Height = 1;
            if (left) {
                Height = std::max(Height, left->Height + 1);
            }
            if (right) {
                Height = std::max(Height, right->Height + 1);
            }
        }

        explicit Node(T key) : Left(nullptr), Right(nullptr), Key(key), Height(1) {}
    };
    Node *Root;

    static size_t GetHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        } else {
            return node->Height;
        }
    }

    static Node* BalanceLeft(Node* current) {
        if (GetHeight(current->Left) <= GetHeight(current->Right) + 1) {
            return current;
        }
        // need rotation
        if (GetHeight(current->Left->Left) == GetHeight(current->Right)) { // big rotation
            auto left = current->Left;
            auto currentImage = new Node(left->Right->Left, current->Right, current->Key);
            auto leftRightImage = new Node(left->Left, left->Right->Right, left->Right->Key);
            auto leftImage = new Node(leftRightImage, currentImage, left->Key);
            delete left->Right;
            delete left;
            delete current;
            return leftImage;
        } else { //small
            auto currentImage = new Node(current->Left->Right, current->Right, current->Key);
            auto leftImage = new Node(current->Left->Left, currentImage, current->Left->Key);
            delete current->Left;
            delete current;
            return leftImage;
        }
    }

    static Node* BalanceRight(Node* current) {
        if (GetHeight(current->Left) + 1 >= GetHeight(current->Right)) {
            return current;
        }
        // need rotation
        if (GetHeight(current->Right->Right) == GetHeight(current->Left)) { // big rotation
            auto right = current->Right;
            auto currentImage = new Node(current->Left, right->Left->Right, current->Key);
            auto rightLeftImage = new Node(right->Left->Left, right->Right, right->Left->Key);
            auto leftImage = new Node(currentImage, rightLeftImage, right->Key);
            delete right->Left;
            delete right;
            delete current;
            return leftImage;
        } else { //small
            auto currentImage = new Node(current->Left, current->Right->Left, current->Key);
            auto rightImage = new Node(currentImage, current->Right->Right, current->Right->Key);
            delete current->Right;
            delete current;
            return rightImage;
        }
    }

    static Node* InsertNode(Node* current, T key) {
        if (current == nullptr) {
            return new Node(key);
        }
        if (key == current->Key) {
            return current;
        }
        if (key < current->Key) {
            current->Left = InsertNode(current->Left, key);
            return BalanceLeft(current);
        } else {
            current->Right = InsertNode(current->Right, key);
            return BalanceRight(current);
        }
    }

    static Node* GoRight(Node* current) {
        while(current->Right != nullptr) {
            current = current->Right;
        }
        return current;
    }

    static Node* DeleteNode(Node* current, T key) {
        if (current->Key == key) {
            if (current->Left == nullptr) {
                auto result = current->Right;
                delete current;
                return result;
            } else if (current->Right == nullptr) {
                auto result = current->Left;
                delete current;
                return result;
            } else {
                auto replacement = GoRight(current->Left);
                auto replacementKey = replacement->Key;
                current->Left = DeleteNode(current->Left, replacementKey);
                current->Key = replacementKey;
                return BalanceRight(current);
            }
        } else if (key < current->Key) {
            current->Left = DeleteNode(current->Left, key);
            return BalanceRight(current);
        } else {
            current->Right = DeleteNode(current->Right, key);
            return BalanceLeft(current);
        }
    }

    static void PrintKeysFor(Node* current, std::ostream& out) {
        if (current == nullptr) {
            return;
        }
        PrintKeysFor(current->Left, out);
        out << current->Key << ' ';
        PrintKeysFor(current->Right, out);
    }

public:
    AVLTree() = default;

    void Insert(T key) {
        Root = InsertNode(Root, key);
    }

    void Delete(T key) {
        Root = DeleteNode(Root, key);
    }

    void PrintKeys(std::ostream& out) {
        PrintKeysFor(Root, out);
        out << std::endl;
    }
};
