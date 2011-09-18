#include "GameConfig.hpp"

/**
    On déclare les attributs statics
**/
map<string,int> GameConfig::g_config;

map<int,mobType> GameConfig::g_mob;

map<string,sf::SoundBuffer> GameConfig::g_soundManag;

map<string,imgAnim> GameConfig::g_imgManag;

/**
    Constructeur
**/
GameConfig::GameConfig()
{
}
/**
    Chargement de la configuration
**/
void GameConfig::LoadConfig(){
    TiXmlDocument doc("config/config.xml");
    doc.LoadFile();

    TiXmlHandle hDoc(&doc);
    TiXmlHandle hRoot(0);
    TiXmlElement* pElem;
    //! Chargement des textures
    pElem=hDoc.FirstChild("img").FirstChild().Element();
    for(; pElem; pElem=pElem->NextSiblingElement()){
        imgAnim newAnim;
        sf::Texture newImg;
        if(!newImg.LoadFromFile(pElem->Attribute("path"))){
            cerr<<"[FATAL ERROR]Image not found: "<<pElem->Attribute("path")<<endl;
            exit(0);
        }
        newAnim.img=newImg;
        newAnim.nbrCollum=atoi(pElem->Attribute("nbrCollums"));
        newAnim.nbrLine=atoi(pElem->Attribute("nbrLines"));
        g_imgManag[pElem->Attribute("name")]=newAnim;
    }
    //! Chargement des mobs
    pElem=hDoc.FirstChild("enemies").FirstChild().Element();
    for(; pElem; pElem=pElem->NextSiblingElement()){
        mobType newMob;
        newMob.path=atoi(pElem->Attribute("path"));
        newMob.x=atoi(pElem->Attribute("x"));
        newMob.y=atoi(pElem->Attribute("y"));
        newMob.width=atoi(pElem->Attribute("width"));
        newMob.height=atoi(pElem->Attribute("height"));

        g_mob[atoi(pElem->Attribute("type"))]=newMob;
    }
    //! Chargement des sons
    pElem=hDoc.FirstChild("sound").FirstChild().Element();
    for(; pElem; pElem=pElem->NextSiblingElement()){
        sf::SoundBuffer newSound;
        newSound.LoadFromFile(pElem->Attribute("path"));
        g_soundManag[pElem->Attribute("name")]=newSound;
    }
    //! Chargement des proprietés
    pElem=hDoc.FirstChild("config").FirstChild().Element();
    for(; pElem; pElem=pElem->NextSiblingElement()){
        GameConfig::g_config[pElem->Attribute("name")]=atoi(pElem->Attribute("value"));
    }
}

sf::Color GameConfig::NbrToColor(int nbr){
    switch(nbr){
      case 1:
        return sf::Color::Red;
      break;
      case 2:
        return sf::Color::Yellow;
      break;
      default:
        return sf::Color::White;
    }
}

int GameConfig::ColorToNbr(sf::Color myColor){
    if(myColor==sf::Color::Red)
        return 1;
    else if(myColor==sf::Color::Yellow)
        return 2;
    else
        return 6;
}

GameConfig::~GameConfig()
{
}
