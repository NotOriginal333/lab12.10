#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

void addNode(TreeNode*& root, int value) {
    if (!root) {
        root = new TreeNode;
        root->data = value;
        root->left = nullptr;
        root->right = nullptr;
    }
    else {
        if (value < root->data) {
            addNode(root->left, value);
        }
        else {
            addNode(root->right, value);
        }
    }
}

void printTree(TreeNode* root) {
    if (!root)
        return;

    printTree(root->left);
    std::cout << root->data << " ";
    printTree(root->right);
}

void deleteNode(TreeNode*& root, int value) {
    if (!root)
        return;

    if (value < root->data) {
        deleteNode(root->left, value);
    }
    else if (value > root->data) {
        deleteNode(root->right, value);
    }
    else {
        if (!root->left && !root->right) {
            delete root;
            root = nullptr;
        }
        else if (!root->left) {
            TreeNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (!root->right) {
            TreeNode* temp = root;
            root = root->left;
            delete temp;
        }
        else {
            TreeNode* minNode = root->right;
            while (minNode->left) {
                minNode = minNode->left;
            }
            root->data = minNode->data;
            deleteNode(root->right, minNode->data);
        }
    }
}

void readNumbersFromFile(const std::string& filename, std::vector<int>& numbers) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    int num;
    while (file >> num) {
        numbers.push_back(num);
    }

    file.close();
}

void deleteNodesInRange(TreeNode*& root, int minVal, int maxVal) {
    if (!root)
        return;

    if (root->data >= minVal && root->data <= maxVal) {
        deleteNode(root, root->data);
        deleteNodesInRange(root, minVal, maxVal);
    }
    else {
        deleteNodesInRange(root->left, minVal, maxVal);
        deleteNodesInRange(root->right, minVal, maxVal);
    }
}

bool search(TreeNode* root, int value) {
    if (!root)
        return false;

    if (root->data == value)
        return true;
    else if (value < root->data)
        return search(root->left, value);
    else
        return search(root->right, value);
}

int main() {
    std::vector<int> numbers;
    readNumbersFromFile("numbers.txt", numbers);

    TreeNode* root = nullptr;
    for (int num : numbers) {
        addNode(root, num);
    }

    std::cout << "Binary Tree before deletion: ";
    printTree(root);
    std::cout << std::endl;

    int minVal = *std::min_element(numbers.begin(), numbers.end());
    int maxVal = *std::max_element(numbers.begin(), numbers.end());
    int midVal = (minVal + maxVal) / 2;

    deleteNodesInRange(root, minVal, midVal);

    std::cout << "Binary Tree after deletion: ";
    printTree(root);
    std::cout << std::endl;

    delete root;

    return 0;
}
