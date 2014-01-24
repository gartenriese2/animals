#include "areadatabasereader.hpp"

#include "console.hpp"

AreaDatabaseReader::AreaDatabaseReader() {
	openFile();
}

AreaDatabaseReader::~AreaDatabaseReader() {
}

void AreaDatabaseReader::openFile() {

	m_file.open(k_filename);
	if (!m_file.good()) {
		EXIT("Bad area database!");
	}

}

const twoDimArray AreaDatabaseReader::getBaseFromEntry(const std::string & str) {

	return convertStringToTwoDimArr(getTagContentFromEntry('b', str));

}

const portalMap AreaDatabaseReader::getPortalMapFromEntry(const std::string & str) {
	
	return convertStringToPortalMap(getTagContentFromEntry('p', str));

}

const likelyhoodTuples AreaDatabaseReader::getLikelyhoodsFromEntry(const std::string & str) {

	std::string content = getTagContentFromEntry('l', str);
	return convertStringToLikelyhoodTuples(content);

}

const portalMap AreaDatabaseReader::getNPCSFromEntry(const std::string & str) {

	return convertStringToNPCMap(getTagContentFromEntry('c', str));

}

const portalMap AreaDatabaseReader::convertStringToPortalMap(const std::string & str) {

	portalMap map;
	
	unsigned int count = 0;
	
	while (count < str.size()) {
	
		std::string x;
		std::string y;
		std::string to;
		
		while (str[count++] != ',') x += str[count - 1];
		while (str[count++] != '>') y += str[count - 1];
		while (str[count++] != '\n') to += str[count - 1];
		Position p(std::stoi(x), std::stoi(y));
		map.emplace(p,to);

	}

	return map;

}

const twoDimArray AreaDatabaseReader::convertStringToTwoDimArr(const std::string & str) {

	twoDimArray arr;

	bool eol = false;
	unsigned int count = 0;
	for (unsigned int i = 0; i < k_height; ++i) {
		for (unsigned int j = 0; j < k_width; ++j) {
			arr[i][j] = eol ? ' ' : str[count++];
			if (str[count - 1] == '\n' || count > str.size()) {
				eol = true;
				arr[i][j] = ' ';
			}
		}
		eol = false;
	}
	
	return arr;
}

const likelyhoodTuples AreaDatabaseReader::convertStringToLikelyhoodTuples(const std::string & str) {

	likelyhoodTuples tup;

	unsigned int count = 0;
	
	while (count < str.size()) {
	
		std::string name;
		std::string a;
		std::string b;
		std::string prob;
		
		while (str[count++] != '>') name += str[count - 1];
		while (str[count++] != '-') a += str[count - 1];
		while (str[count++] != '>') b += str[count - 1];
		while (str[count++] != '\n') prob += str[count - 1];
		
		tup.emplace_back(std::make_tuple(name, std::stoi(a), std::stoi(b), std::stof(prob)));

	}

	return tup;

}

const portalMap AreaDatabaseReader::convertStringToNPCMap(const std::string & str) {

	portalMap map;
	
	unsigned int count = 0;
	
	while (count < str.size()) {
	
		std::string x;
		std::string y;
		std::string name;
		
		while (str[count++] != ',') x += str[count - 1];
		while (str[count++] != '>') y += str[count - 1];
		while (str[count++] != '\n') name += str[count - 1];
		Position p(std::stoi(x), std::stoi(y));
		map.emplace(p,name);

	}

	return map;

}
