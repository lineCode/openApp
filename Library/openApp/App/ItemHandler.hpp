/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** ItemHandler
*/

#pragma once

#include <openApp/Types/Memory.hpp>
#include <openApp/Types/String.hpp>

namespace oA
{
    namespace ItemUtils { class ItemHandler; }

    class Item;

    /**
     * @brief Pointer to Item
     */
    using ItemPtr = Shared<Item>;
}

class oA::ItemUtils::ItemHandler
{
public:
    /**
     * @brief Destroy the Item Handler object
     */
    virtual ~ItemHandler(void) = default;

    /**
     * @brief Add a child ItemPtr by copy
     *
     * @param child Value to copy
     */
    Item &appendChild(const ItemPtr &child);

    /**
     * @brief Add a child ItemPtr by move
     *
     * @param child Value to move
     */
    Item &appendChild(ItemPtr &&child);

    /**
     * @brief Remove a child (using internal id)
     *
     * @param id Matching child id
     */
    void removeChild(const String &id);

    /**
     * @brief Remove a child using index
     *
     * @param id Child index
     */
    void removeChild(Uint index);

    /**
     * @brief Event called when appending a new Item
     */
    virtual void onAppendChild(Item &) {}

    /**
     * @brief Event called when removing an Item
     */
    virtual void onRemoveChild(Item &) {}

    /**
     * @brief Check existence of a child (using internal id)
     *
     * @param id Child id to find
     * @return true Child has been found
     * @return false Child hasn't been found
     */
    bool existsChild(const String &id) const noexcept;

    /**
     * @brief Return a non-const reference to matching child (using internal id)
     *
     * @param id Child id to find
     * @return Item& Matching child
     */
    Item &getChild(const String &id);

    /**
     * @brief Return a const reference to matching child (using internal id)
     *
     * @param id Child id to find
     * @return Item& Matching child
     */
    const Item &getChild(const String &id) const;

    /**
     * @brief Return a non-const reference to matching child using index
     *
     * @param index Child index
     * @return Item& Child at index
     */
    Item &getChild(Uint index);

    /**
     * @brief Return a const reference to matching child using index
     *
     * @param index Child index
     * @return Item& Child at index
     */
    const Item &getChild(Uint index) const;

    /**
     * @brief Get the ItemPtr object matching key
     *
     * @param key Expression key to match
     * @return ItemPtr Result expression
     */
    ItemPtr getItemPtr(const String &key) const noexcept;


protected:
    List<ItemPtr> _children;
};