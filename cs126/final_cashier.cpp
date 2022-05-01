#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <numeric>
#include <cctype>

using namespace std;

// ---------------- variable start ---------------- //
string item_desc;															  // description
string item1, item2, item3, item4, item5, item6, item7, item8, item9, item10; // list of items

const string TAB = "	"; // indents for selected item/quantity/customer cash+change entry
const string SEPARATOR = "|"; // for the table in message()

// self-explanatory
int selected_item, item_quantity;
float item_price, items_subtotal, items_totalamt, customer_cash, customer_change;

// for change breakdown
const int ONEK_PESOS = 1000;
const int FIVEH_PESOS = 500;
const int TWOH_PESOS = 200;
const int ONEH_PESOS = 100;
const int FIFTY_PESOS = 50;
const int TWENTY_PESOS = 20;
const int TEN_PESOS = 10;
const int FIVE_PESOS = 5;
const int ONE_PESO = 1;
const float TWENTY_FIVE_CENTAVO = 0.25;
const float TEN_CENTAVO = 0.10;
const float FIVE_CENTAVO = 0.05;
const float ONE_CENTAVO = 0.01;

// 1 peso = 100 centavos; used only in change_amount_calculate()
const int THOUSANDS = 100000;
const int FIVE_HUNDREDS = 50000;
const int TWO_HUNDREDS = 20000;
const int HUNDREDS = 10000;
const int FIFTIES = 5000;
const int TWENTIES = 2000;
const int TENS = 1000;
const int FIVES = 500;
const int ONES = 100;
const int TWENTY_FIVE_CENTAVOS = 25;
const int TEN_CENTAVOS = 10;
const int FIVE_CENTAVOS = 5;
const int CENTS_TO_PESO = 100;

// change for each bill/coin
float ch_1k, ch_500, ch_200, ch_100, ch_50, ch_20, ch_10, ch_5, ch_1,
	  ch_0_25, ch_0_10, ch_0_05, ch_0_01;

// amounts of each bill/coin used (ex. 2x 1k bills, 5x 500 bills, etc.)
int am_1k, am_500, am_200, am_100, am_50, am_20, am_10, am_5, am_1,
	am_0_25, am_0_10, am_0_05, am_0_01;

char response(char);
char transaction_bool, resp_temp;

vector<float> customer_cart{};

// item format: 	 itemcode,  itemdesc, 			    itemprice
vector<string> item_list{"100", "Sweet 'n Ripe Grapes", "125.35",
						 "101", "Crunchy Apples", 		"52.20",
						 "102", "Roast Chicken", 		"458.00",
						 "103", "Orange Juice", 		"26.50",
						 "104", "Chocolate Biscuits", 	"84.75",
						 "105", "Vanilla Ice Cream", 	"550.00",
						 "106", "Assorted Candy Packs", "65.25",
						 "107", "Water Bottle", 		"15.00",
						 "108", "Vegetable Salad", 		"130.65",
						 "109", "Green Peas", 			"25.75"};

// ---------------- variable end ---------------- //

void message(void)
{
	item1  = "100        | Sweet 'n Ripe Grapes   | 125.35";
	item2  = "101        | Crunchy Apples         | 52.20";
	item3  = "102        | Roast Chicken          | 458.00";
	item4  = "103        | Orange Juice           | 26.50";
	item5  = "104        | Chocolate Biscuits     | 84.75";
	item6  = "105        | Vanilla Ice Cream      | 550.00";
	item7  = "106        | Assorted Candy Packs   | 65.25";
	item8  = "107        | Water Bottle           | 15.00";
	item9  = "108        | Vegetable Salad        | 130.65";
	item10 = "109        | Green Peas             | 25.75";

	cout << "Welcome to CS126 Mart!" << endl
		 << endl
		 << "Item Codes " << SEPARATOR << " Description	    " << SEPARATOR << " Price" << endl
		 << "-------------------------------------------------" << endl
		 << item1 << endl
		 << item2 << endl
		 << item3 << endl
		 << item4 << endl
		 << item5 << endl
		 << item6 << endl
		 << item7 << endl
		 << item8 << endl
		 << item9 << endl
		 << item10 << endl;
}

