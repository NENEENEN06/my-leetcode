class Solution {
public:
    void updateParents(vector<int>& parent, vector<list<int>>& children,
                       unordered_map<char, stack<int>>& ancestorsByChar, string& labels, int node) {
        if (!ancestorsByChar[labels[node]].empty()) {
            parent[node] = ancestorsByChar[labels[node]].top();
        }
        ancestorsByChar[labels[node]].push(node);

        for (int child : children[node]) {
            updateParents(parent, children, ancestorsByChar, labels, child);
        }
        ancestorsByChar[labels[node]].pop();
    }

    int countSubtreeSizes(vector<list<int>>& children, int node, vector<int>& result) {
        for (int child : children[node]) {
            result[node] += countSubtreeSizes(children, child, result);
        }
        return result[node];
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string labels) {
        int nodeCount = parent.size();
        vector<list<int>> children(nodeCount);
        vector<int> result(nodeCount, 1);
        unordered_map<char, stack<int>> ancestorsByChar;
        for (int nodeIndex = 1; nodeIndex < nodeCount; nodeIndex++) {
            children[parent[nodeIndex]].push_back(nodeIndex);
        }
        updateParents(parent, children, ancestorsByChar, labels, 0);
        children.assign(nodeCount, {});
        for (int nodeIndex = 1; nodeIndex < nodeCount; nodeIndex++) {
            children[parent[nodeIndex]].push_back(nodeIndex);
        }
        countSubtreeSizes(children, 0, result);
        return result;
    }
};
