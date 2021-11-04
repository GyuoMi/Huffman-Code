#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <vector>

using namespace std;

class TreeNode{
public:
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    char value = '*';
    int frequency = -1;

};

// We use this to order the heap
struct cmp
{
	bool operator()(TreeNode *&l,TreeNode *&r)
	{
		// item at front of priority queue will have the lowest freq
		// return l->frequency > r->frequency;
        if (l->frequency > r->frequency)
            return true;
        if (l->frequency == r->frequency)
            return l->value > r->value;
        
        return false;
	}
};

TreeNode *node_alloc(char c, int freq)
{
    TreeNode *curr = new TreeNode();

	curr->value = c;
	curr->frequency = freq;

	return curr;
}

TreeNode *node_merge(TreeNode *l, TreeNode *r)
{
    TreeNode *curr = new TreeNode();

	curr->frequency = l->frequency + r->frequency;
	curr->left = l;
	curr->right = r;

	return curr;
}
void decode(TreeNode* root, int &index, string str)
{
	if (root == nullptr) {
		return;
	}

	// Traverse to the leaf node
	if (!root->left && !root->right)
	{
		cout << root->value;
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}


void createTree(map<char, int> freq, string encoded)
{

    priority_queue<TreeNode*, vector<TreeNode*>, cmp> p_queue;
    for (auto pair: freq) {
		p_queue.push(node_alloc(pair.first, pair.second));
	}

    //we make sure this is > 1 because otherwise we would be trying to merge
    //a single node, with a node that doesn't exist
    while (p_queue.size() != 1)
    {
        TreeNode *l = p_queue.top(); 
        p_queue.pop();
        /* if we set the condition to != -1 this pointer would be left
         as dangling i.e. memory leaks -_-*/
        TreeNode *r = p_queue.top();
        p_queue.pop();

        p_queue.push(node_merge(l, r));
    }

    TreeNode* root = p_queue.top();
    int idx = -1;
    while (idx < (int)encoded.size() - 2)
    {
        decode (root, idx, encoded);
    }

}

int main()
{
    string line = "";
    int num = 0;
    getline(cin, line);

    // Build frequency table
    map<char, int> freq;
    for (int i = 0; i < line.length(); i += 2)
    {
        cin >> num;
        freq[line[i]] = num;
    }
    string encoded = "";
    cin >> encoded;
    createTree(freq, encoded);
    return 0;
}
