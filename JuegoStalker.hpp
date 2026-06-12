#pragma once
#define CURSES

#include <iostream>

#include "Laberinto/Laberinto.hpp"
#include "UI/UI.hpp"

#ifdef CURSES
#include "UI/UINcurses.hpp"
#elif QT
//#include "UI/UIQT.hpp"
#endif
