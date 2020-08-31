#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
	vector<int> perm(9);
	generate(perm.begin(), perm.end(), [] {static int i = 8; return i--; });
	auto max_perm = make_pair(perm, DBL_MIN);
	for_each(perm.begin(), perm.end(), [](int value) { cout << value << ' '; });
	cout.put('\n');
	for (double lenght(0.); prev_permutation(perm.begin(), perm.end()); lenght = 0.) {
		vector<bool> visited(9, false);
		adjacent_find(perm.begin(), perm.end(),
			[&](int first, int second) -> bool {
				int first_x = first % 3, first_y = first / 3, second_x = second % 3, second_y = second / 3;
				if (!visited[second])
					lenght += hypot(first_x - second_x, first_y - second_y);
				visited[first] = true;
				if ((first_x % 2 == second_x % 2) && (first_y % 2 == second_y % 2))
					visited[(first_x + second_x) / 2 + (first_y + second_y) / 2 * 3] = true;
				return visited[second];
			});
		if (lenght > max_perm.second)
			max_perm = { perm , lenght };
	}
	for_each(max_perm.first.begin(), max_perm.first.end(), [](int value) { cout << value << ' '; });
	cout.put('\n');
	cout << "max lenght = " << max_perm.second << '\n';
	return 0;
}