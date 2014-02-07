#ifndef _AREADATABASEREADER_HPP
#define _AREADATABASEREADER_HPP

#include "databasereader.hpp"
#include "typedefs.hpp"

#include <string>

class AreaDatabaseReader : public DatabaseReader {

	public:

		AreaDatabaseReader();
		~AreaDatabaseReader();
		
		const std::vector<std::string> getBaseFromEntry(const std::string &);
		const portalMap getPortalMapFromEntry(const std::string &);
        const likelyhoodTuples getLikelyhoodsFromEntry(const std::string &);
        const portalMap getNPCSFromEntry(const std::string &);

	private:

        const portalMap convertContentToPortalMap(const std::vector<std::string> &);
        const twoDimArray convertContentToTwoDimArr(const std::vector<std::string> &);
        const likelyhoodTuples convertContentToLikelyhoodTuples(const std::vector<std::string> &);
        const portalMap convertContentToNPCMap(const std::vector<std::string> &);

};

#endif // _AREADATABASEREADER_HPP