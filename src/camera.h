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
        CircularCamera(double XZpathRadius, double Yheight) {
            pathRadius = XZpathRadius;
            pathAngle = 0;
            posY = Yheight;
            updateXZ();
        }

        double get_posX() {
            return posX;
        }
        double get_posY() {
            return posY;
        }
        double get_posZ() {
            return posZ;
        }

        void translate(double angleDelta) {
            pathAngle += angleDelta;
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
            posY += heightDelta;
        }
};