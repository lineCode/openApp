/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Instantiator
*/

#include <openApp/Core/Path.hpp>
#include <openApp/App/ItemFactory.hpp>
#include <openApp/Language/Instantiator.hpp>
#include <openApp/Language/Nodes.hpp>
#include <openApp/Language/ShuntingYard.hpp>
#include <openApp/Language/Parser.hpp>

oA::ItemPtr oA::Lang::Instantiator::ProcessFile(const String &path)
{
    return Instantiator().processName(path);
}

oA::ItemPtr oA::Lang::Instantiator::ProcessString(const String &string, const String &context)
{
    return Instantiator().processStringUnit(string, context);
}

oA::ItemPtr oA::Lang::Instantiator::processName(const String &name)
{
    bool isItem = ItemFactory::Exists(name);
    auto path = getNamePath(name);

    if (path.empty() || (hasContext() && name == unit().first)) {
        if (isItem)
            return ItemFactory::Instanciate(name);
        throw AccessError("Instantiator", "Can't access file @" + name + "@" + getErrorContext());
    }
    return processUnit(path);
}

oA::String oA::Lang::Instantiator::getNamePath(const String &name) const noexcept
{
    auto path = Path::Exists(name) ? Path::GetCanonicalPath(name) : String();

    if (!path.empty())
        return path;
    for (const auto &import : _imports) {
        path = import + path;
        if (Path::Exists(name))
            return Path::GetCanonicalPath(path);
    }
    return String();
}

oA::ItemPtr oA::Lang::Instantiator::processUnit(const String &path)
{
    auto it = _units.find(path);

    if (it == _units.end())
        it = _units.emplace_hint(it, path, ASTNodePtr());
    it->second = Parser::ParseFile(path);
    pushContext(*it);
    processNode(*it->second);
    resolveUnresolved();
    return popContext();
}

oA::ItemPtr oA::Lang::Instantiator::processStringUnit(const String &string, const String &context)
{
    auto it = _units.emplace_hint(_units.end(), context, ASTNodePtr());

    it->second = Parser::ParseString(string, context);
    pushContext(*it);
    processNode(*it->second);
    resolveUnresolved();
    return popContext();
}

void oA::Lang::Instantiator::processNode(const ASTNode &node)
{
    switch (node.getType()) {
    case ASTNode::Root:
        return processRoot(node);
    case ASTNode::Import:
        return processImport(dynamic_cast<const ImportNode &>(node));
    case ASTNode::Class:
        return processClass(dynamic_cast<const ClassNode &>(node));
    case ASTNode::Declaration:
        return processDeclaration(dynamic_cast<const DeclarationNode &>(node));
    default:
        throw LogicError("Instantiator", "Invalid unit tree node" + getErrorContext());
    }
}

void oA::Lang::Instantiator::processRoot(const ASTNode &node)
{
    for (const auto &child : node.children) {
        processNode(*child);
    }
}

void oA::Lang::Instantiator::processImport(const ImportNode &node)
{
    _imports.emplace_back(node.directory);
}

void oA::Lang::Instantiator::processClass(const ClassNode &node)
{
    auto item = processName(node.name);

    if (!root())
        root().swap(item);
    else
        root()->appendChild(std::move(item));
    root()->setID(node.id);
    processRoot(node);
}

void oA::Lang::Instantiator::processDeclaration(const DeclarationNode &node)
{
    ShuntingYard::Mode mode;

    if (!root())
        throw LogicError("Instantiator", "Can't process @declaration@ of null root object" + getErrorContext());
    switch (node.type) {
    case DeclarationNode::AssignmentDeclaration:
        mode = ShuntingYard::Expression;
        break;
    case DeclarationNode::PropertyDeclaration:
        mode = ShuntingYard::Expression;
        root()->append(node.name);
        break;
    case DeclarationNode::FunctionDeclaration:
        mode = ShuntingYard::Function;
        root()->append(node.name);
        break;
    case DeclarationNode::EventDeclaration:
        mode = ShuntingYard::Event;
        break;
    }
    try {
        ShuntingYard::ProcessTokenList(*root(), node.name, node.tokens, mode, context().unit.first);
    } catch (...) {
        auto &item(*root());
        context().unresolved.emplace_back([this, &node, mode, item, ctx = context().unit.first](void) mutable {
            ShuntingYard::ProcessTokenList(item, node.name, node.tokens, mode, ctx);
        });
    }
}