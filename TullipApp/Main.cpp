#include "DateTime.h"

int main(int argc, char* argv[])
{
	try
	{
		DateTime time_now = DateTime(50, 6, 2025, 15, 54, 24);

		std::cout << time_now;
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