int item_select_display(string x, float y) // x: description, y: price
{
	cout << TAB << "Selected item: " << x << " (Price: " << y << ")" << endl;

	return 0;
}

float compute_quantity(string a, int b, float c) // a: description, b: quantity, c: price
{
	while (true)
	{
		cout << TAB << TAB << "Enter quantity of item \"" << a << "\": ";
		cin >> b;

		if (b <= 0)
		{
			cout << TAB << "Invalid quantity, please enter again." << endl
				 << endl;
			continue;
		}
		else
		{
			return (c * b);
		}
		break;
	}
}

void reset_all_variables(void)
{
	item_price = 0;
	item_quantity = 0;
	items_subtotal = 0;
	items_totalamt = 0;
	customer_change = 0;

	// change in pesos
	ch_1k = 0;
	ch_500 = 0;
	ch_200 = 0;
	ch_100 = 0;
	ch_50 = 0;
	ch_20 = 0;
	ch_10 = 0;
	ch_5 = 0;
	ch_1 = 0;
	ch_0_25 = 0;
	ch_0_10 = 0;
	ch_0_05 = 0;
	ch_0_01 = 0;

	// amounts of each bill/coin used for ^
	am_1k = 0;
	am_500 = 0;
	am_200 = 0;
	am_100 = 0;
	am_50 = 0;
	am_20 = 0;
	am_10 = 0;
	am_5 = 0;
	am_1 = 0;
	am_0_25 = 0;
	am_0_10 = 0;
	am_0_05 = 0;
	am_0_01 = 0;

	customer_cart.clear();
}

float change_amount_calculate(float i)
{
	int decimal_amt;
	int peso_amt;

	peso_amt = static_cast<int>(i);
	decimal_amt = (i - peso_amt) * 100;
	
	int ch_temp_in_cents;

	ch_temp_in_cents = decimal_amt + (peso_amt * CENTS_TO_PESO);

	// 1,000
	am_1k = ch_temp_in_cents / THOUSANDS;
	ch_1k = am_1k * ONEK_PESOS;
	ch_temp_in_cents = ch_temp_in_cents % THOUSANDS;

	// 500
	am_500 = ch_temp_in_cents / FIVE_HUNDREDS;
	ch_500 = am_500 * FIVEH_PESOS;
	ch_temp_in_cents = ch_temp_in_cents % FIVE_HUNDREDS;

	// 200
	am_200 = ch_temp_in_cents / TWO_HUNDREDS;
	ch_200 = am_200 * TWOH_PESOS;
	ch_temp_in_cents = ch_temp_in_cents % TWO_HUNDREDS;
	
	// 100
	am_100 = ch_temp_in_cents / HUNDREDS;
	ch_100 = am_100 * ONEH_PESOS;
	ch_temp_in_cents = ch_temp_in_cents % HUNDREDS;

	// 50
	am_50 = ch_temp_in_cents / FIFTIES;
	ch_50 = am_50 * FIFTY_PESOS;
	ch_temp_in_cents = ch_temp_in_cents % FIFTIES;

	// 20
	am_20 = ch_temp_in_cents / TWENTIES;
	ch_20 = am_20  * TWENTY_PESOS;
	ch_temp_in_cents = ch_temp_in_cents % TWENTIES;

	// 10
	am_10 = ch_temp_in_cents / TENS;
	ch_10 = am_10 * TEN_PESOS;
	ch_temp_in_cents = ch_temp_in_cents % TENS;

	// 5
	am_5 = ch_temp_in_cents / FIVES;
	ch_5 = am_5 * FIVE_PESOS;
	ch_temp_in_cents = ch_temp_in_cents % FIVES;

	// 1
	am_1 = ch_temp_in_cents / ONES;
	ch_1 = am_1 * ONE_PESO;
	ch_temp_in_cents = ch_temp_in_cents % ONES;

	// 0.25
	am_0_25 = ch_temp_in_cents / TWENTY_FIVE_CENTAVOS;
	ch_0_25 = am_0_25 * TWENTY_FIVE_CENTAVO;
	ch_temp_in_cents = ch_temp_in_cents % TWENTY_FIVE_CENTAVOS;

	// 0.10
	am_0_10 = ch_temp_in_cents / TEN_CENTAVOS;
	ch_0_10 = am_0_10 * TEN_CENTAVO;
	ch_temp_in_cents = ch_temp_in_cents % TEN_CENTAVOS;

	// 0.05
	am_0_05 = ch_temp_in_cents / FIVE_CENTAVOS;
	ch_0_05 = am_0_05 * FIVE_CENTAVO;
	ch_temp_in_cents = ch_temp_in_cents % FIVE_CENTAVOS;

	// 0.01
	am_0_01 = ch_temp_in_cents;
	ch_0_01 = am_0_01 * ONE_CENTAVO;

	return 0;
}

