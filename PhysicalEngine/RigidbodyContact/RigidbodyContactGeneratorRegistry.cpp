#include "RigidbodyContactGeneratorRegistry.h"

#include "../Scene/GameObject.h"
#include <cmath>
#include "RigidbodyContact/RigidbodyContact.h"

RigidbodyContactGeneratorRegistry::RigidbodyContactGeneratorRegistry() {
}

void RigidbodyContactGeneratorRegistry::checkForContact(RigidbodyPrimitiveCollider* rpc1, RigidbodyPrimitiveCollider* rpc2) {
    //    calculateContact((RigidbodySphereCollider*)rigidbodySphereCollider1, (RigidbodySphereCollider*)rigidbodySphereCollider2);
}

void RigidbodyContactGeneratorRegistry::calculateContact(RigidbodyPrimitiveCollider* rpc1, RigidbodyPrimitiveCollider* rpc2) {
    switch (rpc1->getColliderType())
    {
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_NONE:
        std::cerr << "Collision issue, type is NONE" << std::endl;
        break;
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_SPHERE:
        calculateContactSphere(dynamic_cast<RigidbodySphereCollider*>(rpc1), rpc2);
        break;
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_BOX:
        calculateContactCuboid(dynamic_cast<RigidbodyCuboidRectangleCollider*>(rpc1), rpc2);
        break;
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_PLANE:
        calculateContactPlane(dynamic_cast<RigidbodyPlaneCollider*>(rpc1), rpc2);
        break;
    default:
        std::cerr << "Collision issue, unknown collider type" << std::endl;
        break;
    }
}

void RigidbodyContactGeneratorRegistry::calculateContactSphere(RigidbodySphereCollider* rsc, RigidbodyPrimitiveCollider* other) {
    switch (other->getColliderType())
    {
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_SPHERE: {
        Vector3d position1 = rsc->getGameObject()->transform.getPosition();
        auto* otherSphereCollider = dynamic_cast<RigidbodySphereCollider*>(other);
        Vector3d position2 = otherSphereCollider->getGameObject()->transform.getPosition();
        if (pow(position1.distance(position2), 2) < (rsc->getRadius() + otherSphereCollider->getRadius()))
        {
            std::cout << "Sphere to sphere contact between " << rsc->getGameObject()->getName() << " and " << otherSphereCollider->getGameObject()->getName() << std::endl;
        }
        break;                
    }
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_PLANE: {
        auto* planeCollider = dynamic_cast<RigidbodyPlaneCollider*>(other);

        float distance = distanceToPlane(rsc->getGameObject()->transform.getPosition(),planeCollider);

        if (distance <= rsc->getRadius())
        {
            std::cout << "Sphere to plane contact between " << rsc->getGameObject()->getName() << " and " << planeCollider->getGameObject()->getName() << std::endl;
        }
        break;
    }
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_BOX: {
        break;
    }
    default:
        std::cerr << "Collision issue in Sphere collision function" << std::endl;
        break;
    }
}

void RigidbodyContactGeneratorRegistry::calculateContactCuboid(RigidbodyCuboidRectangleCollider* rcrc, RigidbodyPrimitiveCollider* other) {
    switch (other->getColliderType())
    {
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_SPHERE: {
        break;
    }
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_PLANE: {
        auto* planeCollider = dynamic_cast<RigidbodyPlaneCollider*>(other);
        Vector3d points[8];
        rcrc->getAllPoints(points);
        Matrix34 transformMatrix = rcrc->getGameObject()->transform.getMatrix();
        bool collision = false;
        Rigidbody* rigid = nullptr;
        rcrc->getGameObject()->getComponentByClass(rigid);
        if (rigid == nullptr || rigid->getIsKinematic()) {
            return;
        }
        RigidbodyContact contactInfo(rigid);
        for (int i = 0; i < 8; i++)
        {
            points[i] = transformMatrix.transformPosition(points[i]);
            float distance = distanceToPlane(points[i], planeCollider);

            if (distance < 0)
            {
                float interpenetration = std::abs(distance);
                Vector3d normal = planeCollider->getNormalVector();
                Vector3d pointContact = points[i];
                collision = true;
                contactInfo.m_points.push_back(pointContact);
                contactInfo.m_normal = normal;
                contactInfo.m_interpenetration.push_back(interpenetration);
            }
        }
        if (collision)
        {
            
            Rigidbody* rigid = nullptr;
            rcrc->getGameObject()->getComponentByClass(rigid);
            if (rigid != nullptr)
            {
                rigid->stop();
            }
            std::cout << "Collision box plane:" << std::endl;
            Vector3d n = contactInfo.m_normal;
            std::cout << "  -normal: "
                      << "(" << n.getx() << "," << n.gety() << "," << n.getz() << ")" << std::endl;
            for (int i = 0; i < contactInfo.m_points.size(); i++) {
                Vector3d pContact = contactInfo.m_points[i];
                float interp = contactInfo.m_interpenetration[i];

                std::cout << "  Point " << (i + 1) << " : "
                          << "(" << pContact.getx() << "," << pContact.gety() << "," << pContact.getz() << ")" << std::endl;
                std::cout << "  Interpenetration "<< (i+1) <<" : "<< interp << std::endl;
            }
        }
    }
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_BOX: {
        break;
    }
    default:
        std::cerr << "Collision issue in Cuboid collision function" << std::endl;
        break;
    }
}

void RigidbodyContactGeneratorRegistry::calculateContactPlane(RigidbodyPlaneCollider* rpc, RigidbodyPrimitiveCollider* other) {
    switch (other->getColliderType())
    {
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_SPHERE: {
        break;
    }
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_PLANE: {
        break;
    }
    case RIGIDBODY_PRIMITIVE_COLLIDER_TYPE_BOX: {
        auto* boxCollider = dynamic_cast<RigidbodyCuboidRectangleCollider*>(other);
        calculateContactCuboid(boxCollider, rpc);
        break;
    }
    default:
        std::cerr << "Collision issue in Cuboid collision function" << std::endl;
        break;
    }
}

float RigidbodyContactGeneratorRegistry::distanceToPlane(Vector3d point, RigidbodyPlaneCollider* plane) {
    return point.dot(plane->getNormalVector()) - plane->getCenter().dot(plane->getNormalVector());
}
