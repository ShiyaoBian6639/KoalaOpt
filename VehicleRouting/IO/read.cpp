
#include"read.h"

/* class methods of "Read" */
string Read::getFileName() {
	return fileName;
}

void Read::read() {
	ifstream instance;
	instance.open(fileName);
	vector<int> current(6);
	int i;
	if (instance.is_open()) {
		auto start = chrono::steady_clock::now();
		string line;

		/* get instance name */
		getline(instance, line);
		while (line == "") {
			getline(instance, line);
		}
		instanceName = line;

		/* get vehicle number and capacity */
		getline(instance, line);
		while (line != "VEHICLE") {
			getline(instance, line); 
		}
		getline(instance, line); /* skip NUMBER    CAPACITY */
		instance >> numVehicle >> capacity;

		/* get customer data */
		getline(instance, line);
		while (line != "CUSTOMER") {
			getline(instance, line);
		}
		getline(instance, line);

		int id, x, y, demand, ready, due, service;
	
		while (instance >> id >> x >> y >> demand >> ready >> due >> service) {
			current[0] = x; current[1] = y; current[2] = demand; current[3] = ready; current[4] = due; current[5] = service;
			customer.push_back(current);
		}
		auto end = chrono::steady_clock::now();
		chrono::duration<double> elapsed = end - start;

		numCustomer = customer.size() - 1;
		cout << endl << "reading instance '" << instanceName << "' takes " << elapsed.count() << " seconds" << endl;
		cout << "instance contains " << numCustomer << " customers" << endl;
		cout << "fleet size is: " << numVehicle << endl;
		cout << "vehicle capacity is: " << capacity << endl;

		instance.close();
	}
	else {
		cout << "instance " << fileName << " is not valid!" << endl;
	}
}

void Read::printCustomer(void)
{
	int i, j;
	cout << "Customer data is: " << endl;
	for (i = 0; i < customer.size(); i++) {
		vector<int> current;
		current = customer[i];
		for (j = 0; j < 6; j++)
			cout << current[j] << " ";
		cout << endl;
	}
}

