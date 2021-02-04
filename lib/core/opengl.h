#ifndef OPENGL_H
#define OPENGL_H

#include "graphics.h"


class OpenGL final : public Graphics {
private:
    void InitOpenGL();

public:
    OpenGL(const OpenGL&) = delete;
    OpenGL(OpenGL&&) noexcept = delete;
    OpenGL& operator=(const OpenGL&) = delete;
    OpenGL& operator=(OpenGL&&) noexcept = delete;

    OpenGL();
    ~OpenGL() = default;

protected: /* Graphics */
    void Init() override;

public: /* Graphics */
    void UpdateViewportSize() const override;
    void Flush() const override;

public: /* IProcess */
    void Processing() override;
};

#endif // OPENGL_H
