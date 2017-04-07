#include <dirent.h>
#include <utility>
#include <sys/stat.h>
#include "Core.hpp"
#include "GameState.hpp"
#include "Logger.hpp"

//
// PLEASE READ CAREFULLY
//
// To compile you need "dirent.h".
// This file is not directly available in Visual Studio.
// You can download it here:
// https://raw.githubusercontent.com/tronkko/dirent/master/include/dirent.h
//
// Then move it in your Visual Studio include directory:
// VS 17 (on two lines): C:\Program Files (x86)\Microsoft Visual Studio\
// 2017\Enterprise\VC\Tools\MSVC\14.10.25017\include
// VS 14: C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include
//
// To finish relaunch your Visual Studio and it should be ok :)
//

namespace arcade
{
  Core::Core() :
    m_currentGameId(0), 
    m_currentLibId(0), 
    m_gameState(LOADING),
    m_selectedGameId(0)
  {
    m_state = INGAME;

    m_map = std::make_unique<Map>(0, 0);
    m_gui = std::make_unique<GUI>();

    // Create the main menu GUI
    Color dark(0, 0, 0, 80);

    m_gui->push(Component(0, 0, 1, 1, Color(20, 20, 20)));
    m_gui->push(Component(0.3, 0.1, 0.4, 0.1, dark));
    m_gui->push(Component(0.35, 0.13, 0.3, 0.04, Color::Transparent, "Arcade"));
    m_gui->push(Component(0.1, 0.3, 0.35, 0.6, dark));
    m_gui->push(Component(0.55, 0.3, 0.35, 0.6, dark));

    m_firstLibIndex = m_gui->size();

#ifdef DEBUG
    Nope::Log::Debug << "Core constructed";
#endif
  }

  Core::~Core()
  {
#ifdef DEBUG
    Nope::Log::Debug << "Core destructed";
#endif
  }

  void Core::launch(std::string const &lib)
  {
    m_gameState = MENU;

    // Log
    Nope::Log::Info << "Launching the core";

    // Load all the game and graphic libraries
    this->initLists(lib);

    // Set the current library to the first one
    m_lib = std::unique_ptr<IGfxLib>(m_libList[m_currentLibId].getFunction<IGfxLib* ()>("getLib")());

    while (m_gameState != QUIT)
    {
      switch (m_gameState)
      {
      case MENU:
        if (m_game.get() == this)
          m_game.release();
        this->m_game = std::unique_ptr<IGame>(this);
      case INGAME:
        m_gameState = LOADING;
        m_gameState = this->gameLoop();
        if (m_gameState == QUIT)
          std::cout << "QUIT #3" << std::endl;
        break;
      default:
        m_gameState = QUIT;
        break;
      }
    }
    // Log
    if (m_game.get() == this)
      m_game.release();
    Nope::Log::Info << "Exiting the core";
  }

  GameState Core::gameLoop()
  {
    std::vector<Sound> sounds;
    Event ev;

    Nope::Log::Info << "Launching a game";
    while (true)
    {
      if (m_gameState == LOADING)
      {
        this->loadGame();
        m_gameState = INGAME;
      }

      m_eventBuffer.clear();
      sounds.clear();
      m_lib->clear();
      if (m_gameState != INGAME)
      {
        std::cout << "Quit 1" << std::endl;
        break;
      }
      // Events
      ev = { ET_NONE, AT_NONE, { KB_NONE }, { 0, 0 }, { 0, 0 } };
      while (m_lib->pollEvent(ev))
      {
        mainEvent(ev);
        ev = { ET_NONE, AT_NONE, { KB_NONE }, { 0, 0 }, { 0, 0 } };
      }
      // m_eventBuffer.push_back(ev);
      if (m_gameState == QUIT)
        std::cout << "QUIT #1" << std::endl;
      if (m_gameState != INGAME && m_gameState != LOADING)
      {
        if (m_gameState == QUIT)
          std::cout << "QUIT #2" << std::endl;
        std::cout << "Quit 2" << std::endl;
        break;
      }
#ifdef DEBUG
      Nope::Log::Debug << "Polled events";
#endif
      m_game->notifyEvent(std::move(m_eventBuffer));
#ifdef DEBUG
      Nope::Log::Debug << "Notified events";
#endif

      if (m_game.get() == nullptr)
      {
        std::cout << "Quit 3" << std::endl;
        return (QUIT);
      }
      // Network
      // TODO: implement

      // Game loop
      m_game->process();
#ifdef DEBUG
      Nope::Log::Debug << "Processed game loop";
#endif
      // Sound
      sounds = m_game->getSoundsToPlay();
#ifdef DEBUG
      Nope::Log::Debug << "Get sounds to play";
#endif
      // play sounds

      // Map
      m_lib->updateMap(m_game->getCurrentMap());
#ifdef DEBUG
      Nope::Log::Debug << "Send map to lib";
#endif

      // GUI
      m_lib->updateGUI(m_game->getGUI());
#ifdef DEBUG
      Nope::Log::Debug << "Send GUI to lib";
#endif
      // Display
      m_lib->display();
#ifdef DEBUG
      Nope::Log::Debug << "Displayed";
#endif
      // GameState
      m_gameState = m_game->getGameState();
#ifdef DEBUG
      Nope::Log::Debug << "Game state updated";
#endif
    }
    Nope::Log::Info << "Exiting a game";
    return (m_gameState);
  }

