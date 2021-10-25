#pragma once

#include <iostream>
#include <sstream>
#include <chrono>

namespace tick
{
	class HHMMSS_Format {
	public:
		HHMMSS_Format(const std::chrono::nanoseconds& dur) : dur(dur) {}

		friend std::ostream& operator<<(std::ostream& os, const HHMMSS_Format& obj) {
			using namespace std::chrono;

			const nanoseconds & elapsed = obj.dur;
			hours hrs = duration_cast<hours>(elapsed);
			minutes min = duration_cast<minutes>(elapsed) - hrs;
			seconds sec = duration_cast<seconds>(elapsed) - hrs - min;

			std::stringstream ss;

			// --- Hours ---
			if (hrs.count() > 0)
				ss << hrs.count() << ':';

			//  --- Minutes ---
			ss << min.count() << ':';

			// --- Seconds ---
			if (sec.count() < 10)
				ss << '0';

			ss << sec.count();

			os << ss.str();

			return os;
		}

	public:
		std::chrono::nanoseconds dur;
	};

	class HrsMinSec_Format {
	public:
	};
} // namespace tick