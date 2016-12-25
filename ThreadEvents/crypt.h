#pragma once
#ifndef CRYPT_H
#define CRYPT_H
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include "des.h"
#include "network.h"

using namespace std;

 ustring EncryptPassword(string&, string&);
#endif