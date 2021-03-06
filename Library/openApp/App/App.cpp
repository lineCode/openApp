/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** App
*/

#include <openApp/App/App.hpp>
#include <openApp/Items/Window.hpp>
#include <openApp/Language/Instantiator.hpp>
#include <openApp/Items/Label.hpp>

bool oA::App::onEvent(const Event &event)
{
    if (event.getType() != Event::Window || event.getAs<WindowEvent>().type != WindowEvent::Close)
        return false;
    auto it = _children.find(event.window);
    if (it == _children.end())
        return false;
    _renderer->closeWindow(event.window);
    _children.erase(it);
    return true;
}

bool oA::App::isRunning(void)
{
    if (!_running)
        return false;
    else if (_children.size())
        return true;
    stop();
    return false;
}

void oA::App::run(void)
{
    _running = true;
    onRun();
    while (isRunning()) {
        update();
        render();
    }
}

void oA::App::stop(void)
{
    _running = false;
    onStop();
}

void oA::App::parseFile(const String &path, bool verbose, bool showItem)
{
    openWindow(oA::Lang::Instantiator::ProcessFile(path, verbose, showItem));
}

void oA::App::parseString(const String &string, const String &context, bool verbose, bool showItem)
{
    openWindow(oA::Lang::Instantiator::ProcessString(string, context, verbose, showItem));
}

void oA::App::openWindow(ItemPtr &&root)
{
    auto *wnd = dynamic_cast<Window *>(root.get());
    auto index = 0;

    if (!_renderer->supportsMultipleWindows() && !_children.empty())
        throw LogicError("App", "Internal renderer doesn't supports multiple windows");
    if (!root.get())
        throw LogicError("App", "Can't add null @root@ Item");
    if (wnd) {
        index = _renderer->openWindow(wnd->getWindowContext());
        wnd->setWindowIndex(index);
    } else {
        index = _renderer->openWindow(WindowContext(
            "openApp",
            V2i(),
            V2i(root->get("width").toInt(), root->get("height").toInt()),
            Color(),
            WindowContext::Fixed
        ));
    }
    _children[index] = std::move(root);
}

void oA::App::setDefaultFont(const String &path)
{
    Label::GetDefaultFont() = path;
}


void oA::App::update(void)
{
    pollEvents();
    _children.apply([this](auto &pair) { pair.second->update(*_renderer); });
}

void oA::App::render(void)
{
    _children.apply([this](auto &pair) {
        _renderer->clearWindow(pair.first);
        pair.second->draw(*_renderer, pair.second->getAreaContext());
        _renderer->renderWindow();
    });
    _renderer->handleTargetFPS();
}

void oA::App::pollEvents(void)
{
    for (Event event; _renderer->pollEvent(event);) {
        if (onEvent(event))
            continue;
        if (event.window < 0)
            _children.findIf([this, &event](auto &pair) { return pair.second->propagate(*_renderer, event); });
        else {
            _children.findIf([&event, this](auto &pair) {
                if (pair.first != event.window)
                    return false;
                pair.second->propagate(*_renderer, event);
                return true;
            });
        }
    }
}