#ifndef CANVAS_OBJECT_H
#define CANVAS_OBJECT_H

#include "../Utilities.h"
#include "../Vector4.h"
#include "IMouse.h"
#include "IKeyboard.h"
#include "IRender.h"
class CanvasObject : public IRender, public IKeyboard, public IMouse
{
public:
    struct Transform
    {
        Vector4 position;
        Vector4 scale;
        Vector4 rotation;
    };
    Transform transform;
    void keyboard(int key) override;
    void keyboardUp(int key) override;

    void mouse(int button, int state, int wheel, int direction, int x, int y) override;
    void onMouseEnter(int x, int y) override;
    void onMouseLeave(int x, int y) override;
    void onMouseStay(int x, int y) override;
    void onMouseButonDown(int button, int state, int x, int y) override;
    void onMouseButonUp(int button, int state, int x, int y) override;

    void render() override;

    CanvasObject();
    virtual void setActive(bool isActive);
    bool getActive();
    bool checkIfCanExecuteCallback();

    virtual void translate(Vector4 translation);
    virtual void rotate(Vector4 rotation);
    virtual void scale(Vector4 scale);

protected:
    bool isActive;
    int objectId;

private:
    bool lastActiveState;
};
#endif
