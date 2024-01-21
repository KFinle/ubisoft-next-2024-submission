#pragma once
#include "../utility/TypeIDGenerator.h"
#include "vector"

using ComponentTypeID = IDType;

enum ComponentAttribute {
    NoAttributeComponent = 0,
    UpdatableComponent = 1 << 0,
    RenderableComponent = 1 << 1,
    CollidingComponent = 1 << 3,
    // Add more attributes as needed
};

class BaseComponent {
public:

    virtual ~BaseComponent() {}
    virtual int GetAttributes() const {
        return NoAttributeComponent;
    }
    bool HasAttribute(ComponentAttribute attribute) const {
        return (GetAttributes() & static_cast<int>(attribute)) != 0;
    }
    virtual void Update(float delta_time) = 0;

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

    int GetAttributes() const override 
    {
        return attributes;
    }

    void Update(float delta_time) override{}

    // Constructor to set attributes on creation
    Component(int attributes = NoAttributeComponent) : attributes(attributes) {}

private:
    int attributes;
};






