#include "Serializer.h"
#include <fstream>
#include "json.hpp"
#include "BaseComponent.h"
#include "GoManager.h"
#include "GameObject.h"
#include "BaseRTTI.h"
#include "Registry.h"

//using json = nlohmann::json; //Map. orders alphebetically on pushback and insert
using json = nlohmann::ordered_json; //Map. Keeps the order the variables were declared in

Serializer::Serializer()
{

}

Serializer::~Serializer()
{

}

void Serializer::LoadLevel(const std::string& s)
{
	//open file
	std::fstream file;
	file.open(s, std::fstream::in);
	//Check the file is valid
	if (!file.is_open())
	{
		//Print error
		//return;
	}
	json AllData;
	file >> AllData;	//The json has all the file data

	for (auto& item : AllData)//Depending on how you saved, you look for some values or others
	{
		//Create an obj IF this is an obj
		auto obj = item.find("Object");//iterator!
		if (obj != item.end())
		{
			//Create the go
			GameObject* go = new GameObject("Object");
			GoManager::GetInst()->AddObject(go);

			//Find the Component section
			auto cmp = item.find("Components");
			if (cmp == item.end()) //Not Found
				continue;
			//Iterate on the json on cmp for each component, add it
			for (auto& a : *cmp)
			{
				auto t = a.find("Type");
				if (t == a.end())//Not found
					continue; 

				std::string typeName = t.value().dump();//Convert to string
				typeName = "Transform";
				//Look in the registry for this type and create it
				BaseRTTI* p = Registry::GetInst()->FindAndCreate(typeName);
				if (p != nullptr)
				{
					p->LoadFromJson(a);
				}
				//Add the comp to the GO
			}
		}
	}
}

void Serializer::SaveLevel(const std::string& s)
{
	json AllData;
	//Counter instead of name as I do not have one
	int i = 0;
	//iterate on each GameObject
	for (GameObject* go : GoManager::GetInst()->Allobj())
	{
		json obj;
		obj["Object"] = i++;

		json components;
		for (auto c : go->GetAllComp())//map
		{
			BaseComponent* comp = c.second;
			components.push_back(comp->SaveToJson());//Check in a moment
		}
		obj["Components"] = components;
		AllData.push_back(obj);
	}

	//Open file
	std::fstream file;
	file.open(s, std::fstream::out);//Open as write mode. Create it if it does not exist!

	if (!file.is_open())
	{
		//Print error
		//return
	}

	//file << AllData; //All in 1 line
	file << std::setw(2) << AllData;

	file.close();
}