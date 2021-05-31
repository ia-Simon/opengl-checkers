class CircularCamera {
    double pathRadius;
    double pathAngle;
    double posX;
    double posY;
    double posZ;

    void updateXZ() {
        posX = pathRadius * cos(pathAngle * (M_PI/180));
        posZ = pathRadius * sin(pathAngle * (M_PI/180));
    }

public:
    CircularCamera() {}

    CircularCamera(double XZpathRadius, double Yheight) {
        pathRadius = XZpathRadius;
        pathAngle = 90;
        posY = Yheight;
        updateXZ();
    }
    double get_posX() { return posX; }
    double get_posY() { return posY; }
    double get_posZ() { return posZ; }
    double get_pathAngle() { return pathAngle; }
    void set_pathAngle(double angle) { pathAngle = angle; updateXZ(); }

    void translate(double angleDelta) {
        if((pathAngle + angleDelta) >= 360)     pathAngle = (pathAngle + angleDelta) - 360;
        else if((pathAngle + angleDelta) < 0)   pathAngle = 360 - (pathAngle + angleDelta);
        else                                    pathAngle += angleDelta;
        updateXZ();
    }

    void scaleRadius(double distDelta) {
        if(pathRadius + distDelta < 3)
            pathRadius = 3;
        else
            pathRadius += distDelta;
        updateXZ();
    }

    void changeHeight(double heightDelta) {
        if(posY + heightDelta < 2.5)
            posY = 2.5;
        else
            posY += heightDelta;
    }
};