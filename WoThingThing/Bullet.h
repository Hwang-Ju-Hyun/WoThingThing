#pragma once
#include<iostream>
#include "AEVec2.h"

static int remainBullet = 5;

void CreateBullet(AEVec2 initPos, AEVec2 nor_dVec, std::string _bulletname);

void CreateSupplement(AEVec2 initPos);
void AddBullet();