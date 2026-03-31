#include <iostream>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Build BST from level-order traversal
TreeNode* buildBST(int values[], int n) {
    if (n == 0) return nullptr;

    TreeNode* root = new TreeNode(values[0]);
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < n) {
        TreeNode* curr = q.front();
        q.pop();

        // Left child
        if (i < n) {
            TreeNode* leftChild = new TreeNode(values[i]);
            curr->left = leftChild;
            q.push(leftChild);
            i++;
        }

        // Right child
        if (i < n) {
            TreeNode* rightChild = new TreeNode(values[i]);
            curr->right = rightChild;
            q.push(rightChild);
            i++;
        }
    }

    return root;
}

// Find cnt-th largest element using reverse in-order traversal
// (Right -> Root -> Left gives descending order)
void findKthLargest(TreeNode* root, int& cnt, int& result) {
    if (root == nullptr || cnt <= 0) return;

    // Visit right subtree first (larger elements)
    findKthLargest(root->right, cnt, result);

    // Visit current node
    cnt--;
    if (cnt == 0) {
        result = root->val;
        return;
    }

    // Visit left subtree (smaller elements)
    findKthLargest(root->left, cnt, result);
}

// Clean up memory
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    int values[7];
    for (int i = 0; i < 7; i++) {
        cin >> values[i];
    }

    int cnt;
    cin >> cnt;

    // Build BST
    TreeNode* root = buildBST(values, 7);

    // Find cnt-th largest
    int result = -1;
    findKthLargest(root, cnt, result);

    cout << result << endl;

    // Clean up
    deleteTree(root);

    return 0;
}
