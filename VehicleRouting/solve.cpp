#include"solve.hpp"
#include"utils.hpp"


vector<vector<float>> Solve::preprocess()
{
	cout << endl << "begin pre-processing: " << endl;
	unsigned n, i, j;
	int cap_vio = 0; int tw_vio = 0;
	n = customer.size();
	vector<vector<float>> dist_mat(n);
	vector<float> row(n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			float distance = dist(customer[i][0], customer[i][1], customer[j][0], customer[j][1]);
			if (customer[i][3] + customer[i][5] + distance >= customer[j][4]) {
				row[j] = -1.0;
				tw_vio++;
			}
			else if (customer[i][2] + customer[j][2] > capacity) {
				row[j] = -1.0;
				cap_vio++;
			} else
				row[j] = distance;
		}
		dist_mat[i] = row;
	}
	/* pre-process statistics */
	int total_violation = cap_vio + tw_vio;
	float tw_percent = float(tw_vio * 100) / (n * n);
	float cap_percent = float(cap_vio * 100) / (n * n);
	float total_percent = float(total_violation * 100) / (n * n);
	cout << tw_vio << " arcs (" << tw_percent <<  "%) are removed due to time window violation" << endl;
	cout << cap_vio << " arcs (" << cap_percent << "%) are removed due to capacity violation" << endl;
	cout << total_violation << " arcs (" << total_percent << "%) are removed in total" << endl;
	return dist_mat;
}

/* sweep heuristics */
vector<float> Solve::coord2angle() // get hte angle of each customer 
{
	vector<float> result(numCustomer);
	int i;
	int depot_x, depot_y;
	depot_x = customer[0][0];
	depot_y = customer[0][1];
	for (int i = 0; i < numCustomer; i++) {
		result[i] = angle(customer[i + 1][1] - depot_y, customer[i + 1][0] - depot_x);
	}
	return result;
}

vector<int> Solve::argsort()
{
	vector<float> customerAngle = coord2angle();
	vector<int> result(customerAngle.size());
	size_t n(0);
	generate(begin(result), end(result), [&] {return n++; });
	sort(begin(result), end(result), [&](int i1, int i2) {return customerAngle[i1] < customerAngle[i2]; });
	return result;
}

void Solve::printAngle() 
{
	vector<int> sequence = argsort();
	vector<float> angleVec = coord2angle();
	for (int i = 0; i < sequence.size(); i++)
		cout << i << " : " << angleVec[sequence[i]] << endl;

};