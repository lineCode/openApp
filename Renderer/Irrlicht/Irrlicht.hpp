/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Irrlicht
*/

#pragma once

// IRenderer
#include "App/IRenderer3D.hpp"
// Vector
#include "Core/Vector.hpp"

// EventHandler
#include "EventHandler.hpp"

/* Irrlicht is an IRenderer3D's implementation :
    It can be used from 2D gui to 3D games for Linux, Windows and OSX
    ! Not compatible with multiple windows, use App::parseFile 1 time !
    ! Irrlicht doesn't suppport dynamic text size so load a single file per size !
*/
class Irrlicht : public oA::IRenderer3D
{
public:
    Irrlicht(void) {}
    virtual ~Irrlicht(void);

    /* Virtual 2D functions */
    virtual bool setTargetContext(oA::Uint idx);
    virtual bool isRunning(void) const;
    virtual void clear(void);
    virtual void draw(void);
    virtual bool pullEvent(oA::Event &evt);
    virtual oA::Uint pushWindow(const oA::WindowContext &ctx);
    virtual void pullWindow(oA::WindowContext &ctx);
    virtual void drawRectangle(const oA::RectangleContext &ctx);
    virtual void drawText(const oA::TextContext &ctx);
    virtual void drawImage(const oA::ImageContext &ctx);
    virtual void drawCircle(const oA::CircleContext &ctx);
    virtual bool supports3D(void) const noexcept;
    virtual bool supportsMultiContexts(void) const noexcept;

    /* Virtual 3D functions */
    virtual void clearScene(void);
    virtual void addCube(const oA::CubeContext &ctx);
    virtual void addCamera(const oA::CameraContext &ctx);
    virtual void drawScene(void);

private:
    oA::Vector<IrrlichtContext> _ctxs;
    oA::Unique<EventHandler> _handler;
    oA::Uint _idx = 0;

    IrrlichtContext &context(void);
    const IrrlichtContext &context(void) const;
    irr::gui::IGUIFont *getFont(const oA::String &path);
    irr::video::ITexture *getTexture(const oA::String &path);
    irr::core::recti toRect(const oA::ItemContext &ctx) const noexcept;
};
