#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <string>
#include "../../../Utility/Vector3d.h"
#include "../Component.h"
#include "../DefaultComponent.h"
#include "../../../Utility/Quaternion.h"
#include "../../../Utility/Matrix44.h"
#include "../../../Utility/Matrix34.h"

class Transform : private DefaultComponent {
private:
    static constexpr const char *COMPONENT_TYPE = "Transform";

public:
    float positionX, positionY, positionZ;
    float scaleX, scaleY, scaleZ;
    Quaternion rotation;

public:
    Transform();

    ~Transform();

public:
    void drawGui() override;

    void setPosition(float x, float y, float z);

    void setPosition(const Vector3d &position);

    void setRotation(const Quaternion &rotation);

    Quaternion getRotation() const;

    Vector3d getPosition() const;

    Matrix34 getMatrix() const;

    std::string getName() const override;
};


#endif //TRANSFORM_H