  GameState Core::menuLoop()
  {
    Nope::Log::Info << "Entering the main menu";

    // Here we use directly use the first lib and game, but normally
    // there is a menu to let the user choose
    //m_game = std::unique_ptr<IGame>(m_gameList[0].getFunction<IGame* ()>("getGame")());



    Nope::Log::Info << "Leaving the main menu";

    return INGAME;
  }

  // We use dirent.h for cross-platform and lightweight solution
  void Core::initLists(std::string const &lib)
  {
    DIR *dir;
    struct dirent *ent;
    bool found = false;
    struct stat search;
    struct stat file;

    if (stat(lib.c_str(), &search) < 0)
    {
      throw std::exception();
    }

    // Open "dir/" directory
    if ((dir = opendir("lib")) != NULL)
    {
      Nope::Log::Info << "Opened directory 'lib'";
      // Check all the entities in the directory
      while ((ent = readdir(dir)) != NULL)
      {
        Nope::Log::Info << "Reading '" << ent->d_name << "'";
        // If it's a REGULAR file and it's name
        // is formated like "lib_arcade_XXX.so"
        if (ent->d_type == DT_REG &&
#if defined(__linux__) || (__APPLE__)
          Core::isNameValid(ent->d_name, "lib_arcade_", ".so"))
#else
          Core::isNameValid(ent->d_name, "lib_arcade_", ".dll"))
#endif
        {
          Nope::Log::Info << "Adding library '" << ent->d_name << "'";

          std::string libPath = std::string("lib/") + ent->d_name;
          m_libList.emplace_back(libPath);
          if (stat(libPath.c_str(), &file) < 0)
          {
            throw std::exception();
          }
          
          m_gui->push(Component(0.12, 0.35 + 0.07 * (m_libList.size() - 1),
            0.3, 0.05, Color::Transparent, std::string(ent->d_name)));

          // If same file inode
          if (search.st_ino == file.st_ino)
          {
            found = true;
            m_currentLibId = m_libList.size() - 1;
            m_selectedLibId = m_currentLibId;
          }
        }
      }
      // Close the dir after using it because we are well educated people :)
      closedir(dir);
      Nope::Log::Info << "Closing dir 'lib'";
      
      if (found == false)
      {
        throw std::exception();
      }
    }
    else
    {
      throw std::exception(); // TODO: create a good exception
    }

    // Check if there was at least one graphic lib
    if (m_libList.size() == 0)
    {
      throw std::exception(); // TODO: there is no graphic library
    }

    m_firstGameIndex = m_gui->size();

