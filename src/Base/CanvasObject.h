#ifndef CANVAS_OBJECT_H
#define CANVAS_OBJECT_H

#include "../Utilities.h"
#include "IMouse.h"
#include "IKeyboard.h"
#include "IRender.h"
class CanvasObject : public IRender, public IKeyboard, public IMouse
{
public:
    Float3 position;
    Float3 scale;
    Float3 rotation;
    void keyboard(int key) override;
    void keyboardUp(int key) override;

    void mouse(int button, int state, int wheel, int direction, int x, int y) override;
    void render() override;
    void setZIndex(int zIndex);
    int getZIndex();
    CanvasObject();
    virtual void setActive(bool isActive);
    bool getActive();
    bool checkIfCanExecuteCallback();

protected:
    bool isActive;
    int objectId;

private:
    int zIndex;
    bool lastActiveState;
};
#endif