void change_breakdown_display(void)
{
	cout << "=========== CHANGE BREAKDOWN ==========" << endl
		 << ONEK_PESOS 			<< TAB << am_1k 	<< TAB << ch_1k 	<< endl
		 << FIVEH_PESOS 		<< TAB << am_500 	<< TAB << ch_500 	<< endl
		 << TWOH_PESOS 			<< TAB << am_200 	<< TAB << ch_200 	<< endl
		 << ONEH_PESOS 			<< TAB << am_100 	<< TAB << ch_100 	<< endl
		 << FIFTY_PESOS 		<< TAB << am_50 	<< TAB << ch_50 	<< endl
		 << TWENTY_PESOS 		<< TAB << am_20 	<< TAB << ch_20 	<< endl
		 << TEN_PESOS 			<< TAB << am_10 	<< TAB << ch_10 	<< endl
		 << FIVE_PESOS 			<< TAB << am_5 		<< TAB << ch_5 		<< endl
		 << ONE_PESO 			<< TAB << am_1 		<< TAB << ch_1 		<< endl
		 << TWENTY_FIVE_CENTAVO << TAB << am_0_25 	<< TAB << ch_0_25 	<< endl
		 << TEN_CENTAVO 		<< TAB << am_0_10 	<< TAB << ch_0_10 	<< endl
		 << FIVE_CENTAVO 		<< TAB << am_0_05 	<< TAB << ch_0_05 	<< endl
		 << ONE_CENTAVO 		<< TAB << am_0_01 	<< TAB << ch_0_01 	<< endl
		 << "=======================================" << endl
		 << endl;
}

