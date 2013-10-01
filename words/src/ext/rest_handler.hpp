#ifndef __REST_HANDLER__hpp
#define __REST_HANDLER__hpp

#include <string>
#include <sstream>

class RoundLog {
public:
	int score;
	std::string words;
	std::string points;
	std::string version;

	inline std::string ToString() {
		std::stringstream ss;
		ss << "{ ";
			ss << "\"words\":\"" << words << "\", ";
			ss << "\"points\":\"" << points << "\", ";
			ss << "\"score\":\"" << score << "\", ";
			ss << "\"version\":\"" << version << "\"";
		ss << "}";
		return ss.str();
	}
};

class RestHandler {
private:
	static RestHandler* instance;
public:
	/// Initialises this object.
	static void Init();

	/// Returns singleton
	/// @return	null if it fails, else.
	static RestHandler* get();

	/// Query if this object has internet connection.
	/// @return	true if internet connection, false if not.
	bool HasInternetConnection();

	/// Submit round log to the server
	/// @param [in,out]	round_log	If non-null, the round log.
	void SubmitRoundLog(RoundLog* round_log);
};

#endif  // __REST_HANDLER__hpp