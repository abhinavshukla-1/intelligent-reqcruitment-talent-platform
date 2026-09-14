#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

// ================= CANDIDATE =================

struct Candidate {
    int id;
    string name;
    int score;
};

// ================= BINARY SEARCH TREE =================

struct BSTNode {
    Candidate data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Candidate c) {
        data = c;
        left = right = nullptr;
    }
};

BSTNode* insertBST(BSTNode* root, Candidate c) {
    if (root == nullptr)
        return new BSTNode(c);

    if (c.id < root->data.id)
        root->left = insertBST(root->left, c);
    else
        root->right = insertBST(root->right, c);

    return root;
}

void displayBST(BSTNode* root) {
    if (root == nullptr)
        return;

    displayBST(root->left);

    cout << root->data.id << " - "
         << root->data.name << " - Score: "
         << root->data.score << endl;

    displayBST(root->right);
}

// ================= AVL TREE =================

struct AVLNode {
    Candidate data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Candidate c) {
        data = c;
        left = right = nullptr;
        height = 1;
    }
};

int height(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int balanceFactor(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* t = x->right;

    x->right = y;
    y->left = t;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* t = y->left;

    y->left = x;
    x->right = t;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode* insertAVL(AVLNode* root, Candidate c) {
    if (root == nullptr)
        return new AVLNode(c);

    if (c.id < root->data.id)
        root->left = insertAVL(root->left, c);
    else
        root->right = insertAVL(root->right, c);

    root->height =
        max(height(root->left), height(root->right)) + 1;

    int balance = balanceFactor(root);

    if (balance > 1 && c.id < root->left->data.id)
        return rightRotate(root);

    if (balance < -1 && c.id > root->right->data.id)
        return leftRotate(root);

    if (balance > 1 && c.id > root->left->data.id) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && c.id < root->right->data.id) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void displayAVL(AVLNode* root) {
    if (root == nullptr)
        return;

    displayAVL(root->left);
    cout << root->data.id << " - "
         << root->data.name << endl;
    displayAVL(root->right);
}

// ================= MIN HEAP =================

void minHeap(vector<Candidate> candidates) {
    priority_queue<pair<int, string>,
                   vector<pair<int, string>>,
                   greater<pair<int, string>>> heap;

    for (auto c : candidates)
        heap.push({c.score, c.name});

    cout << "\nMin Heap (Lowest Score First):\n";

    while (!heap.empty()) {
        cout << heap.top().second
             << " - Score: "
             << heap.top().first << endl;
        heap.pop();
    }
}

// ================= MAX HEAP =================

void maxHeap(vector<Candidate> candidates) {
    priority_queue<pair<int, string>> heap;

    for (auto c : candidates)
        heap.push({c.score, c.name});

    cout << "\nMax Heap (Highest Score First):\n";

    while (!heap.empty()) {
        cout << heap.top().second
             << " - Score: "
             << heap.top().first << endl;
        heap.pop();
    }
}

// ================= GRAPH =================

class RecruitmentGraph {
private:
    int vertices;
    vector<vector<int>> matrix;
    vector<vector<int>> list;

public:
    RecruitmentGraph(int n) {
        vertices = n;
        matrix.resize(n, vector<int>(n, 0));
        list.resize(n);
    }

    void addEdge(int u, int v) {
        matrix[u][v] = 1;
        matrix[v][u] = 1;

        list[u].push_back(v);
        list[v].push_back(u);
    }

    void displayMatrix() {
        cout << "\nAdjacency Matrix:\n";

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }

    void displayList() {
        cout << "\nAdjacency List:\n";

        for (int i = 0; i < vertices; i++) {
            cout << i << " -> ";

            for (int v : list[i])
                cout << v << " ";

            cout << endl;
        }
    }
};

// ================= MAIN PROGRAM =================

int main() {

    cout << "============================================\n";
    cout << " Intelligent Recruitment and Talent\n";
    cout << " Acquisition Platform\n";
    cout << "============================================\n";

    vector<Candidate> candidates = {
        {101, "Aman", 82},
        {102, "Riya", 95},
        {103, "Karan", 76},
        {104, "Neha", 89},
        {105, "Rahul", 91}
    };

    // Binary Search Tree
    BSTNode* bst = nullptr;

    for (auto c : candidates)
        bst = insertBST(bst, c);

    cout << "\nBinary Search Tree:\n";
    displayBST(bst);

    // AVL Tree
    AVLNode* avl = nullptr;

    for (auto c : candidates)
        avl = insertAVL(avl, c);

    cout << "\nAVL Tree:\n";
    displayAVL(avl);

    // Min Heap
    minHeap(candidates);

    // Max Heap
    maxHeap(candidates);

    // Graph representing candidate-skill-job relationships
    RecruitmentGraph graph(5);

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    graph.displayMatrix();
    graph.displayList();

    return 0;
}
