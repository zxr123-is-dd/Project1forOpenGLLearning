#include "Physics.h"

float distanceSqPointPoint(glm::vec3 a, glm::vec3 b) {
    glm::vec3 r = a - b;
    return glm::dot(r, r);
}

float distanceSqPointSegment(glm::vec3 a, glm::vec3 b, glm::vec3 p, glm::vec3 &e) {
    glm::vec3 d = b - a;
    float t = glm::dot(p - a, d) / glm::dot(d, d);
    t = glm::clamp(t, 0.0f, 1.0f);
    e = a + d * t;
    return distanceSqPointPoint(p, e);
}

float distanceSqPointTriangle(
    glm::vec3 p,
    glm::vec3 a, glm::vec3 b, glm::vec3 c,
    glm::vec3 &e
) {
    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    glm::vec3 ap = p - a;

    float d1 = glm::dot(ab, ap);
    float d2 = glm::dot(ac, ap);
    if (d1 <= 0.0f && d2 <= 0.0f) {
        e = a;
        return distanceSqPointPoint(p, e);
    }

    glm::vec3 bp = p - b;
    float d3 = glm::dot(ab, bp);
    float d4 = glm::dot(ac, bp);
    if (d3 <= 0.0f && d4 <= 0.0f) {
        e = b;
        return distanceSqPointPoint(p, e);
    }

    glm::vec3 cp = p - c;
    float d5 = glm::dot(ab, cp);
    float d6 = glm::dot(ac, cp);
    if (d5 <= 0.0f && d6 <= 0.0f) {
        e = c;
        return distanceSqPointPoint(p, e);
    }

    float vc = d1 * d4 - d3 * d2;
    if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
        e = a + ab * (d1 / (d1 - d3));
        return distanceSqPointPoint(p, e);
    }

    float vb = d5 * d2 - d1 * d6;
    if (vb <= 0.0f && d2 >= 0.0f && d3 <= 0.0f) {
        e = a + ac * (d2 / (d2 - d6));
        return distanceSqPointPoint(p, e);
    }

    float va = d3 * d6 - d5 * d4;
    if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f) {
        e = a + (c - b) * ((d4 - d3) / ((d4 - d3) + (d5 - d6)));
        return distanceSqPointPoint(p, e);
    }

    float demon = 1.0f / (va + vb + vc);
    float v = vb * demon;
    float u = vc * demon;
    e = a + ab * v + ac * u;
    return distanceSqPointPoint(p, e);
}

float distanceSqSegmentSegment(
    glm::vec3 p1, glm::vec3 q1,
    glm::vec3 p2, glm::vec3 q2,
    glm::vec3 &e1, glm::vec3 &e2
) {
    glm::vec3 d1 = q1 - p1;
    glm::vec3 d2 = q2 - p2;
    
    float s1 = glm::dot(d1, d1);
    float s2 = glm::dot(d2, d2);
    
    if (s1 <= EPS && s2 <= EPS) {
        e1 = p1;
        e2 = p2;
        return distanceSqPointPoint(e1, e2);
    }

    if (s1 <= EPS) {
        e1 = p1;
        float distance = distanceSqPointSegment(p2, q2, p1, e2);
        return distance;
    }

    if (s2 <= EPS) {
        float distance = distanceSqPointSegment(p1, q1, p2, e1);
        e2 = p2;
        return distance;
    }
    
    glm::vec3 r = p1 - p2;
    float a = glm::dot(d1, d2);
    float b = glm::dot(d1, r);
    float c = glm::dot(d2, r);

    float demon = a * a - s1 * s2;
    float u, v;

    if (abs(demon) <= EPS) {
        u = 0.0f;
    } else {
        u = glm::clamp((b * s2 - a * c) / demon, 0.0f, 1.0f);
    }
    
    v = (b + s1 * u) / a;
    if (v < 0.0f) {
        v = 0.0f;
        u = glm::clamp(-b / s1, 0.0f, 1.0f);
    } else if (v > 1.0f) {
        v = 1.0f;
        u = glm::clamp((s2 - c) / s1, 0.0f, 1.0f);
    }
    
    e1 = p1 + d1 * u;
    e2 = p2 + d2 * v;
    return distanceSqPointPoint(e1, e2);
}

