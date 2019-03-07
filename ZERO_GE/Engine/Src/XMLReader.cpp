#include "Precompiled.h"
#include "XMLReader.h"


using namespace ZERO;
using namespace ZERO::Engine;
using namespace ZERO::Engine::XMLReader;
using namespace tinyxml2;

bool XMLReader::Read(void* component, const Core::Meta::MetaClass* metaclass, const XMLNode* data)
{
	const XMLNode* dataCopy = data;
	const XMLElement* element = dataCopy->ToElement();

	while (dataCopy != nullptr)
	{
		const XMLAttribute* attribute = dataCopy->ToElement()->FirstAttribute();//name of the field
		const char* name = attribute->Value();
		
		const ZERO::Core::Meta::MetaField* field = metaclass->FindField(name);
		const XMLNode* nextChild = dataCopy->FirstChild();
		const size_t size = field->GetMetaType()->GetSize();
		std::unique_ptr<char[]> typeBuffer = std::make_unique<char[]>(size);
		
		uint32_t bytePos = 0;
		while (nextChild != nullptr)
		{
			size_t sizeOfType = 0;
			const char* typeName = nextChild->Value();
			const char* val = nextChild->FirstChild()->Value();
			char* var = (char*)TypeReader(typeName, val, sizeOfType);

			if (strcmp(typeName, "String") == 0)
			{
				*reinterpret_cast<std::string*>(reinterpret_cast<char*>(component) + field->GetOffset() + bytePos) = var;
				//strcpy((char*)component + field->GetOffset() + bytePos + 4, var);
			}
			else
			{
				memcpy((char*)component + field->GetOffset() + bytePos, var, sizeOfType);
			}
			bytePos += static_cast<uint32_t>(sizeOfType);
			nextChild = nextChild->NextSibling();
		}

		dataCopy = dataCopy->NextSibling();
	}
	

	return true;
}


void* XMLReader::TypeReader(const char* typeName, const char* value, size_t& sizeOfType)
{
	char* buffer;
	if (strcmp(typeName, "Float") == 0)
	{
		float f = static_cast<float>(atof(value));
		sizeOfType = sizeof(float);
		buffer = new char[sizeOfType];
		memcpy(buffer, &f, sizeOfType);
	}
	else if (strcmp(typeName, "Int") == 0)
	{
		int i = static_cast<int>(atoi(value));
		sizeOfType = sizeof(int);
		buffer = new char[sizeOfType];
		memcpy(buffer, &i, sizeOfType);
	}
	else if (strcmp(typeName, "Bool") == 0)
	{
		int i = static_cast<bool>(value);
		sizeOfType = sizeof(bool);
		buffer = new char[sizeOfType];
		memcpy(buffer, &i, sizeOfType);
	}
	else if (strcmp(typeName, "String") == 0)
	{
		std::string s{ value };
		sizeOfType = s.size();
		buffer = new char[sizeOfType + 1];
		strcpy_s(buffer,sizeOfType+1, s.c_str());
	}

	return buffer;
}