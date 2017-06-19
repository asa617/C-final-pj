// Created by Xuan_32 6_12

#ifndef _GlobalDefine_H
#define _GlobalDefine_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"



USING_NS_CC;
using namespace CocosDenshion;

#define WINSIZE Director::getInstance()->getWinSize()

#define setIntToXML     UserDefault::getInstance()->setIntegerForKey
#define setFloatToXML   UserDefault::getInstance()->setFloatForKey
#define setBoolToXML    UserDefault::getInstance()->setBoolForKey
#define getIntFromXML   UserDefault::getInstance()->getIntegerForKey
#define getFloatFromXML UserDefault::getInstance()->getFloatForKey
#define getBoolFromXML  UserDefault::getInstance()->getBoolForKey

#define SOUND_KEY       "soundClose"
#define MUSIC_KEY       "musicClose"
#define GAMELEVEL_KEY   "gameLevel"
#define SELECTGATE      "selectGate"
#define GATEONE         "gateOne"
#define GATETWO         "gateTwo"
#define GATETHREE       "gateThree"
#define GAMEOVER        "gameOver"


#define MONSTERNUMBER 6

#define aduioEngine   SimpleAudioEngine::getInstance()

#define PLAYEFFECT if(getBoolFromXML(SOUND_KEY))\
{\
    aduioEngine->playEffect("button.wav");\
}

#endif // !_GlobalDefine_H
