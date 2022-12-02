#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update> ordered_set;
//find_by_order(k)->kth largest element
//order_of_key(val)->number of item smaller than val



//st.erase(st.find_by_order(st.order_of_key(val)));
