#include "../include/Camera.h"

Camera::Camera() {
    xRot = 110.0f;
    zRot = 0.0f;
    horizontal = 30.0f;
    vertical = 0.0f;
    zDir = 0.0f;
    zoom = 0.4f;
}

void Camera::view() {
    //kameramozgató transzformációk
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
    glTranslatef(horizontal,vertical, zDir);      
}
