#include "resource.h"
#include "runtime.h"
#include <string>
#include <iostream>

#ifdef SERVER_MODULE
    // For filestream
    #include <fstream>
    #include <streambuf>
#endif

void ProcessConfigOptions()
{

    auto cfg = alt::ICore::Instance().GetServerConfig();
    Config::Value::ValuePtr moduleConfig = alt::ICore::Instance().GetServerConfig()["js-module"];
    if (!moduleConfig->IsDict()) return;

    Config::Value::ValuePtr profiler = moduleConfig["profiler"];
    if (profiler->IsDict())
    {
       
    }
    
    std::cout << Config::Util::ConvertValueToString(moduleConfig) << std::endl;
}

bool BoilerplateResource::Start()
{
    //auto data = alt::ICore::Instance().GetPedModelByHash(33);
    //std::cout << &data << std::endl;
    //// Load file
    //auto mvaluenone = alt::ICore::Instance().CreateMValueNone();
    //auto mvaluedict = alt::ICore::Instance().CreateMValueDict();
    //auto mvaluenill = alt::ICore::Instance().CreateMValueNil();
    //mvaluedict->Set("none", mvaluenone);
    //mvaluedict->Set("mvaluenill", mvaluenill);
    ////mvaluedict->SetConst("mvaluenill", mvaluedict->Get("none"));
    ////auto begin = mvaluedict->Begin();
    //
    //for (auto it = mvaluedict->Begin(); it; it = mvaluedict->Next()) {
    //    auto iii = it;
    //    auto key = iii->GetKey();
    //    auto value = iii->GetValue();
    //    auto value2 = value->Clone();
    //    auto iseq = value->Equals(value2);
    //    std::cout << key << std::endl;
    //}
    //auto sdas = mvaluedict->Equals(mvaluedict);
    ////auto kkk = begin->GetKey();

    ProcessConfigOptions();
    
    //auto type = mvaluenone.Get()->GetType();
    //auto size = mvaluedict->GetSize();
    auto main = resource->GetMain();
    auto src = ReadFile(main);
    if(src.empty())
    {
    //    Log::Error << "Failed to read resource main file" << Log::Endl;
        std::cout << "Failed to read resource main file" << std::endl;
        return false;
    }
    //
    //// Now we can access the resource main file and e.g. start a script using the source code
    //// To showcase this, we are just going to log the file content here
    //Log::Info << "Resource main content:" << Log::Endl;
    //Log::Info << src << Log::Endl;
    //core::ICore::Instance().LogDebug(src, resource);
    return true;
}

bool BoilerplateResource::Stop()
{
    // Do everything here that needs cleanup after the resource has been stopped
    // Make sure to clean up EVERYTHING here that the resource has created,
    // so that dynamic resource restarts are possible
    return true;
}

//void BoilerplateResource::OnEvent(const core::CEvent* ev)
//{
//    // Handle incoming events here, e.g. call the event handlers registered by the resource
//}

void BoilerplateResource::OnTick()
{
    // Do everything here that needs to be handled on tick that is resource related
    // This can be e.g. timers
}

//void BoilerplateResource::OnCreateBaseObject(core::IBaseObject* object){
    // Called every time a base object has been created, so you can use this to keep track
    // of all the existing base objects, to check if they are valid in the user scripts
//}

//void BoilerplateResource::OnRemoveBaseObject(core::IBaseObject* object)
//{
    // Called every time a base object has been created, so you can use this to keep track
    // of all the existing base objects, to check if they are valid in the user scripts
//}

std::string BoilerplateResource::ReadFile(std::string path)
{
    auto pkg = resource->GetPackage();
    // Check if file exists
    if(!pkg->FileExists(path)) return std::string();
    // Open file
    alt::IPackage::File* pkgFile = pkg->OpenFile(path);
    std::string src(pkg->GetFileSize(pkgFile), '\0');
    // Read file content
    pkg->ReadFile(pkgFile, src.data(), src.size());
    pkg->CloseFile(pkgFile);

    return src;
}