    // Open "games/" directory
    if ((dir = opendir("games")) != NULL)
    {
      Nope::Log::Info << "Opened directory 'games'";
      // Check all the entities in the directory
      while ((ent = readdir(dir)) != NULL)
      {
        Nope::Log::Info << "Reading '" << ent->d_name << "'";				// If it's a REGULAR file and it's a .so
        if (ent->d_type == DT_REG &&
#if defined(__linux__) || (__APPLE__)
          Core::isNameValid(ent->d_name, "", ".so"))
#else
          Core::isNameValid(ent->d_name, "", ".dll"))
#endif
        {
          Nope::Log::Info << "Adding library '" << ent->d_name << "'";
          m_gameList.emplace_back(std::string("games/") + ent->d_name);

          m_gui->push(Component(0.57, 0.35 + 0.07 * (m_gameList.size() - 1),
            0.3, 0.05, Color::Transparent, std::string(ent->d_name)));
        }
      }
      // Close the dir after using it because we are well educated people
      // and yes all of this was copy/pasted :)
      closedir(dir);
      Nope::Log::Info << "Closing dir 'lib'";
    }
    else
    {
      throw std::exception(); // TODO: create a good exception
    }
  }

  // Check if the name string begins with prefix and end with suffix
  // ex: isNameValid("liboui.a", "lib", ".a") => true
  //	   isNameValid("liboui.a", "lib_arcade", ".a") => false
  //	   isNameValid("liboui.a", "lib", ".so") => false
  bool Core::isNameValid(std::string const & name,
    std::string const &prefix, std::string const &suffix)
  {
    return (name.compare(0, prefix.length(), prefix) == 0 &&
      name.compare(name.length() - suffix.length(),
        suffix.length(), suffix) == 0);
  }

  void Core::loadGame()
  {
    std::cout << "Loading GAME" << std::endl;
    m_lib->loadSounds(m_game->getSoundsToLoad());
    m_lib->loadSprites(m_game->getSpritesToLoad());
    m_gameState = INGAME;
  }

  void Core::mainEvent(Event const & e)
  {
    int game = m_currentGameId;
    int lib = m_currentLibId;

    if (e.type == ET_KEYBOARD && e.action == AT_PRESSED)
    {
      switch (e.kb_key)
      {
      case KB_2:
        if (m_currentLibId == 0)
        {
          m_currentLibId = m_libList.size();
        }
        m_currentLibId--;
        break;
      case KB_3:
        m_currentLibId++;
        if (m_currentLibId == m_libList.size())
        {
          m_currentLibId = 0;
        }
        break;
      case KB_4:
        if (m_currentGameId == 0)
        {
          m_currentGameId = m_gameList.size();
        }
        m_currentGameId--;
        break;
      case KB_5:
        m_currentGameId++;
        if (m_currentGameId == m_gameList.size())
        {
          m_currentGameId = 0;
        }
        break;
      case KB_9:
        m_gameState = MENU;
        break;
      case KB_ESCAPE:
        m_gameState = QUIT;
        break;
      default:
        m_eventBuffer.push_back(e);
        break;
      }

      if (m_currentGameId != game)
      {
        if (m_game.get() == this)
          m_game.release();
        std::cout << "Using game " << m_currentGameId << std::endl;
        m_game = std::unique_ptr<IGame>(m_gameList[m_currentGameId].getFunction<IGame* ()>("getGame")());
        std::cout << "Done." << std::endl;
        m_gameState = LOADING;
        this->loadGame();
      }
      if (m_currentLibId != lib)
      {
        std::cout << "Using lib " << m_currentLibId << std::endl;
        m_lib = std::unique_ptr<IGfxLib>(m_libList[m_currentLibId].getFunction<IGfxLib* ()>("getLib")());
        std::cout << "Done." << std::endl;
        this->loadGame();
      }

      return;
    }
    m_eventBuffer.push_back(e);
  }

  void Core::notifyEvent(std::vector<Event>&& events)
  {
    std::vector<Event> ev = events;

    for (Event const &e : ev)
    {
      if (e.type == EventType::ET_QUIT)
      {
        m_state = QUIT;
        m_game.release();
      }
      else if (e.type == EventType::ET_KEYBOARD &&
        e.action == ActionType::AT_PRESSED)
      {
        if (e.kb_key == KeyboardKey::KB_ESCAPE)
        {
          m_state = QUIT;
          m_game.release();
        }
        else if (e.kb_key == KeyboardKey::KB_SPACE)
        {
          m_game.release();
          m_game = std::unique_ptr<IGame>(m_gameList[m_currentGameId].getFunction<IGame *()>("getGame")());
          this->loadGame();
        }
      }
    }
  }

  std::vector<std::pair<std::string, SoundType > > Core::getSoundsToLoad() const
  {
    return (std::vector<std::pair<std::string, SoundType > >());
  }

  void Core::process()
  {
    for (size_t i = 0; i < m_libList.size(); ++i)
    {
      if (i == m_selectedLibId)
        m_gui->at(m_firstLibIndex + i).setBackgroundColor(Color(80, 80, 80));
      else
        m_gui->at(m_firstLibIndex + i).setBackgroundColor(Color::Transparent);
    }

    for (size_t i = 0; i < m_gameList.size(); ++i)
    {
      if (i == m_selectedGameId)
        m_gui->at(m_firstGameIndex + i).setBackgroundColor(Color(80, 80, 80));
      else
        m_gui->at(m_firstGameIndex + i).setBackgroundColor(Color::Transparent);
    }
  }

  std::vector<std::unique_ptr<ISprite>> Core::getSpritesToLoad() const
  {
    std::vector<std::unique_ptr<ISprite>> s;

    return (s);
  }

#if defined(__linux__)
  WhereAmI * Core::getWhereAmI() const
  {
    return nullptr;
  }
#endif
}