float distanceSqSegmentTriangle(
    glm::vec3 p, glm::vec3 q,
    glm::vec3 a, glm::vec3 b, glm::vec3 c,
    glm::vec3 &e1, glm::vec3 &e2
) {
    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    glm::vec3 normal = glm::cross(ab, ac);
    float normalLen = glm::length(normal);

    if (normalLen < EPS) {
        glm::vec3 e3, e4;
        float dMin = distanceSqSegmentSegment(p, q, a, b, e1, e2);
        
        float dNow = distanceSqSegmentSegment(p, q, a, c, e3, e4);
        if (dNow < dMin) {
            dMin = dNow;
            e1 = e3;
            e2 = e4;
        }

        dNow = distanceSqSegmentSegment(p, q, b, c, e3, e4);
        if (dNow < dMin) {
            dMin = dNow;
            e1 = e3;
            e2 = e4;
        }

        return dMin;
    }

    glm::vec3 segDir = q - p;
    float segLen = glm::length(segDir);
    
    if (segLen < EPS) {
        float d = distanceSqPointTriangle(p, a, b, c, e2);
        e1 = p;
        return d;
    }

    float dist1 = glm::dot(normal, p - a);
    float dist2 = glm::dot(normal, q - a);
    glm::vec3 planeIntersect;
    bool hasPlaneIntersect = false;

    if (dist1 * dist2 <= 0.0f) {
        if (std::abs(dist1 - dist2) > EPS) {
            float t = dist1 / (dist1 - dist2);
            if (t >= 0.0f && t <= 1.0f) {
                planeIntersect = p + segDir * t;
                hasPlaneIntersect = true;
            }
        } else {
            planeIntersect = p;
            hasPlaneIntersect = true;
        }
    }

    if (hasPlaneIntersect) {
        glm::vec3 e;
        float d = distanceSqPointTriangle(planeIntersect, a, b, c, e);
        if (glm::abs(d) < EPS) {
            e1 = planeIntersect;
            e2 = planeIntersect;
            return d;
        }
    }

    float dMin = distanceSqSegmentSegment(p, q, a, b, e1, e2);
    
    glm::vec3 e3, e4;
    float dNow = distanceSqSegmentSegment(p, q, a, c, e3, e4);
    if (dNow < dMin) {
        dMin = dNow;
        e1 = e3;
        e2 = e4;
    }

    dNow = distanceSqSegmentSegment(p, q, b, c, e3, e4);
    if (dNow < dMin) {
        dMin = dNow;
        e1 = e3;
        e2 = e4;
    }

    dNow = distanceSqPointTriangle(p, a, b, c, e3);
    if (dNow < dMin) {
        dMin = dNow;
        e1 = p;
        e2 = e3;
    }

    dNow = distanceSqPointTriangle(q, a, b, c, e3);
    if (dNow < dMin) {
        dMin = dNow;
        e1 = q;
        e2 = e3;
    }

    return dMin;
}

// class Capsule

Capsule::Capsule(glm::vec3 position, float height, float radius)
    : position_(position), height_(height), radius_(radius) {}

void Capsule::movePosition(glm::vec3 offset) {
    position_ += offset;
}

void Capsule::setPosition(glm::vec3 position) {
    position_ = position;
}

void Capsule::setHeight(float height) {
    height_ = height;
}

void Capsule::setRadius(float radius) {
    radius_ = radius;
}

glm::vec3 Capsule::top() const {
    return glm::vec3(position_.x, position_.y + height_ / 2.0f, position_.z);
}

glm::vec3 Capsule::bottom() const {
    return glm::vec3(position_.x, position_.y - height_ / 2.0f, position_.z);
}

bool Capsule::intersectTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 &e1, glm::vec3 &e2) const {
    return distanceSqSegmentTriangle(top(), bottom(), a, b, c, e1, e2) >= radius_ * radius_;
}

// class Sphere

Sphere::Sphere(glm::vec3 position, float radius)
    : position_(position), radius_(radius) {}

void Sphere::movePosition(glm::vec3 offset) {
    position_ += offset;
}

void Sphere::setPosition(glm::vec3 position) {
    position_ = position;
}

void Sphere::setRadius(float radius) {
    radius_ = radius;
}