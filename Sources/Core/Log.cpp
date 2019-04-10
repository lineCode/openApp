/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Log
*/

#include <iostream>
#include "Core/Log.hpp"

const oA::Log oA::cout(oA::Log::COUT);
const oA::Log oA::cerr(oA::Log::CERR, oA::CSL_LIGHT_YELLOW, oA::CSL_BG_BLACK, oA::CSL_LIGHT_RED);
const oA::Log::Repeater oA::repeat;
const oA::Log::Endl oA::endl;

oA::Log::Log(Output out, ConsoleColor text, ConsoleColor background, ConsoleColor quote)
    : _stream(out == CERR ? std::cerr : std::cout), _text(text), _background(background), _quote(quote)
{
    if (_text.empty())
        _text = oA::CSL_WHITE;
    if (_background.empty())
        _background = oA::CSL_BG_BLACK;
    if (_quote.empty())
        _quote = oA::CSL_LIGHT_BLUE;
}

oA::OStream &oA::Log::getStream(void) const noexcept
{
    return _stream;
}

oA::Bool oA::Log::repeat(void) const noexcept
{
    return _repeat ? --_repeat, true : false;
}

void oA::Log::setRepeat(oA::Uint value) const noexcept
{
    _repeat = value;
}

oA::Bool oA::Log::getEnabled(void) const noexcept
{
    return _enabled;
}

void oA::Log::setEnabled(oA::Bool value) noexcept
{
    _enabled = value;
}

void oA::Log::formatConsoleString(oA::String &str) const noexcept
{
    auto end = oA::String::npos;
    oA::ConsoleColor color;

    for (auto pos = str.find('@'); pos != end; pos = str.find('@', pos + 1)) {
        _inQuote = !_inQuote;
        color = _inQuote ? _quote : oA::CSL_RESET + _text;
        str.replace(str.begin() + pos, str.begin() + pos + 1, color);
    }
    str.insert(0, _text);
    str.insert(str.length(), oA::CSL_RESET);
}

template<>
const oA::Log &oA::Log::log(const oA::String &value) const noexcept
{
    oA::String str = value;

    formatConsoleString(str);
    if (!getEnabled())
        return (*this);
    do {
        getStream() << str;
    } while (repeat());
    return (*this);
}

template<>
const oA::Log &oA::Log::log(const char * const & raw) const noexcept
{
    log(oA::String(raw));
    return (*this);
}

const oA::Log &operator<<(const oA::Log &log, const oA::Log::Repeater &repeater)
{
    log.setRepeat(repeater.get());
    return (log);
}

const oA::Log &operator<<(const oA::Log &log, const oA::Log::Endl &endl)
{
    (void)(endl);
    if (!log.getEnabled())
        return (log);
    log.getStream() << std::endl;
    return (log);
}

const oA::Log::Repeater &oA::Log::Repeater::operator()(int x) const noexcept
{
    _x = x;
    return (*this);
}

oA::Uint oA::Log::Repeater::get(void) const noexcept
{
    return _x;
}