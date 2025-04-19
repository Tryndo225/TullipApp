#include "DateTime.h"

int main(int argc, char* argv[])
{
	try
	{
		DateTime time_now = DateTime(20, 4, 2025, 1, 48, 24);

		std::cout << time_now;

		std::cout << "Date: " << time_now.get_date_string() << std::endl;

		std::cout << "Time: " << time_now.get_time_string() << std::endl;

		std::cout << "Date and Time: " << time_now.get_date_string() << " " << time_now.get_time_string() << std::endl;

		time_now.print_long(std::cout);
	}
	catch (const DateTimeError& e)
	{
		std::cout << e;
	}
	catch (...)
	{
		std::cout << "Unknown error occurred.";
	};

	return 0;
}