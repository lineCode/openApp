/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Irrlicht
*/

#pragma once

// IRenderer
#include "App/IRenderer.hpp"
// Vector
#include "Core/Vector.hpp"

// EventHandler
#include "EventHandler.hpp"

/* Irrlicht is an IRenderer3D's implementation :
    It can be used from 2D gui to 3D games for Linux, Windows and OSX
    ! Not compatible with multiple windows, use App::parseFile 1 time !
    ! Irrlicht doesn't suppport dynamic text size so load a single file per size !
*/
class Irrlicht : public oA::IRenderer
{
public:
    Irrlicht(void) {}
    virtual ~Irrlicht(void);

    /* Virtual functions */
    virtual bool isRunning(oA::Uint idx = 0) const;
    virtual void clear(oA::Uint idx = 0);
    virtual void draw(oA::Uint idx = 0);
    virtual bool pullEvent(oA::Event &evt, oA::Uint index = 0);
    oA::Uint pushWindow(const oA::WindowContext &ctx);
    virtual void pullWindow(oA::WindowContext &ctx, oA::Uint idx = 0);
    virtual void drawRectangle(const oA::RectangleContext &ctx, oA::Uint idx = 0);
    virtual void drawText(const oA::TextContext &ctx, oA::Uint idx = 0);
    virtual void drawImage(const oA::ImageContext &ctx, oA::Uint idx = 0);

private:
    oA::Vector<IrrlichtContext> _ctxs;
    oA::Unique<EventHandler> _handler;

    IrrlichtContext &context(oA::Uint index);
    const IrrlichtContext &context(oA::Uint index) const;
    irr::gui::IGUIFont *getFont(const oA::String &path, oA::Uint index);
    irr::video::ITexture *getTexture(const oA::String &path, oA::Uint index);
    irr::core::recti toRect(const oA::ItemContext &ctx) const noexcept;
};