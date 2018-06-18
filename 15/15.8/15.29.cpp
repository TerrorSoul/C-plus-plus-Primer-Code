#include <vector>
#include <iostream>
#include <memory>
#include "..\15.7\15.7.3\Quote.h"
#include "..\15.7\15.7.3\Disc_quote.h"
#include "..\15.7\15.7.4\Bulk_quote.h"

using std::vector;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;

int main() {
	vector<shared_ptr<Quote>> basket;
	basket.push_back(make_shared<Quote>("0-201-82470-1", 50));
	basket.push_back(make_shared<Bulk_quote>("0-201-54858-8", 50, 10, .25));
	double sum_price = 0.0;
	for (auto q : basket) {
		sum_price += q->net_price(15);
	}
	cout << sum_price << endl;
	return 0;
}
