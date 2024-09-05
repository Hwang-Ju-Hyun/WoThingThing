#pragma once
#include<iostream>
#include "AEVec2.h"

static int remainBullet = 5;

void CreateGun(AEVec2 initPos);
void CreateBullet(AEVec2 initPos, AEVec2 nor_dVec, std::string _bulletname, bool _enemyShoot);
void CreateSupplement(AEVec2 initPos);

void AddBullet();