#ifndef LOGIC_ELEMENTS_H
#define LOGIC_ELEMENTS_H

#include <memory>

#include "player.h"
#include "npc_goomba.h"

class LogicElements {
private:
    std::unique_ptr<Player> p_p1 = nullptr;
    std::unique_ptr<Map> p_map = nullptr;
    bool _shouldClose = false;
    std::vector<std::unique_ptr<NpcGoomba>> _ennemies_a;

public:
    LogicElements();
    ~LogicElements();

    /// <summary>
    /// Inits the memory within the object, creates a player object.
    /// </summary>
    void Init();

    /// <summary>
    /// Retrieves the Raw pointer of the Player member object.
    /// </summary>
    /// <returns>Raw pointer of the Player class</returns>
    Player* getP1() const;

    /// <summary>
    /// Retrieves the number of enemies stored within the engine.
    /// </summary>
    /// <returns>Number of enemies, size of the ennemy vector</returns>
    int getEnnemiACount() const;

    /// <summary>
    /// Sets the number of enemies to initalize in the engine. Pushes a unique ptr in the enemy vector.
    /// </summary>
    /// <param name="number">Number of enemies to make</param>
    void setEnnemiA(int const number);

    /// <summary>
    /// Retrieves an enemy from the enemy vector with the index.
    /// </summary>
    /// <param name="index">index to fetch the data from in the vector</param>
    /// <returns>raw pointer to the enemy as NPCGoomba, or nullptr if out of bounds</returns>
    NpcGoomba* getEnnemiA(int const index) const;

    /// <summary>
    /// Sets the map object contained within. Takes ownership of a Map unique_ptr. To be ran alongside the Init method.
    /// </summary>
    /// <param name="map">Map to be stored in the object instance</param>
    void setMap(std::unique_ptr<Map> map);

    /// <summary>
    /// Retrieves the Map stored within the instance.
    /// </summary>
    /// <returns>Raw pointer of a Map object</returns>
    Map* getMap() const;

    /// <summary>
    /// To be used to close the Logic Thread. Sets the stored boolean _shouldClose to true;
    /// </summary>
    void setShouldClose();

    /// <summary>
    /// Retrieves the _shouldClose boolean, to be used to close the Thread when seeking to exit the game.
    /// </summary>
    /// <returns>boolean indicating if the thread should be stopped</returns>
    bool getShouldClose() const;
};

#endif
