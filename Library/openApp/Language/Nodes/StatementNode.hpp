/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** StatementNode
*/

#pragma once

#include <openApp/Language/ASTNode.hpp>
#include <openApp/Language/Statement.hpp>

namespace oA::Lang { struct StatementNode; }

struct oA::Lang::StatementNode : public ASTNode
{
    Lang::Statement statement;

    StatementNode(Lang::Statement state) : statement(state) {}

    virtual ~StatementNode(void) = default;

    virtual NodeType getType(void) const { return NodeType::Statement; }

    virtual VarRef compute(void);

    VarRef computeIf(void);
    VarRef computeSwitch(void);
    VarRef computeWhile(void);
    VarRef computeFor(void);
};