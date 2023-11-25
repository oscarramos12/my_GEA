#include <print.h>
#include <string>
#include <sol/sol.hpp>
#include "Pong/Pong.h"

int main () {
  Pong pong = Pong("GAME", 800, 600);

  pong.run();
  /*sol::state lua;
  lua.open_libraries(sol::lib::base);
    lua.script("print('Hello, World!')");*/
}