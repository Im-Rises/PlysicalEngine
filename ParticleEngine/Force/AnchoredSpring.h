#ifndef ANCHOREDSPRING_H
#define ANCHOREDSPRING_H

#include "ForceGenerator.h"
#include "../Utility/Vector3d.h"

class AnchoredSpring : public ForceGenerator {
private:
    static constexpr const char *FORCE_TYPE = ANCHORED_SPRING_FORCE;

    Vector3d m_anchor;
    float m_k;
    float m_restLength;

public:
    AnchoredSpring();

    ~AnchoredSpring();

    AnchoredSpring(Vector3d anchor, float k, float restLength);

    AnchoredSpring(const AnchoredSpring &aSpring);

    void addForce(Particle *particle, float duration) override;

    std::string getName() const override;
};

#endif /* ANCHOREDSPRING_H */
