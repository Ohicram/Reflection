#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void ParseAndGenerate(const std::filesystem::path& path);
void GenerateHeader(const std::filesystem::path& path, std::string className);
void GenerateSource(const std::filesystem::path& path, std::string className, std::vector<std::pair<std::string, std::string>> propertyList);
std::string ParseClassName(std::string classLine);
std::pair<std::string, std::string> ParseProperty(std::string propertyLine);


int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cerr << "Wrong number of input parameters. It is required to specify the root folder of the project.\n";
		return 1;
	}
	for (const auto& entry : std::filesystem::directory_iterator(argv[1]))
	{
		if(entry.path().extension() == ".h")
		{
			ParseAndGenerate(entry.path());
		}
	}
	return 0;
}

void ParseAndGenerate(const std::filesystem::path& path)
{
	std::fstream fileStream;
	fileStream.open(path.c_str());
	std::string line;
	std::string className;
	std::vector<std::pair<std::string, std::string>> parsedProperties;
	
	while(std::getline(fileStream, line))
	{
		if(line.find("CLASS") != std::string::npos && line.find("#") == std::string::npos)
		{
			className = ParseClassName(line);
			GenerateHeader(path, className);
		}
		else if (className.size() > 0 && line.find("PROPERTY") != std::string::npos && line.find("#") == std::string::npos)
		{
			parsedProperties.push_back(ParseProperty(line));
		}
	}
	if(parsedProperties.size() > 0)
	{
		GenerateSource(path, className, parsedProperties);
	}
}

std::string ParseClassName(std::string classLine)
{
	const auto startPos = classLine.find("(");
	const auto endPos = classLine.find(")");
	return classLine.substr(startPos+1, endPos-startPos-1);
}

std::pair<std::string, std::string> ParseProperty(std::string propertyLine)
{
	const auto startPos = propertyLine.find("(");
	const auto endPos = propertyLine.find(")");
	const std::string innerDataStr = propertyLine.substr(startPos + 1, endPos - startPos-1);
	const auto separatorPos = innerDataStr.find(" ");
	const std::string propertyType = innerDataStr.substr(0, separatorPos);
	const std::string propertyName = innerDataStr.substr(separatorPos + 1, innerDataStr.size() - separatorPos - 1);
	return {propertyType, propertyName};
}

void GenerateHeader(const std::filesystem::path& path, std::string className)
{	
	std::wstring fileName(path.c_str());
	fileName.erase(fileName.size() - 2, fileName.size());
	fileName.append(L"_generated.h");
	std::ofstream outfile(fileName);
	outfile << "#pragma once\n#include \"RObject.h\"" << std::endl;
	outfile << "class " << className << ";\n\n";
	outfile << "RObject const* GetClassImpl(ClassTag<" << className << ">);\n";
	outfile.close();
}

void GenerateSource(const std::filesystem::path& path, std::string className, std::vector<std::pair<std::string, std::string>> propertyList)
{
	std::wstring filePathName(path.c_str());
	std::wstring fileName(path.filename().c_str());
	filePathName.erase(filePathName.size() - 2, filePathName.size());
	filePathName.append(L"_generated.cpp");
	std::ofstream outfile(filePathName);
	
	outfile << "#include \"" << std::string(fileName.begin(), fileName.end()) << "\"\n";
	outfile << "RObject const* GetClassImpl(ClassTag<" << className << ">)\n{\n";
	outfile << "\tstatic RObject s_Object(" << propertyList.size() << ");\n\n";
	for(int i = 0; i < propertyList.size(); ++i)
	{
		outfile << "\ts_Object.fields[" << i << "].type = GetType<"<< propertyList[i].first <<">();\n";
		outfile << "\ts_Object.fields[" << i << "].name = \"" << propertyList[i].second << "\\0\";\n";
		outfile << "\ts_Object.fields[" << i << "].offset = offsetof(" << className << "," << propertyList[i].second << ");\n";
	}
	outfile << "\treturn &s_Object;\n}\n";
	
	outfile.close();
}