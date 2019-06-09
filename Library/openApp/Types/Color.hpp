/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Color
*/

#pragma once

#include <openApp/Types/Scalars.hpp>
#include <openApp/Types/String.hpp>

namespace oA { class Color; }

/**
 * @brief Abstraction of a concatenated RGBA color
 *
 * Note that the internal value is A.R.G.B shifted in a single Uint
 */
class oA::Color
{
public:
    /**
     * @brief Construct a new Color object
     *
     * @param r Red intensity
     * @param g Green intensity
     * @param b Blue intensity
     * @param a Alpha intensity
     */
    Color(UByte r = 0, UByte g = 0, UByte b = 0, UByte a = 255) { set(r, g, b, a); }

    /**
     * @brief Get alpha intensity
     *
     * @return UByte Alpha intensity
     */
    UByte getA(void) const noexcept { return (_val >> 24) & 0xff; }

    /**
     * @brief Get red intensity
     *
     * @return UByte Red intensity
     */
    UByte getR(void) const noexcept { return (_val >> 16) & 0xff; }

    /**
     * @brief Get green intensity
     *
     * @return UByte Green intensity
     */
    UByte getG(void) const noexcept { return (_val >> 8) & 0xff; }

    /**
     * @brief Get blue intensity
     *
     * @return UByte Blue intensity
     */
    UByte getB(void) const noexcept { return _val & 0xff; }

    /**
     * @brief Get the internal concatened value
     *
     * @return Uint Concatenated value
     */
    Uint getValue(void) const noexcept { return _val; }

    /**
     * @brief Set a new concatened value
     *
     * @param r Red intensity
     * @param g Green intensity
     * @param b Blue intensity
     * @param a Alpha intensity
     */
    void set(UByte r, UByte g, UByte b, UByte a = 255);

    /**
     * @brief Set alpha intensity
     *
     * @param a Alpha intensity
     */
    void setTransparency(UByte a);

    /**
     * @brief Retreive a color using a String identifier
     *
     * @param color Identifier
     * @return Color Identified color
     */
    static Color RetreiveColor(const String &color);

private:
    Uint _val = 0;

    /**
     * @brief Pack ARGB values into a single Uint
     *
     * @param r Red intensity
     * @param g Green intensity
     * @param b Blue intensity
     * @param a Alpha intensity
     * @return Uint Final concatened value
     */
    inline static Uint Pack(UByte r, UByte g, UByte b, UByte a);
};