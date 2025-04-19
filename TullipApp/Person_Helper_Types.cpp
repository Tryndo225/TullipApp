#include "Person_Helper_Types.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>


// Contacts class implementation
// Copy to clipboard function
#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
// pbcopy
#elif defined(__linux__)
// xclip
#else
#error Unsupported platform
#endif

bool Contacts::copy_to_clipboard(const std::string& text)
{
#if defined(_WIN32)
	// Open and lock the clipboard; ensure it always closes even on early return
	if (!OpenClipboard(nullptr)) return false;

	struct Closer { ~Closer() { CloseClipboard(); } } guard;

	EmptyClipboard();

	// Allocate a movable global block and copy the text + null-term
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
	if (!hMem) return false;

	char* memPtr = static_cast<char*>(GlobalLock(hMem));

	if (!memPtr) {
		GlobalFree(hMem);
		return false;
	}

	std::memcpy(memPtr, text.c_str(), text.size() + 1);
	GlobalUnlock(hMem);

	// Place ownership of hMem into the clipboard
	if (!SetClipboardData(CF_TEXT, hMem)) {
		GlobalFree(hMem);
		return false;
	}
	return true;

#elif defined(__APPLE__) || defined(__linux__)
	// Choose the right command for macOS / Linux
	const char* cmd =
#if defined(__APPLE__)
		"pbcopy"
#else
		"xclip -selection clipboard"
#endif
		;

	// Open a pipe to the clipboard tool
	FILE* pipe = popen(cmd, "w");
	if (!pipe) return false;

	// Write all the data
	size_t written = std::fwrite(text.data(), 1, text.size(), pipe);
	int status = pclose(pipe);

	// Success only if everything was written and the tool exited cleanly
	return (written == text.size() && status == 0);
#endif
}

// Email class implementation
// Constructor implementations
Email::Email(const std::string& email) : email_(email) {}
Email::Email(std::string&& email) : email_(std::move(email)) {}
// operator<< overload
std::ostream& operator<<(std::ostream& stream, const Email& email)
{
	stream << email.get_email();
	return stream;
}


// Phone class implementation
// Constructor implementations
Phone::Phone(const std::string& phone) : phone_(phone) {}
Phone::Phone(std::string&& phone) : phone_(std::move(phone)) {}
// operator<< overload
std::ostream& operator<<(std::ostream& stream, const Phone& phone)
{
	stream << phone.get_phone();
	return stream;
}
