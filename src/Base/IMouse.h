#ifndef IMOUSE_H
#define IMOUSE_H

class IMouse
{
public:
    virtual void mouse(int button, int state, int wheel, int direction, int x, int y) = 0;

    virtual void onMouseEnter(int x, int y) = 0;
    virtual void onMouseLeave(int x, int y) = 0;
    virtual void onMouseStay(int x, int y) = 0;
    virtual void onMouseButonDown(int button, int state, int x, int y) = 0;
    virtual void onMouseButonUp(int button, int state, int x, int y) = 0;
};
#endif
