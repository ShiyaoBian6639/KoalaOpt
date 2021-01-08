#include"performance.h"

int nested_vector_access(Read instance)
{
	auto begin = chrono::steady_clock::now();
	vector<vector<int>> customer;
	customer = instance.customer;
	unsigned i, j, k, total;
	for (k = 0; k < NUM; k++) {
		total = 0;
		for (i = 0; i < customer.size(); i++) {
			for (j = 0; j < customer[0].size(); j++)
				total += customer[i][j];
		}
	}

	cout << total << endl;

	auto end = chrono::steady_clock::now();
	chrono::duration<double> elapsed = end - begin;
	cout << "nested vector accessing takes " << elapsed.count() << " seconds" << endl;

	/* compare with contigeous array */
	begin = chrono::steady_clock::now();
	unsigned n = 1001; unsigned m = 6;
	int** arr = dynamic_array(n, m);
	for (k = 0; k < NUM; k++) {
		total = 0;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				total += arr[i][j];
			}
		}
	}
	cout << total << endl;
	end = chrono::steady_clock::now();
	elapsed = end - begin;
	cout << "contigeous array takes " << elapsed.count() << " seconds" << endl;
	free(arr);
	return total;
}

void dictionary_vs_arr()
{
	int n, m, i, j, k,total, pos;
	n = 1001; m = 6;
	boost::unordered_set<int> dict;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			pos = i * n + j;
			if (pos % 1 == 0)
				dict.insert(pos);
		}
	}
	
	auto begin = chrono::steady_clock::now();
	for (k = 0; k < NUM; k++) {
		total = 0;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				pos = i * n + j;
				if (dict.find(pos) != dict.end())
					total += 99;
			}
		}
	}
	cout << total << endl;
	auto end = chrono::steady_clock::now();
	chrono::duration<double> elapsed = end - begin;
	cout << "dictionary size is: " << dict.size() << endl;

	cout << "dictionary accessing takes " << elapsed.count() << " seconds" << endl;
	
}
void perf_bench()
{
	/* if you are not sure about the best way to implement something.
	* try to benchmark all methods in your mind
	* hopefully you can find one method that is significantly more efficient than others
	*/

	Read input("./data/homberger_1000/C1_10_6.TXT");
	int val = nested_vector_access(input);
	dictionary_vs_arr();
}

int** dynamic_array(unsigned n, unsigned m)
{
	unsigned i, j;
	int** arr = (int**)malloc(n * sizeof(int*));
	if (arr) {
		for (i = 0; i < n; i++) {
			arr[i] = (int*)malloc(m * sizeof(int));
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			arr[i][j] = 99;
		}
	}
	return arr;
}