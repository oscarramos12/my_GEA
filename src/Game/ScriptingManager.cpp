#include "Game/ScriptingManager.h"

sol::state ScriptingManager::lua;

void ScriptingManager::init(){
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
}
void ScriptingManager::runScript(const std::string& script){
    lua.script(script);
}
void ScriptingManager::runScriptFile(const std::string& scriptFile){
    lua.script_file("assets/" + scriptFile);
}