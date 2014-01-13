#ifndef _AREADATABASEREADER_HPP
#define _AREADATABASEREADER_HPP

#include "databasereader.hpp"
#include "typedefs.hpp"

class AreaDatabaseReader : public DatabaseReader {

	public:

		AreaDatabaseReader();
		~AreaDatabaseReader();
		
		const twoDimArray getBaseFromEntry(const std::string &);
		const portalMap getPortalMapFromEntry(const std::string &);
        const likelyhoodTuples getLikelyhoodsFromEntry(const std::string &);

	private:

		const std::string k_filename = "data/areas.database";

        void openFile();
        const std::string nextEntry();

        const portalMap convertStringToPortalMap(const std::string &);
        const twoDimArray convertStringToTwoDimArr(const std::string &);
        const likelyhoodTuples convertStringToLikelyhoodTuples(const std::string &);

};

#endif // _AREADATABASEREADER_HPP