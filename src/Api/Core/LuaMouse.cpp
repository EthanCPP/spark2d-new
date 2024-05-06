#include "LuaMouse.h"


LuaMouse::LuaMouse(std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<SparkGlobals> globals)
{
    mSceneManager = sceneManager;
    mWindow = window;
    mGlobals = globals;
}

LuaMouse::~LuaMouse()
{

}

void LuaMouse::setup(sol::state& lua)
{
    /*
    * =========================================
    * Instantiate the mouse table of utilities
    * =========================================
    */
    lua["spark"]["mouse"] = lua.create_table_with(
        "x", 0,
        "y", 0
    );


    /*
    * =========================================
    * Mouse code bindings
    * TODO put this somewhere nicer
    * =========================================
    */

    // -- spark.mouse.button.left 
    lua["spark"]["mouse"]["button"] = lua.create_table_with(
        "left", 0,
        "right", 1,
        "middle", 2,
        "x1", 3,
        "x2", 4
    );

    lua["spark"]["mouse"]["wheel"] = lua.create_table_with(
        "up", 1,
        "down", -1
    );
}