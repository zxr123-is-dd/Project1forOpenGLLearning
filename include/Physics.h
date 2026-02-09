#pragma once

#include <cmath>
#include <limits>

#include <glm/glm.hpp>

constexpr float EPS = 1e-9f;

float distanceSqPointPoint(glm::vec3 a, glm::vec3 b);

float distanceSqPointSegment(glm::vec3 a, glm::vec3 b, glm::vec3 p, glm::vec3 &e);

float distanceSqSegmentSegment(
    glm::vec3 p1, glm::vec3 q1,
    glm::vec3 p2, glm::vec3 q2,
    glm::vec3 &e1, glm::vec3 &e2
);

float distanceSqPointTriangle(
    glm::vec3 p,
    glm::vec3 a, glm::vec3 b, glm::vec3 c,
    glm::vec3 &e
);

float distanceSqSegmentTriangle(
    glm::vec3 p, glm::vec3 q,
    glm::vec3 a, glm::vec3 b, glm::vec3 c,
    glm::vec3 &e1, glm::vec3 &e2
);

class Capsule {
public:
    Capsule(glm::vec3 position, float height, float radius);
    void movePosition(glm::vec3 offset);
    void setPosition(glm::vec3 position);
    
    void setHeight(float height);
    void setRadius(float radius);

    glm::vec3 top() const;
    glm::vec3 bottom() const;

    // a, b, c are three vertices of triangle
    bool intersectTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 &e1, glm::vec3 &e2) const;

private:
    // center of Capsule
    glm::vec3 position_;

    float height_;
    float radius_;
};

class Sphere {
public:
    Sphere(glm::vec3 position, float radius);
    void movePosition(glm::vec3 offset);
    void setPosition(glm::vec3 position);
    void setRadius(float radius);

private:
    // centeral position of sphere
    glm::vec3 position_;
    float radius_;
};