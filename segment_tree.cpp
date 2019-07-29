class segment_tree{
private:
    int n;
    vector<int> tree;
    vector<int> leaves;
    int get_range_(int left, int right, int start, int end, int tree_pos) {
        assert(left >= start && right <= end);
        if (left == right) {
            return 0;
        }
        if (left == start && right == end) {
            return tree[tree_pos];
        }
        int mid = (start + end + 1) / 2;
        if (right <= mid) {
            return get_range_(left, right, start, mid, tree_pos*2+1);
        } else if (left >= mid) {
            return get_range_(left, right, mid, end, tree_pos*2+2);
        } else {
            return get_range_(left, mid, start, mid, tree_pos*2+1) + get_range_(mid, right, mid, end, tree_pos*2+2);
        }
    }
    int build_tree(vector<int> &a, int start, int end, int tree_pos) {
        if (start == end) {
            return 0;
        }
        if (start + 1 == end) {
            tree[tree_pos] = a[start];
            return tree[tree_pos];
        }
        int mid = (start + end + 1) / 2;
        int x = build_tree(a, start, mid, tree_pos*2+1) + build_tree(a, mid, end, tree_pos*2+2);
        tree[tree_pos] = x;
        return x;
    }
public:
    segment_tree(vector<int> &a) : n(a.size()), leaves(a), tree(n*4) {
        build_tree(a, 0, n, 0);
    }

    int get_range(int left, int right) {
        return get_range_(left, right, 0, n, 0);
    }

    void update(int i, int val) {
        int change = val - leaves[i];
        leaves[i] = val;
        int tree_pos = 0, start = 0, end = n;
        while(true) {
            tree[tree_pos] += change;
            if (start + 1 == end) break;
            int mid = (start + end + 1) / 2;
            if (i >= mid) {
                start = mid;
                tree_pos = tree_pos * 2 + 2;
            } else {
                end = mid;
                tree_pos = tree_pos * 2 + 1;
            }
        };
    }
};
