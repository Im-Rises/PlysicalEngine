#ifndef INTEGRABLE_H
#define INTEGRABLE_H

#include "../../../../Force/Gravity.h"
#include "../../../../Utility/Matrix34.h"
#include "../../../../Utility/Quaternion.h"
#include "../../../../Utility/Vector3d.h"
#include "../../Component.h"
#include "../PhysicalComponent.h"
#include <vector>

class ForceGenerator;

struct ForcePoint {
    ForceGenerator* force;
    Vector3d point;
};

class Rigidbody : public PhysicalComponent {
private:
    static constexpr const char* COMPONENT_TYPE = RIGIDBODY_COMPONENT;

protected:
    float m_mass;
    Vector3d m_speed;
    Vector3d m_acceleration;
    Vector3d m_rotation;

    Matrix33 m_inertiaTensor;
    Matrix34 m_transformMatrix;

    Quaternion m_orientation;

    Vector3d m_angularSpeed;
    Vector3d m_angularAcceleration;
    Vector3d m_forceAccum;
    Vector3d m_torqueAccum;

    std::vector<ForcePoint> pointForceGeneratorsList;

public:
    explicit Rigidbody(GameObject* gameObject);

    ~Rigidbody() override;

    void addForceToPointList(ForceGenerator* forceGenerator, const Vector3d& point);

private:
    void addForceAtPoint(const Vector3d& force, Vector3d worldPoint);

    void addForceAtBodyPoint(const Vector3d& force, const Vector3d& LocalPoint);

    void calculateAcceleration();
    void calculateOrientation(float deltaTime);
    void calculateSpeed(float time);

    void clearAccumulator();

    //    void addForceAtPointToList(ForceGenerator *forceGenerator, const Vector3d &point);

public:
    void update(float time) override;

    void calculateDerivedData();

    void drawGui() override;

    void drawGuiForceGeneratorsAtPoint();

    std::string getName() const override;

    Vector3d getAngularSpeed() const;

    void deleteForceAtPoint(ForceGenerator* forceGenerator);

    //    template<class T>
    //    void deleteForceAtPointByClass(T *&comp) {
    //        for (auto it = pointForceGeneratorsList.begin(); it != pointForceGeneratorsList.end(); ++it) {
    //            if (dynamic_cast<T *>(*it->force) != nullptr) {
    //                delete it->force;
    //                pointForceGeneratorsList.erase(it);
    //                return;
    //            }
    //        }
    //    }
};

#endif // !INTEGRABLE_H