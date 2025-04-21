#include "DateTime.h"
#include "Data_Helper_Types.h"

int main(int argc, char* argv[])
{
	try
	{
		DateTime time_now = DateTime::get_current_datetime();
		std::cout << "Current date and time: " << time_now << std::endl;
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