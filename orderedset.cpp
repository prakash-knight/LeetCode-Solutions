#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ordered_set = tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

int main() {
    ordered_set s;

    s.insert(10);
    s.insert(20);
    s.insert(30);
    s.insert(40);
    s.insert(50);

    auto it1 = s.lower_bound(25);
    auto it2 = s.upper_bound(25);

    if(it1 != s.end())
        cout << "Lower Bound = " << *it1 << endl;

    if(it2 != s.end())
        cout << "Upper Bound = " << *it2 << endl;
}