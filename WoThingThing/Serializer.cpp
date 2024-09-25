#include "Serializer.h"
#include <fstream>
#include "json.hpp"
#include "BaseComponent.h"
#include "GoManager.h"
#include "GameObject.h"
#include "NaveMeshManager.h"
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

static int nodeID = 0;

//털끝 하나 건들지 말것 ↓
void Serializer::LoadLevel(const std::string& s)
{
	static bool IsNodeCheck = false;
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
	int i = 0;
	nlohmann::ordered_json::basic_json::iterator item;
	for (nlohmann::ordered_json::basic_json::value_type& item : AllData)//Depending on how you saved, you look for some values or others
	{
		//json object는 key와 value로 표현 (map이랑 비슷)
		//Create an obj IF this is an obj
		//auto obj = item.find("Platform");//iterator!
		nlohmann::ordered_json::basic_json::iterator obj = item.find("Platform");
		if (obj != item.end())
		{						
			//Create the go

			GameObject* go = new GameObject("Platform");
			GoManager::GetInst()->AddObject(go);
			go->SetID(i++);
			//Find the Component section
			nlohmann::ordered_json::basic_json::iterator cmp = item.find("Components");
			if (cmp == item.end()) //Not Found
				continue;
			//Iterate on the json on cmp for each component, add it
			nlohmann::ordered_json::basic_json::value_type& cmpo =*cmp;
			for (nlohmann::ordered_json::basic_json::value_type &a : cmpo)
			{
				nlohmann::ordered_json::basic_json::iterator t = a.find("Type");
				if (t == a.end())//Not found
					continue; 

				std::string typeName = *t;//Convert to string //요거이 질문				
				//Look in the registry for this type and create it
				BaseRTTI* p = Registry::GetInst()->FindAndCreate(typeName);
				if (p != nullptr)
				{
					p->LoadFromJson(a);
				}

				if (*t == "Transform")
				{
					//Add the comp to the GO
					auto nodes = a.find("Nodes");
					
					if (nodes != a.end())
					{
						if (IsNodeCheck == false)
						{
							for (const auto& node : *nodes)
							{
								auto x = node.begin().value();
								auto y = (node.begin() + 1).value();
								NaveMeshManager::GetInst()->AddNode({ nodeID++, {x,y} });
								IsNodeCheck = true;
							}
						}
						// You might need to set these nodes data to your component here
					}
				}								
			}
		}
	}
	IsNodeCheck = false;
	file.close();	
}

void Serializer::SaveLevel(const std::string& s)
{
	json AllData;
	//Counter instead of name as I do not have one
	int i = 0;
	//iterate on each GameObject
	for (GameObject* go : GoManager::GetInst()->Allobj())
	{
		auto aa = GoManager::GetInst()->Allobj();
		aa.size();
		json components;
		if (go->GetName() == "Platform")
		{
			json obj;
			obj["Platform"] = i++;
			go->SetID(i);
			for (auto c : go->GetAllComp())//map
			{
				BaseComponent* comp = c.second;
				components.push_back(comp->SaveToJson(s));//Check in a moment			
			}
			obj["Components"] = components;
			AllData.push_back(obj);
		}				
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

GameObject* Serializer::LoadEnemy(const std::string& s)
{		
	//open file
	std::fstream file;
	file.open(s, std::fstream::in);
	//Check the file is valid
	if (!file.is_open())
	{
		//std::cout << "file is not exist" << std::endl;
		return nullptr;
	}
	json AllData;
	file >> AllData;	//The json has all the file data
	nlohmann::ordered_json::basic_json::iterator item;
	for (nlohmann::ordered_json::basic_json::value_type& item : AllData)//Depending on how you saved, you look for some values or others
	{
		//json object는 key와 value로 표현 (map이랑 비슷)
		//Create an obj IF this is an obj
		//auto obj = item.find("Platform");//iterator!
		nlohmann::ordered_json::basic_json::iterator obj = item.find("Enemy");
		if (obj != item.end())
		{
			//Create the go

			GameObject* go = new GameObject("Enemy");
			GoManager::GetInst()->AddObject(go);

			//Find the Component section
			nlohmann::ordered_json::basic_json::iterator cmp = item.find("Components");
			if (cmp == item.end()) //Not Found
				continue;
			//Iterate on the json on cmp for each component, add it
			nlohmann::ordered_json::basic_json::value_type& cmpo = *cmp;
			for (nlohmann::ordered_json::basic_json::value_type& a : cmpo)
			{
				nlohmann::ordered_json::basic_json::iterator t = a.find("Type");
				if (t == a.end())//Not found
					continue;

				std::string typeName = *t;//Convert to string //요거이 질문				
				//Look in the registry for this type and create it
				BaseRTTI* p = Registry::GetInst()->FindAndCreate(typeName);
				if (p != nullptr)
				{
					p->LoadFromJson(a);
				}			
			}
			file.close();
			return go;
		}		
	}	
	
	
}

void Serializer::SaveEnemy(const std::string& s)
{
	json AllData;
	//Counter instead of name as I do not have one	
	int i = 0;

	//iterate on each GameObject	
	for (GameObject* go : GoManager::GetInst()->Allobj())
	{		
		json components;
		if (go->GetName() == "Enemy")
		{
			json obj;
			obj["Enemy"] = i++;
			for (auto c : go->GetAllComp())//map
			{
				BaseComponent* comp = c.second;
				components.push_back(comp->SaveToJson(s));//Check in a moment	
			}
			obj["Components"] = components;
			AllData.push_back(obj);
			break;
		}
		
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
