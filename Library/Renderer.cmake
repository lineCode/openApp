cmake_minimum_required(VERSION 3.0.0)
project(openApp)

# This file need variables 'oAPath' and 'oARendererTarget' to be set !

include(openApp.cmake)

set(oARenderer ${oARoot}/Renderer)
set(oASDL ${oARenderer}/SDL)

set(oASDLRenderer
    ${oASDL}/SDLRenderer.hpp
    ${oASDL}/SDLRenderer.cpp
    ${oASDL}/Extern/SDL_FontCache.h
    ${oASDL}/Extern/SDL_FontCache.c
)