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
        const std::string getTextFromEntry(const std::string &);

	private:

		const std::string k_filename = "data/npcs.database";

        void openFile();

        const partyTuples convertStringToPartyTuples(const std::string &);
        const locationTuple convertStringToLocationTuple(const std::string &);

};

#endif // _NPCDATABASEREADER_HPP