#pragma once

class UI {
public:
    virtual void dibujarPared(int x, int y) = 0;
    virtual void borrarPared(int x, int y) = 0;
    virtual ~UI() = default;
};