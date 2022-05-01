#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const double LOLLIPOP_PRICE = 5.00; // each lollipop costs Php 5.00
const double VAT_RATE = 0.12; // VAT rate (12%)

int main() {
	int lollipopAmount; // how many lollipops does the customer want?
	double lollipopTotalPrice;
	double customerPayment, customerChange;
	double lollipopVatRate, vatableAmount;
	string arrow = "-> ";

	cout << "Welcome to the Lollipop Factory!" << endl;
	cout << endl;
	cout << "How many would you want to buy? Each sweet and minty lollipop costs 5 pesos. " << arrow;
	cin >> lollipopAmount;

	lollipopTotalPrice = lollipopAmount * LOLLIPOP_PRICE;

	// 2 decimal place workaround for prices
	cout << fixed << showpoint;
	cout << setprecision(2); 

	cout << "You have bought " << lollipopAmount << " lollipops. Please pay PhP " << lollipopTotalPrice << ". " << arrow;
	cin >> customerPayment;

	vatableAmount = lollipopTotalPrice / (VAT_RATE + 1);
	lollipopVatRate = vatableAmount * VAT_RATE;
	customerChange = customerPayment - lollipopTotalPrice;

	cout << endl;
	cout << "Please examine the transaction details below:" << endl;
	cout << endl;

	cout << "Amount Due (VAT inclusive): PhP " << lollipopTotalPrice << endl;
	cout << "VAT (12%): PhP " << lollipopVatRate << endl;
	cout << "VATable Amount: PhP " << vatableAmount << endl;
	cout << "Amount of Cash: PhP " << customerPayment << endl;
	cout << "Change: PhP " << customerChange << endl;
	cout << endl;

	cout << "\"Thanks and enjoy our lollipops!\"" << endl;

	return 0;
}