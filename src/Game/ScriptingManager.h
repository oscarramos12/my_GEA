#pragma once

#include <sol/sol.hpp>
#include <string>

class ScriptingManager{
    public:
    static sol::state lua;

    static void init();
    static void runScript(const std::string& script);
    static void runScriptFile(const std::string& scriptFile);
};