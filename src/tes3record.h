#ifndef TES3_RECORD_H
#define TES3_RECORD_H

#include <cstdint>
#include <vector>
#include <istream>


namespace ESP {

	/**
	* @brief record storage class without record-specific information
	*/
	class TES3Record
	{
	public:
		TES3Record();

		bool readFrom(std::istream &stream);

	private:
		struct Header {
			char type[4];
			float version;
			long unknown;
		} m_Header;
	};

}

#endif // TES3_RECORD_H
