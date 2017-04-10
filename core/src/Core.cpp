#include <dirent.h>
#include <utility>
#include <sys/stat.h>
#include "Core.hpp"
#include "GameState.hpp"
#include "Logger.hpp"
#include "RessourceError.hpp"

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
    m_selectedGameId(0),
    m_menuLib(true)
  {
    m_state = INGAME;

    m_map = std::make_unique<game::Map>(0, 0);
    m_gui = std::make_unique<game::GUI>();

    // Create the main menu GUI
    Color dark(10, 10, 10);

    m_gui->push(game::Component(0, 0, 1, 1, Color(20, 20, 20)));
    m_gui->push(game::Component(0.3, 0.1, 0.4, 0.1, dark));
    m_gui->push(game::Component(0.35, 0.13, 0.3, 0.04, Color::Transparent, "Arcade"));
    m_gui->push(game::Component(0.1, 0.3, 0.35, 0.6));
    m_gui->push(game::Component(0.55, 0.3, 0.35, 0.6));

    m_firstLibIndex = m_gui->size();

    try
    {
      m_soundLib.load("sound/lib_arcade_sfml_sound.so");
      m_sound = std::unique_ptr<IGfxLib>(m_soundLib.getFunction<IGfxLib* ()>("getLib")());
    }
    catch (RessourceError const &e)
    {
      Nope::Log::Warning<< "Backup sound lib not found";
    }

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
      if (m_lib->doesSupportSound())
      {
        for (Sound const &s : sounds)
        {
          m_lib->soundControl(s);
        }
      }
      else if (m_sound.get())
      {
        for (Sound const &s : sounds)
        {
          m_sound->soundControl(s);
        }
      }
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
      throw RessourceError("Library " + lib + " not found");
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
            throw RessourceError("Error while accessing " + libPath);
          }

          m_gui->push(game::Component(0.12, 0.35 + 0.07 * (m_libList.size() - 1),
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
        throw RessourceError("The given file does not seems to be in the ./lib/ directory");
      }
    }
    else
    {
      throw RessourceError("Cannot open ./lib/ directory");
    }

    // Check if there was at least one graphic lib
    if (m_libList.size() == 0)
    {
      throw RessourceError("No graphic library was found");
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

          m_gui->push(game::Component(0.57, 0.35 + 0.07 * (m_gameList.size() - 1),
            0.3, 0.05, Color::Transparent, std::string(ent->d_name)));
        }
      }
      // Close the dir after using it because we are well educated people
      // and yes all of this was copy/pasted :)
      closedir(dir);
      Nope::Log::Info << "Closing dir 'games'";
    }
    else
    {
      throw RessourceError("Cannot open ./games/ directory");
    }

    // Check if there was at least one graphic lib
    if (m_gameList.size() == 0)
    {
      throw RessourceError("No game was found");
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
    m_lib->loadSprites(m_game->getSpritesToLoad());
    
    std::vector<std::pair<std::string, SoundType>> s = m_game->getSoundsToLoad();

    if (m_lib->doesSupportSound())
    {
      m_lib->loadSounds(s);
    }
    if (m_sound.get())
    {
      m_sound->loadSounds(s);
    }
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
        switch (e.kb_key)
        {
        case KB_ESCAPE:
        {
          m_state = QUIT;
          m_game.release();
        }
        break;
        case KB_ARROW_UP:
          if (m_menuLib)
          {
            if (m_selectedLibId == 0)
            {
              m_selectedLibId = m_libList.size();
            }
            m_selectedLibId--;
          }
          else
          {
            if (m_selectedGameId == 0)
            {
              m_selectedGameId = m_gameList.size();
            }
            m_selectedGameId--;
          }
          m_soundsToPlay.emplace_back(0, PLAY);
          break;
        case KB_ARROW_DOWN:
          if (m_menuLib)
          {
            m_selectedLibId++;
            if (m_selectedLibId == m_libList.size())
            {
              m_selectedLibId = 0;
            }
          }
          else
          {
            m_selectedGameId++;
            if (m_selectedGameId == m_gameList.size())
            {
              m_selectedGameId = 0;
            }
          }
          m_soundsToPlay.emplace_back(0, PLAY);
          break;
        case KB_ARROW_LEFT:
          if (m_menuLib == false)
          {
            m_soundsToPlay.emplace_back(1, PLAY);
          }
          m_menuLib = true;
          break;
        case KB_ARROW_RIGHT:
          if (m_menuLib == true)
          {
            m_soundsToPlay.emplace_back(1, PLAY);
          }
          m_menuLib = false;
          break;
        case KB_ENTER:
          if (m_menuLib)
          {
            if (m_currentLibId != m_selectedLibId)
            {
              m_currentLibId = m_selectedLibId;
              m_lib = std::unique_ptr<IGfxLib>(m_libList[m_currentLibId].getFunction<IGfxLib *()>("getLib")());
              this->loadGame();
            }   
          }
          else
          {
            m_soundsToPlay.emplace_back(2, PLAY);
            m_currentGameId = m_selectedGameId;
            m_game.release();
            m_game = std::unique_ptr<IGame>(m_gameList[m_currentGameId].getFunction<IGame *()>("getGame")());
            m_gameState = LOADING;
            this->loadGame();
          }
          break;
        default:
          break;
        }
      }
    }
  }

  std::vector<std::pair<std::string, SoundType>> Core::getSoundsToLoad() const
  {
    std::vector<std::pair<std::string, SoundType>> s;

    s.emplace_back("assets/sounds/Menu_Navigate_03.wav", SoundType::MUSIC);
    s.emplace_back("assets/sounds/Menu_Navigate_00.wav", SoundType::MUSIC);
    s.emplace_back("assets/sounds/Menu_Navigate_01.wav", SoundType::MUSIC);

    size_t musicIndex = s.size();

    s.emplace_back("assets/music/pizzadox.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/shooting_stars.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/class01.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/complication.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/dead_feelings.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/john_cena.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/knas.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/mask_of_sanity.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/massdownloader.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/mental_delivrance.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/nero_burning_rom.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/radioactive.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/razor1911.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/rickroll.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/unreeeal_superhero3.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/what_does_the_fox_say.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/what_is_love.ogg", SoundType::MUSIC);
    s.emplace_back("assets/music/who_easy.ogg", SoundType::MUSIC);

    size_t musicCount = s.size() - musicIndex;

    // Init mode
    m_soundsToPlay.clear();

    m_soundsToPlay.emplace_back(0, UNIQUE);
    m_soundsToPlay.emplace_back(0, VOLUME, 100.0);
    m_soundsToPlay.emplace_back(1, UNIQUE);
    m_soundsToPlay.emplace_back(1, VOLUME, 100.0);
    m_soundsToPlay.emplace_back(2, REPEAT);
    m_soundsToPlay.emplace_back(2, VOLUME, 100.0);

    for (size_t i = 0; i < musicCount; ++i)
    {
      m_soundsToPlay.emplace_back(i + musicIndex, REPEAT);
      m_soundsToPlay.emplace_back(i + musicIndex, VOLUME, 50.0);
    }

    if (musicCount)
    {
     // m_soundsToPlay.emplace_back(musicIndex + rand() % musicCount, PLAY);
    }
    return (s);
  }

  void Core::process()
  {
    for (size_t i = 0; i < m_libList.size(); ++i)
    {
      if (i == m_selectedLibId)
        m_gui->at(m_firstLibIndex + i).setBackgroundColor(Color(60, 60, 60));
      else
        m_gui->at(m_firstLibIndex + i).setBackgroundColor(Color::Transparent);
    }

    for (size_t i = 0; i < m_gameList.size(); ++i)
    {
      if (i == m_selectedGameId)
        m_gui->at(m_firstGameIndex + i).setBackgroundColor(Color(60, 60, 60));
      else
        m_gui->at(m_firstGameIndex + i).setBackgroundColor(Color::Transparent);
    }

    Color dark(10, 10, 10);
    Color light(30, 30, 30);

    if (m_menuLib)
    {
      m_gui->at(3).setBackgroundColor(light);
      m_gui->at(4).setBackgroundColor(dark);
    }
    else
    {
      m_gui->at(3).setBackgroundColor(dark);
      m_gui->at(4).setBackgroundColor(light);
    }
  }

  void Core::notifyNetwork(std::vector<NetworkPacket> &&events)
  {
    if (m_sock)
    {
      sock_t		socket = m_sock->getSocket();
      fd_set		writefds;
      struct timeval	tv;
      int		ret;

      FD_ZERO(&writefds);
      FD_SET(socket, &writefds);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
      ret = select(socket + 1, nullptr, &writefds, nullptr, &tv);
      if (ret > 0)
      {
        for (NetworkPacket const &pck : events)
        {
          // Convert packet to uint8_t *
          size_t len = sizeof(NetworkPacketHeader) + sizeof(uint32_t) + ntohl(pck.len);
          std::unique_ptr<uint8_t[]>	data = std::make_unique<uint8_t[]>(len);
          uint8_t				*cur = data.get();

          std::memcpy(cur, &pck, sizeof(NetworkPacketHeader) + sizeof(uint32_t));
          std::memcpy(cur + sizeof(NetworkPacketHeader) + sizeof(uint32_t),
            pck.data, ntohl(pck.len));

          // Send
          m_sock->send(data.get(), len);
          delete pck.data;
        }
      }
    }
  }

  std::vector<NetworkPacket> Core::getNetworkToSend()
  {
    std::vector<NetworkPacket>	pcks;
    uint8_t			*data;
    size_t			maxSize = Core::pckBuffSize;
    ssize_t			pckSize;

    if (m_sock != nullptr)
    {
      sock_t		socket = m_sock->getSocket();
      fd_set		readfds;
      struct timeval	tv;
      int	        ret;

      FD_ZERO(&readfds);
      FD_SET(socket, &readfds);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
      ret = select(socket + 1, &readfds, nullptr, nullptr, &tv);
      if (ret > 0 && FD_ISSET(socket, &readfds) &&
        m_sock->rec(reinterpret_cast<void **>(&data), maxSize, &pckSize) == true)
      {
        // Build packet
        NetworkPacket			*tmp = reinterpret_cast<NetworkPacket *>(data);
        NetworkPacket			pck;

        std::memcpy(&pck, data, sizeof(NetworkPacketHeader) + sizeof(uint32_t));
        pck.data = new uint8_t[ntohl(pck.len)];
        std::memcpy(pck.data, &tmp->data, ntohl(pck.len));
        delete[] data;
        pcks.push_back(pck);
      }
    }
    return (std::move(pcks));
  }

  std::vector<std::unique_ptr<ISprite>> Core::getSpritesToLoad() const
  {
    std::vector<std::unique_ptr<ISprite>> s;

    return (s);
  }

#if defined(__linux__)
  void Core::WhereAmI(std::ostream &) const
  {
  }
#endif
}
