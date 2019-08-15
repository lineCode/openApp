/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** IRenderer
*/

#pragma once

#include <openApp/Types/Memory.hpp>
#include <openApp/App/RenderContexts.hpp>
#include <openApp/App/Event.hpp>

namespace oA
{
    class IRenderer;

    using IRendererPtr = Unique<IRenderer>;
}

/**
 * @brief IRenderer is the generic renderer interface of openApp.
 *
 * This renderer should only compute 2D graphics, and supports multiple-windows.
 * For 3D graphics, refer to its derived IRenderer3D.
 */
class oA::IRenderer
{
public:
    virtual ~IRenderer(void) = default;

    /**
     * @brief Create a new window
     *
     * @param context Window's context
     * @return Int Window's index
     */
    virtual Int openWindow(const WindowContext &context) = 0;

    /**
     * @brief Close a Window
     *
     * @param index Window's index
     */
    virtual void closeWindow(Int index) = 0;

    /**
     * @brief Push a window context
     *
     * @param context Current target window context patch
     */
    virtual void pushWindow(const WindowContext &context) = 0;

    /**
     * @brief Poll informations of drawing target
     *
     * @param context Current target window's context target
     */
    virtual void pollWindow(WindowContext &context) = 0;

    /**
     * @brief Clear a Window set it as drawing target
     *
     * @param index Window's index
     */
    virtual void clearWindow(Int index) = 0;

    /**
     * @brief Renderer drawing target
     */
    virtual void renderWindow(void) = 0;

    /**
     * @brief Draw Line in drawing target
     *
     * @param context Line data
     */
    virtual void draw(const LineContext &context) = 0;

    /**
     * @brief Draw Triangle in drawing target
     *
     * @param context Triangle data
     */
    virtual void draw(const TriangleContext &context) = 0;

    /**
     * @brief Draw Rectangle in drawing target
     *
     * @param context Rectangle data
     */
    virtual void draw(const RectangleContext &context) = 0;

    /**
     * @brief Draw Circle in drawing target
     *
     * @param context Circle data
     */
    virtual void draw(const CircleContext &context) = 0;

    /**
     * @brief Draw Ellipse in drawing target
     *
     * @param context Ellipse data
     */
    virtual void draw(const EllipseContext &context) = 0;

    /**
     * @brief Draw Image in drawing target
     *
     * @param context Image data
     */
    virtual void draw(const ImageContext &context) = 0;

    /**
     * @brief Poll an event from drawing target
     *
     * @param target Event to fill in
     * @return true An event has been polled
     * @return false No event has been polled
     */
    virtual bool pollEvent(Event &target) = 0;
};