#include <vector>
#include <assert.h>

using namespace std;

class segment_tree{
private:
    int n;
    vector<int> tree;
    // struct tree_node{
    //     int tree_pos;
    //     int start;
    //     int end;
    //     tree_node left_child(){
    //         int mid = (start + end + 1) / 2;
    //         return tree_node{tree_pos*2, start, mid};
    //     }
    //     tree_node right_child() {
    //         int mid = (start + end + 1) / 2;
    //         return {tree_pos*2+1, mid, end};
    //     }
    // };
    // tree_node tree_rrot;
public:
    segment_tree(vector<int> &a) : n(a.size()), tree(n*4) {
        build_tree(a, 0, n, 0);
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
        int x = build_tree(a, start, mid, tree_pos*2) + build_tree(a, start, mid, tree_pos*2+1);
    }
    int get_range(int left, int right) {
        return get_range_(left, right, 0, n, 0);
    }
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
            return get_range_(left, right, start, mid, tree_pos*2);
        } else if (left >= mid) {
            return get_range_(left, right, mid, end, tree_pos*2+1);
        } else {
            return get_range_(left, mid, start, mid, tree_pos*2) + get_range_(mid, right, mid, end, tree_pos*2+1);
        }
    }
};