// main
int main()
{
	// 2 decimal place workaround for prices
	cout << fixed << showpoint;
	cout << setprecision(2);

	while (true)
	{
		message();

		while (true) // item selection
		{
			cout << endl
				 << "Enter item code: ";
			cin >> selected_item;

			switch (selected_item)
			{
			case 0:
				break;
			case 100: // 0
				item_desc = item_list[1];
				item_price = stof(item_list[2]);

				item_select_display(item_desc, item_price);
				items_subtotal = compute_quantity(item_desc, item_quantity, item_price);
				cout << TAB << TAB << "Subtotal: " << items_subtotal << endl;

				customer_cart.push_back(items_subtotal);
				continue;
			case 101: // 3
				item_desc = item_list[4];
				item_price = stof(item_list[5]);

				item_select_display(item_desc, item_price);
				items_subtotal = compute_quantity(item_desc, item_quantity, item_price);
				cout << TAB << TAB << "Subtotal: " << items_subtotal << endl;

				customer_cart.push_back(items_subtotal);
				continue;
			case 102: // 6
				item_desc = item_list[7];
				item_price = stof(item_list[8]);

				item_select_display(item_desc, item_price);
				items_subtotal = compute_quantity(item_desc, item_quantity, item_price);
				cout << TAB << TAB << "Subtotal: " << items_subtotal << endl;

				customer_cart.push_back(items_subtotal);
				continue;
			case 103: // 9
				item_desc = item_list[10];
				item_price = stof(item_list[11]);

				item_select_display(item_desc, item_price);
				items_subtotal = compute_quantity(item_desc, item_quantity, item_price);
				cout << TAB << TAB << "Subtotal: " << items_subtotal << endl;

				customer_cart.push_back(items_subtotal);
				continue;
			case 104: // 12
				item_desc = item_list[13];
				item_price = stof(item_list[14]);

				item_select_display(item_desc, item_price);
				items_subtotal = compute_quantity(item_desc, item_quantity, item_price);
				cout << TAB << TAB << "Subtotal: " << items_subtotal << endl;

				customer_cart.push_back(items_subtotal);
				continue;
			case 105: // 15
				item_desc = item_list[16];
				item_price = stof(item_list[17]);

				item_select_display(item_desc, item_price);
				items_subtotal = compute_quantity(item_desc, item_quantity, item_price);
				cout << TAB << TAB << "Subtotal: " << items_subtotal << endl;

				customer_cart.push_back(items_subtotal);
				continue;
			case 106: // 18
				item_desc = item_list[19];
				item_price = stof(item_list[20]);

				item_select_display(item_desc, item_price);
				items_subtotal = compute_quantity(item_desc, item_quantity, item_price);
				cout << TAB << TAB << "Subtotal: " << items_subtotal << endl;

				customer_cart.push_back(items_subtotal);
				continue;
			case 107: // 21
				item_desc = item_list[22];
				item_price = stof(item_list[23]);

				item_select_display(item_desc, item_price);
				items_subtotal = compute_quantity(item_desc, item_quantity, item_price);
				cout << TAB << TAB << "Subtotal: " << items_subtotal << endl;

				customer_cart.push_back(items_subtotal);
				continue;
			case 108: // 24
				item_desc = item_list[25];
				item_price = stof(item_list[26]);

				item_select_display(item_desc, item_price);
				items_subtotal = compute_quantity(item_desc, item_quantity, item_price);
				cout << TAB << TAB << "Subtotal: " << items_subtotal << endl;

				customer_cart.push_back(items_subtotal);
				continue;
			case 109: // 27
				item_desc = item_list[28];
				item_price = stof(item_list[29]);

				item_select_display(item_desc, item_price);
				items_subtotal = compute_quantity(item_desc, item_quantity, item_price);
				cout << TAB << TAB << "Subtotal: " << items_subtotal << endl;

				customer_cart.push_back(items_subtotal);
				continue;
			default:
				cout << TAB << TAB << "Invalid item code entered. Please enter a valid item code."
					 << endl;
				continue;
			}
			break;
		}

		// add all prices in the customer's cart
		items_totalamt = accumulate(customer_cart.begin(), customer_cart.end(), decltype(customer_cart)::value_type(0));

		cout << TAB << "Total Amount Due: " << items_totalamt << endl
			 << endl;

		while (true) // cash -> change
		{
			cout << TAB << "Cash: ";
			cin >> customer_cash;

			if (customer_cash < items_totalamt)
			{
				cout << TAB << "Insufficient cash!" << endl
					 << endl;
				continue;
			}
			else if (customer_cash > items_totalamt)
			{
				customer_change = customer_cash - items_totalamt;
				cout << TAB << "Change: " << customer_change << endl
					 << endl;

			    change_amount_calculate(customer_change);
				change_breakdown_display();
			}
			else if (customer_cash = items_totalamt)
			{
				customer_change = 0;
				cout << TAB << "Change: " << customer_change << endl
					 << endl;

				change_breakdown_display();
			}
			break;
		}

		while (true) // transaction repeat
		{
			cout << "Do you want another transaction? <y/n> ";
			cin >> resp_temp;

			transaction_bool = response(resp_temp);

			if (transaction_bool == 'N')
			{
				cout << "Thank you for shopping at CS126 Mart!" << endl
					 << endl;
				return 0;
			}
			else if (transaction_bool == 'Y')
			{
				reset_all_variables();
			}
			else
			{
				cout << transaction_bool << " is an invalid response. Please type <y/n>." << endl
					 << endl;
				continue;
			}
			break;
		}
	}
}

char response(char resp)
{
	resp = toupper(resp);
	return resp;
}
