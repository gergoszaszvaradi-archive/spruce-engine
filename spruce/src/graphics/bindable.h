#pragma once
#include "core.h"

#include "GL/glew.h"

namespace spr {

    class Bindable {
    public:
        SPR_API Bindable() : id(0) {};

        virtual SPR_API void Bind() const = 0;
        virtual SPR_API void Unbind() const = 0;

        inline uint32 GetID() const { return id; }
        inline SPR_API operator GLuint() const { return id; }

    protected:
        uint32 id;
    };

}