/*
*   Players using BBA
*   Kevin Chen - 29/6/18
*   outi = either 0 or i for all honest players
*
*/
#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cstring>

struct MSG
{
    std::string ecrpt, orig;
    //BigInteger E, N;
    bool operator == (MSG& right)
    {
        return ecrpt.compare(right.ecrpt) == 0;
    }
};


class Player
{
private:
int ID, n, t = 0, b;
bool aff, halt = false;

MSG message;
MSG ESIGi, ESIGb; //ESIG of player, ESIG blank
std::string v;

std::pair <std::string, int> VGPair;
std::vector<MSG> recieved;

public:
Player(int _ID, bool _aff = true):ID(_ID), aff(_aff)
{
    srand(time(NULL));
}
~Player(){}

void findV(std::vector<Player> &PList, int _t);
std::pair <std::string, int> getPair(){return VGPair;}
std::pair <int, int> count01();

bool isHonest(){return aff;}

void msg(std::vector<Player> &PList);
void check();
void outDet();
void coin0();
void coin1();
void coinFlip();

void print(int i = 0)
{
    switch(i)
    {   
        case 1:
            std::cout << "ID: " << ID << " ";
            break;
        case 2:
            std::cout << "Aff: " << aff << " ";
            break;
        case 3:
            //std::cout << "Msg: " << message << " ";
            break;
        case 4:
            std::cout << "pair: " << VGPair.first << " " << VGPair.second << " ";
            break;
        default:
            std::cout << "ID: " << ID << " ";
            std::cout << "Aff: " << aff << " ";
            //std::cout << "Msg: " << message << " ";
            std::cout << "pair: " << VGPair.first << " " << VGPair.second << " ";
            break;
    }

    std::cout << "\n";
}
void clearMsg(){recieved.clear();}
void newRound(){halt = false;}
void corrupt()
{
    aff = false;
}

};

void Player::findV(std::vector<Player> &PList, int _t)
{
    n = PList.size();
    t = _t;
    // int j = 0;
    // std::string minHash /*= sha256(PList[0].credentials)*/, curHash;
    // for (int i = 1; i < n; i ++)
    // {
    //     //curHash = sha256(PList[i].credentials);
    //     if (curHash > minHash)
    //     {
    //         minHash = curHash;
    //         j = i;
    //     }
    // }
    // if(PList[j].prevBlock != NULL && sha256(prevBlock) == sha(cert.Block))
    // {
    //     v = hash()
    // }
    // else
    // {
    //     v = "";
    // }

    MSG newMSG;
    //newMSG.encrpt = v; // turn v into a message using j
    newMSG.orig = v;
    message = newMSG;

    ESIGi = newMSG;
    return;
}
void Player::msg(std::vector<Player> &PList)
{
    for(int i = 0; i < n; i ++)
    {
        if(i != ID) 
        {
            PList[i].recieved.push_back(message);
        }
    }
    return;
}

void Player::check()
{
    int count = 0;
    for (int i = 0; i < recieved.size(); i ++)
    {
        if(i != ID)
        {
            if(recieved[i].orig == ESIGi.orig)count++;
        }
    }
    v = "";
    if(count > (n * 2/3) + 1)
    {
        v = ESIGi.orig;
    }
    
    MSG newMSG;
    //newMSG.encrpt = v; // turn v into a message using j
    newMSG.orig = v;
    message = newMSG;

    ESIGi = newMSG;

    return;
}

void Player::outDet()
{
    int count = 0;
    for (int i = 0; i < recieved.size(); i ++)
    {
        if(i != ID)
        {
            if(recieved[i].orig == ESIGi.orig)count++;
        }
    }
    VGPair.first = "";
    if(count > (t * 2 / 3) + 1)
    {
        VGPair.first = ESIGi.orig;
        VGPair.second = 2;
    }
    else if(count > (t / 3) + 1)
    {
        VGPair.first = ESIGi.orig;
        VGPair.second = 1;
    }
    else
    {
        //VGPair.first = Hash(B)
        VGPair.second = 0;
    }

    b = 1;
    if (VGPair.second == 2) b = 0;


    MSG newMSG;
    //newMSG.encrpt = v; // turn v into a message using j
    newMSG.orig = v;
    message = newMSG;

    ESIGi = newMSG;

    return;
}

// void Player::coin0()
// {
//     std::pair <int, int> count = count01();
//     int count2 = 0;
//     for (int i = 0; i < n; i ++)
//     {
//         if(i != ID)
//         {
//             if(recieved[i] == ESIG)count2++;
//         }
//     }
// }

#endif