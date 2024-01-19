#pragma once
#include "../utility/TypeIDGenerator.h"
#include "vector"

using ComponentTypeID = IDType;

enum ComponentAttribute {
    NoAttribute = 0,
    Updatable = 1 << 0,
    Renderable = 1 << 1,
    // Add more attributes as needed
};

class BaseComponent {
public:
    virtual ~BaseComponent() {}
    virtual int GetAttributes() const {
        return NoAttribute;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Component : public BaseComponent {
public:

    template <typename T>
    static const ComponentTypeID m_id = TypeIDGenerator<T>::GenerateNewID();

    template<typename T>
    ComponentTypeID GetTypeID() {
        return m_id;
    }

    int GetAttributes() const override {
        return attributes;
    }

    // Constructor to set attributes on creation
    Component(int attributes = NoAttribute) : attributes(attributes) {}

private:
    int attributes;
};




