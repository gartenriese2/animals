#ifndef _NPCDATABASEREADER_HPP
#define _NPCDATABASEREADER_HPP

#include "databasereader.hpp"
#include "typedefs.hpp"

class NPCDatabaseReader : public DatabaseReader {

	public:

		NPCDatabaseReader();
		~NPCDatabaseReader();
		
		const partyTuples getPartyTuplesFromEntry(const std::string &);
        const locationTuple getLocationFromEntry(const std::string &);
        const std::vector<std::string> getTextFromEntry(const std::string &);

	private:

        const partyTuples convertContentToPartyTuples(const std::vector<std::string> &);
        const locationTuple convertContentToLocationTuple(const std::vector<std::string> &);

};

#endif // _NPCDATABASEREADER_HPP