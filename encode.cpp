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
//comparator function to order p_queue
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

void encode(TreeNode* root, string str, map<char, string> &codes)
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		codes[root->value] = str;
	}

	encode(root->left, str + "0", codes);
	encode(root->right, str + "1", codes);
}

void print(string &line, map<char, string> &codes, map<char, int> &freq)
{
    int uncoded = line.length() * 8;
    string coded; // The encoded string

    for (char &c : line)
    {
        coded += codes[c];
    }
    
    for (pair<char, int> v : freq)
    {
        cout << v.first << " ";
    }

    cout << "\n";

    for (pair<char, int> v : freq)
    {
        cout << v.second << " ";
    }

    cout << "\n";
    cout << coded << "\n";
    cout << "Total Bits (Original):" << uncoded << "\n";
    cout << "Total Bits (Coded):" << coded.length() << "\n";
}

void createTree(string line, map<char, int> freq)
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

    map<char, string> codes;
    encode(root, "", codes);
    print (line, codes, freq);
}

int main()
{
    string line = "";
    getline(cin, line);

    // Build frequency table
    map<char, int> freq;
    for (char c: line)
    {
        freq[c]++;
    } 

    // Create the tree
    // Encode the string
    // Output encoding
    createTree(line, freq);

    return 0;
}
